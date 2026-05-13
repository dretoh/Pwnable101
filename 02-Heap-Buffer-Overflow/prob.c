#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
	uint32_t secret;
	char data[];
} secret_box;

secret_box *boxes[2];

int win(){
	system("/bin/sh");
}

void check(){
	for(int i = 0; i < 2; i++){
		if(boxes[i] && memcmp(&boxes[i]->secret, "win", 3) == 0)
			win();
	}
}

int main(){
	setvbuf(stdout, NULL, _IONBF, 0);
        setvbuf(stdin, NULL, _IONBF, 0);
	
	int sel, idx;

	while(1){
		check();

		printf("1. alloc\n2. free\n3. write\n > ");
		if(scanf("%d", &sel) != 1)
			return 0;

		printf("idx> ");
		if(scanf("%d", &idx) != 1)
			return 0;
		if(idx < 0 || idx >= 2)
			continue;

		if(sel == 1){
			boxes[idx] = calloc(1, 0x30);
		} else if(sel == 2){
			scanf("%s", boxes[idx]->data);
		}
	}
}
