//Siddharth Thakur, 1601CS46
//Date - 28th August,2017
//Assign5B.c

#include <stdio.h> //importing required header files
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct NODE{ //definition of a PLAYER
	char name[100];
	unsigned int runs;
}PLAYER;
typedef PLAYER* PLAYERPTR;

void displayArray(PLAYER array[],size_t size){ //function to display contents of Array

	printf("\n\nSorted Way:\n\n\tPlayer Name\tRuns\n\n");
	size_t i;
	for(i=0;i<size;i++)
		printf("%15s\t\t%u\n",array[i].name,array[i].runs);
	printf("\n\n");
}

void countingSortRuns(PLAYER array[],size_t size,unsigned int placeValue){
//function to counting sort array based on placed digits in the numbers

	unsigned int digitCount[10]={0}; //array to hold count of digit occurences
	
	PLAYER sortedArray[size]; //temporary array to hold sorted array based on faceValue of the digit at given placeValue

	size_t i; //for iterations
	
	i=0;
	while(i<size){ //keeping count of occurrences of digits
		digitCount[(array[i].runs/placeValue)%10]++;
		i++;
	}
	
	i=1;
	while(i<10){ //modifying the array to hold position in sorted array for a digit
		digitCount[i]+=digitCount[i-1];
		i++;
	}
	
	i=size-1;
	while(i>0){ //now putting elements in temporary array based on position given by digitCount array
		sortedArray[digitCount[(array[i].runs/placeValue)%10]-1]=array[i];
		digitCount[(array[i].runs/placeValue)%10]--;
		i--;
	}
	sortedArray[digitCount[(array[0].runs/placeValue)%10]-1]=array[0];

	i=0;
	while(i<size){ //transfering sorted contents from temporary array to original array 
		array[i]=sortedArray[i];
		i++;
	}
} //end function countingSort

void radixSortRuns(PLAYER array[],size_t size,unsigned int maxRuns){
//function to radix sort PLAYER array on basis of runs

	unsigned int i=1;//for iterations
	while(maxRuns/i>0){
		 //running counting sort on each positioned digit from lowest placeValued digit to highest placeValued digit
		countingSortRuns(array,size,i);
		i*=10; //increasing placeValue
	}
} //end function radixSortRuns

void sortNames(PLAYER array[],size_t idxb,size_t idxe){
//function to sort players on basis of names in case of equal runs by them

	size_t min=strlen(array[idxb].name); //to store minimum length 

	size_t i,j,k; //for iterations

	for(i=idxb+1;i<=idxe;i++){ //finding minimum length of names
		if(min>strlen(array[i].name))
			min=strlen(array[i].name);
	}

	for(i=idxb;i<=idxe;i++){ //sorting on basis of names of players
		for(j=idxb+1;j<=idxe;j++){ //comparing names
			int flag=0;
			for(k=0;k<min;k++){ //comparing first m characters of all the names to break tie
				
				if(tolower(array[j-1].name[k])<tolower(array[j].name[k])){ //tie breaker 1
					flag=1;
					break;
				}
				if(tolower(array[j-1].name[k])==tolower(array[j].name[k]))
					continue;
				
				if(tolower(array[j-1].name[k])>tolower(array[j].name[k])){ //tie breaker 2
					PLAYER temp; //swapping players
					temp=array[j];
					array[j]=array[j-1];
					array[j-1]=temp;
					flag=1;
					break;
				}
			}
			if(flag==0&&strlen(array[j-1].name)>strlen(array[j].name)){ //case of all first m characters same
				PLAYER temp; //swapping players
				temp=array[j];
				array[j]=array[j-1];
				array[j-1]=temp;
				flag=1;
			}
		}
	}
} //end function sortNames

void sortArray(PLAYER array[],size_t size,unsigned int maxRuns){
//function to sort PLAYER Array in non-decreasing order first on basis of runs and then on basis of names in case of equal runs
	
	radixSortRuns(array,size,maxRuns); //sorting on the basis of runs
	
	size_t i; //for iterations
	
	size_t idxb=0,idxe=0,flag=0; //to store indices and flag

	for(i=1;i<size;i++){ //iterating through sorted array to look for equal runs cases
		if(array[i].runs==array[i-1].runs){ //if runs are equal then sorting players lexicographically
			idxe=i;
			if(flag==0){
				idxb=i-1;
				flag=1;
			}
		}
		else if(idxb<idxe){ //case of more than 1 players having equal runs
			sortNames(array,idxb,idxe);
			idxb=idxe=idxe+1;
			flag=0;
		}
	}
	if(idxb<idxe){ //case of more than 1 players having equal runs
		sortNames(array,idxb,idxe);
		//displayArray(array,size);
		idxb=idxe=idxe+1;
		flag=0;
	}
} //end function SortArray
	
int main(){ //main method

	size_t N; //to store number of players
	printf("\nEnter number of players (> 0): ");
	scanf("%zd",&N);
	
	printf("\nEnter:\n\nPlayer Name(single word)\t\tRuns\n\n"); //taking inputs
	PLAYER array[N];

	size_t i; //for iterations
	unsigned int maxRuns=0; //to store maximum runs scored by a player
	for(i=0;i<N;i++){
		scanf("%s %u",array[i].name,&array[i].runs);
		if(maxRuns<array[i].runs)
			maxRuns=array[i].runs;
	}

	sortArray(array,N,maxRuns); //sorting the array in required format
	
	displayArray(array,N); //displaying sorted array
	
	return 0;	
} //end main

