#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

char timestamp[24];
char type[2];
char code[2];
char value[4];

bool SWITCH=false;

bool compare_code(char* code1, char* code2){
	for(int i = 0; i < 2; i++){
		if(code1[i] != code2[i])
			return false;
	}
	return true;
}

bool compare_type(char* type1, char* type2){
	for(int i = 0; i < 2; i++){
		if(type1[i] != type2[i])
			return false;
	}
	return true;
}

bool is_shortcut(struct shortcut* shortcuts, char* s_code) {
	for (int i = 0; i < 512; i++) {
		if (shortcuts[i].code == NULL) break;
		if (shortcuts[i].code[0] == s_code[0]) return true;
	}
}

char* get_command_path(struct shortcut* shortcuts, char* s_code) {
	for (int i = 0; i < 512; i++) {
		if (shortcuts[i].code == NULL) break;
		if (shortcuts[i].code[0] == s_code[0]) return shortcuts[i].command_path;
	}
}

int key_listener(struct shortcut* shortcuts) {

	FILE* f;
	f = fopen("/dev/input/event4", "rb");
	if (f == NULL) {
		printf("error %d", errno);
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
			if(is_shortcut(shortcuts, code)){
				if (!SWITCH) {
					char* path = get_command_path(shortcuts, code);
					system(path);
				}
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
