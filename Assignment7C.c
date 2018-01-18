//Siddharth Thakur, 1601CS46
//Date - 25th September, 2017
//Assignment7C.c

#include <stdio.h> //including necessary header files
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct $ //structure definition for each natural number 
{
	int minSteps; //to store minimimum steps to reduce to 1
	int* path; //the path followed
}NUMBER;

int main(){ //main method

	int n; //to store the number

	printf("\nEnter the number ( > 0 )  : "); //taking inputs
	scanf("%d",&n);

	NUMBER* dpArray=(NUMBER*)calloc(n+1,sizeof(NUMBER)); //to store decompostion of each natural number
	dpArray[0].minSteps=-1; //initialisations
	dpArray[1].minSteps=0;

	int i; 
	for(i=2;i<=n;i++){ //finding decmposition of each natural number upto 'n'
		//using bottom-up approach of Dynamic Programing in O(n) time
		
		int steps=INT_MAX; 
		int j1,j2; //to store path follwed
		
		if(i%2==0){ //finding minimum steps	
			if(steps>(dpArray[i/2].minSteps+1)){
				steps=(dpArray[i/2].minSteps+1);
				j1=i/2;
				j2=2;
			}
		}
		if(i%3==0){
			if(steps>(dpArray[i/3].minSteps+1)){
				steps=(dpArray[i/3].minSteps+1);
				j1=i/3;
				j2=3;	
			}
		}
		if(i%5==0){
			if(steps>(dpArray[i/5].minSteps+1)){
				steps=(dpArray[i/5].minSteps+1);
				j1=i/5;
				j2=5;
			}
		}
		if(i%7==0){
			if(steps>(dpArray[i/7].minSteps+1)){
				steps=(dpArray[i/7].minSteps+1);
				j1=i/7;
				j2=7;
			}
		}
		if(i>1){
			if(steps>(dpArray[i-1].minSteps+1)){
				steps=(dpArray[i-1].minSteps+1);
				j1=i-1;
				j2=-1;
			}
		}

		dpArray[i].minSteps=steps; //storing minimum number of steps required to reduce the number to one
		
		dpArray[i].path=(int*)calloc(dpArray[i].minSteps,sizeof(int)); //storing corresponding path
		int k=0;
		for(k=0;k<dpArray[j1].minSteps;k++)
			dpArray[i].path[k]=dpArray[j1].path[k];
		dpArray[i].path[k]=j2;
	}

	printf("\nThe minimum number of steps required to reduce the number to 1 = %d\n",dpArray[n].minSteps); //displaying outputs
	printf("\nThe steps follwed are :- \n\n");
	int num=n; 
	for(i=dpArray[n].minSteps-1;i>=0;i--){
		printf("Step %d : ",dpArray[n].minSteps-i);
		if(dpArray[n].path[i]==-1){
			printf("%d-1 = %d\n",num,num-1);
			num--;
		}
		else{
			printf("%d/%d = %d\n",num,dpArray[n].path[i],num/dpArray[n].path[i]);
			num/=dpArray[n].path[i];
		}
	}

	putchar('\n');
	return 0;
} //end main

