#include <stdlib.h>
#include <string.h>

#include "shortcut.c"

void process_line(char* line, struct shortcut* shortcuts, int idx) {
	int token_n = 0;

	char code[3] = {0};
	int code_idx = 0;
	char path[4096] = {0};
	int path_idx = 0;
	for (int i = 0; i < strlen(line); i++) {
		if(line[i] == ' ' || line[i] == '\n') continue;

		if (line[i] == ':') {
			token_n++;
			continue;
		}

		if (token_n == 0) {
			code[code_idx++] = line[i];
		} else if (token_n == 1) {
			path[path_idx++] = line[i];
		}

	}
	int* code_arr = malloc(2 * sizeof(int));
	code_arr[0] = atoi(code);
	code_arr[1] = 0;
	shortcuts[idx].code = code_arr;
	shortcuts[idx].command_path = strdup(path);
}

int process_file(char *path, struct shortcut* shortcuts) {

	FILE *f;
	int counter = 0;
	do {
		f = fopen(path, "r");
		if (++counter >= 5000) break;
	} while(f == NULL);

	int idx = 0;
	while (true) {
		char line[512];
		if (fgets(line, sizeof(line), f) == NULL) break;
		process_line(line, shortcuts, idx++);
	}
}
