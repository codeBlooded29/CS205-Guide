//Siddharth Thakur, 1601CS46
//Date-11th September,2017
//MidsemB.c

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int m,n; //to store number of rows and columns respectively

int compare(const void* a,const void* b){ //utility function for qsort library function to sort in ascending order
	
	int v1=*(int*)a;
	int v2=*(int*)b;

	if(v1<v2)
		return -1;
	else if(v1==v2)
		return 0;
	else
		return 1;
}

void createYoungTableau(int minHeap[],int size,int Young[][n]){ //Function to create Young Tableau from input array 
	
	int i,j;

	for(i=0;i<m;i++){
		for(j=0;j<n;j++)
			Young[i][j]=INT_MAX;
	}
	
	int level=log2(size);
	int idx=0;
	
	for(i=0;i<=level;i++){
		int r=(i>(m-1)?m-1:i),c=0;
		if(i>(m-1))
			c=1;
		for(j=0; j<pow(2,i) && idx<size && r>=0 && c<n ;j++){	
			Young[r][c]=minHeap[idx];
			r--;
			c++;
			idx++;
		}
	}
}

void printYoungTableau(int Young[][n]){ //Funtion to print Young Tableau
	
	int i,j;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(Young[i][j]<INT_MAX)
				printf("%d ",Young[i][j]);
			else
				printf("INF ");
		}
		putchar('\n');
	}
}

int insertNewElement(int* minHeap,int size,int Young[][n]){
	
	if(size==m*n){
		printf("\nYoung TAbleau already full!");
		return size;
	}
	
	int e; //to store element to be added
	printf("\nEnter new element to be added : ");
	scanf("%d",&e);
	
	int i,j;
	for(i=0;i<size;i++){ //determining position of element to be added in min-Heap
		if(minHeap[i]>e) 
			break;
	} //linear time implementation
	
	for(j=size;j>i;j--) //putting the element in its position
		minHeap[j]=minHeap[j-1];
	minHeap[i]=e; //linear time implementation
	size++; //increasing size of min-Heap
	
	createYoungTableau(minHeap,size,Young); //Creating valid Young Tableau after adding new element in original one

	return size;
}
	
int main(){ //main method

	printf("\nEnter 'm' & 'n' ( > 0 ) : "); //taking inputs
	scanf("%d %d",&m,&n);
	
	int i,j; //for iterations
	int size; //to store size of original numbers of inputs
	
	printf("\nEnter total no. of numbers to be input ( < m*n ) : ");
	scanf("%d",&size);
	
	//min-Heap implementation througn array
	int* minHeap=calloc(size,sizeof(int));
	printf("\nEnter numbers (space-separated integers)  : \n"); //putting input numbers in min-Heap
	for(i=0;i<size;i++)
		scanf("%d",&minHeap[i]);
	qsort(minHeap,size,sizeof(int),compare); //sorting the numbers to generate min-Heap
	
	int Young[m][n]; //to store input in Young Tableau format
	createYoungTableau(minHeap,size,Young); //creating Young Tableau from min-Heap
	
	printf("\nThe input in Young Tableau : \n\n"); //displaying original Young Tableau
	printYoungTableau(Young);

	size=insertNewElement(minHeap,size,Young); //inserting a new element in non-full Young Tableau

	printf("\nThe new Young Tableau : \n\n"); //displaying output	
	printYoungTableau(Young);
	putchar('\n');

	return 0;
} //end main

	





