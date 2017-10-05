#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
//Jason Wang
int add (int x, int y) {
	int added = 0;
	added = x^y;
	while ((x & y) != 0) {
		int temp = x & y;
		y = temp << 1;
		x = added;
		added = x ^ y;
	}
	return added;
}

int subtract(int x, int y) {
        y = add(~y, 1);
        int subtracted = 0;
        subtracted = add(x, y);
        return subtracted;
}
 
main() {
	//int x = 13441;
	//int y = 12;
	//int s = 0;
	//s = subtract(x,y);
	//printf("Subtraced=%d\n",s);
	//printf("\n");
	int count = 0;
	int failed = 0; 
	while (count < 1000) {
		int y = rand() % (INT_MAX/2);
		int x = y + rand() % (INT_MAX/2);
		int realsub = x - y;
		int bitsub = subtract(x, y);
		if (realsub != bitsub) {
			printf("The two values are not the same!\n");
			failed = 1;
			break;
		}
		count++;
	}
	if(failed == 0) {
		printf("All the numbers are the same! Success!\n");   
	}			
}
