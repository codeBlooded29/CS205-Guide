//Siddharth Thakur, 1601CS46, 31st July, 2017
//assign1C.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book //structure of a book in library
{
		int serialNumber;
		char* author;
		char* title;
		char issueStatus;
		struct book* next;
};

typedef struct book BOOK;
typedef BOOK* BOOKPTR;

BOOKPTR makeNewEntryOfBook(BOOKPTR head){ //function to make a new entry of a book
	char name[100];
	BOOKPTR temp=(BOOKPTR)malloc(sizeof(BOOK));
	printf("\nEnter Sr. No. : "); //taking inputs
	scanf("%d",&temp->serialNumber);

	printf("Enter Author Name : ");
	scanf(" %99[^\r\n]",name);
	temp->author=(char*)calloc(strlen(name)+1,sizeof(char));
	strcpy(temp->author,name);

	printf("Enter Book Title : ");
	scanf(" %99[^\r\n]",name);
	temp->title=(char*)calloc(strlen(name)+1,sizeof(char));
	strcpy(temp->title,name);

	temp->issueStatus='N'; //adding the new book node to the linked list 
	temp->next=head;
	head=temp;
	printf("\nEntry Successful!\n");
	return head;
}

void viewDetailsOfABook(BOOKPTR head){ //function to display details of any book

	if(head==NULL){
		printf("\nNo Books are available in Library! Please make some entries first.\n");
		return;
	}
	
	while(1){
		BOOKPTR current;
		printf("\nChoose option to view by:-\nEnter 'a' : By Sr. No.\n"); //taking inputs
		printf("Enter 'b' : By Author Name\n");
		printf("Enter 'c' : By Book Title\n");
		printf("Enter 'd' : To Exit\n");
		char option;
		printf("\nEnter Option : ");
		scanf(" %c",&option);
		printf("\nFor Issue Status : Y => Issued , N => Not Issued\n");
		switch(option){ //displaying books according to options
			case 'a' :	{printf("\nEnter the Sr. No. : ");
						int sn=0,flag=0;
						scanf("%d",&sn);
						current=head;
						while(current!=NULL){ //searching book according to Sr. No.
							if(current->serialNumber==sn){
								flag=1;
								printf("\nBook Found!\nSr. No. : %d\n",current->serialNumber);
								printf("Title : %s\n", current->title);
								printf("Author : %s\n",current->author);
								printf("Issue Status : %c\n",current->issueStatus);
								break;
							}
							current=current->next;
						}
						if(flag==0) //displaying apt. error messages
							printf("\nNo book with the entered Sr. No. exists! Try Again.\n");
						break;}

			case 'b' :	{printf("\nEnter the Author Name : "); //searching books according to author
						char name[100];
						int flag=0;
						scanf(" %99[^\r\n]",name);
						current=head;
						while(current!=NULL){
							if(strcasecmp(name,current->author)==0){
								flag=1;
								printf("\nBook Found!\nSr. No. : %d\n",current->serialNumber);
								printf("Title : %s\n", current->title);
								printf("Author : %s\n",current->author);
								printf("Issue Status : %c\n\n",current->issueStatus);
							}
							current=current->next;
						}
						if(flag==0) //displaying apt. error messages
							printf("\nNo book with the entered author name exists! Try Again.\n");
						break;}

			case 'c' :	{printf("\nEnter the Book Title : "); //searching books according to title
						char name[100];
						int flag=0;
						scanf(" %99[^\r\n]",name);
						current=head;
						while(current!=NULL){
							if(strcasecmp(name,current->title)==0){
								flag=1;
								printf("\nBook Found!\nSr. No. : %d\n",current->serialNumber);
								printf("Title : %s\n", current->title);
								printf("Author : %s\n",current->author);
								printf("Issue Status : %c\n\n",current->issueStatus);
							}
							current=current->next;
						}
						if(flag==0)
							printf("\nNo book with the entered title exists! Try Again.\n"); //displaying apt. error messages
						break;}

			case 'd' :	return;
						break;

			default :	printf("\nWrong Choice! Try Again.\n"); //displaying apt. error messages	
		}
	}
}

void showListOfAvailableBooks(BOOKPTR head){ //function to show list of books available for issuing

	if(head==NULL){
		printf("\nNo Books are available in Library! Please make some entries first.\n");
		return;
	}
	printf("\nList of books available for issuing:- \n\n");
	while(head!=NULL){
		if(head->issueStatus=='N'){
			printf("\nSr. No. : %d\n",head->serialNumber);
			printf("Title : %s\n", head->title);
			printf("Author : %s\n\n",head->author);
		}
		head=head->next;
	}
}

void issueBook(BOOKPTR head){ //function to issue a book by Sr.No.

	if(head==NULL){
		printf("\nNo Books are available in Library! Please make some entries first.\n");
		return;
	}
	printf("\nEnter the Sr. No. to issue book : ");
	int sn,flag=0;
	scanf("%d",&sn);
	while(head!=NULL){
		if(head->serialNumber==sn){
			flag=1;
			if(head->issueStatus=='N'){
				head->issueStatus='Y';
				printf("\nSr.No.- %d Successfully Issued!\n",head->serialNumber);
				break;
			}
			else
				printf("\nBook already issued earlier!\n");
		}
		head=head->next;
	}
	if(flag==0)
		printf("\nBook with the entered Sr. No. dosen't exist!\n");
}

void returnBook(BOOKPTR head){ //function to return a book by its Sr.No.

	if(head==NULL){
		printf("\nNo Books are available in Library! Please make some entries first.\n");
		return;
	}
	printf("\nEnter the Sr. No. to return book : ");
	int sn,flag=0;
	scanf("%d",&sn);
	while(head!=NULL){
		if(head->serialNumber==sn){
			flag=1;
			if(head->issueStatus=='Y'){
				head->issueStatus='N';
				printf("\nSr.No.- %d Successfully Returned!\n",head->serialNumber);
				break;
			}
			else
				printf("\nBook has already not been issued!\n");
		}
		head=head->next;
	}
	if(flag==0)
		printf("\nBook with the entered Sr. No. dosen't exist!\n");
}

int main(){ //main method
	BOOKPTR head=NULL;
	printf("\n\"Welcome to the New Library Information System!\"\n");
	char option;
	
	while(1){ //taking interactive inputs
		printf("\nChoose from the following options:-\nEnter 'a' : Make a new entry of book\n");
		printf("Enter 'b' : View Details of a book\n");
		printf("Enter 'c' : Show list of available books\n");
		printf("Enter 'd' : Issue a book\n");
		printf("Enter 'e' : Return a book\n");
		printf("Enter 'f' : Exit\n\n");
		printf("\nEnter Your Option : ");
		scanf(" %c",&option);

		switch(option){ //doing tasks according to choice
			case 'a' :	head=makeNewEntryOfBook(head);
						break;

			case 'b' :	viewDetailsOfABook(head);
						break;

			case 'c' :	showListOfAvailableBooks(head);
						break;

			case 'd' :	issueBook(head);
						break;

			case 'e' :	returnBook(head);
						break;

			case 'f' :	return 0;

			default :	printf("\nWrong Choice! Try Again.\n");
		}
	}
	return 0;
} //end main

