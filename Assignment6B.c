//Siddharth Thakur 1601CS46
//Date - 4th September, 2017
//Assignment6B.c

#include <stdio.h> //including necessary header files
#include <stdlib.h>
#include <limits.h>
#include <string.h>
 	 
typedef struct structure{ //structure definition for every room to store minimum cost of 
	//reaching it and required path 
	int minCost;
	int pathCount; //counter of steps taken
	char** path;
}ROOM;

int M,N; //to store number of rows and columns respectively

char* word1="rightward"; //words indicating movement on 2d-array
char* word2="diagonal";
char* word3="downward";

int minimumDetector(int a,int b,int c){ //function to find minimum of three numbers 
	
	if(a<b&&a<c) //if a is minimum
		return a;
	
	if(b<a&&b<c) //if b is minimum
		return b;
	
	return c; //if c is minimum
}

void dpMinimumCostAndPath(int Cost[][N],ROOM array[][N]){
//function to implement Bottom-Up approach of DP by calculating minimum cost for reaching each room 
	//and path for the same

	int i,j,k; //for iterations
	
	array[0][0].minCost=Cost[0][0]; //base case

	i=1;
	while(i<M){ //initialisation of rooms lying in first column of 2d-array
		array[i][0].minCost=array[i-1][0].minCost+Cost[i][0];
		array[i][0].pathCount=i;
		for(k=0;k<i;k++)
			strcpy(array[i][0].path[k],word3); //downwards movements only
		i++;
	}
	j=1;
	while(j<N){ //initialisation of rooms lying in first row of 2d-array
		array[0][j].minCost=array[0][j-1].minCost+Cost[0][j];
		array[0][j].pathCount=j;
		for(k=0;k<j;k++)
			strcpy(array[0][j].path[k],word1); //rightwards movements only
		j++;
	}

	i=1; //looping for analyzing each room's minimum cost and path 
	while(i<M){
		j=1;
		while(j<N){
			
			int cost1=array[i][j-1].minCost; //cost of path routing from horizontally leftside room
			int cost2=array[i-1][j-1].minCost; //cost of path routing from diagonally above room
			int cost3=array[i-1][j].minCost; //cost of path routing from vertically above room
			int cost4=minimumDetector(cost1,cost2,cost3); //finding minimum of the three
			
			if(cost1==cost4){
				array[i][j].minCost=cost1+Cost[i][j]; //storing minimum
				array[i][j].pathCount=array[i][j-1].pathCount+1; //counting number of steps
				for(k=0;k<array[i][j-1].pathCount;k++) //copying path to reach previous
					strcpy(array[i][j].path[k],array[i][j-1].path[k]);
				strcpy(array[i][j].path[k],word1); //adding latest step
			}
			else if(cost2==cost4){
				array[i][j].minCost=cost2+Cost[i][j]; //storing minimum
				array[i][j].pathCount=array[i-1][j-1].pathCount+1; //counting number of steps
				for(k=0;k<array[i-1][j-1].pathCount;k++) //copying path to reach previous
					strcpy(array[i][j].path[k],array[i-1][j-1].path[k]);
				strcpy(array[i][j].path[k],word2); //adding latest step
			}
			else{
				array[i][j].minCost=cost3+Cost[i][j]; //storing minimum
				array[i][j].pathCount=array[i-1][j].pathCount+1; //counting number of steps
				for(k=0;k<array[i-1][j].pathCount;k++) //copying path to reach previous
					strcpy(array[i][j].path[k],array[i-1][j].path[k]); 
				strcpy(array[i][j].path[k],word3); //adding latest step
			}
			j++;
		}
		i++;
	}
} //end of function dpMinimumCostAndPath

int main(){ //main method

	printf("\nEnter Number of rows 'm' (> 0 ): "); //taking inputs
	scanf("%d",&M);
	printf("\nEnter Number of columns 'n' (> 0 ): "); //taking inputs
	scanf("%d",&N);

	
	int Cost[M][N]; //for storing cost associated with the different rooms
	printf("\nEnter the Cost Matrix (space separated +ve integers)(in conventional format):-\n\n"); //taking inputs
	int  i,j,k;
	for(i=0;i<M;i++){
		for(j=0;j<N;j++)
			scanf("%d",&Cost[i][j]);
	}
	
	ROOM array[M][N]; //array for storing related to every rooms
	for(i=0;i<M;i++){ //initialising info for each room 
		for(j=0;j<N;j++){
			array[i][j].minCost=INT_MAX;
			array[i][j].pathCount=0;
			array[i][j].path=(char**)calloc(100,sizeof(char*));
			for(k=0;k<100;k++)
				array[i][j].path[k]=(char*)calloc(20,sizeof(char));
		}
	}

	dpMinimumCostAndPath(Cost,array); //to generate required information for each rooms

	printf("\nMinimum Cost Incurred : %d\n",array[M-1][N-1].minCost); //displaying output
	printf("\nMinimum Cost Incurring path : \n");
	for(i=0;i<array[M-1][N-1].pathCount;i++)
		printf("%s , ",array[M-1][N-1].path[i]);
	printf("\b\b \n\n");
	
	return 0;
} //end main











