#Name	  	- Jon Preuth
#Username	- jdpreuth
#Description    - This program reads positive integers in until a negative number is entered. The program then outputs the number of inputed numbers, the sum and product of the numbers, and the maximum value entered

#Initialize values for the program
	li	$t0, 0		#intIn	 - register to hold the most recent inputed number. Initialized to 0
	li	$t1, 0		#count	 - register to maintain the number of inputed numbers. Initialized to 0
	li	$t2, 0		#sum	 - register to maintain the sum of the inputed numbers. Initialized to 0
	li	$t3, 1		#product - register to maintain the product of the inputer nubers. Initialied to 1
	li	$t4, 0		#max	 - register to maintain the maximum inputed number. Initialized to 0

#Input loop to read in integer values
INPUT:
	#Read a value in and store it in $t0(intIn)
	li 	$v0, 5
	syscall 
	move 	$t0, $v0
	
	#Check to see if the number is greater than zero. If not, goto OUTPUT 
	bltz	$t0, OUTPUT
	
	#Process the inputed number
	addi	$t1, $t1, 1	#Increments the count variable 
	add	$t2, $t2, $t0	#Increase the sum by the inputed number
	mult	$t3, $t0	#Multiply the current product with the inputed number
	mflo	$t3		#Stores the previous multiplication as the new product
	
	#Check to see if the inputed number is greater than the current max value. If so goto SETMAX, else goto INPUT 
	bgt	$t0, $t4, SETMAX 
	b	INPUT
	
#Input loop exit that outputs the stored values
OUTPUT:
	#Check to see if at least one number was inputed. If not, terminate the program
	beq	$t1, $0, TERMINATE 
	
	#Output the count variable and then print a line feed
	li	$v0, 1
	move	$a0, $t1
	syscall 
	li	$v0, 11
	addi	$a0, $0, 0xA
	syscall
	
	#Output the sum and then print a line feed 
	li	$v0, 1
	move	$a0, $t2
	syscall 
	li	$v0, 11
	addi	$a0, $0, 0xA
	syscall
	
	#Output the product and then print a line feed
	li	$v0, 1
	move	$a0, $t3
	syscall 
	li	$v0, 11
	addi	$a0, $0, 0xA
	syscall
	
	#Output the max and then print a line feed 
	li	$v0, 1
	move	$a0, $t4
	syscall 
	li	$v0, 11
	addi	$a0, $0, 0xA
	syscall 
	
	# Terminate the program
	b	TERMINATE 

#Sets the max value to the most recent inputed number when this is called and then loop back for more input 
SETMAX:
	move	$t4, $t0
	b 	INPUT 

#Terminates the program 
TERMINATE:
	li	$v0, 10
	syscall 
	