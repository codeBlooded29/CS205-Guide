//Siddharth Thakur 1601CS46
//Date - 4th September, 2017
//Assignment6A.c

#include <stdio.h> //including necessary header files
#include <stdlib.h>
#include <limits.h>

typedef struct structure{ //structure definition of an amount of money to store minimum coins required
	//and their configuration
	int* denominationCount; //array for storing configuration of different denominations available
	int coinsCount; //to store minimum number of coins required to achieve that amount
}SUM;

void findMinimumCoins(int Values[],int  N,int S,SUM array[]){
//function to use Bottom-Up approach of DP to calculate minimum coins and their configuration

	if(S<Values[0]) //an impossible case
		return;

	array[0].coinsCount=0; //basic case
	array[Values[0]].coinsCount=1;
	array[Values[0]].denominationCount[0]=1;
 
  	int  i,j; //for iterations
	for(i=Values[0]+1;i<=S;i++){ //looping for calculation of configurations of all the amounts upto given amounts
		
		int temp=INT_MAX; //to store minimum number of coins required
		int  index=-1; //to store index of a particular denomination
		
		for(j=0;j<N;j++){
			if((i-Values[j])<0) //amount not possible
				break;
			if((i-Values[j])==0){ //if amount matches value of a denomination
				temp=1;
				index=j;
				break;
			}
			if(temp>array[i-Values[j]].coinsCount&&array[i-Values[j]].coinsCount>0){ //detecting minimum coins
				temp=array[i-Values[j]].coinsCount+1;
				index=j;
			}
		}
		if(index>=0){ //storing minimum coins required and their configuration for a particular amount
			array[i].coinsCount=temp;
			for(j=0;j<N;j++)
				array[i].denominationCount[j]=array[i-Values[index]].denominationCount[j];
			array[i].denominationCount[index]++;
		}
	}
}	

int compareFunction(const void* a,const void* b){ //utility function(for ascending order) for qsort library function
	
	int v1=*(const int*)a;
	int v2=*(const int*)b;

	if(v1<v2)
		return -1;
	else if(v1==v2)
		return 0;
	else
		return 1;
}
 	 
int main(){ //main method

	int N; //to store number of different denominations available
	printf("\nEnter Number of Different Denomination Coins available (> 0 ): "); //taking inputs
	scanf("%d",&N);
	
	int Values[N]; //for storing values of different denomination coins
	printf("\nEnter Values of the Denominations (space separated positive integers):-\n");
	int  i,j;
	for(i=0;i<N;i++)
		scanf("%d",&Values[i]);
	
	qsort(Values,N,sizeof(int),compareFunction); //sorting in ascending order
	
	printf("\nEnter Total Sum ( > 0) : ");
	int S; //to store total sum
	scanf("%d",&S);

	SUM array[S+1]; //to store optimal configurations for different amounts of money
	for(i=0;i<S+1;i++){ //initialisations
		array[i].coinsCount=0;
		array[i].denominationCount=(int*)calloc(N,sizeof(int));
		for(j=0;j<N;j++)
			array[i].denominationCount[j]=0;
	}

	findMinimumCoins(Values,N,S,array); //generating optimal configuartions
	
	int amt=0; //checking if optimal configuration is valid
	for(i=0;i<N;i++)
		amt+=array[S].denominationCount[i]*Values[i];
	
	if(array[S].coinsCount<=0||amt!=S) //impossibility case
		printf("\nChange Not possible for given Sum!\n\n");
	
	else{ //possibility
		printf("\nChange Possible for given Sum!\n"); //displaying outputs
		printf("\nMinimum Number of Coins Required = %d\n",array[S].coinsCount);
		printf("\nCoins configuration : \n");	
		printf(" Value\t\tNumber of Coins\n");	
		for(i=0;i<N;i++){
			if(array[S].denominationCount[i]>0)
					printf("  %d\t\t\t%d\n",Values[i],array[S].denominationCount[i]);
		}
	}
	putchar('\n');
	return 0;
} //end main











