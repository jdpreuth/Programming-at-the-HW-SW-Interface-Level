/*
* Name: Jon Preuth
* Username: jdpreuth
* Description: Method implementations for the key struct
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Key.h"
#include "Stats.h"

/*
* Initialized a key struct to hold a key from a file
* Param: Key* key: Pointer to a key struct to hold the key
* Param: char* filename: Name of the file that has the key
*/
bool initKey(Key* key, const char* filename){
	//Open File
	FILE* file = fopen(filename, "rb");
	if (file == NULL){
		return false;
	}

	//Initialize values
	key->size = 0;
	key->pos = 0; 

	//Put key into memory 
	int letter;
	while((letter = fgetc(file)) != EOF){
		key->size++;
		key->data = realloc(key->data, key->size);
		if(key == NULL){
			printf("Realloc failed");
			return false;
		}
		key->data[key->size-1] = (char)letter; 
	}

	//Close the open file and returned true
	fclose(file);
	return true;
}

/*
* Frees the memmory of a key struct
* Param: Key* key: Pointer to the key to be freed
*/
void freeKey(Key* key){
	free(key->data);
	free(key);
	key = NULL;
}

/*
* Applys the key to a passed character and updates the stats
* Param: Key* key: Pointer to a key struct to be useued for encryption
* Param: Stats* stats: Pointer to a stats struct that will be updated
* Param: char ch: character to be encrypted
* Param: bool debug: determines if optional debug output is printed
*/
char applyKey(Key* key, Stats* stats, char ch, bool debug){
	char cypherKey = key->data[key->pos];	//Cypher key extracted from key struct
	char result = ch ^ key->data[key->pos];	//The result of applying the cypher 
	
	//Move the key pos forward
	key->pos++;
	if(key->pos == key->size){	//Reset the pos to the beginning if all char have been usued
		key->pos = 0;
	}
	updateStats(stats, result);

	//Optional debug text
	if(debug){
		unsigned char chInt = ch;
		unsigned char cypherInt = cypherKey;
		unsigned char resultInt = result;
		if(ch < 32 || ch > 126){	//Check if original character is 'other'	
			ch = '~';
		}
		if(cypherKey < 32 || cypherKey > 126){	//Check if result character is 'other'
			cypherKey = '~';
		}
		if(result < 32 || result > 126){	//Check if result character is 'other'
			result = '~';
		}
		printf("%3u '%c' ^ %3u '%c' -> %3u '%c'\n", chInt, ch, cypherInt, cypherKey, resultInt, result);
	}
	return result;
}