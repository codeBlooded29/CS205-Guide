//Siddharth Thakur, 1601CS46, 7th August,2017
//Assign2C.c

#include <stdio.h>

unsigned long long int steps=0; //global variable to count number of steps performed 

long long int recursiveFunction(long long int N){ //recursive function to perform required operations
	
	if(N==1) //base case
		return 1;

	if(N%2==0) //propagation
		N/=2;
	else
		N=N*3+1;
	printf("Next value is : %lld\n",N); //displaying generated values
	steps++;

	long long int finalValue=recursiveFunction(N); //recursively calling the function
	return finalValue;
}

int main(){ //main method
	
	long long int N; //to store the number
	printf("Enter the Number: "); //taking input
	scanf("%lld",&N);
	
	while(N<1){ //checking validity of input
		printf("\nError! Input value should be greater than 1. Try Again!\n");
		printf("\nEnter the Number: ");
		scanf("%lld",&N);
	}

	printf("\nOutput:-\nInitial value is : %lld\n",N); //displaying output
	long long int finalValue=recursiveFunction(N); //function call
	printf("Final value is : %lld, number of steps = %llu\n",finalValue,steps);
	return 0;
} //end main

