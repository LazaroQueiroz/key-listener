#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

bool SWITCH = false;

char timestamp[16];
char type[2];
char code[2];
char value[4];

int main() {

	FILE* f;
	f = fopen("/dev/input/event4", "rb");
	if (f == NULL) {
		printf("error %d", errno);
		return -1;
	} else {
		char c;
		int index = 0;
		while(true) {
			for(int i = 0; i < 16; i++) {
				c = fgetc(f);
				timestamp[i] = c;
			};
			for(int i = 0; i < 2; i++) {
				c = fgetc(f);
				type[i] = c;
			};
			for(int i = 0; i < 2; i++) {
				c = fgetc(f);
				code[i] = c;
			};
			if (!SWITCH && index == 1) {
				printf("char %d\n", code[0]);
			}
			SWITCH = !SWITCH;
			for(int i = 0; i < 4; i++) {
				c = fgetc(f);
				value[i] = c;
			};
			index = ++index % 3;
		}
	}
	return 0;
}
