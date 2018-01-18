//Siddharth Thakur, 1601CS46, 7th August,2017
//Assign2Aa.c

#include <stdio.h>

int countOdd(long long int N){ //recursive function to find the count of odd digits in a number
	
	if(N==0) //base case
		return 0;

	int count=0;
	if((N%10)%2==1) //checking evenness of the digit
		count++;
	return (count+countOdd(N/10)); //recursive function call
}

int main(){ //main method
	
	long long int N; //to store the number
	printf("Enter the Number: "); //taking inputs
	scanf("%lld",&N);
	if(N<0)
		N*=-1;
	
	int count=countOdd(N); //function call
	printf("Count of odd digits in the number is : %d\n",count); //displaying output
	return 0;
} //end main

