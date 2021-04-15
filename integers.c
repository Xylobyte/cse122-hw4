#include <stdio.h>
#include <stdlib.h>

#define LEN 100

struct data_t {
	int nval; 		/* current number of values in array */
	int max; 		/* allocated number of values */
	int *data;		/* the data array */
};

enum {INIT = 1, GROW = 2};

int main(void) 
{
	FILE *fp = fopen("test_data", "r");
	char buf[LEN];
	int i = 0;
	struct data_t *data = malloc(sizeof(struct data_t));
	data->nval = INIT;
	data->max = INIT;
	data->data = NULL;
	while (fgets(buf, LEN, fp)) {
		if (data->data == NULL)
			data->data = malloc(sizeof(int));
		else if (data->nval > data->max) {
			data->data = realloc(data->data, GROW * data->max *sizeof(int));
			data->max = GROW * data->max;
		}
		*(data->data + i) = atoi(buf); 
		i++;
                data->nval++;		
	}	
        /* overcounted */
        data->nval--;
	for(i = 0; i < data->nval; i++)
		printf("data->data[%d] = %d\n", i, *(data->data +i));
	fclose(fp);
        /* no frees! this needs to be fixed */
	return 0;
}

