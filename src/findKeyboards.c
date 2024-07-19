#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <dirent.h> // for DIR

// I literally thought of a random # for this, gotta make it better by reading up more about the event files
#define BUFFER_SIZE 1024

// This function will return the number of /dev/input/eventX files
int get_event_file_count() {
	struct dirent *entry;
	int count = -1; // want count to go up if 0 exists
	DIR *dp = opendir("/dev/input");

	if (dp == NULL) {
		perror("opendir");
		return -1;
	}

	while ((entry = readdir(dp)) != NULL) {
		if (strncmp(entry->d_name, "event", 5) == 0) {
			count++;
		}
	}

	closedir(dp);
	return count;
}

int* get_keyboard_events() {
	FILE *fp;
	int arrSize=0;
	char response[BUFFER_SIZE];
	
	// Execute udevadm command to find every event in the inputs dir (yes bash in C code, sorry)
	fp = popen("udevadm info --query=property --name=/dev/input/event*", "r");
	if (fp == NULL) {
		perror("Failed to run udevadm command");
		exit(EXIT_FAILURE);
	}
	// Read response from udevadm
	while (fgets(response, sizeof(response), fp) != NULL) {
		// Check if response contains "ID_INPUT_KEYBOARD"
		if (strstr(response, "ID_INPUT_KEYBOARD") != NULL) {
			arrSize++;
		}
	}
	// Close udevadm output stream
	if (pclose(fp) == -1) {
		perror("Failed to close udevadm stream");
		exit(EXIT_FAILURE);
	}
	// reutnr arr.data
	return 0;
}
