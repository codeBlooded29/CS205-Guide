//Assignment8C.c
//Siddharth Thakur, 1601CS46
//Date - 9th October,2017

#include <stdio.h> //importing necessary header files
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct $ //structure definition of a vertex
{
	char* word;
	char alphaCount[26]; //count of alphabets
}VERTEX;

void visitDFS(int** graph,int N,int node,int grandNode,char* seen){
	//Recusrsive function to traverse the whole graph through DFS and detect cycles

	if(graph[node][grandNode]==1) //if we reach same vertex after starting from it
		seen[grandNode]='c'; //marking that vertex as a part of some cycle
	
	seen[node]='Y';
	int i;
	for(i=1;i<N+1;i++){ //recursive DFS traversal
	   	if(graph[node][i]==1&&seen[i]=='N')
	      	visitDFS(graph,N,i,grandNode,seen);
	}
}

int main(){ //main method
	
	int N; //to store total number of words
	printf("\nEnter total number of words ( > 1) : ");
	scanf("%d",&N); 
	
	VERTEX* wordList=(VERTEX*)calloc(N+1,sizeof(VERTEX)); //list of vertices(words)
	char word[6];
	
	printf("\nEnter %d distinct words(5 letters only) : \n",N); //taking inputs
	
	int i,j;
	for(i=1;i<N+1;i++){
		printf("(%d) ",i);
		scanf("%s",word);
		wordList[i].word=(char*)calloc(strlen(word)+1,sizeof(char)); //storing words
		strcpy(wordList[i].word,word);
		for(j=0;j<27;j++)
			wordList[i].alphaCount[j]=0;
		for(j=0;j<strlen(word);j++)
			wordList[i].alphaCount[toupper(word[j])-'A']++;
	}
	
	int** graph=(int**)calloc(N+1,sizeof(int*)); //adjacency matrix representation of graph

	for(i=0;i<N+1;i++){ //intialising the matrix
		graph[i]=(int*)calloc(N+1,sizeof(int));
		for(j=0;j<N+1;j++)
			graph[i][j]=0;
	}
	
	int k;
	for(i=1;i<N+1;i++){ //filling the adjacency matrix

		for(j=1;j<N+1;j++){
			if(j==i)
				continue;
			int c=0;
			for(k=0;k<26;k++){
				if(wordList[i].alphaCount[k]!=wordList[j].alphaCount[k])
					c++;
			}
			//connecting vertices based on given condition
			if(c==0) 
				graph[i][j]=graph[j][i]=1;	
			if(c==2){
				if((wordList[i].alphaCount[toupper(wordList[i].word[0])-'A']-
					wordList[j].alphaCount[toupper(wordList[i].word[0])-'A'])==1)
					graph[i][j]=1;
			}
		}
	}

	//displaying the Adjcency Matrix
	printf("\nThe Adjcency Matrix : \n");
	printf("\n     ");
	for(i=1;i<N+1;i++)
		printf(" %s",wordList[i].word);
	putchar('\n');\
	putchar('\n');
	for(i=1;i<N+1;i++){
		printf("%s",wordList[i].word);
		for(j=1;j<N+1;j++)
			printf("   %d  ",graph[i][j]); 
		putchar('\n');
		putchar('\n');
	}
	
	char** truthTable=(char**)calloc(N+1,sizeof(char*)); //Matrix for showing existence of path

	for(i=0;i<N+1;i++){ //intialising the Truth Table
		truthTable[i]=(char*)calloc(N+1,sizeof(char));
		for(j=0;j<N+1;j++)
			truthTable[i][j]='N';
	}

	for(i=1;i<N+1;i++){ //determining path between every pair of vertices
		char* seen=(char*)calloc(N+1,sizeof(char));
		int k;
		for(k=0;k<N+1;k++)
			seen[k]='N';
		visitDFS(graph,N,i,i,seen); //doing DFS
		for(j=1;j<N+1;j++)
			truthTable[i][j]=seen[j];
	}

	//displaying output
	printf("\nCyclic Nature of graph :- ");
	int flag=0;
	for(i=1;i<N+1;i++){
		if(truthTable[i][i]=='c'){
			printf("GRAPH IS CYCLIC\n");
			flag=1;
			break;
		}
	}
	if(flag==0)
		printf("GRAPH IS ACYCLIC\n");

	//displaying output
	printf("\nMatrix of existance of path between any two pairs of vertices ('Y' => YES & 'N' => NO)\n\n");

	printf("     ");
	for(i=1;i<N+1;i++)
		printf(" %s",wordList[i].word);
	putchar('\n');\
	putchar('\n');

	for(i=1;i<N+1;i++){
		printf("%s",wordList[i].word);
		for(j=1;j<N+1;j++){
			if(truthTable[i][j]=='c')
				truthTable[i][j]='Y';
			printf("   %c  ",truthTable[i][j]); 
		}
		putchar('\n');
		putchar('\n');
	}

	return 0;
} //end main

