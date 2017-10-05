  .text
  .align 2
main:
  la $a0, in_string #get the string to print
  li $v0, 4
  syscall #print out the string

  li $v0, 8 #read in the string
  la $a0, buffer
  li $a1, 256 #allocate the amount of space for the input string
  move $t0, $a0 #put the string into t0
  syscall

addi $sp, $sp, -4
sw $ra, 0($sp)
jal iter #go to the iter
addi $v0, $v0, -1
move $t2, $v0
li $v0,1 # print int
move $a0, $t2 #move the output to $a0
syscall #print the int in $a0

li $v0,10 #end program
syscall

iter:
  addi $sp, $sp, -4 #allocate room on stack
  sw $ra, 0($sp) #save the return address to the stack
  lbu $t1, 0($t0) #get the first character
  bne $t1, $zero, ELSE #check to see if it is reached the end of string
  li $v0, 0 #set the return value to 0
  addi $sp, $sp, 4 ##reformat stack pointer
  jr $ra

ELSE:
  addi $t0, $t0, 1 #remove the first character
  jal iter
  addi $v0, $v0, 1 #add 1 to the strlen
  lw $ra, 0($sp) #load from memory to return address
  addi $sp, $sp, 4
  jr $ra

  .data
  .align 2
in_string: .asciiz "Enter a string:\n"
buffer: .space 256
