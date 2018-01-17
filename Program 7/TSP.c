/*
* Name: Jon Preuth
* Username: jdpreuth
* Description: This program calculates the tour distance for a passed set of points using a given huresitic
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

// Constants that define the method to use when adding points to the tour
#define INSERT_FRONT      0
#define NEAREST_NEIGHBOR  1
#define SMALLEST_INCREASE 2

// Node of a linked list that stores (x, y) location of points.
// You should NOT need to modify this.
typedef struct node
{
   double x;            // x-coordinate of this point in the tour
   double y;            // y-coordinate of this point in the tour
   struct node* next;   // Pointer to the next node in the linked list
} Node;

// Function prototypes, you should NOT need to modify these.
Node* addFront(Node* first, double x, double y);
void printNode(Node* node);
void printTour(Node* first);
int tourSize(Node* first);
double distance(Node* a, Node* b);
double tourDistance(Node* first);
void freeTour(Node* first);
Node* addNearestNeighbor(Node* first, double x, double y);
Node* addSmallestIncrease(Node* first, double x, double y);

// Add a new point to the front of the tour.
// Passed a pointer to the first node in the tour, NULL if creating a new tour.
// Returns pointer to the first node in the linked list after the addition.
Node* addFront(Node* first, double x, double y)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->x = x;
	newNode->y = y;
	newNode->next = first;
   	return newNode;
}

// Print out the point stored at the given node.
// Round to 4 decimal places and output a line feed (\n), e.g.:
// (1.2345, 6.7890)
void printNode(Node* node)
{
	printf("(%.4f, %.4f)\n", node->x, node->y);
}

// Print out all the points in the tour from first to last.
// Passed a pointer to the first node in the tour.
// If the first is NULL, doesn't print anything.
void printTour(Node* first)
{
	Node* cursor = first;
	while(cursor != NULL){
		printNode(cursor);
		cursor = cursor->next;
	}
}

// Get the number of points in the tour.
// Passed a pointer to the first node in the tour.
// If first is NULL, return a size of 0.
int tourSize(Node* first)
{
	int tourSize = 0;
	Node* cursor = first;
	while(cursor != NULL){
		tourSize++;
		cursor = cursor->next;
	}
  	return tourSize;
}

// Calculate the Euclidean distance between two nodes.
// You can assume both a and b are both not NULL.
double distance(Node* a, Node* b)
{
	double distance = 0;
	double x1 = a->x;
	double y1 = a->y;
	double x2 = b->x;
	double y2 = b->y;
	distance = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
  	return distance;
}

// Calculate the total distance between all points in the tour.
// Since the tour is circular, this includes the distance from the last point back to the start.
// Passed a pointer to the first node in the tour.
// If first is NULL, return a tour length of 0.0.
double tourDistance(Node* first)
{
	double tourDistance = 0;
	if(first != NULL){
		Node* cursor = first;
		while(cursor->next != NULL){
			tourDistance += distance(cursor, cursor->next);		
			cursor = cursor->next;
		}
		tourDistance += distance(cursor, first);
	}
	return tourDistance;
}

// Add a new point after the point that it is closest to.
// If there is a tie, insert it after the first such point you find.
// Passed a pointer to the first node in the tour, NULL if creating a new tour.
// Returns pointer to the first node in the linked list after the addition.
Node* addNearestNeighbor(Node* first, double x, double y)
{
	double minDistance = DBL_MAX;  //Min distance for finding nearest neighbor
	Node* insertion = NULL;    //Node to be inserted after
	Node* newNode = malloc(sizeof(Node));  //The new node to be added
	newNode->x = x;
	newNode->y = y;
	if(first == NULL){ //If the linked list is empty, create a new tour
		first = newNode;
		newNode->next = NULL; 
		return first;
	} 	
   	Node* cursor = first;
	while(cursor != NULL){     //Calculate the distance between the new node and all other nodes in the tour
		double pointDistance = distance(newNode, cursor);
		if(pointDistance < minDistance){  //Updates the minDistance and insertion node if a closer node is found
			minDistance = pointDistance;
			insertion = cursor;
		}
		cursor = cursor->next;
	}
    //Relinks the linked list
    newNode->next = insertion->next;
	insertion->next = newNode;
	return first; 
}

// Add a new point after the point where it results in the least increase in tour length.
// If there is a tie, insert it after the first such point you find.
// Passed a pointer to the first node in the tour, NULL if creating a new tour.
// Returns pointer to the first node in the linked list after the addition.
Node* addSmallestIncrease(Node* first, double x, double y)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->x = x;
	newNode->y = y;

	if(first == NULL){ //If the linked list is empty, creates a new tour
		first = newNode;
		newNode->next = NULL; 
		return first;
	} 	

	double minChange = DBL_MAX;    //Smallest change in tour distance
	Node* before = NULL;   //The node that will be before the new node
   	Node* cursor = first;
	while(cursor != NULL){ //Computes the change in tour distance for the new node's insertion at all possible insertion points
		double change = 0;
		if(cursor->next == NULL){ //Handles the edge distance calculation where the cursor is the last node in the linked list
			change = (distance(cursor, newNode) + distance(newNode, first)) - distance(cursor, first);
			
		}else{    //Calculate change in total distance
			change = (distance(cursor, newNode) + distance(newNode, cursor->next)) - distance(cursor, cursor->next);
		}		

		if(change < minChange){   //Updates minChange and before if a better insertion point is found
			minChange = change;
			before = cursor;
		}
		cursor = cursor->next;
	}
	
        //Relinks the linked list
		newNode->next = before->next;
		before->next = newNode;
		return first;
	
}

// Deallocate all the memory of the Node structures in the linked list.
// Passed a pointer to the first node in the tour.
// If first is NULL, don't do anything.
void freeTour(Node* first)
{
	Node* cursor = first;
	Node* next = NULL;
	while(cursor != NULL){
		next = cursor->next;
		free(cursor);
		cursor = next;
	}
	free(cursor);
	free(next);
	first = NULL;
}

// Main function, you should NOT need to modify this.
// You may want to comment it out temporarily and insert your own test code during development.
int main(int argc, char** argv)
{
   // Default to inserting nodes right after the first node
   int heuristic = INSERT_FRONT;

   // If we get a command line argument it is setting the heurstic
   if (argc > 1)
      heuristic = atoi(argv[1]);

   // Start with an empty linked list
   Node* first = NULL;

   // Variables for reading in the next point from standard input
   double x = 0.0;
   double y = 0.0;

   // Read in points until we run out of data
   while (scanf("%lf %lf", &x, &y) == 2)
   {
      // Add the point to the linked list according to the heursitic set by the command line arg
      if (heuristic == INSERT_FRONT)
         first = addFront(first, x, y);
      else if (heuristic == NEAREST_NEIGHBOR)
         first = addNearestNeighbor(first, x, y);
      else if (heuristic == SMALLEST_INCREASE)
         first = addSmallestIncrease(first, x, y);
      else
      {
         printf("Invalid heuristic of %d!\n", heuristic);
         return 1;
      }
   }

   printTour(first);
   printf("Tour distance = %.4f\n", tourDistance(first));
   printf("Number of points = %d\n", tourSize(first));

   freeTour(first);
   first = NULL;

   return 0;
}
