//Siddharth Thakur, 1601CS46, 7th August, 2017
//Assign2Ac.c

#include <stdio.h>

void binaryEquivalent(int N){ //recursive to function to find and print binary equivalent of a number
	if(N==0){ //base case
		printf("%d",N);
		return;
	}

	binaryEquivalent(N/2); //recursive function call 
	printf("%d",N%2); //printing binary_digit
}

int main(){ //main method
	
	int N; //to store the input number
	printf("\nEnter the Number (positive) : "); //taking inputs
	scanf("%d",&N);

	printf("Binary Equivalent of the number : "); //displaying output
	binaryEquivalent(N); //function call
	putchar('\n');
	return 0;
} //end main

