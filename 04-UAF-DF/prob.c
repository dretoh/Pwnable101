#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

char *notes[MAX];

void menu(){
	printf("1. alloc\n2. free\n3. write\n4. read\n > ");
}

int main(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);

	int sel, idx;
	unsigned int size;

	while(1){
		menu();
		if(scanf("%d", &sel) != 1)
			return 0;

		printf("idx> ");

		if(scanf("%d", &idx) != 1)
			return 0;
		if(idx < 0 || idx >= MAX)
			continue;

		if(sel == 1){

			printf("size> ");
			if(scanf("%u", &size) != 1)
				return 0;
			notes[idx] = malloc(size);

		} else if(sel == 2){

			free(notes[idx]);

		} else if(sel == 3){

			printf("data> ");
			scanf("%s", notes[idx]);

		} else if(sel == 4){

			puts(notes[idx]);

		}
	}
}
