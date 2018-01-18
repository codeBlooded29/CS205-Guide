//Siddharth Thakur, 1601CS46, 7th August,2017
//Assign2Bb.c

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

void max_min_SortingAlgorithm(int arr[],int firstIndex,int lastIndex){ 	//recursive function to sort by
																		//finding max and min in a list 
																		//and appending it to the two ends 
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
	return;
}

int modifiedBinarySearchElement(int arr[],int firstIndex,int lastIndex,int e){  //recursive function to search element in a
																				//list by dividing it into 2 parts
																				//of lengths two-fifth and three-fifth
	
	if(firstIndex>=lastIndex){ //base case
		if(e==arr[lastIndex])
			return lastIndex;
		else
			return -1;
	}

	//dividing list into two sublists of two-fifth and three-fifth size
	int mark=firstIndex+2*(lastIndex-firstIndex)/5; //first two-fifth sublist
	int index; //to store index of matching element
	
	if(e<arr[mark]) //if expected occurence in first sublist
		index=modifiedBinarySearchElement(arr,firstIndex,mark-1,e);
	else if(e==arr[mark]) //matching case
		index=mark;
	else
		index=modifiedBinarySearchElement(arr,mark+1,lastIndex,e); //if expected occurence in second sublist
	return index;
}

int main(){ //main method
	
	int N; //to store size of list
	int i; //for iterations
	
	printf("Enter the Size of Array (> 0): "); //taking inputs
	scanf("%d",&N);
	int arr[N]; 
	printf("Enter %d integers (space-separated) : \n",N);
	for(i=0;i<N;i++)
		scanf("%d",&arr[i]);

	max_min_SortingAlgorithm(arr,0,N-1); //recursively sorting the input array
	printf("\nSorted Array (non-decreasing order) : \n"); //displaying sorted list
	for(i=0;i<N;i++)
		printf("%d ",arr[i]);
	putchar('\n');
	
	int e; //element to be searched
	char choice='y'; //choice variable
	
	while(choice!='n'){ //searching 
		printf("\nEnter element to be searched : ");
		scanf("%d",&e);
		int index=modifiedBinarySearchElement(arr,0,N-1,e); //performing modified way of binary search
		if(index==-1){
			printf("Element Not Found! Want to try again? (y/n) ");
			scanf(" %c",&choice);
		}
		else{
			printf("Element found at index : %d \nWant to try again? (y/n) ",index);
			scanf(" %c",&choice);
		}
	}
	return 0;
} //end main

