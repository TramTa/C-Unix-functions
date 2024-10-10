// ******************************
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <limits.h>
#include <string.h>


// ******************************
int main(int argc, char *argv[])
{ // command:  ./wgrep foo input1.txt input2.txt

	if(argc == 1){ // no input argument
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}

	if( strcmp(argv[1], "") == 0 )
	// if( !argv[1] ) // argv[1] is empty 
		return 0;

	FILE *fp_in;
	char *word = argv[1];
	char *line = NULL;

	size_t len;
	ssize_t nread;

	int i = 2;
	while(1)
	{
		if(argc == 2){ // input is from stdin
			fp_in = stdin;
		}
		else {
			fp_in = fopen(argv[i], "r");
			if(fp_in == NULL){				
				printf("wgrep: cannot open file\n"); // fprintf(stderr, "...\n");
				exit(1);
			}
		}

		while( (nread = getline(&line, &len, fp_in)) != -1 ){
			// char *strstr(const char *haystack, const char *needle); // return NULL if substr not found
			if(strstr(line, word) != NULL){ // case sensitive
				printf("%s", line);
			}			
		}

		if(argc == 2)	
			break;
		else {
			fclose(fp_in);
			i++;
		}

		if(i == argc)
			break;
	}
	free(line);
	return 0; 
}
