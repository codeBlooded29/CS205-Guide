//Siddharth Thakur, 1601CS46, 7th August,2017
//Assign2B.c

#include <stdio.h>

int sumOfDigits(long long int N){ //recursive function to calculate sum of digits of a number
	
	if(N==0) //base case
		return 0;
	
	long long int sum=0;
	sum+=N%10; //intialisation
	return (sum+sumOfDigits(N/10)); //recursive function call
}

void recursiveSumOfDigits(long long int N){ //recursive function to find and print repetitive sum of digits of a number
	
	if(N/10==0){ //base case
		printf("%lld ",N);
		return;
	}

	long long int sum=sumOfDigits(N); //function call to find sum of digits
	printf("%lld -> ",sum); //printing repetitive sum
	recursiveSumOfDigits(sum); //recursive function call
}

int main(){ //main method
	
	long long int N; //to store input numbers
	printf("Enter the Number: "); //taking inputs
	scanf("%lld",&N);
	printf("Recursive Sum of Digits : %lld -> ",N); //displaying output
	recursiveSumOfDigits(N); //function call
	putchar('\n');
	return 0;
} //end main

