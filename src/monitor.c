#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>

const float WAIT_T = 1;

struct stat file_stats;

int monitor(char* path, time_t* last_mtime) {
	int status;
	while (true) {
		status = stat(path, &file_stats);

		if (status == -1) {
			return errno;
	 	}

		if (file_stats.st_mtime != *last_mtime || *last_mtime == -1) {
			*last_mtime = file_stats.st_mtime;
			return 0;
		}
	}
	return -1;
}

