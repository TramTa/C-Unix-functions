#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>


//***************** 
// check if 2 files are the same
int same_file(int fd1, int fd2) {
    struct stat stat1, stat2;
    if(fstat(fd1, &stat1) < 0) return -1;
    if(fstat(fd2, &stat2) < 0) return -1;
    return (stat1.st_dev == stat2.st_dev) && (stat1.st_ino == stat2.st_ino);
}


//*****************
struct LLnode{
	char *line; 
	struct LLnode *next, *prev;
};

//*****************
struct LLnode *create_dLL(FILE *fp_in){	
	size_t len;
	ssize_t nread;
	struct LLnode *head, *cur, *last, *tmp_node;

	head = (struct LLnode *)malloc(sizeof(struct LLnode));
	if( head==NULL ){
		fprintf(stderr,"malloc failed\n");
		exit(1);
	}

	head->prev = NULL;
	head->line = NULL;
	cur = head;

	while( (nread = getline(&cur->line, &len, fp_in)) != -1 ){
		cur->next = (struct LLnode *)malloc(sizeof(struct LLnode));
		if( cur->next == NULL ){
			fprintf(stderr,"malloc failed\n");
			exit(1);
		}
		
		tmp_node = cur;
		cur = cur->next;
		cur->line = NULL;
		cur->prev = tmp_node;		
	}

	last = cur->prev;
	free(cur->line);
	free(cur);
	cur = NULL;
	return last;
}


// ******************************
int main(int argc, char *argv[])
{
	if(argc > 3) {
		fprintf(stderr, "%s\n", "usage: reverse <input> <output>");
		exit(1);
	}

	FILE *fp_in, *fp_out;
	fp_in = stdin;
	fp_out = stdout;

	if(argc == 2){ // cmd:  ./reverse input.txt
		fp_in = fopen(argv[1], "r");
		if(fp_in == NULL){
			fprintf(stderr, "reverse: cannot open file \'%s\'\n", argv[1]);
			exit(1);
		}
	}

	else if(argc == 3){ // cmd:  ./reverse input.txt output.txt		
		fp_in = fopen(argv[1], "r");
		fp_out = fopen(argv[2], "w");

		if(fp_in == NULL){
			fprintf(stderr, "reverse: cannot open file \'%s\'\n", argv[1]);
			exit(1);
		}
		if(fp_out == NULL){
			fprintf(stderr, "reverse: cannot open file \'%s\'\n", argv[2]);
			exit(1);
		}		
		if( same_file(fileno(fp_in), fileno(fp_out)) ){
			fprintf(stderr, "%s\n", "reverse: input and output file must differ");
			exit(1);
		}
	}

	struct LLnode *last=NULL, *cur=NULL , *tmp_node=NULL;
	last = create_dLL(fp_in);
	cur = last;
				
	while(cur != NULL){
		fprintf(fp_out, "%s", cur->line); 
		free(cur->line);

		tmp_node = cur;
		cur = cur->prev;
		free(tmp_node);	
	}

	if (argc == 2) {
		fclose(fp_in);
	}
	else if (argc == 3) {
		fclose(fp_in);
		fclose(fp_out);
	}
	
	return 0;
}
