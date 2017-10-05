README
Problem One:
I have an add function and then a subtraction function that uses that add function. I successfully implemented all the test cases.

Problem Three:
My code needs to be run in g++ or use flag -std=99. I generally write g++ -o hw1q3 hw1q3.c to compile it. 
I have two helper functions that get the City and the State from the address line. 
In my add function, I made sure to go through first checking City names, then States, then lastnames, then firstnames like the TAs at office hours said so.
My add function takes the new node and puts it in the right location so I do not need another function to sort.
In my main function, I read in the input line by line and get the necessary information to put into a node. I then add it into the linked list and print out the appropriate information. I then add the three new nodes and then remove the two and reprint out the information. I then free the memory allocated.