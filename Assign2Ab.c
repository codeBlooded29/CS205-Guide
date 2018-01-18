//Siddharth Thakur, 1601CS46, 7th August,2017
//Assign2Ab.c

#include <stdio.h>

int maxDigit; //to store maximum digit in a number
int minDigit; //to store minimum digit in a number

void max_min_Digit(long long int N){ //function to determine both max and min digits in a number
	
	if(N==0) //base case
		return; 
	
	if(maxDigit<N%10) //finding maximum digit
		maxDigit=N%10; 

	if(minDigit>N%10)
		minDigit=N%10; //finding minimum digit		
	
	max_min_Digit(N/10); //recursive function call
	return;	
}

int main(){ //main method
	
	long long int N; //to store the input number
	printf("Enter the Number: "); //taking inputs
	scanf("%lld",&N);
	if(N<0)
		N*=-1;
	
	maxDigit=N%10; //initialisation
	minDigit=N%10;

	max_min_Digit(N/10); //function call
	printf("Maximum digit in the number is : %d\n",maxDigit); //displaying outputs
	printf("Minimum digit in the number is : %d\n",minDigit);
	return 0;
} //end main

