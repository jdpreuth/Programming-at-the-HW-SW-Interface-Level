/* Name: Jon Preuth
 * Username: jdpreth
 * Description: Prints ASCII Art given a list of commands
 */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

// TODO: add a parameter list and the implementation for the following 6 functions:
void initImage(int width, int height, double image[width][height]) 
{
	for(int w = 0; w < width; w++){
		for(int h = 0; h < height; h++){
			image[w][h] = 0.00;
		}
	}
}

void printImage(int width, int height, double image[width][height]) 
{
	//Print the top boarder
	for(int h = 0; h < height; h++){
		if(h == 0){
			printf("+");
			for(int i = 0; i < width; i++){
				printf("-");
			}
			printf("+\n");
		}

		printf("|");	//Prints the side boarder
	
		//Prints the appropriate character
		for(int w = 0; w < width; w++){
			double value = image[w][h];
			if(value >= 0.0 && value < 0.2){
				printf(" ");
			}else if(value >= 0.2 && value < 0.4){
				printf(".");
			}else if(value >= 0.4 && value < 0.6){
				printf("o");
			}else if(value >= 0.6 && value < 0.8){
				printf("O");
			}else{
				printf("@");
			}
		}
		printf("|\n");	//Prints the side boarder
		
		//Prints the bottom border
		if(h == height - 1){
			printf("+");
			for(int i = 0; i < width; i++){
				printf("-");
			}
			printf("+\n");
		}
	}
}

void drawPoint(int width, int height, double image[width][height], int x, int y, double color) 
{
	if(x < width && x >= 0 && y < height && y >= 0){	//Checks to make sure the point is inside the canvas
		image[x][y] = color;
	}
} 

void drawRectangle(int width, int height, double image[width][height], int left, int top, int rectangleWidth, int rectangleHeight, double color) 
{
	int x = left;
	int y = top;
	for(int w = 0; w < rectangleWidth; w++){	//Draws the rectangles width left to right
		for(int h = 0; h < rectangleHeight; h++){	//Draws the rectangles height top to bottom 
			drawPoint(width, height, image, x, y, color);	 
			y++;
		}
		x++;
		y = top;	//Resets the y cordinate to the top 
	}
}

void getImageStats(int width, int height, double image[width][height], double* minColor, double* maxColor, double* avgColor) 
{
	*minColor = DBL_MAX;	//Pointer to the address of the min value 
	*maxColor = -DBL_MAX;	//Pointer to the address of the max value
	double sum = 0.0;	//Running sum 
	int n = 0;		//Number of characters

	for(int w = 0; w < width; w++){
		for(int h = 0; h < height; h++){
			if(image[w][h] < *minColor){	//Check to see if this is the new min
				*minColor = image[w][h];
			}
			if(image[w][h] > *maxColor){	//Checks to see if this is the new max
				*maxColor = image[w][h];
			}
			sum += image[w][h];	//Adds the value to the running sum
			n++;	
		}
	}

	*avgColor = sum / n;
}

void floodFill(int width, int height, double image[width][height], int x, int y, double color) 
{
	//Sets the point to the given color
	if(x < width && y < height){
	image[x][y] = color;
	}

	//Recursively call to the right
	if(x + 1 < width && color > image[x+1][y]){
		floodFill(width, height, image, x+1, y, color);
	}
	//Recursively call to the left
	if(x - 1 >= 0 && color > image[x-1][y]){
		floodFill(width, height, image, x-1, y, color);
	}
	//Recursively call to the top
	if(y + 1 < height && color > image[x][y+1]){
		floodFill(width, height, image, x, y+1, color);
	}
	//Recursively call to the bottom
	if(y - 1 >= 0 && color > image[x][y-1]){
		floodFill(width, height, image, x, y-1, color);
	} 
}

// Read in a set of drawing instructions from standard input.
// Print the resulting greyscale image as ASCII art. 
// DO NOT MODIFY!
int main(void)
{
   // Read in the size of the drawing canvas
   int width = 0;
   int height = 0;
   int result = scanf("%d %d", &width, &height);
   
   // Program only supports images that are 1x1 or bigger
   if ((width <= 0) || (height <= 0) || (result != 2))
   {
      printf("Failed to read a valid width and height from standard input!\n");
      return 0;
   }
   
   // Create the 2D arary and initialize all the greyscale values to 0.0
   double image[width][height];
   initImage(width, height, image);
   
   char command = '\0';
   double color = 0.0;
   
   // Keep reading in drawing commands until we reach the end of the input
   while (scanf(" %c", &command) == 1)
   {
      switch (command)
      {		
         case 'p': 	
         {
            // Draw a point, read in: x, y, color
            int x = 0;
            int y = 0;
            result = scanf("%d %d %lf", &x, &y, &color);
            if (result != 3)
            {
               printf("Invalid point command!\n");
               return 0;
            }
            
            drawPoint(width, height, image, x, y, color);
            break;
         }

         case 'r': 	
         {
            // Draw a rectangle, read in: x, y, w, h, color
            int left = 0;
            int top = 0;
            int rectangleWidth = 0;
            int rectangleHeight = 0;
            result = scanf("%d %d %d %d %lf", &left, &top, &rectangleWidth, &rectangleHeight, &color);
            if (result != 5)
            {
               printf("Invalid rectangle command!\n");
               return 0;
            }
         
            drawRectangle(width, height, image, left, top, rectangleWidth, rectangleHeight, color);
            break;
         }

         case 'f':
         {
            // Flood fill a color in, read in: x, y, color
            int x = 0;
            int y = 0;
            result = scanf("%d %d %lf", &x, &y, &color);
            if (result != 3)
            {
               printf("Invalid flood fill command!\n");
               return 0;
            }
            
            floodFill(width, height, image, x, y, color);
            break;
         }

         default:
         {
            printf("Unknown command!\n");
            return 0;
         }
      }
   }
   
   // Print the final image
   printImage(width, height, image);
   
   // Finally display some statistics about the image
   double minColor = 0.0;
   double maxColor = 0.0;
   double avgColor = 0.0;
   getImageStats(width, height, image, &minColor, &maxColor, &avgColor);
   printf("Color range [%.2f, %.2f], average %.4f\n", minColor, maxColor, avgColor);
}
