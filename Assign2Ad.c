//Siddharth Thakur, 1601CS46, 7th August,2017
//Assign2Ad.c

#include <stdio.h>

int maxFunction(int arr[],int firstIndex,int lastIndex){ //recursive function to find maximum element in a list
	
	if(firstIndex>=lastIndex) //base case
		return firstIndex;

	int temp=maxFunction(arr,firstIndex+1,lastIndex); //recursively finding maximum in sublist
	if(arr[firstIndex]<arr[temp]) //checking for maximum
		firstIndex=temp;
	return firstIndex;
}

int minFunction(int arr[],int firstIndex,int lastIndex){ //recursive function to find minimum element in a list
	
	if(firstIndex>=lastIndex) //base case
		return firstIndex;

	int temp=minFunction(arr,firstIndex+1,lastIndex); //recursively finding minimum in sublist
	if(arr[firstIndex]>arr[temp]) //checking for minimum
		firstIndex=temp;
	return firstIndex;
}

void max_min_SortingAlgorithm(int arr[],int firstIndex,int lastIndex){  //recursive function to sort by
																		//finding max and min in a list and
																		//appending it to the two ends
																		//of the sorted sublist
	if(firstIndex>=lastIndex) //base case
		return;
	
	int max=maxFunction(arr,firstIndex,lastIndex); //recursively finding maximum in sublist
	int min=minFunction(arr,firstIndex,lastIndex); //recursively finding minimum in sublist
	
	if(max==firstIndex) //max index protection step
		max=min;
	int temp=arr[firstIndex]; //appending minimum at beginning and maximum at end of the list
	arr[firstIndex]=arr[min];
	arr[min]=temp;
	temp=arr[lastIndex];
	arr[lastIndex]=arr[max];
	arr[max]=temp;
	
	max_min_SortingAlgorithm(arr,firstIndex+1,lastIndex-1); //recursive function call
}

int main(){ //main method

	int N; //to store input number
	int i; //for iterations

	printf("Enter the Size of Array (> 0): "); //taking inputs
	scanf("%d",&N);
	int arr[N]; 
	printf("Enter %d integers (space-separated) : \n",N);
	for(i=0;i<N;i++)
		scanf("%d",&arr[i]);

	max_min_SortingAlgorithm(arr,0,N-1); //fuction call
	printf("\nSorted Array (non-decreasing order) : \n"); //displaying output
	for(i=0;i<N;i++)
		printf("%d ",arr[i]);
	putchar('\n');
	return 0;
} //end main

