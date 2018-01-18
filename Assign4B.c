//Siddharth Thakur, 1601CS46
//Date - 21st August, 2017
//Assign4B.c

#include <stdio.h> //importing necessary header files
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* decimalToBinary(long long int num,char* numB){ //function to generate binary string of a decimal number

	int i=0; //generating binary string
	do{
		i++;
		numB=realloc(numB,(i+1)*sizeof(char));
		numB[i-1]=num%2+'0';
		num/=2;
	}while(num>0);
	numB[i]='\0';

	return numB; //returning binary string of the number
}

int equalizeBits(char* numB1,char* numB2){
	//function to equalize size of two binary strings by adding zeroes in shorter string

    int l1=strlen(numB1); //finding lengths of two strings
    int l2=strlen(numB2);

    if(l1==l2) //when both are of equal lengths
    	return l1;

    int i; //equalizing lengths in case of differences
    if (l1<l2){ //case 1
      	numB1=realloc(numB1,l2*sizeof(char));
      	i=l1;
       	while(i<l2){
       		numB1[i]='0';
       		i++;
       	}
       	numB1[l2]='\0';
       	return l2; //returning final length of equalized strings
    }
    
    if(l1>l2){ //case 2
    	numB2=realloc(numB2,l1*sizeof(char));
    	i=l2;
       	while(i<l1){
       		numB2[i]='0';
       		i++;
       	}
       	numB2[l1]='\0';
       	return l1; //returning final length of equalized strings
   	}
} //end function equalizeBits

char* addBinary(char* numB1,char* numB2,char* sum){ //function to add two binary numbers
	
	int len=equalizeBits(numB1,numB2); //equalizing the two binary strings two be added
	
	int carryover=0; //to store any carry forward
	int bit1,bit2,bit3; //to store bits and their sum bit

	int i=0; //adding the two binary numbers
	while(i<len){
		bit1=numB1[i]-'0';
		bit2=numB2[i]-'0';
		bit3=bit1+bit2+carryover;
		sum=realloc(sum,(i+2)*sizeof(char));
		sum[i]=bit3%2+'0';
		carryover=bit3/2;
		i++;
	}
	sum[i+1]='\0';
	if(carryover!=0){
		sum=realloc(sum,(i+2)*sizeof(char));
		sum[i]='1';
	}
	sum[i+1]='\0';

	return sum; //returning binary string of the sum
}

long long int multiplyBinary(char* nb1,char* nb2){
//recursive function to multiply two binary numbers by using Karatsuba Algorithm (O(n^1.59)) 

	int bitSize=equalizeBits(nb1,nb2); //equalizing length of the two binary strings

	if(bitSize==0) //base cases
		return 0;
	if(bitSize==1)
		return ((nb1[0]-'0')*(nb2[0]-'0'));
	
	//dividing the binary numbers into two halves
	int llen=bitSize/2;
	int rlen=bitSize-llen;
	
	char* nb1L=calloc(llen+1,sizeof(char));
	memcpy(nb1L,&nb1[rlen],llen);
	nb1L[llen]='\0';

	char* nb2L=calloc(llen+1,sizeof(char));
	memcpy(nb2L,&nb2[rlen],llen);
	nb2L[llen]='\0';
	
	char* nb1R=calloc(rlen+1,sizeof(char));
	memcpy(nb1R,nb1,rlen);
	nb1R[rlen]='\0';
	
	char* nb2R=calloc(rlen+1,sizeof(char));
	memcpy(nb2R,nb2,rlen);
	nb2R[rlen]='\0';
	
	//According to Karatsuba Algorithm we do multiplication only three times instead of usual 4
	long long int part1=multiplyBinary(nb1L,nb2L); //recursive function call to multiply the left-half of two binary strings

	char *sum1='\0',*sum2='\0'; //sum of two halves of the same binary string
	sum1=addBinary(nb1L,nb1R,sum1);
	sum2=addBinary(nb2L,nb2R,sum2);


	long long int part2=multiplyBinary(sum1,sum2); //recursive function call to multiply both sums

	long long int part3=multiplyBinary(nb1R,nb2R); //recursive function call to multiply the right-half of two binary strings 

	part2-=part1+part3; //calculating final result
	part2=part2<<rlen;
	rlen=rlen<<1;
	part1=part1<<rlen;

	long long int product=part1+part2+part3; //the final result
	return product; //returning product of two numbers
}

int main(){ //main method

	long long int n1; //first input number
	long long int n2; //second input number
	long long int n3; //product number
	
	int flag=0; //flag for handling negative numbers

	printf("\nEnter two numbers (space separated integers) : "); //taking inputs
	scanf("%lld %lld",&n1,&n2);
	
	if(n1<0&&n2>0||n1>0&&n2<0){ //if either of them is -ve
		flag=1;
		if(n1<0)
			n1*=-1;
		else
			n2*=-1;
	}

	if(n1<0&&n2<0){ //if both of them are negative
		n1*=-1;
		n2*=-1;
	}
	
	char* nb1='\0'; //to store binary string of first input number
	char* nb2='\0'; //to store binary string of second input number


	nb1=decimalToBinary(n1,nb1); //generating the binary strings
	nb2=decimalToBinary(n2,nb2);

	n3=multiplyBinary(nb1,nb2); //function call to multiply the binary numbers
	
	if(flag==0) //displaying the output
		printf("\n%lld * %lld = %lld\n\n",n1,n2,n3);
	else
		printf("\n-(%lld * %lld) = -%lld\n\n",n1,n2,n3);
	
	return 0; //end main
}

