//Siddharth Thakur, 1601CS46
//Date - 25th September, 2017
//Assignment7A.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printArray(int* arr, int idxb, int idxe){ //utility function to print elements of array
	int i;	
	printf("Array: ");	
	for(i=idxb;i<=idxe;i++)
		printf("%d ",arr[i]);
	putchar('\n');
}

void insertionSort(int arr[],int idxb, int idxe){
 //function to use insertion sort to sort in ascending order the group of 5 elements

	int i;
	for(i=idxb+1;i<idxe-idxb+1;i++){ //insertion sort algorithm
		int key=arr[i];
		int j=i-1;
		while(j>=idxb&&arr[j]>key){
			arr[j+1]=arr[j];
			j--;
		}
		arr[j+1]=key;
	}
}

int ithOrderStatistics(int* arr, int size, int idx){
//recursive funtion to determine ith smallest element in an array by 'median of 5' and 'median of medians' method
//in linear time in worst case also ( O(n) time in all the cases including the worst case )

	if(size<=1) //base case
		return arr[0];

	int numberOfmedians=(int)ceil(size/5.0); //number of sets of 5 possible
	
	int* medians=(int*)calloc(numberOfmedians,sizeof(int)); //to hold medians of groups of 5 elements
	
	int i=0,j=0; //for iterations
	while(i<(size-size%5)){
		
		insertionSort(arr,i,i+4); //sorting 5 elements in each group to determine their median
		medians[j]=arr[i+2];
		i+=5;
		j++;
	}
	insertionSort(arr,i,size-1); //last group analysis
	medians[j]=arr[i+(size-i)/2];

	int medianOfmedian=medians[(numberOfmedians-1)/2]; //determining median of medians

	int *arr1; //to store first sub-array (elements less than median of medians)
	int *arr2; //to store second sub-array (elements equal to median of medians)
	int *arr3; //to store third sub-array (elements greater than median of medians)
	
	int i1=0,i2=0,i3=0;
	for(i=0;i<size;i++){ //partitioning the array around median of medians

		if(arr[i]<medianOfmedian){ //sub-array of elements less than median of medians
			i1++;
			if(i1==1)
				arr1=(int*)calloc(1,sizeof(int));
			else
				arr1=(int*)realloc(arr1,i1*sizeof(int));
			arr1[i1-1]=arr[i];
		}

		if(arr[i]==medianOfmedian){ //sub-array of elements equal to median of medians
			i2++;
			if(i2==1)
				arr2=(int*)calloc(1,sizeof(int));
			else
				arr2=(int*)realloc(arr2,i2*sizeof(int));
			arr2[i2-1]=arr[i];
		}

		else if(arr[i]>medianOfmedian){ //sub-array of elements greater than median of medians
			i3++;
			if(i3==1)
				arr3=(int*)calloc(1,sizeof(int));
			else
				arr3=(int*)realloc(arr3,i3*sizeof(int));
			arr3[i3-1]=arr[i];
		}
	}

	int result; //to store ith smallest element
	
	if(idx<i1){ //checking if result lies in first sub-array
		result=ithOrderStatistics(arr1,i1,idx); //recursive function call
		return result;
	}
	else if((i1-1)<idx&&idx<(i1+i2)){ //checking if required element is equal to median of medians
		result=medianOfmedian;
		return result;
	}
	else{ //if the result lies in third-subarray
		result=ithOrderStatistics(arr3,i3,idx-i1-i2); //recursive fuction call
		return result;
	}
	
	free(arr1); //freeing the allocated memory to prevent memory leaks
	free(arr2);
	free(arr3);
}

int main(){ //main method
	
	int n; //to store total number of elements

	printf("\nEnter total number of elements ( > 0 )  : "); //taking inputs
	scanf("%d",&n);
	
	int i;
	int* arr=(int*)calloc(n,sizeof(int)); //declaration of array
	printf("\nEnter %d elements (space-separated integers) : \n",n); //input of array elemets
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);

	char ch='y';
	while(ch=='y'){ //determining ith order statistics
		
		int idx; //taking inputs 
		printf("\nEnter 'i' for 'i'th order statistic (array index starting from 1) ( 1 <= i <= %d ) : ",n);
		scanf("%d",&idx);
		idx--;

		int result = ithOrderStatistics(arr,n,idx);
		printf("\nThe %dth smallest element = %d\n\n",idx+1,result); //displaying result
		printf("Continue? (y/n) : ");
		scanf(" %c",&ch);
	}
	putchar('\n');
	
	return 0;
} //end main

