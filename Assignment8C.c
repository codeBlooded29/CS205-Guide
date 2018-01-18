//Assignment8B.c
//Siddharth Thakur, 1601CS46
//Date - 9th October,2017

#include <stdio.h> //importing necessary header files
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int countingEdges(int** graph,int N,int node){ //recursive function to count number of edges in a connected component
	//of the graph using DFS like algorithm 

	graph[node][0]=1;
  	int edgeCount=0;

  	int j;
  	for(j=1;j<N+1;j++){ //DFS like algorithm to count number of edges
  		if(graph[node][j]==1){
  			edgeCount++;
			
			if(node==j) //if self-loops exists 
				edgeCount++;
		}

    	if(graph[j][0]==0&&graph[node][j]==1)
      		edgeCount+=countingEdges(graph,N,j);
    }

    return edgeCount;
}

int main(){ //main method
	
	int N; //to store total number of vertices
	printf("\nEnter total number of vertices ( > 1) : ");
	scanf("%d",&N); 
	
	int M; //to store number pairs of vertices having edge between them
	printf("\nEnter the number of pairs of vertices having edge between them (non-negative integer) : ");
	scanf("%d",&M);
	
	int** graph=(int**)calloc(N+1,sizeof(int*)); //adjacency matrix representation of graph

	int i,j;
	for(i=0;i<N+1;i++){ //intialising the matrix
		graph[i]=(int*)calloc(N+1,sizeof(int));
		for(j=0;j<N+1;j++)
			graph[i][j]=0;
	}
	
	//taking inputs
	printf("\nNOTE:- Each vertex is denoted by a natural number (starting from 1).");
	printf("\n\nEnter the %d pairs of vertices having edge between them( two distinct space separated natural numbers  ) :\n",M);
	
	int x,y;
	for(i=0;i<M;i++){
		printf("(%d) ",i+1);
		scanf("%d %d",&x,&y);
			
		graph[x][y]=graph[y][x]=1;
	}
	
	int maxCount=INT_MIN; 
	for(i=1;i<N+1;i++){ //counting number of edges in each connected and then finding the maximum value out of them
		
		int edgeCount=0; 

		if(graph[i][0]==0){
			edgeCount+=countingEdges(graph,N,i);
			if(maxCount<edgeCount)
				maxCount=edgeCount;
		}
	}
	//printf("max:%d\n",maxCount);
	maxCount=(int)ceil(maxCount/2.0); //as each edge is counted twice
	printf("\nMaximum number of edges in any connected component is = %d\n\n",maxCount); //displaying output

	return 0;
} //end main

