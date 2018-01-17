/**
 * Name: Jon Preuth
 * Username: jdpreuth
 * Description: Takes the x and y cordinates along with the radius of two circles and outputs the two circles, the distance between them, and if
 * the two circles intersect. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv){
	//Check to see if the commandline arguments are correct 
	if(argc < 7){
		printf("TwoCircles <x1> <y1> <r1> <x2> <y2> <r2> \n");
		return 0;
	}
	
	//Assign varialbes to the corresponding commandline arguments and calc distance
	double c1X = atof(argv[1]);
	double c1Y = atof(argv[2]);
	double c1R = atof(argv[3]);
	double c2X = atof(argv[4]);
	double c2Y = atof(argv[5]);
	double c2R = atof(argv[6]);
	double distance	 = sqrt(pow((c2X - c1X),2.0) + pow((c2Y - c1Y),2));

	//Print out the circle information and the distance between them
	printf("Circle 1: (%.2f, %.2f) r = %.2f\n", c1X, c1Y, c1R);
	printf("Circle 2: (%.2f, %.2f) r = %.2f\n", c2X, c2Y, c2R);	
	printf("Distance between centers = %.4f\n", distance);
	
	//Check to see if the circles intersect and print out if they do
	if(distance < c1R + c2R){
		printf("%.4f < %.4f, circles intersect\n", distance, c1R + c2R);
	}else{
		printf("%.4f >= %.4f, circles do not intersect\n", distance, c1R + c2R);
	}

	return 0;	
}
