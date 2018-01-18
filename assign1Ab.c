//Siddharth Thakur, 1601CS46, 31st July, 2017
//assign1Ab.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{ //structure to store names
	char firstLetter;
	struct node* next;
};
typedef struct node NODE;
typedef NODE* NODEPTR;

NODEPTR createList(char nameList[][100],int l,int index){ //fuction to create linked-list
	int i;
	NODEPTR head=(NODEPTR)malloc(sizeof(NODE)); //head pointer
	head->firstLetter=nameList[index][0];
	l--;
	NODEPTR previous=head;
	NODEPTR current;
	i=index+1;
	while(l--){ //creating list from array
		current=(NODEPTR)malloc(sizeof(NODE));
		current->firstLetter=nameList[i][0];
		current->next=NULL;
		previous->next=current;
		previous=current;
		i++;
	}
	return head;
}

void arrangeList(NODEPTR head,int size){ //function to arrange the list in sprcified order
	while(size--){
		NODEPTR current=head;
		char temp;
		while(current->next!=NULL){ //using switch-case to determine and arrange vowels over consonants
			switch(current->firstLetter){
				case 'a':
				case 'A':
				case 'e':
				case 'E':
				case 'i':
				case 'I':
				case 'o':
				case 'O':
				case 'u':
				case 'U':	
						break;
				default:	switch(current->next->firstLetter){ //if previous was consonant
							case 'a':
							case 'A':
							case 'e':
							case 'E':
							case 'i':
							case 'I':
							case 'o':
							case 'O':
							case 'u':
							case 'U':	temp=current->firstLetter;
									current->firstLetter=current->next->firstLetter;
									current->next->firstLetter=temp;
						}				
			}
			current=current->next;
		}
	}
}

void displayList(NODEPTR head){ //fuction to display the list
	printf("Linked List:- \n");
	NODEPTR current=head;
	while(current!=NULL){
		printf("%c -> ",current->firstLetter);
		current=current->next;
	}
	printf("\b\b \b\b \n\n");
}

void palindromeDetector(NODEPTR head,int size){ //function to determine plaindromes in the arranged list
	char arr[size]; 
	int i=0,j,k;
	while(head!=NULL){
		arr[i]=head->firstLetter;
		head=head->next;
		i++;	
	}

	for(i=2;i<=size;i++){ //detecting and printing plaindromes
		for(j=0;j<=size-i;j++){
			char* subArray=(char*)calloc(i,sizeof(char)); //creating subArray to check for palindromes
			for(k=j;k<j+i;k++)
				subArray[k-j]=arr[k];
			int flag=0;
			for(k=0;k<i;k++){
				if(subArray[k]!=subArray[i-k-1])
					flag=1;
			}
			if(flag==0){ //if palindromes detected than we print it
				printf("\nPalindrome (of size - %d): ",i);
				for(k=0;k<i;k++)
					printf("%c -> ",subArray[k]);
				printf("\b\b \b\b ");
			}	
		}
	}
}
int main(){ //main method
	
	int N; //to store total no. of students
	int i; //for iterations
	NODEPTR head=NULL,previous=NULL;
	printf("\nEnter total number of students: "); //taking inputs
	scanf("%d",&N);
	printf("\nEnter the names: \n");
	char ch;
	char nameList[N][100];
	for(i=0;i<N;i++){
		printf("(%d) ",i+1);
		scanf(" %[^\r\n]s",nameList[i]);
	}
	int x,y;
	x=N/2;
	y=N-x;
	NODEPTR head1=createList(nameList,x,0); //creating the two sublists
	NODEPTR head2=createList(nameList,y,x);

	printf("\n\nOriginal (List X) "); //displaying original sublists of first-letters
	displayList(head1);
	printf("Original (List Y) ");
	displayList(head2);

	arrangeList(head1,x); //arranging the sublists as required
	arrangeList(head2,y);

	printf("\nArranged (List X) "); //displaying the arranged sublists
	displayList(head1);
	printf("Arranged (List Y) ");
	displayList(head2);

	palindromeDetector(head1,x); //detecting palindromes if any
	palindromeDetector(head2,y);
	putchar('\n');
	putchar('\n');
	return 0;
} //end main

