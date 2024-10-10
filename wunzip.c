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
{ // command:  ./wunzip input1.txt input2.txt

	if(argc == 1) { // no input argument
		printf("wunzip: file1 [file2 ...]\n");
		exit(1);
	}

	FILE *fp_in;
	char c;
	int n, j, fi;
	size_t st;

	for(fi=1; fi<argc; fi++)
	{
		fp_in = fopen(argv[fi], "r");
		if(fp_in == NULL){				
			printf("wunzip: cannot open file\n"); // fprintf(stderr, "...\n");
			exit(1);
		}

		while(1) {
			// size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
			st = fread(&n, sizeof(int), 1, fp_in);
			if(st != 1)  
				break;

			st = fread(&c, sizeof(char), 1, fp_in);
			if(st != 1)  
				break;
			
			for(j=0; j<n; j++)  
				printf("%c", c);
			// if(n==1) printf("=========%d\n", n);
		}
		fclose(fp_in);
	}
	return 0;
}
