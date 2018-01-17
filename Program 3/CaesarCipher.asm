#Name:	Jon Preuth
#ID:	jdpreuth
#This program uses a linked list stored in memory to apply a caeser cipher to all uppercase letters saved in the 
#linked list and prints out the result 

.text 
#Declare variables 
la	$t0, first	#Cursor: the pointer to the memory address of the current node being worked with. Initialized to the first node
lw	$t1, ($t0)	#Next: the pointer to the memory address of the next node in the linked list
add	$t5, $t0, 4	#CurrentChar: Keeps track of the current byte position of a given character in the string
lbu	$t2, ($t5) 	#Char: the ascii value of a given character in the string stored in the node . Iniitlizaed to the value of the first node
la	$t3, 4($t0)	#String: the string stored at a given node. Initialized to the value of the first node
lw	$t4, shift	#Key: the key to be used to encode/decode 


#Encode/Decode every uppercase letter based on the given key
SHIFT:
	beqz	$t2, NEXT_NODE	#Gets the next node if the current char is the null character 
	
	#Goes to the next character if the current character isn't an uppercase letter 
	blt	$t2, 65, NEXT_CHAR
	bgt	$t2, 90, NEXT_CHAR
	
	add	$t2, $t2, $t4	#Shifts the current character by the given key 
	
	#Wraps around if nessecary 
	blt	$t2, 65, ADD		
	bgt	$t2, 90, SUBTRACT
	
	#Save the byte back into the node and get the next char
	sb	$t2, ($t5)
	b	NEXT_CHAR

	#Wraps the caeser shift around from z to a
	SUBTRACT:
		addi	$t2, $t2, -26
		sb	$t2, ($t5)
		b	NEXT_CHAR
	
	#Wraps the caesar shift around from a to z
	ADD:
		addi	$t2, $t2, 26
		sb	$t2, ($t5)
		b	NEXT_CHAR
	
	#Gets the next character in the string 
	NEXT_CHAR:
		addi	$t5, $t5, 1
		lb	$t2, ($t5)
		b	SHIFT
	
	#Checks to see if theres a next node and if so, calls the function GET_NEXT_NODE and then encodes/decodes the new node 
	NEXT_NODE:
		blez	$t1, PRINT	#Outputs the encoded/decoded string after all nodes have been shifted 
		jal	GET_NEXT_NODE
		b	SHIFT 
	
#Outputs the contents of the linked list	
PRINT: 
	la	$t0, first	#Resets the cursor to the first node
	lw	$t1, ($t0)	#Resets the next pointer to the next node
	la	$t3, 4($t0)	#Loads the string stored in the first node
	
	#Iterates through the linked list and prints out the strings located at each node
	TRAVERSE:
		#Break if the cursor points at the last node
		blez	$t1, TERMINATE
	
		#Print string located at the node
		move	$a0, $t3
		li	$v0, 4
		syscall 
		
		#Print a space
		li	$v0, 11
		addi	$a0, $0, 32
		syscall 
		
		#Get the next node
		jal GET_NEXT_NODE
		
		#Continue traversing 
		b TRAVERSE

#Prints the string in the last node and then terminates the program
TERMINATE:
	#Print string located at the node
	move	$a0, $t3
	li	$v0, 4
	syscall
	
	#Terminate the program
	li	$v0, 10
	syscall 

#Function: Moves the cursor forward and sets new references 
GET_NEXT_NODE: 
	la	$t0, ($t1)	#Moves the cursor forward to the next node in the linked list
	lw	$t1, ($t0)	#Sets the next reference to the next node in the linked list
	add	$t5, $t0, 4	#Reset currentChar
	lbu	$t2, ($t5)	#Loads the char at currentChar into char
	la	$t3, 4($t0)	#Sets the value of string to the word stored at the node pointed to by the cursor
	jr	$ra 

### START DATA ###
.data
shift:  .word     -3
first:  .word     node2
        .asciiz   "HELLO"
node3:  .word     -1
        .asciiz   "CIPHER!!!"
node2:  .word     node3
        .asciiz   "CAESAR"

### END DATA ###