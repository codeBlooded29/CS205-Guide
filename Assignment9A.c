//Siddharth Thakur, 1601CS46
//Date - 16th October, 2017
//Assignment9A.c

#include <stdio.h> //including necessary header files
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct $ //structure definition of a house
{
	char* name; //name of house
	char alphaCount[26]; //count of alphabets
	int ASCIIsum;
	float boreWellCost; //cost of digging borewell
	
	int parent; //attributes required for Prim's algorithm
	float key;
	int inTree;
	int boreWell;
	int waterSupply;
	
	int seen; //for DFS
}HOUSE;

void minPipeCostSpanningTree(HOUSE* houseList,int** pipeCostMatrix,int N){
//function to implement Prim's MST algorithm to find the most efficient and economical water supply  
	
	int queueSize=N;	
	int i;

	while(queueSize>0){
		
		int u;
		int key=INT_MAX;
		for(i=1;i<=N;i++){
			if(houseList[i].inTree==0&&houseList[i].key<key){
				key=houseList[i].key;
				u=i;
			}
		}
		queueSize--;

		houseList[u].inTree=1;
		if(houseList[u].waterSupply==0){
			houseList[u].boreWell=1;
			houseList[u].waterSupply=1;
		}

		for(i=1;i<=N;i++){ //looping for updating value of key
			if(houseList[i].inTree==0){
				if(pipeCostMatrix[u][i]<=houseList[i].key){
					houseList[i].parent=u;
					houseList[i].key=pipeCostMatrix[u][i];
					houseList[i].boreWell=0;
					houseList[i].waterSupply=1;
				}	
			}
		}
	}
} //end minPipeCostSpanningTree function

void dfs(HOUSE* houseList,int N,int** MST,int root){
//function to use DFS to find particular MST vertices in minimum spanning forests

	int j;
	if(houseList[root].seen==0){

		printf("%s",houseList[root].name);
		if(houseList[root].boreWell==1)
			printf(" (Borewell present)\n");
		else
			putchar('\n');

		houseList[root].seen=1;

		for(j=1;j<=N;j++){ //visiting adjacent vertices (houses)
			if(MST[root][j]==1)
				dfs(houseList,N,MST,j);
		}
	}
} //end function dfs

int main(){ //main method
	
	int N; //to store number of houses
	printf("\nEnter the total number of houses ( > 0 ) : ");
	scanf("%d",&N);
	
	HOUSE* houseList=(HOUSE*)calloc(N+1,sizeof(HOUSE)); //list of vertices(houses)
	char name[100];
	
	int i,j; //taking inputs
	printf("\nEnter the distinct names of %d House Owners (single word):\n",N); 
	
	for(i=1;i<N+1;i++){

		printf("(%d) ",i);
		scanf("%s",name);
		houseList[i].name=(char*)calloc(strlen(name)+1,sizeof(char)); //storing names
		strcpy(houseList[i].name,name);
		for(j=0;j<26;j++)
			houseList[i].alphaCount[j]=0;
		
		//initialisations
		houseList[i].parent=0;
		houseList[i].inTree=0;
		houseList[i].boreWell=0;
		houseList[i].waterSupply=0;
		houseList[i].seen=0;

		for(j=0;j<strlen(name);j++){
			houseList[i].alphaCount[toupper(name[j])-'A']++;
			houseList[i].boreWellCost+=(int)name[j];
		}

		houseList[i].ASCIIsum=houseList[i].boreWellCost;
		houseList[i].boreWellCost/=strlen(houseList[i].name)*1.0;
		houseList[i].key=houseList[i].boreWellCost;
	}
	
	int** pipeCostMatrix=(int**)calloc(N+1,sizeof(int*)); //adjacency matrix representation of cost of connecting pipes

	for(i=0;i<N+1;i++){ //intialising the matrix
		pipeCostMatrix[i]=(int*)calloc(N+1,sizeof(int));
		for(j=0;j<N+1;j++)
			pipeCostMatrix[i][j]=INT_MAX;
	}
	
	int k;
	for(i=1;i<N+1;i++){ //filling the adjacency matrix

		for(j=1;j<N+1;j++){ //if name X is convertible to Y based on given condition
			if(j==i)
				continue;
			if(abs(strlen(houseList[i].name)-strlen(houseList[j].name))==1){
				int c=0;
				int l;
				for(k=0;k<26;k++){
					if(houseList[i].alphaCount[k]!=houseList[j].alphaCount[k]){
						c++;
						l=k;
					}
				}
				//connecting vertices based on given condition
				if(c==1){
					if(abs(houseList[i].alphaCount[l]-houseList[j].alphaCount[l])==1)
						pipeCostMatrix[i][j]=abs(houseList[i].ASCIIsum-houseList[j].ASCIIsum);
				}
			}
		}
	}

	/*putchar('\n');
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			if(pipeCostMatrix[i][j]<INT_MAX)
				printf(" %d ",pipeCostMatrix[i][j]);
			else
				printf(" INF ");
		}
		putchar('\n');
	}
	putchar('\n');*/

	int** MST=(int**)calloc(N+1,sizeof(int*)); //adjacency matrix representation of Minimum Spanning Forest
	for(i=0;i<=N;i++)
		MST[i]=(int*)calloc(N+1,sizeof(int));

	minPipeCostSpanningTree(houseList,pipeCostMatrix,N);
	
	double totalCost=0; //calculation min cost of water supply
	for(i=1;i<=N;i++)
		totalCost+=houseList[i].key;

	//displaying output
	printf("\nTotal minimised cost to supply water in all the houses is:- %.2lf\n",totalCost);
	printf("\nThe Borewells are present in the following houses:- \n\n");
	int c=0;
	for(i=1;i<=N;i++){
		if(houseList[i].boreWell==1){
			c++;
			printf("(%d) %s\n",c,houseList[i].name);
		}
	}

	for(i=1;i<=N;i++)
		MST[i][houseList[i].parent]=MST[houseList[i].parent][i]=1;
	printf("\nThe list of houses clusters (minimum spanning trees) that share water connection through pipes:- \n");
	for(i=1;i<=N;i++){
		if(houseList[i].seen==0){
			printf("\nCluster: \n\n");
			dfs(houseList,N,MST,i);
			putchar('\n');
		}
	}

	return 0;
} //end main

