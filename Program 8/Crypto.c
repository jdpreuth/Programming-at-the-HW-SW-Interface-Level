/*
* Name: Jon Preuth
* Username: jdpreuth
* Description: Crypto main file. Encrypts an input file using a key file and saves it to an output file. Optional debugging avaiable by passing a non-zero number
*/

#include <stdio.h>
#include <stdlib.h>
#include "Key.h"
#include "Stats.h"

int main(int argc, char** argv){
	//Ensure command line arguments are correct
	if(argc < 4){
		printf("Crypto <input file> <output file> <key file> [debug]\n");
		return 1;
	}

	//Declare variables
	char* inputFile = argv[1];
	char* outputFile = argv[2];
	char* keyFile = argv[3];
	bool debug = false;
	if(argc > 4){	//Checks if optional debug is enabled
		int arg = atoi(argv[4]);
		if(arg != 0){
			debug = true;
		}
	}

	//Create key struct
	Key* key = malloc(sizeof(Key));
	if(key == NULL){
		printf("Malloc of key failed\n");
		return 1;
	}
	if(!initKey(key, keyFile)){
		printf("Failed to load key file: %s\n", keyFile);
		return 1;
	}

	//Create stat struct
	Stats* stats = malloc(sizeof(Stats));
	if(stats == NULL){
		printf("Malloc of stats failed\n");
		return 1; 
	}
	initStats(stats);

	//Apply Cipher

	//Open Input file
	FILE* input = fopen(inputFile, "rb");
	if(input == NULL){
		printf("Failed to open input file: %s\n", inputFile);
		return 1;
	}
	//Open output file
	FILE* output = fopen(outputFile, "wb");
	if(output == NULL){
		printf("Failed to open output file: %s\n", outputFile);
		fclose(input);
		input = NULL;
		return 1;
	}
	int letter;
	while((letter = fgetc(input)) != EOF){	//Iterate through the input file and apply the cypher
		fflush(stdout);
		fputc(applyKey(key, stats, (char)letter, debug), output);
	}

	printStats(stats);

	//Free Usued Memory and Close Files
	fclose(input);
	fclose(output);
	freeKey(key);
	free(stats);
	return 0;
}