#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#define LEN 50
#define DEBUG 0

enum {INIT = 1, GROW = 2};

struct data_t {
	int nval;
	int max;
	char **data;
};

int validate(struct data_t *data, char word[]);
int findPlay(struct data_t *data, char word[]);
int valueWord(char word[]);

int main() {
    FILE *fp = fopen("scrabble.txt", "r");
	char buf[LEN];
	int i = 0;
	struct data_t *data = malloc(sizeof(struct data_t));
	data->nval = INIT;
	data->max = INIT;
	data->data = NULL;
	while (fgets(buf, LEN, fp)) {
		if (data->data == NULL)
			data->data = malloc(sizeof(char *));
		else if (data->nval > data->max) {
			data->data = realloc(data->data, GROW * data->max * sizeof(char *));
			data->max = GROW * data->max;
		}
        *(data->data + i) = malloc(sizeof(buf));
        buf[strcspn(buf, "\n")] = 0;

        //printf("buf: %s\n", buf);   //debug

		strncpy(*(data->data + i), buf, strlen(buf));
		i++;
        data->nval++;
	}	
    data->nval--;

	fclose(fp);

    while(1){
        printf("Scrabble Menu\n");
        printf("1. Find if a word is in the scrabble dictionary\n");
        printf("2. Determine best play from tiles\n");
        printf("3. Quit\n");
        printf("Enter an option [1, 2, 3]: ");
        fgets(buf, LEN, stdin);
        sscanf(buf, "%d", &i);
        switch(i) {
            case 1:
                printf("Enter word: ");
                fgets(buf, LEN, stdin);
                sscanf(buf, "%s\n", buf);
                printf("\n%s %s a valid scrabble word\n\n", buf, validate(data, buf) ? "is" : "is not");
                break;
            case 2:
                printf("Enter tiles as a word: ");
                fgets(buf, LEN, stdin);
                sscanf(buf, "%s\n", buf);
                for(i = 0; i < strlen(buf); i++)
                    buf[i] = tolower(buf[i]);
                int found = findPlay(data, buf);
                if(found != -1)
                    printf("\nBest play is '%s' (%d points)\n\n", *(data->data + found), valueWord(*(data->data + found)));
                else
                    printf("\nNo plays found for '%s'\n\n", buf);
                break;
            case 3:
                goto EXIT;
        }
    }
    

    EXIT:
    for(i = 0; i < data->nval; i++){
        free(*(data->data + i));
    }
    free(data->data);
    free(data);
}

int validate(struct data_t *data, char word[]) {
    for(int i = 0; i < data->nval; i++){
        if(strcmp(*(data->data + i), word) == 0)
            return 1;
    }
    return 0;
}

int findPlay(struct data_t *data, char word[]) {
    int max = 0;
    int found = 0;
    char tmp[strlen(word)];
    char *c = malloc(sizeof(char));
    for(int i = 0; i < data->nval; i++){
        strncpy(tmp, word, strlen(word));
        if(strlen(*(data->data + i)) > strlen(word))
            continue;
        for(int j = 0; j < strlen(*(data->data + i)); j++) {
            *c = *(*(data->data + i) + j);
            if(strchr(tmp, *(*(data->data + i) + j)) != NULL) {
                memmove(&tmp[strcspn(tmp, c)], &tmp[strcspn(tmp, c) + 1], strlen(tmp) - strcspn(tmp, c)); //c = *(data->data + i)[j]
                if(DEBUG) printf("looking at '%s' : %s : removed '%s'\n", *(data->data + i), tmp, c);
            }
            else {
                if(DEBUG) printf("Nope.\n");
                break;
            }
            if(j == strlen(*(data->data + i)) - 1 && valueWord(*(data->data + i)) > valueWord(*(data->data + max))) {
                max = i;
                found = 1;
                if(DEBUG) printf("Found!\n");
            }

        }
    }
    free(c);
    if(found)
        return max;
    else 
        return -1;
}

int valueWord(char word[]) {
    int score = 0;
    for(int i = 0; i < strlen(word); i++){
        switch (word[i]) {
            case 'a':
            case 'e':
            case 'i':
            case 'l':
            case 'n':
            case 'o':
            case 'r':
            case 's':
            case 't':
            case 'u':
                score += 1;
                break;
            case 'd':
            case 'g':
                score += 2;
                break;
            case 'b':
            case 'c':
            case 'm':
            case 'p':
                score += 3;
                break;
            case 'f':
            case 'h':
            case 'v':
            case 'w':
            case 'y':
                score += 4;
                break;
            case 'k':
                score += 5;
                break;
            case 'j':
            case 'x':
                score += 8;
                break;
            case 'q':
            case 'z':
                score += 10;
                break;
        }
    }
    return score;
}