//Siddharth Thakur 1601CS46
//Date - 4th September, 2017
//Assignment6C.c

#include <stdio.h> //including necessary header files
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef struct structure{ //structure definition for every particular value of subset sum
	int possibility; //whether sum is possible for any subset
	int countSet1; //cardinal number of that subset
	int countSet2; //cardinal number of remaining subset
	int set1[100]; //to store elements of that subet
	int set2[100]; //to store elements of remaining subset
}SUM;

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

	int N; //to store number of integers
	printf("\nEnter Number of Integers (> 0 ): "); //taking inputs
	scanf("%d",&N);
	
	int  i,j,k; //for iterations

	int array[N]; //for storing different integers
	int totalSum=0; //to store sum of all elements

	printf("\nEnter Integers (space separated +ve integers):-\n"); //taking inputs
		for(i=0;i<N;i++){
		scanf("%d",&array[i]);
		totalSum+=array[i];
	}

	qsort(array,N,sizeof(int),compareFunction); //sorting in ascending order

	SUM sumPossibility[N+1][totalSum+1]; //2d-array to indicate whether a subset-sum exists and its characteristics 
	
	i=0;
	while(i<=N){ //initialising first column to true as 0 subset-sum can exist
		sumPossibility[i][0].possibility=1;
		sumPossibility[i][0].countSet1=0;
		sumPossibility[i][0].countSet2=0;
		for(k=0;k<100;k++){
			sumPossibility[i][0].set2[k]=INT_MIN;
			sumPossibility[i][0].set1[k]=INT_MIN;
		}
		i++;
	}

	j=1;
	while(j<=totalSum){ //initialising first row to false as any subset-sum cannot
		//exist with including 0 elements excecpt 0 itself
		sumPossibility[0][j].possibility=0;
		sumPossibility[0][j].countSet1=0;
		sumPossibility[0][j].countSet2=0;
		for(k=0;k<100;k++){
			sumPossibility[0][j].set2[k]=INT_MIN;
			sumPossibility[0][j].set1[k]=INT_MIN;	
		}
		j++;
	}

	i=1; //now using bottom-Up approach to fill our 2d-array of subset-sum possibility
	while(i<=N){ //looping to detect possibilty of various subset-sums and storing their characteristics
		j=0;
		while(j<=totalSum){
			
			//checking possibility of sum 'j' if we exclude 'i'th element in set1
			sumPossibility[i][j].possibility=sumPossibility[i-1][j].possibility;
			sumPossibility[i][j].countSet1=sumPossibility[i-1][j].countSet1;
			sumPossibility[i][j].countSet2=sumPossibility[i-1][j].countSet2; //bottom-Up approach
			for(k=0;k<100;k++){
				sumPossibility[i][j].set2[k]=sumPossibility[i-1][j].set2[k];
				sumPossibility[i][j].set1[k]=sumPossibility[i-1][j].set1[k];
			}
			sumPossibility[i][j].countSet2++; //putting the 'i'th element in set2
			sumPossibility[i][j].set2[sumPossibility[i][j].countSet2-1]=array[i-1];

			if(array[i-1]<=j){ //checking possibility of sum 'j' if we include 'i'th element in set1
				
				sumPossibility[i][j].possibility=sumPossibility[i][j].possibility|sumPossibility[i-1][j-array[i-1]].possibility;
				sumPossibility[i][j].countSet1=sumPossibility[i-1][j-array[i-1]].countSet1;
				sumPossibility[i][j].countSet2=sumPossibility[i-1][j-array[i-1]].countSet2; //bottom-Up approach
				for(k=0;k<100;k++){
					sumPossibility[i][j].set2[k]=sumPossibility[i-1][j-array[i-1]].set2[k];
					sumPossibility[i][j].set1[k]=sumPossibility[i-1][j-array[i-1]].set1[k];
				}
				sumPossibility[i][j].countSet1++; //putting the 'i'th element in set1
				sumPossibility[i][j].set1[sumPossibility[i][j].countSet1-1]=array[i-1];
			}
			j++;
		}
		i++;
	}

	int set1Sum; //to store the subset sum which gives minimum difference 
	int minDiff=INT_MAX; //to store minimum difference between 2 disjoint subsets
	
	for(j=0;j<=totalSum;j++){ //checking minimum difference
		if(sumPossibility[N][j].possibility==1){
			if(minDiff>abs(totalSum-2*j)){ //(totalSum-2*j) = subset-sums difference
				minDiff=abs(totalSum-2*j);
				set1Sum=j;
			}
		}
	}

	//displaying required output
	printf("\nThe minimum difference = %d\n",abs(totalSum-2*set1Sum));
	printf("\nThe two disjoint sub-sets are:-\n\nSet1 = {");
	for(i=0;i<100;i++){
		if(sumPossibility[N][set1Sum].set1[i]>INT_MIN)
			printf(" %d ,",sumPossibility[N][set1Sum].set1[i]);
	}
	printf("\b}\nSet2 = {");
	for(i=0;i<100;i++){
			if(sumPossibility[N][set1Sum].set2[i]>INT_MIN)
			printf(" %d ,",sumPossibility[N][set1Sum].set2[i]);
	}
	printf("\b}\n\n");

	return 0;
} //end main method

