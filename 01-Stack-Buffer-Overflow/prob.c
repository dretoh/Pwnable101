#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void win(){
	system("/bin/sh");
}

int main(){
	uint8_t buf[0x30];
	write(1, "> ", 0x2);
	read(0, buf, 0x40);

	return 0;
}
