//Siddharth Thakur, 1601CS46
//Date - 25th September, 2017
//Assignment7B.c

#include <stdio.h> //including necessary header files
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct $ //structure definition for each natural number 
{
	int sum; //to store maximum sum
	int pathSize;
	int* path; //the path followed
}ELEMENT;

void printArray(int* arr, int idxb, int idxe){ //utility function to print elements of array
	int i;	
	printf("Array: ");	
	for(i=idxb;i<=idxe;i++)
		printf("%d ",arr[i]);
	putchar('\n');
}

int comparisonFunction(const void* a,const void* b){ //utility function for qsort library function

	int v1=*((int*)a);
	int v2=*((int*)b);

	if(v1<v2)
		return -1;
	else if(v1==v2)
		return 0;
	else
		return 1;
}

int main(){ //main method

	int n; //to store total number of elements
	printf("\nEnter the total number of elements 'n' ( > 1 )  : "); //taking inputs
	scanf("%d",&n);

	int i,j; //for iterations
	int* arr=(int*)calloc(n,sizeof(int)); //declaration of array
	printf("\nEnter %d elements (space-separated distinct +ve integers) : \n",n); //input of array elemets
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	
	int m; //to store max difference value
	printf("\nEnter 'm' ( +ve )  : "); //taking inputs
	scanf("%d",&m);

	qsort(arr,n,sizeof(int),comparisonFunction); //sorting the array in ascending order
	//printArray(arr,0,n-1);

	ELEMENT* sumArrayDP=(ELEMENT*)calloc(n,sizeof(ELEMENT)); //array to store max sum of pairs and corresponding pairs
	//upto each index of our input array
	
	sumArrayDP[0].sum=0; //base case
	sumArrayDP[0].pathSize=0;
	
	if((arr[1]-arr[0])<=m){ //base case
		
		sumArrayDP[1].sum=arr[0]+arr[1];
		sumArrayDP[1].pathSize=2;
		sumArrayDP[1].path=(int*)calloc(sumArrayDP[1].pathSize,sizeof(int));
		for(j=0;j<sumArrayDP[1].pathSize;j++)
			sumArrayDP[1].path[j]=arr[j];
	}

	else{
		sumArrayDP[1].sum=0;
		sumArrayDP[1].pathSize=0;	
	}

	i=2; //implementation of O(NlogN) dp algorithm
	while(i<n){ //using bottom-Up approach of Dynamic Programing to calculate
		//max sum of pairs and corresponding pairs upto each index of our input array

		if((arr[i]-arr[i-1])<=m){ //if pairing possible based on condition

			sumArrayDP[i].sum=(sumArrayDP[i-2].sum+arr[i-1]+arr[i]);
			
			sumArrayDP[i].pathSize=sumArrayDP[i-2].pathSize+2;
			
			sumArrayDP[i].path=(int*)calloc(sumArrayDP[i].pathSize,sizeof(int));
			for(j=0;j<sumArrayDP[i-2].pathSize;j++) //storing elements forming pairs
				sumArrayDP[i].path[j]=sumArrayDP[i-2].path[j];
			sumArrayDP[i].path[j]=arr[i-1];
			sumArrayDP[i].path[j+1]=arr[i];
		}

		else{ //if pairing not possible

			sumArrayDP[i].sum=sumArrayDP[i-1].sum;
			
			sumArrayDP[i].pathSize=sumArrayDP[i-1].pathSize;
			
			sumArrayDP[i].path=(int*)calloc(sumArrayDP[i].pathSize,sizeof(int));
			for(j=0;j<sumArrayDP[i-1].pathSize;j++) //storing elements forming pairs
				sumArrayDP[i].path[j]=sumArrayDP[i-1].path[j];
		}
		i++;
	}

	printf("\nThe maximum sum of disjoint pairs = %d\n",sumArrayDP[n-1].sum); //displaying output
	printf("\nThe %d disjoint pairs are :-\n",sumArrayDP[n-1].pathSize/2);
	j=1;
	for(i=0;i<sumArrayDP[n-1].pathSize;i+=2){ //displaying disjoint pairs giving max sum
		printf("%d) ( %d , %d )\n",j,sumArrayDP[n-1].path[i],sumArrayDP[n-1].path[i+1]);
		j++;
	}
	putchar('\n');

	return 0;
} //end main

