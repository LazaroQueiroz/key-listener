#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "monitor.c"
#include "process_file.c"
#include "key_listener.c"
#include "shortcut.c"

time_t last_mtime = -1;
struct shortcut shortcuts[512];


char* USER = "";
int main() {
	// const char* USER = getenv("USER");
	char PATH[4096]; 
	snprintf(PATH, sizeof(PATH), "/home/%s/.config/key_listener/shortcuts.txt", USER);
	// monitor(path, &last_mtime);
	process_file(PATH, shortcuts);
	key_listener(shortcuts);
	return 0;
}
