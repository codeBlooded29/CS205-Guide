//Siddharth Thakur, 1601CS46 
//Date - 14th August, 2017
//assign3B.c

#include <stdio.h> //importing required libraries
#include <stdlib.h>
#include <string.h>

#define bool int //defining boolean type
#define true 1
#define false 0

bool isEvenWord(char* word){ //recursive function to detect evenness of a word
	
	if(strlen(word)==0) //base cases
		return true;
	if(strlen(word)==1)
		return false;

	char* ptr=strchr(word+1,*word); //searching for another occurence of first letter
	
	if(ptr==NULL)
		return false;
	else{ 
		int index=ptr-word; //index of another occurence of first letter
		memmove(&word[index], &word[index+1], strlen(word) - index); //rearranging word by removing another occurence of the first letter
		return isEvenWord(word+1); //recursive function call
	}	
}		
		
int main(){ //main method
	
	char word[500]={'\0'}; //to store the input word
	printf("\nEnter Your Word : "); //taking input
	scanf("%s",word);

	bool result=isEvenWord(word); //checking evenness of the word
	
	if(result==true) //displaying output
		printf("\nThe entered word is an EVEN Word.\n\n");
	else
		printf("\nThe entered word is NOT an EVEN Word.\n\n");
	
	return 0;
} //end main
