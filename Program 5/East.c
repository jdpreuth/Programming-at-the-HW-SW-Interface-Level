/**
 * Name: Jon Preuth
 * Username: jdpreuth
 * Description: Reads in elevation data, prints out basic information, and the path of least resistance
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int main(int argc, char** argv){
	int width = 0;			//The width of the data grid
	int height = 0;			//The height of the data grid
	int size = 0;			//The number of data points
	int data = 0;			//Temp variable for reading data
	int wCursor = 0;		//Position in the column
	int hCursor = 0;		//Row position
	int minElevation = INT_MAX;	//Minimum elevation
	int maxElevation = INT_MIN;	//Maximum Elevation 
	double averageElevation = 0;	//Average Elevation
	int bestRow = 0;		//Best starting row
	int bestCost = INT_MAX;		//Cost of the best path
	int stepCost = 0;		//Cost of a given step
	int cost = 0;			//Cost of a given path
	bool verbose = false;		//If verbose mode is enabled or not. Default to off
	char move;			//Stores the move made for use in verbose mode 

	//Check for verbose mode
	if(argc > 1){
		int check = atoi(argv[1]);
		if(check != 0){
			verbose = true;
		}
	}  

	scanf("%d %d", &width, &height);	//Reads in Width and Height
	int elevations[width][height];		//Creates an array of width x height to hold elevation data

	//Scan in elevation data and track size, min, max, and average elevation
	while(scanf("%d", &data) > 0){
		if(wCursor < width){
			elevations[wCursor][hCursor] = data; 
			wCursor++;	
		}else{
			wCursor = 0;
			hCursor++;
			elevations[wCursor][hCursor] = data; 
			wCursor++;	
		}
		size++;
		if(data < minElevation){
			minElevation = data;
		}
		if(data > maxElevation){
			maxElevation = data;
		}
		averageElevation += data;
	}
	averageElevation = averageElevation / size;	

	//Prints out the elevation stats
	printf("Data points: %d\nAvg elevation: %.2f\nMin elevation: %d\nMax elevation: %d\n", size, averageElevation, minElevation, maxElevation);
	
	//Greedy Algorihm 
	for(int h = 0; h < height; h++){	//Calculate the greedy method cost starting at each row 
		hCursor = h; //Starting height (row) 
		cost = 0; 
		for(wCursor = 0; wCursor < width - 1; wCursor++){
			if(verbose){	//Output for verbose mode 
				printf("(%d,%d) %d ", wCursor, hCursor, elevations[wCursor][hCursor]);
			}
			if(hCursor == 0){	//The current position is the first row
				int forward = abs(elevations[wCursor + 1][hCursor]  - elevations[wCursor][hCursor]);
				int down = abs(elevations[wCursor + 1][hCursor + 1] - elevations[wCursor][hCursor]);
				stepCost = forward;	//Assume forward is the lowest cost
				move = 'F'; 
				if(down < stepCost){	//Down is the lowest cost
					stepCost = down;
					hCursor++;
					move = 'D';
				}
			}else if(hCursor == height - 1){	//The current position is the last row
				int up = abs(elevations[wCursor + 1][hCursor - 1]  - elevations[wCursor][hCursor]);
				int forward = abs(elevations[wCursor + 1][hCursor] - elevations[wCursor][hCursor]);
				stepCost = forward;	//Assume forward is the lowest cost
				move = 'F';
				if(up < stepCost){	//Up is the lowest cost
					stepCost = up;
					hCursor--;
					move = 'U';
				} 
			}else{	//The current position is not the first or last row 
				int up      = abs(elevations[wCursor + 1][hCursor - 1] - elevations[wCursor][hCursor]);
				int forward = abs(elevations[wCursor + 1][hCursor]     - elevations[wCursor][hCursor]);
				int down    = abs(elevations[wCursor + 1][hCursor + 1] - elevations[wCursor][hCursor]);
				stepCost = forward;	//Assume forward is the lowest cost
				move = 'F';
				if(down <= up){		//Down is lower than up. Down wins ties 
					if(down < stepCost){	//Down is the lowest cost
						stepCost = down;
						hCursor++;
						move = 'D';
					}
				}else{	//Up is lower than down
					if(up < stepCost){	//Up is the lowest cost
						stepCost = up;
						hCursor--; 
						move = 'U';
					}
				}

			}	 
			cost += stepCost;	//Add the step cost to total cost of the row
			if(verbose){
				printf("%c, ", move); 
			}
		}
		if(verbose){	//Output for verbose mode 
			printf("(%d,%d) %d, cost %d\n", wCursor, hCursor, elevations[wCursor][hCursor], cost);
		} 
		if(cost < bestCost){	//Determines if the current row has a better cost than the current best row 
			bestCost = cost;
			bestRow = h;
		}
	}
 
	//Print the best cost info
	printf("Best: row %d, cost %d\n", bestRow, bestCost); 	

	return 0;
}


