.text
.align 2
main:
  li $s1, 1 #To compare to 1

  li $v0, 9 #allocate memory
  li $a0, 100 #100 bytes in the heap
  syscall
  move $s0, $v0 #first struct is in $s0

  li $v0, 8 #read in the string
  la $a0, 0($s0) #put the string in $a0
  li $a1, 60
  syscall
#  move $s5, $a0 #put the string into $s5

  la $t0, 0($s0); #make $t0 the string inputted
  la $t1, finished; #make $t1 DONE
  jal strcomp #go to strcomp
  beq $t6, $zero, END #if $v0 is 0 then go to END
#  sw $s5, 0($s0) #store the string into the first 4 bytes of the node

  li $v0, 6 #get the points
  syscall
  mov.s $f1, $f0
#  swc1 $f0, 4($s0) #put the points into the next 4 bytes of the node

  li $v0, 6 #get the rebounds
  syscall
  mov.s $f2, $f0
#  swc1 $f0, 8($s0) #put the rebounds into the next 4 bytes of the node

  li $v0, 6 #get the turnovers
  syscall
  mov.s $f3, $f0
#  swc1 $f0, 12($s0) #put the turnovers into the next 4 bytes of the node

  add.s $f4, $f1, $f2
  div.s $f5, $f4, $f3 #$f5 should contain the value of the head node
  swc1 $f5, 60($s0)
  sw $zero, 64($s0) #for the first node make the pointer to next node 0

NOTDONE:
  li $v0, 9 #allocate memory for next node
  li $a0, 100 #100 bytes
  syscall
  move $s2, $s0 #make curr node
  move $s4, $v0 #put the struct into $s4
  li $v0, 8 #read in the string
  la $a0, 0($s4) #put the string in $a0
  li $a1, 60
  syscall
#  move $s5, $a0 #put the address into $s5

  la $t0, 0($s4); #make $t0 the string inputted
  la $t1, finished; #make $t1 DONE
  jal strcomp #go to strcomp
  beq $t6, $zero, END #if $v0 is 0 then go to END
#  sw $s5, 0($s4) #store the string into the first 4 bytes of the node

  li $v0, 6 #get the points
  syscall
  mov.s $f1, $f0
#  swc1 $f0, 4($t5) #put the points into the next 4 bytes of the node

  li $v0, 6 #get the rebounds
  syscall
  mov.s $f2, $f0
#  swc1 $f0, 8($t5) #put the rebounds into the next 4 bytes of the node

  li $v0, 6 #get the turnovers
  syscall
  mov.s $f3, $f0
#  swc1 $f0, 12($t5) #put the turnovers into the next 4 bytes of the node
  add.s $f4, $f1, $f2
  div.s $f6, $f4, $f3 #$f6 should contain the value of the adding node
  swc1 $f6, 60($s4)
  sw $zero, 64($s4) #make pointer to next node null

  lwc1 $f5, 60($s0) #get head value
  c.le.s $f5, $f6 #if head value is less than adding value make code == 1
  bc1t PUTHEAD #if code == 1
  bc1f NOTHEAD #if code == 0

AFTER:
  lw $t7, 64($s4)
  beq $t7, $zero, LAST #if adding node still points to zero go to LAST
GOBACK:
  j NOTDONE #go back to start of loop

END:
  move $s7, $s0 #create temp head node
loop:
  beqz $s7, COMP #check to see if we reached the end of the linked list
  la $a0, 0($s7) #get the string from the node
  move $t1, $a0
removeend: #remove the \n at the end of the name
  lbu $t2, 0($t1) #get the first character into $t2
  addi $t1, $t1, 1 #move on to next character
  bnez $t2, removeend #if not at end of string go back to loop
  addi $t1, $t1, -2 #go back 2 for \n
  sb $0, 0($t1) #add the NULL character there to show it is the end of the string

  li $v0, 4 #print out the string
  syscall
#  li $t0, 0
  la $a0, aspace #add a space to the end of the string 
  li $v0, 4
  syscall

  li $v0, 2 #get the value
  l.s $f12, 60($s7)
  syscall
  la $a0, seperator #newline
  li $v0, 4
  syscall
  lw $s7, 64($s7) #get the next node
  b loop

COMP:
  la $a0, 0($s0) #get the MVP
  li $v0, 4 #print out the MVP
  syscall
  li $v0, 10 #end
  syscall

PUTHEAD:
  sw $s0, 64($s4) #make the adding node point to head
  move $s0, $s4 #make the head now equal to the adding node
  j AFTER

NOTHEAD:
  lw $s6, 64($s2) #get the next node
  beq $s6, $zero, AFTER #if the next node is zero then we are at end of list
  lwc1 $f8, 60($s2) #get the value of the current node
  lwc1 $f9, 60($s6) #get the value of the next node
  c.le.s $f6, $f9 #if value of adding node is less than value of next node set code = 1
  bc1t CONTINUE #if code = 1, go to CONTINUE
  bc1f PUTIN #if code = 0, go to PUTIN

CONTINUE:
  move $s2, $s6 #make current node equal to the next node
  j NOTHEAD

PUTIN:
  sw $s6, 64($s4) #make the adding node point to the next node
  sw $s4, 64($s2) #make the current node point to the adding node
#  move $s2, $s4 #make the adding node the current node
  j AFTER

LAST:
  sw $s4, 64($s2) #make the current node point to the adding node
  j GOBACK

strcomp:
  lbu $t2, 0($t0) #get first characters from both strings
  lbu $t3, 0($t1)
  beq $t3, $zero, SAME #check to see if reached end of DONE
  addi $t0, $t0, 1 #increment to next characters
  addi $t1, $t1, 1
  seq $t4, $t2, $t3 #check to see if the characters are the same
  beq $t4, $s1, strcomp #if they are the same then continue through both strings
  bne $t4, $s1, notsame #if not then set $t6 to 1 saying its not DONE

notsame:
  li $t6, 1 #set $t6 to 1
  jr $ra

SAME:
  li $s3, 10 #check if reached end of input string
  bne $t2, $s3, notsame #if we reached DONE but the input word is DONEwas or something
  li $t6, 0 #make $t6 0
  jr $ra

  .data
  .align 2
buffer: .space 60
finished: .asciiz "DONE"
seperator: .asciiz "\n"
aspace: .asciiz " "
