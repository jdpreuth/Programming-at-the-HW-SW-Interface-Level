/**
 * Name: Jon Preuth
 * Username: jdpreuth
 * Description: Takes a command line argument and computes the number of bits in the number. Prints a ussage message or illegal input if
 * invalid input is given.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	//Checks to see if the commandline arguments are correct. Prints a usage message otherwise
	if(argc != 2){
		printf("Bits <integer N>\n");
		return 0;
	}

	//Assigns bit to the commandline arguments and initialzied the number of bits
	int bit = atoi(argv[1]);
	int numBits = 0;

	//If the inputed integer is negative prints an illegal input message
	if(bit < 0){
		printf("Illegal Input\n");
		return 0;
	}

	//Checks to see how many bits are in the given integer 
	while(bit > 0){
		bit = bit / 2;
		numBits++;
	} 

	//Prints the number of bits 
	printf("%d\n", numBits);

	return 0;
}

