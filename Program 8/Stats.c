/*
* Name: Jon Preuth
* Username: jdpreuth
* Description: Method implementation for the stat struct
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Key.h"
#include "Stats.h"

/*
* Initialized a stats structure
* Param: Stats* stats: pointer to a stat struct to be initialized
*/
void initStats(Stats* stats){
	fflush(stdout);
	stats->letters = 0;
	stats->spaces = 0;
	stats->numbers = 0;
	stats->other = 0;
}

/*
* Updates the stats with the new character
* Param: Stats* stats: pointer to a stat struct to be updated
* Param: char ch: character to be used to update the stats
*/
void updateStats(Stats* stats, char ch){
	unsigned char new = (unsigned char) ch;
	if((new >= 65 && new <=90) || (new >= 97 && new <= 122)){	//Is Letter
		stats->letters++;
	}else if(new == 32){	//Is Space
		stats->spaces++;
	}else if(new >= 48 && new <= 57){ //Is Number
		stats->numbers++;
	}else{	//Is Other
		stats->other++;
	}
}

/*
* Prints out the stat information
* Param: Stats* stats: pointer to a stats struct to be printed
*/
void printStats(Stats* stats){
	int total = stats->letters + stats->spaces + stats->numbers + stats->other;
	printf("Output %d characters: %.2f%% letters, %.2f%% spaces, %.2f%% numbers, %.2f%% other\n", total, (double)(stats->letters)/total*100, (double)(stats->spaces)/total*100, (double)(stats->numbers)/total*100, (double)(stats->other)/total*100);
}