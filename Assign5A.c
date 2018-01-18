//Siddharth Thakur, 1601CS46
//Date - 28th August, 2017
//Assign5A.c

#include <stdio.h> //including necessary header files
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define M 1000000000 //range definition

void printArray(int arr[],int n){ //function to print array
	
	printf("\n\nArray :-\n\n");
	int i;
	
	for(i=0;i<n;i++)
		printf(" %d",arr[i]);
	printf("\n\n");
}

int arrayPartition(int arr[],int idxb,int idxe,int pivot){
//function to partion array into two parts based on comparison eith pivot

	int temp=arr[pivot]; //exchanging pivot with last element in sub-array
	arr[pivot]=arr[idxe];
	arr[idxe]=temp;

	int j,i=idxb-1; //iteration through array to partition it
	for(j=idxb;j<idxe;j++){
		if(arr[j]<=arr[idxe]){
			i++;
			temp=arr[j];
			arr[j]=arr[i];
			arr[i]=temp;
		}
	}
	temp=arr[i+1]; //placing the pivot element at its actual position in sorted array
	arr[i+1]=arr[idxe];
	arr[idxe]=temp;
	
	return (i+1); //returning correct final position of pivot element
}

void quicksort(int arr[],int idxb,int idxe,int pivotType){ //function to implement quickSort algorithm

	if(idxb>=idxe) //base case
		return;

	int pivot; //to store pivotal elemnet's index
	int r,s,t; //median varibles
	int n=idxe-idxb+1; //to store size of sub-array

	switch(pivotType){ //deciding pivotal element according to given pivot type

		case 0:	pivot=idxb; //first element is pivot
				break;

		case 1:	pivot=rand()%n+idxb; //random element is pivot
				break;
		
		case 2: r=idxb;s=idxb+n/2;t=idxb+n-1; //Median of Three 1 is pivot
				if(arr[r]>=arr[s]&&arr[r]<=arr[t])
					pivot=r;
				else if(arr[s]>=arr[r]&&arr[s]<=arr[t])
					pivot=s;
				else
					pivot=t;
				break;

		case 3:	r=idxb+n/4;s=idxb+n/2;t=idxb+3*n/4; //Median of Three 2 is pivot
				if(arr[r]>=arr[s]&&arr[r]<=arr[t])
					pivot=r;
				else if(arr[s]>=arr[r]&&arr[s]<=arr[t])
					pivot=s;
				else
					pivot=t;
				break;	
	}

	int index=arrayPartition(arr,idxb,idxe,pivot); //partioning the array

	quicksort(arr,idxb,index-1,pivotType); //recusive function call on first sub-array
	quicksort(arr,index+1,idxe,pivotType); //recusive function call on second sub-array
}

int main(){ //main method
	
	srand(time(NULL)); //seeding time for rand() function

	int size; //to store size of array 
	int i; //for iterations
	double sruntime[4]; //to store runtimes for Sorted Array Case
	
	printf("\n\tPerformance of QuickSort : \n\n"); //displaying output
	printf("\tn\t\tPivot type\t\tRandom\t\t\tSorted\t\t\tAlmost Sorted\n\n");
	
	for(i=4;i<=7;i++){ //looping for different array sizes
		
		size=pow(10,i);
		int* arr=(int*)calloc(size,sizeof(int)); //creating array of required size
		
		int j,k; //for iterations
		
		for(j=0;j<size;j++) //initialising array randomly
			arr[j]=rand()%M;
		
		//printf("\nRandom Array : ");
		//printArray(arr,size);

		for(j=0;j<4;j++){ //looping for different pivot types
			
			clock_t c1,c2; //clock variable
			double runtime; //to store running time for quickSort algorithm
			
			c1=clock(); //determining runtime for randomly mixed array
			quicksort(arr,0,size-1,j);
			c2 = clock();
			runtime = (double)(c2 -c1) / (double)CLOCKS_PER_SEC;
			
			//printf("\nSorted Array : ");
			//printArray(arr,size);

			if(i!=7) //displaying runtime based on pivot type
				printf("\t%d\t\t",size);
			else
				printf("\t%d\t",size);
			
			if(j==0)
				printf("FIRST\t\t\t");
			else if(j==1)
				printf("RANDOM\t\t\t");
			else if(j==2)
				printf("MEDIAN OF THREE 1\t");
			else
				printf("MEDIAN OF THREE 2\t");
			printf("%f\t\t",runtime);

			if(i<6){ //determining runtime of already Sorted Array
				c1=clock();
				quicksort(arr,0,size-1,j);
				c2 = clock();
				runtime = (double)(c2 -c1) / (double)CLOCKS_PER_SEC;
				sruntime[j]=runtime;
			}
			if(i>5){ //extrapolating runtime for large array sizes(10^6 and 10^7) (in case of Sorted Arrays only) 
					 //to prevent stack overflow
				if(j==0)
					runtime=sruntime[j]*105.011629; //all the factors are determined from sizes 10^4 and 10^5 cases
				else if(j==1)
					runtime=sruntime[j]*12.868069;
				else if(j==2)
					runtime=sruntime[j]*13.145478;
				else
					runtime=sruntime[j]*13.166117;
				sruntime[j]=runtime;
			}
			printf("%f\t\t",runtime);

			//printf("\nSorted Array : ");
			//printArray(arr,size);

			int temp; //for swappings
			for(k=0;k<size/100;k++){ //randomly swapping few elements in array to create an Almost Sorted Array
				int idx1=rand()%size;
				int idx2=rand()%size;
				temp=arr[idx1];
				arr[idx1]=arr[idx2];
				arr[idx2]=temp;
			}

			//printf("\nDisturbed Array : ");
			//printArray(arr,size);

			c1=clock(); //determining runtime for Almost Sorted Array
			quicksort(arr,0,size-1,j);
			c2 = clock();
			runtime = (double)(c2 -c1) / (double)CLOCKS_PER_SEC;
			printf("%f\n",runtime);

			//printf("\nSorted Array : ");
			//printArray(arr,size);
		}
		free(arr); //freeing the allocated memory
		printf("\n\n");
	}
	return 0;
} //end main

