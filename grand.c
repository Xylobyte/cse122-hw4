#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "random.h"


void create_random_ints(FILE *fp, int size, int mod)
{
	int i;
	seed();

	for (i = 0; i < size; i++) {
		fprintf(fp, "%d\n", nrand(mod));
	}
}

int main(int argc, char **argv) 
{
	/* create a file of random integers */
	int size = 0;
	int mod = 0;
	FILE *fp = NULL;
	int c = 0;


	if (argc == 1) {

		printf("usage: ./grand -n [NUM] -m [MAX]  -f [FILE]\n");
		printf("[NUM] is the number of random integers to create\n");
		printf("create random numbers between [0, [MAX])\n");
		printf("[FILE] is the name of the file the data is written to\n");
		exit(EXIT_SUCCESS);		
	}

	/* pass a string of options to getopt
         * the colon after a letter signifies that the option expects an argument 
         * leading colon lets you distinguish between invalid option and missing argument cases
         */
	while((c = getopt(argc, argv, ":hn:m:f:")) != -1)

		switch(c) {
		case 'n':
			size = atoi(optarg);
 			break;
		case 'm':
			mod = atoi(optarg);
			break;
		case 'f':
			errno = 0; /* set to 0 so can process it if an error occurs */
			fp = fopen(optarg, "w");
			if (fp == NULL) {
				/* strerror */
				fprintf(stderr, "%s: argument to option '-f' failed: %s\n", argv[0], strerror(errno));
				exit(EXIT_FAILURE);
			}

			break;

		case 'h': 	/* help */

			if (fp != NULL)
				fclose(fp);

			printf("usage: ./grand -n [NUM] -m [MAX]  -f [FILE]\n\n");
			printf("[NUM] is the number of random integers to create\n");
			printf("create random numbers between [0, [MAX])\n");
			printf("[FILE] is the name of the file the data is written to\n");
			exit(EXIT_SUCCESS);
		case ':':
			/* missing option argument */
			/* optopt contains the option */
			/* argv[0] is the programs name */
			/* stderr is 1 of 3 files open for you -- stdin, stdout, stderr. By default stdout and stderr are mapped to the same location */
			if (fp != NULL)
				fclose(fp);

			fprintf(stderr, "%s: option '-%c' reguires an argument\n", argv[0], optopt);
			exit(EXIT_FAILURE);
		case '?': 	/* getopt default invalid option */
		default:
			if (fp != NULL)
				fclose(fp);
			printf("illegal option %c - ignored\n", optopt);
			break;				
		}


	/* all options are required, check to make sure they are valid */
	if (fp == NULL) {
		printf("the option -f [FILE] is required\n");
		printf("usage: ./grand -n [NUM] -m [MAX] -f [FILE]\n");
		exit(EXIT_FAILURE);
	}
	
	if (size <= 0) {
		printf("the option -m [MAX] is required\n");
		printf("usage: ./grand -n [NUM] -m [MAX] -f [FILE]\n");
		if (fp == NULL)
			fclose(fp);
		exit(EXIT_FAILURE);
	}

	if (mod <= 0) {
		printf("the option -m [MAX] is required\n");
		printf("usage: ./grand -n [NUM] -m [MAX] -f [FILE]\n");
		if (fp == NULL)
			fclose(fp);
		exit(EXIT_FAILURE);
	}	

	
	create_random_ints(fp, size, mod);

	fclose(fp);
	
	return 0;
}
