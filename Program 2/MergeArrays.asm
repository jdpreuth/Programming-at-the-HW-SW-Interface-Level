#Name	- Jon Preuth
#ID	- jdpreuth
#This program takes in two sorted arrays, merges them together, and prints the new array in both ascending and descending order

.text 
#Declare Variables
#Left Array (in1)
li	$t0, 0			#leftArrayIndex -> index variable for in1
lw	$t1, len1		#leftArraySize variable -> size variable for in1
	add 	$t1, $t1, $t1	#Mulitply leftArraySize to account for byte offset
	add 	$t1, $t1, $t1
li	$t2, 0			#leftArrayValue -> value of in1 at a given index
#Right Array (in2)
li	$t3, 0			#rightArrayIndex -> index variable for in2
lw	$t4, len2		#rightArraySize variable -> size variable for in2
	add 	$t4, $t4, $t4	#Mulitply rightArraySize to account for byte offset
	add 	$t4, $t4, $t4
li	$t5, 0			#rightArrayValue -> value of in2 at a given index
#Output Array
li	$t6, 0			#outputIndex -> index variable for out
li	$t7, 0			#outputSize -> size variable for out

#Main merge section to combine the arrays together
MERGE:
	bge	$t0, $t1, FINISH_RIGHT	#Check to see if the leftIndex is valid
	bge	$t3, $t4, FINISH_LEFT	#Check to see if the rightIndex is valid

	#Compares the values of the two arrays and puts one of them into the output array
	COMPARE_LEFT_RIGHT:
		lw	$t2, in1($t0)	#loads leftArrayValue with the value of in1 at leftArrayIndex
		lw	$t5, in2($t3)	#loads rightArrayValue with the value of in2 at rightArrayIndex
		
		bge 	$t2, $t5, ADD_RIGHT	#Determines if the left or right value is smaller
		
		#Adds the value of the left array to out
		ADD_LEFT:
			sw	$t2, out($t6)	#save leftArrayValue to out
			addi	$t6, $t6, 4	#increment outputIndex
			addi	$t7, $t7, 4	#increment outputSize
			addi	$t0, $t0, 4	#increment leftArrayIndex
			b	MERGE		
								
		#Adds the value of the right array to out
		ADD_RIGHT:
			sw	$t5, out($t6)	#save rightArrayValue to out
			addi	$t6, $t6, 4	#increment outputIndex
			addi	$t7, $t7, 4	#increment outputSize
			addi	$t3, $t3, 4	#increment rightArrayIndex
			b	MERGE		
	
	#Puts the remaining values in the right array into out
	FINISH_RIGHT:
		bge	$t3, $t4, OUTPUT	#Exits the loop once all the values have been iterated through
		lw	$t5, in2($t3)		#loads rightArrayGValue with the value of in2 at rightArrayIndex
		sw	$t5, out($t6)		#save rightArrayValue to out
		addi	$t6, $t6, 4		#increment outputIndex
		addi	$t7, $t7, 4		#increment outputSize
		addi	$t3, $t3, 4		#increment rightArrayIndex
		b	FINISH_RIGHT		
	
	#Puts the remaining values in the left array into out
	FINISH_LEFT:
		bge	$t0, $t1, OUTPUT	#Exits the loop once all the values have been iterated through
		lw	$t2 in1($t0)		#loads leftArrayGValue with the value of in2 at leftArrayIndex
		sw	$t2, out($t6)		#save leftArrayValue to out
		addi	$t6, $t6, 4		#increment outputIndex
		addi	$t7, $t7, 4		#increment outputSize
		addi	$t0, $t0, 4		#increment leftArrayIndex
		b	FINISH_LEFT	
	
#Outputs the sorted array in ascending and descending order
OUTPUT:
	
	li	$t6, 0		#Sets outputIndex to 0 to prepare to iterate through the array
	
	#Prints the contents of out in ascending order
	PRINT_FORWARD:
		bge	$t6,$t7, PREP_PRINT_BACKWARD	#Brake the loop after going through every index
		#Print the value of out[outputIndex]
		lw	$a0, out($t6)		#Prepares the value at out[outputIndex] to be printed
		li	$v0, 1			#Tells syscall to print an int
		syscall 
		#Print a space
		li      $v0, 11     		# Tell syscall to print a character
		addi    $a0, $0, 32 		# ASCII code 32 is a space
		syscall
		#Incremement outputIndex and loop
		addi	$t6, $t6, 4
		b 	PRINT_FORWARD
	
	#Reset values to print backwards
	PREP_PRINT_BACKWARD:
		addi	$t6, $t6, -4		#Decrements outputIndex so its equal to the last position in out
		#Print a line
		li      $v0, 11     		# syscall 11 prints character in $a0
		addi    $a0, $0, 10 		# ASCII code 10 is a line feed
		syscall
	
	#Prints the values of out in descending order
	PRINT_BACKWARD:
		bltz	$t6, TERMINATE		#Brakes the loop after iterating through every index
		#Print the value of out[outputIndex]
		lw	$a0, out($t6)		#Prepares the value at out[outputIndex] to be printed
		li	$v0, 1			#Tells syscall to print an int
		syscall 
		#Print a space
		li      $v0, 11     		# Tell syscall to print a character
		addi    $a0, $0, 32 		# ASCII code 32 is a space
		syscall
		#Decrement outputIndex and loop
		addi	$t6, $t6, -4
		b 	PRINT_BACKWARD

TERMINATE:
	li	$v0, 10
	syscall 
	

.data
len1:   .word   0
in1:    .word   100
len2:   .word   0
in2:    .word   50
out:    .space  0


