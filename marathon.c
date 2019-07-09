#include <stdio.h>
#include <stdlib.h>

#include "user.h"

#define DEFAULT_FILE "user.txt"

int main(int argc, char* argv[])
{
  	int number = 0, ret = 0;
	char *datafile = NULL;
	user *p = NULL;

	// Read a filename
	if(argc == 1) {
		datafile = DEFAULT_FILE;
	} else if (argc == 2) {
		datafile = argv[1];
	} else {
		printf("Usage : %s datafile\n", argv[0]);
		exit(-1);
	}

	// Load data from the file
	ret = user_create(datafile, &p, &number);
  	if( ret != 0 ) {
		printf("user_create() returns error! %d\n", ret);
		exit(ret);
	}

	// Display some statistic data
	ret = user_stat(p, number);
	if( ret != 0 ) {
		printf("user_stat returns() error (errno: %d)\n", ret);
	}

	// Close the file data
	user_close();

	return 0;
}
