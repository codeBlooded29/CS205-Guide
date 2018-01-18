//Siddharth Thakur, 1601CS46, 31st July, 2017
//assign1Aa.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{ //structure to store names
	char name[100];
	struct node* next;
};
typedef struct node NODE;
typedef NODE* NODEPTR;

void sortList(NODEPTR head,int size){ //function to bubble-sort the linked list
	if(head==NULL)
		return;

	NODEPTR current;
	int i,j;
	for(i=0;i<size;i++){ //bubble sort algorithm
		current=head;
		while(current->next!=NULL){
			if(strcasecmp(current->name,current->next->name)>0){
				char temp[100]={'\0'};
				strcpy(temp,current->next->name);
				strcpy(current->next->name,current->name);
				strcpy(current->name,temp);
			}
			current=current->next;
		}
	}
	return;
}

void printLinked_List(NODEPTR head){ //function to print elements of Linked_List
	NODEPTR current=head;
	while(current!=NULL){
		printf("%s -> ",current->name);
		current=current->next;
	}
	printf("\b\b \b\b \n");
}

void printList(NODEPTR head,char nameList[][100],int size){ //function to print sorted full names 
	int i,j;
	printf("\nSorted List of Names:-\n");
	NODEPTR current;
	current=head;
	while(current!=NULL){ 
		int index=0;
		for(i=0;i<size;i++){ //checking out the maximum match between short-forms and full names
			if(strlen(current->name)>strlen(nameList[i]))
				continue;
			for(j=0;j<strlen(current->name)&&j<strlen(nameList[i]);j++){
				if(current->name[j]!=nameList[i][j])
					break;
			}
			if(j==strlen(current->name)){
				index=i;
				if(strlen(nameList[i])==strlen(current->name))
					break;
			}
		}
		printf("%s\n",nameList[index]);
		current=current->next;
	}
	putchar('\n');
}

int main(){ //main method
	
	int N; //to store number of names 
	int i,j,k;//for iterations

	printf("\nEnter the number of students:- ");
	scanf(" %d",&N);
	char nameList[N][100]; //storage input names
	
	printf("\nEnter names of the students (all inputs should be in same format):\n"); //inputting names
	for(i=0;i<N;i++){
		printf("(%d) ",(i+1));
		scanf(" %[^\r\n]s",nameList[i]);
	}

	NODEPTR head=NULL,previous=NULL; //head-pointer
	int index=-1,length=0; //to store max-length of unique short-forms
	for(i=0;i<N;i++){ //looping through nameList
		length=0;
		for(j=0;j<N;j++){
			if(i==j)
				continue;
			for(k=0;k<strlen(nameList[i])&&k<strlen(nameList[j]);k++){ //getting unique short-forms
				if(nameList[i][k]!=nameList[j][k])
					break;
			}
			index=k;
			if(k==strlen(nameList[i]))
				index--;
			if((index+1)>length)
				length=index+1;
		}
		NODEPTR current=(NODEPTR)malloc(sizeof(NODE)); //creating linked-list
		strncpy(current->name,nameList[i],length);
		if(head==NULL){
			head=current;
			previous=head;
			current->next=NULL;
			continue;
		}
		previous->next=current;
		current->next=NULL;
		previous=current;
	}
	printf("\nOriginal Linked List Created:-\n");
	printLinked_List(head);

	sortList(head,N); //bubble-sorting the linked-list
	printf("\nSorted Linked List:-\n");
	printLinked_List(head);

	printList(head,nameList,N); //printing full-names by iterating through the sorted linked-list
	
	return 0;
} //end main

