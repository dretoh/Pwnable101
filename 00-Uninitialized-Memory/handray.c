#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

void check(){
	uint64_t buf[3];
	if (buf[0] == 0xdeadbeef) {
		
		puts("[*] YOU WIN !");
		exit(1);
	} else {
		puts("NOPE");
	}

}

void print(){
	uint64_t buf[3];
	*(uint64_t *)buf = 0;
	*(uint64_t *)(buf+1) = 0;
	*(uint64_t *)(buf+2) = 0;
	uint32_t n = read(0, (char *)buf, 23);

	if (n <= 0) {
		puts("no.");
		return;
	}
	
	printf("-> %s\n", (char *)buf);
}


int main(int argc, char **argv){
	int sel = 0;

	while(1){
		write(1, "> ", 2);
		read(0, &sel, 2);
		switch(*(uint8_t *)&sel){	
			case 0x31:
				print();
				break;	
			case 0x32:
				puts("Hello World!");
				break;
			case 0x33:
				check();
				break;
			default:
				continue;
		}
	}
	return 0;
}
