//Siddharth Thakur, 1601CS46, 31st July, 2017
//assign1B.c

#include <stdio.h>

int ldigit=0; //global variable to store largest digit int the number

void LargeDigit(int num){ //recursive function to find the largest digit in the number
	if(ldigit<(num%10))
		ldigit=num%10;

	if(num/10==0)
		return;
	
	LargeDigit(num/10); //recursive call
	return;
}

int maxOf(int a,int b){ //function to find maximum of two numbers
	
	if(a>b)
		return a;
	else
		return b;
}

int main(){ //main method
	int N,result=0; //N : storage of number of boxes 		result : storage of maximum number of chocolates
	int i,j; //for iteration

	printf("\nEnter number of boxes : "); //taking input from user
	scanf("%d",&N);
	int arr[N];
	printf("\nEnter the no. of chocolates each box contain (space separated) : \n");
	for(i=0;i<N;i++){
		scanf("%d",&arr[i]);
	}

	//Now calculating maximum possible number of chocolates
	int result1=arr[0]; //to store max_sum including previous element
	int result2=0; //to store max_sum excluding previous element
	int curr_maxe; //to store current_max excluding current element

	for(i=1;i<N;i++){
		curr_maxe=maxOf(result1,result2);
		result1=result2+arr[i]; //max_sum including current element
		result2=curr_maxe; //max_sum excluding current element
	}

	//finalising the result	
	if(result1>=result2)
		result=result1;
	else
		result=result2;

	printf("\nOutput:- \n\nAnswer of Part-a = %d",result); //displaying the results

	LargeDigit(result);
	printf("\nLargest digit in answer of Part-a = %d\n\n",ldigit);

	return 0;
} //end main

