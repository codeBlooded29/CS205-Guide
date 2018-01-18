//Siddharth Thakur, 1601CS46
//Date - 9th October,2017
//Assignment9B.c

#include <stdio.h> //importing necessary header files
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct $ //structure definition of a vertex
{
	int seen;
	int name;
	int parent; 
	float reliability; //overall path reliability 
}VERTEX;

int maxReliability(VERTEX* vertexList,int V){ //function to find vertex with the most reliable path from source
	
	int i;
	int max=INT_MIN;
	int idx;
	for(i=1;i<=V;i++){
		if(max<vertexList[i].reliability&&vertexList[i].seen==0){
			max=vertexList[i].reliability;
			idx=i;
		}
	}
	return idx;
}

void maxReliablePath(float** wMatrix,int source,VERTEX* vertexList,int V){
//function to find the most reliable paths from the given source to all the vertices using Dijkstra's algorithm 

	int queueSize=V;
	vertexList[source].reliability=1.0;
	vertexList[source].parent=0;
	
	while(queueSize!=0){ //looping for all the vertices

		int u=maxReliability(vertexList,V); 
		vertexList[u].seen=1;
		queueSize--;

		int i;
		for(i=1;i<=V;i++){ //relaxing all other edges i.e., updating path reliabilty of vertices
			if(u==i)
				continue;
			if(wMatrix[u][i]>0){
				if(vertexList[i].reliability<(vertexList[u].reliability*wMatrix[u][i])){
					vertexList[i].reliability=(vertexList[u].reliability*wMatrix[u][i]);
					vertexList[i].parent=u;
				}
			}
		}
	}
}

void printPath(VERTEX* vertexList,int destination){
//recursive funtion to print the most reliable path from give source to given destination

	if(vertexList[destination].parent!=0)
		printPath(vertexList,vertexList[destination].parent); //recursive function call
	
	printf(" %d ->",destination);
}

int main(){ //main method
	
	int V; //to store total number of vertices

	//taking inputs
	printf("\nEnter total number of vertices ( > 0) : ");
	scanf("%d",&V);
	
	VERTEX* vertexList=(VERTEX*)calloc(V+1,sizeof(VERTEX)); //list of vertices
	float** wMatrix=(float**)calloc(V+1,sizeof(float*)); //edge reliability probability matrix

	int i,j;
	for(i=1;i<V+1;i++){ //intialising list of vertices
		
		vertexList[i].name=i;
		vertexList[i].parent=0;
		vertexList[i].reliability=0.0;
		vertexList[i].seen=0;
		
		wMatrix[i]=(float*)calloc(V+1,sizeof(float));
	}

	//taking inputs	
	printf("\nNote:- Vertices are numbered from 1 to %d and 0 <= r(x,y) <= 1 .\n",V);
	printf("\nEnter the (directed graph) adjacency matrix (all space separated) m[i,j] = r[i,j] with r(i,j) ");
	printf("as reliability probability of channel from i to j and, is zero if i not connected with j.\n\n");

	for(i=1;i<=V;i++){ //filling the adjacency matrix
		for(j=1;j<=V;j++)
			scanf("%f",&wMatrix[i][j]);
	}

	int source,destination;
	printf("\nEnter the source and destination vertices (space separated): ");
	scanf("%d %d",&source,&destination); 
	
	maxReliablePath(wMatrix,source,vertexList,V); //finding out single source most reliable path

	//displaying outputs
	printf("\nThe Most Reliable Path of Reliability = %f between the two given vertices is : \n\n",vertexList[destination].reliability);
	printPath(vertexList,destination);
	printf("\b\b  \n");

	return 0;
} //end main

