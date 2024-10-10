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
{ // command:  ./wzip input1.txt input2.txt

	if(argc == 1) { // no input argument
		printf("wzip: file1 [file2 ...]\n");
		exit(1);
	}

	FILE *fp_in;
	int prev_chr, cur_chr, fi, n=0;
	int firstchar = 1; // boolean

	for(fi=1; fi<argc; fi++)
	{
		fp_in = fopen(argv[fi], "r");
		if(fp_in == NULL){				
			printf("wzip: cannot open file\n"); // fprintf(stderr, "...\n");
			exit(1);
		}

		while(1)
		{
			// char *fgets(char *restrict s, int size, FILE *restrict stream);
			cur_chr = fgetc(fp_in);

			if( feof(fp_in) )  // check EOF
				break;

			if(firstchar) { // first char ever
				prev_chr = cur_chr;
				n = 1;
				firstchar = 0;
				continue;					
			}			

			if(cur_chr == prev_chr) 
				n++;
			else {
				// size_t fwrite(const void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream);
				fwrite(&n, sizeof(n), 1, stdout);
				fwrite(&prev_chr, sizeof(char), 1, stdout); // not sizeof(prev_chr)

				prev_chr = cur_chr;
				n = 1;
			}
		}
		fclose(fp_in);
	}
	if(n > 0){
		fwrite(&n, sizeof(int), 1, stdout);
		fwrite(&prev_chr, sizeof(char), 1, stdout);
	}
	return 0;
}
