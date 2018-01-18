//Siddharth Thakur, 1601CS46
//Date - 30th October,2017
//Assignment11B.c

#include <stdio.h> //importing necessary header files
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int BFS(int** residualGraphAdjMatrix,int N,int* parentArray){
//function to use BFS to find an augmented path from source(0) to sink(N+1) 

	int queueSize=1; //denotes queuesize

	int* seen=(int*)calloc(N+2,sizeof(int)); //seen array to store whether a vertex is visited or not
	
	int* queueOfvertices=(int*)calloc(N+2,sizeof(int)); //circular array implementation of queue
	queueOfvertices[0]=0;
	seen[0]=1;
	int start=0,end=1;

	while(queueSize>0){ //BFS implementation

		int u=queueOfvertices[start]; //frontmost vertex
		queueSize--;
		
		if(u==N+1) //if sink is reached
			return 1;

		int i;
		for(i=0;i<N+2;i++){ //finding path through residual graph
			if(residualGraphAdjMatrix[u][i]>0&&seen[i]==0){
				queueOfvertices[end]=i;
				parentArray[i]=u;
				end++;
				seen[i]=1;
				queueSize++;
		    }
		}
		start++;
	}

	return 0; //if sink not found
}

void traversePath(int** residualGraphAdjMatrix,int N,int cFlow,int* parentArray){
//function to update the flow in edges of residual graph after current flow has been identified

	int i=N+1,j;
	while(i!=0){
			
		j=parentArray[i];
		residualGraphAdjMatrix[j][i]-=cFlow;
		residualGraphAdjMatrix[i][j]+=cFlow;
		i=parentArray[i];
	}
}

int FordFulkerson_EdmondKarpAlgorithm(int** residualGraphAdjMatrix,int N){
//function to implement Ford-Fulkerson method

	int maximumFlow=0; //to store max possible flow

	int i,j,k; //for iterations

	int* parentArray=(int*)calloc(N+2,sizeof(int)); //to store parents of vertices in BFS
	for(i=0;i<N+2;i++)
		parentArray[i]=-1;

	int flag=BFS(residualGraphAdjMatrix,N,parentArray); //whether BFS visited sink or not

	while(flag==1){ //until augmented path from source to sink exists

		int cFlow=INT_MAX; //to store current flow in residual graph (i.e., minimum of all residual flow)
		i=N+1;
		while(i!=0){

			j=parentArray[i];
			if(cFlow>residualGraphAdjMatrix[j][i])
				cFlow=residualGraphAdjMatrix[j][i];
			i=parentArray[i];
		}

		traversePath(residualGraphAdjMatrix,N,cFlow,parentArray); //updating residual graph

		maximumFlow+=cFlow; //increment of max possible flow

		flag=BFS(residualGraphAdjMatrix,N,parentArray);
	}

	return maximumFlow;
}

int main(){ //main method

	int N; //to store total number of vertices

	//taking inputs
	printf("\nNote:- problem constraints are not clearly defined for N < 4.");
	printf("\nHence, enter total number of vertices (N) excluding Source and Sink ( N > = 4) : ");
	scanf("%d",&N);
	
	int i,j,k;

	int** GraphAdjMatrix=(int**)calloc(N+2,sizeof(int*)); //adjacency matrix representation of flow network
	for(i=0;i<N+2;i++){
		GraphAdjMatrix[i]=(int*)calloc(N+2,sizeof(int));
		for(j=0;j<N+2;j++)
			GraphAdjMatrix[i][j]=INT_MIN;
	}

	int** residualGraphAdjMatrix=(int**)calloc(N+2,sizeof(int*)); //adjacency matrix representation of residual flow network
	for(i=0;i<N+2;i++){
		residualGraphAdjMatrix[i]=(int*)calloc(N+2,sizeof(int));
		for(j=0;j<N+2;j++)
			residualGraphAdjMatrix[i][j]=INT_MIN;
	}
	
	//creating graph and residual graph based on given conditions of connectivity
	for(i=1;i<=N/4;i++){
		GraphAdjMatrix[0][i]=residualGraphAdjMatrix[0][i]=i;
		residualGraphAdjMatrix[i][0]=0;
	}

	for(i=1;i<=N;i++){
		j=i+1;
		while(j<=N&&0<=(j-i)&&(j-i)<=3){
			GraphAdjMatrix[i][j]=residualGraphAdjMatrix[i][j]=i+j;
			residualGraphAdjMatrix[j][i]=0;
			j++;
		}
	}

	for(i=(3*N)/4;i<=N;i++){
		GraphAdjMatrix[i][N+1]=residualGraphAdjMatrix[i][N+1]=i;
		residualGraphAdjMatrix[N+1][i]=0;
	}

	int maximumFlow=FordFulkerson_EdmondKarpAlgorithm(residualGraphAdjMatrix,N); //determining maximum possible flow

	//displaying output
	printf("\nMaximum Flow Possible = %d\n\n",maximumFlow);

	return 0;
} //end main

