#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "monitor.c"
#include "process_file.c"
#include "key_listener.c"
#include "shortcut.c"

time_t last_mtime = -1;
struct shortcut shortcuts[512];

char* PATH="/home/lazaro/key_listener/config/shortcuts.txt";

int main() {
	char path[4096];
	// monitor(path, &last_mtime);
	process_file(PATH, shortcuts);
	key_listener(shortcuts);
	return 0;
}
