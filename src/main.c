#include <stdio.h>

int
main( int argc ,char* argv[]) {
	FILE *filed = fopen("test/test.c","r");
	if (filed == NULL) {
		printf( "coudlnt open file \n");
		return -1;
	}

	fclose(filed);
	return 0;
}
