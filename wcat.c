#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <limits.h>


// ******************************
int main(int argc, char *argv[])
{ // command:  cat input1.txt input2.txt ...
	if(argc == 1){
		return 0;
	}

	FILE *fp_in;
	char *line = NULL;

	size_t len;
	ssize_t nread;

	int i;
	for(i=1; i<argc; i++)
	{
		fp_in = fopen(argv[i], "r");
		if(fp_in == NULL){
			printf("wcat: cannot open file\n");
			exit(1);
		}

		while( (nread = getline(&line, &len, fp_in)) != -1 ){
			printf("%s", line);
		}
		fclose(fp_in);
	}
	free(line);

	return 0; 
}

