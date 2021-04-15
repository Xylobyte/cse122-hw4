#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "random.h"

/**
 * returns a uniform random number between 0 <= rand num < range
 * @param int range, defines the range of the random number [0,range)  
 * @return int, the generated random number
 */
int nrand(int range) 
{
	return rand() % range;
}

/**
 * call this to seed the random number generator rand()
 * uses a simple seed -- the number of seconds since the epoch 
 * call once before using nrand and similar functions that call rand()
 */
void seed(void) 
{
  	srand((unsigned int)time(NULL));
}
