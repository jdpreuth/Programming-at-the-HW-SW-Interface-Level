/**
 * Name: Jon Preuth
 * Username: jdpreuth
 * Description: This program takes a greeting and 3 names and outputs the greeting with each name.
 */

#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv){
	//Checks to see if the command line arguments are correct. Prints a usage message otherwise 
	if(argc != 5){
		printf("Greetings <greeting> <name1> <name2> <name3>\n");
        return 0;
	}

	//Save the greeting from the command line into a string
	char* greeting = argv[1];

	//Prints out the greeting and the person's name 
	for(int i = 2; i < argc; i++){
		printf("%s %s!\n", greeting, argv[i]);
	} 

	return 0;
}

