#include <stdio.h>
#include <stdlib.h>

char timestamp[24];
char type[2];
char code[2];
char value[4];

const char PS[2] = {99, 0};
const char MSC[2] = {1, 0};

bool SWITCH=false;

bool compare_code(char *code){
	for(int i = 0; i < 2; i++){
		if(code[i] != PS[i])
			return false;
	}
	return true;
}

bool compare_type(char *type){
	for(int i = 0; i < 2; i++){
		if(type[i] != MSC[i])
			return false;
	}
	return true;
}

int main() {
	FILE* f;
	f = fopen("/dev/input/event4", "rb");
	if (f == NULL) {
		return -1;
	} else {
		char c;
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
			if(compare_code(code) && compare_type(type)){
				if (!SWITCH)
					system("/home/lazaro/.scripts/printscreen.sh");
				SWITCH=!SWITCH;
			}
			for(int i = 0; i < 4; i++) {
				c = fgetc(f);
				value[i] = c;
			};
		}
	}
	return 0;
}
