#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

__attribute__((constructor))
void init(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setbuf(stdout, NULL);
}

int main(){
	char buf[0x40];

	printf("> ");
	read(0, buf, 80);
	printf(buf);

	return 0;
}
