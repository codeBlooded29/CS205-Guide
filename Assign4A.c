//Siddharth Thakur, 1601CS46
//Date - 21st August, 2017
//Assign4A.c

#include <stdio.h> //importing required header files
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node{ //definition of patient
	
	char name[100]; //name of patient
	int time; //arrival time of patient
	int priority; //priority of patient
}PATIENT;

int getPriority(char name1[],char name2[]){ //function to calculate priority of a patient
	
	int i=0,j=0; //for iterations
	int c=0; //to store count of matched characters

	int matched1[strlen(name1)]; //record of matched characters
	int matched2[strlen(name2)];
	for(i=0;i<strlen(name1);i++)
		matched1[i]=0;	//intialisations
	for(i=0;i<strlen(name2);i++)
		matched2[i]=0;
	
	for(i=0;i<strlen(name1);i++){ //determining match of characters
		for(j=0;j<strlen(name2);j++){
			if(abs(name1[i]-name2[j])%32==0 && matched1[i]==0 && matched2[j]==0){
				c++;
				matched1[i]++;
				matched2[j]++;
			}
		}
	}
	
	return c; //returning the numbers of characters matched 1 to 1
}

void max_heapfy(PATIENT* heap,int index,int heapSize){
//recursive function to create max-heap for implementation of priority queue
				
	int leftChild=2*index+1; //indexes of children
	int rightChild=2*index+2;
	int largest=index;
	
	if(leftChild<heapSize && heap[leftChild].priority>heap[index].priority) //checking max-heap properties
		largest=leftChild;
	else if(leftChild<heapSize && heap[leftChild].priority==heap[index].priority && heap[leftChild].time<heap[index].time)
		largest=leftChild;
	if(rightChild<heapSize && heap[rightChild].priority>heap[largest].priority)
		largest=rightChild;
	else if(rightChild<heapSize && heap[rightChild].priority==heap[largest].priority && heap[rightChild].time<heap[largest].time)
		largest=rightChild;

	if(largest!=index){ //in case of violation of max-heap property
		PATIENT temp=heap[index];
		heap[index]=heap[largest];
		heap[largest]=temp;
		max_heapfy(heap,largest,heapSize); //recursive function call
	}
}

void prioritize(PATIENT* heap,int heapSize){
//function to prioritize queue using max-heap i.e., to build max-heap

	int i=(heapSize-2)/2; //last parent node index
	while(i>=0){
		max_heapfy(heap,i,heapSize); //checking max-heap properties
		i--;
	}
}

int main(){ //main method

	int n; //to store number of patients
	int i; //for iterations
	int heapSize=0; //to store size of the heap
	int clock=8*60; //clock timer
	
	char doctorName[100]; //to store doctors name
	
	printf("\nEnter name of the Doctor : "); //taking inputs
	scanf("%s",doctorName);
	printf("\nEnter number of patients ( > 0 ) : ");
	scanf("%d",&n);
	printf("\nEnter Name(single word) & arrival time (increasing-order)(format :- hh:mm ) of patients : \n   Name\t\tArrival Time\n");
	int hh,mm;
	
	PATIENT input[n]; //patients input array
	for(i=0;i<n;i++){
		printf("(%d) ",i+1);
		scanf("%s\t%d:%d",input[i].name,&hh,&mm);
		input[i].priority=getPriority(input[i].name,doctorName);
		input[i].time=hh*60+mm;
		if(input[i].time<=clock)
			heapSize++;
	}

	printf("\n\nOrder of checkups of patients :- \n"); //displaying outputs
	
	PATIENT *heap; //using max-heap to simulate priority queue
	heap=(PATIENT*)calloc(heapSize,sizeof(PATIENT)); //heap initialization
	for(i=0;i<heapSize;i++)
		heap[i]=input[i];
	
	i=0; 
	int idx1,idx2; //to store beginning and end index of currently available patients 
	idx1=idx2=heapSize-1;
	
	while(i<n){ //looping for each patient
		
		prioritize(heap,heapSize); //putting currently available patients in priority queue
		
		if(heapSize>0){ //if patient is available for check-up
			
			printf("(%d) %s \n",(i+1),heap[0].name);
			i++;
			clock+=9; //check-up time
			heap[0]=heap[heapSize-1];
			heapSize--;
			heap=realloc(heap,(heapSize)*sizeof(PATIENT)); //decreasing queue size
		}
		clock++; //time running

		idx1++;
		while(idx2<n-1 && input[idx2+1].time<=clock)
			idx2++; //arrival of new patients
		
		int j;
		for(j=idx1;j<=idx2;j++){ //inducting new patients in heap
			heapSize++;
			if(heapSize==1)
				heap=calloc(1,sizeof(PATIENT));
			else
				heap=realloc(heap,(heapSize)*sizeof(PATIENT));
			heap[heapSize-1]=input[j];
		}
		
		idx1=idx2;
	}
	putchar('\n');
	return 0; //end main
}
		
	
