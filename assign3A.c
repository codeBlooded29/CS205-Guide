//Siddharth Thakur, 1601CS46
//Date - 14th August, 2017
//assign3A.c

#include <stdio.h> //importing necessary header files
#include <stdlib.h>
#include <string.h>
#include <math.h>

int* arr; //global array to store original data
int N; //to store size of original array
int K; //to store index of required element (here median (N/2 th element))

int find_median(int arr[],int size,int offset){ //recursive function to find median of array 

	int i,i1=0,i2=0; //for iterations
	
	if(size==1) //base case
		return arr[size-1];

	srand(time(NULL)); //choosing pivot randomly
	int index=rand()%size;

	
	int *arr1; //to store first sub-array
	int *arr2; //to store second sub-array
	
	for(i=0;i<size;i++){ //partitioning the array around pivot
		
		if(i==index)
			continue;

		if(arr[i]<=arr[index]){ //sub-array of elements less than or equal to pivot
			i1++;
			if(i1==1)
				arr1=(int*)calloc(1,sizeof(int));
			else
				arr1=(int*)realloc(arr1,i1*sizeof(int));
			arr1[i1-1]=arr[i];
		}
		else if(arr[i]>arr[index]){ //sub-array of elements greater than pivot
			i2++;
			if(i2==1)
				arr2=(int*)calloc(1,sizeof(int));
			else
				arr2=(int*)realloc(arr2,i2*sizeof(int));
			arr2[i2-1]=arr[i];
		}
	}

	int median; //to store median

	if((i1+offset)==K){ //checking if choosen pivot is at median postion
		median=arr[index];
		return median;
	}

	if(offset<=K&&K<=(i1+offset)){ //checking if median lies in first sub-array
		median=find_median(arr1,i1,offset); //recursive function call
		return median;
	}
	else{ //if the median lies in second-subarray
		median=find_median(arr2,i2,offset+i1+1); //recursive fuction call
		return median;
	}
}

int main(){ //main method

	srand(time(NULL));
	
	printf("\nEnter number of elements in array ( > 0 ) : "); //taking inputs
	scanf("%d",&N);
	
	arr=(int*)calloc(N,sizeof(int)); //alloctaing required amount of memory

	printf("\nEnter the elements of array (space separated +ve integers) : \n");
	int i;	
	for(i=0;i<N;i++)
		scanf("%d",&arr[i]);

	K=(N-1)/2; //required index in sorted array (here median)
	int median=find_median(arr,N,0); //function call to find median
	
	printf("\nMedian of input data is : %d\n\n",median); //displaying output
	
	return 0; 
} //end main
	
