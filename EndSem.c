//Siddharth Thakur, 1601CS46
//EndSem.c
//Date - 13th November, 2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
	
void visitDFS(int v,int** adjM,int N,int* seen){
//recursive function to use DFS O(V+E) to detect path between 2 vertices
	
	seen[v]=1;
	int i;	
	for(i=0;i<N;i++){
		if(seen[i]==0&&adjM[v][i]<INT_MAX)
			visitDFS(i,adjM,N,seen);
	}
}

int triDFS(int v,int** adjM,int N,int* seen,int idx){
//recursive function to use DFS O(V+E) to detect any triangle in the graph
	
	if(idx>4)
		return 0;
	if(seen[v]==1&&idx==4) //if triangle?
		return 1;
	seen[v]=idx;
	
	int i;
	int flag=0;	
	for(i=0;i<N;i++){
		if((seen[i]==0||(seen[i]==1&&seen[v]==3))&&adjM[v][i]<INT_MAX)
			flag=triDFS(i,adjM,N,seen,idx+1);
		if(flag==1)
			return 1;
	}
	return 0;
}

int findEditDistance(char* string1,char* string2){
//function to find edit distance between two strings using DP 

	int l1=strlen(string1);
	int l2=strlen(string2);

	int distDP[l1+1][l2+1];

	int i,j;
	for(i=0;i<=l1;i++){ //using bottom-up approach of DP to find the edit distance
		for(j=0;j<=l2;j++){ 

			if(i==0)
				distDP[i][j]=j;
			else if(j==0)
				distDP[i][j]=i;

			else if(toupper(string1[i-1])==toupper(string2[j-1]))
				distDP[i][j]=distDP[i-1][j-1];

			else{

				int min=distDP[i][j-1];

				if(min<distDP[i-1][j])
					min=distDP[i-1][j];

				if(min<distDP[i-1][j-1])
					min=distDP[i-1][j-1];

				distDP[i][j]=1+min;
			}
		}
	}

	return distDP[l1][l2];
}

int main(){

	int N;
	int i,j,k;
	printf("\nEnter the number of cities: - "); //taking inputs
	scanf("%d",&N);

	char** cityList=(char**)calloc(N,sizeof(char*)); //list of cities
	printf("\nEnter the names of %d cities: - \n",N);
	for(i=0;i<N;i++){
		cityList[i]=(char*)calloc(100,sizeof(char));
		scanf("%s",cityList[i]);
	}

	int** adjM=(int**)calloc(N,sizeof(int*)); //intializations (adjacency matrix representation of graph
	int** TT=(int**)calloc(N,sizeof(int*)); //to store truth table of existence of path between vertices
	for(i=0;i<N;i++){
		adjM[i]=(int*)calloc(N,sizeof(int));
		TT[i]=(int*)calloc(N,sizeof(int));
		for(j=0;j<N;j++){
			if(i==j)
				adjM[i][j]=1;
			else
				adjM[i][j]=INT_MAX;
			TT[i][j]=0;
		}
	}

	int alpha1[26];
	int alpha2[26];

	for(i=0;i<N;i++){ //creating graph

		for(k=0;k<26;k++)
			alpha1[k]=0;

		for(k=0;k<strlen(cityList[i]);k++)
			alpha1[toupper(cityList[i][k])-'A']++;
		
		for(j=0;j<N;j++){
			
			for(k=0;k<26;k++)
				alpha2[k]=0;

			for(k=0;k<strlen(cityList[j]);k++)
				alpha2[toupper(cityList[j][k])-'A']++;
	
			int flag=0;			
			for(k=0;k<26;k++){
				if(alpha1[k]>0&&alpha2[k]>0){
					flag=1;
					break;
				}
			}
	
			if(flag==1){
				adjM[i][j]=findEditDistance(cityList[i],cityList[j]);
			}
		}
	}

	printf("\nThe adjacency matrix (%d * %d) for the graph is:- \n",N,N); //dispalying adjacency matrix
	printf("-1 indicates that edge is not present between the two vertices.\n");
	putchar('\n');
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			if(adjM[i][j]<INT_MAX)
				printf(" %d ",adjM[i][j]);
			else
				printf(" -1 ");
		}
		putchar('\n');
	}
	putchar('\n');

	char ch='y';
	int* seen=(int*)calloc(N,sizeof(int));
	while(ch=='y'){ //taking choices
		printf("\nChoose from below options : \n");
		printf("\n(a) : Is the graph connected?\n");
		printf("(b) : Is the graph having any triangle?\n");
		printf("\nEnter choice : ");
		scanf(" %c",&ch);
		
		int flag;
		switch(ch){
			case 'a':	for(i=0;i<N;i++){ //Detecting if graph is connected through efficient DFS algorithm O(V+E)
						for(k=0;k<N;k++)
							seen[k]=0;
						for(j=0;j<N;j++){
							visitDFS(i,adjM,N,seen);
							if(seen[j]==1)
								TT[i][j]=1;
						}
					}

					flag=0;
					for(i=0;i<N;i++){
						for(j=0;j<N;j++){
							if(TT[i][j]!=1){
								flag=1;
								break;
							}
						}
						if(flag==1)
							break;
					}

					if(flag==0)
						printf("\nYes, the constructed Graph is Connected!\n");
					else
						printf("\nNo, the constructed Graph is NOT Connected!\n");
							
					break;

			case 'b': for(i=0;i<N;i++){ //detecting triangles through efficient DFS algorithm O(V+E)
						for(j=0;j<N;j++)
							seen[j]=0;
						flag=0;
						flag=triDFS(i,adjM,N,seen,1);
						if(flag==1)
							break;
					}
					if(flag==1)
						printf("\nYes, the constructed Graph is having a triangle!\n");
					else
						printf("\nNo, the constructed Graph is NOT having a triangle!\n");
					break;

			default: printf("Wrong Choice ! Try Again \n");
		}
		
		printf("\nWant to Continue ? (y/n) ");
		scanf(" %c",&ch);
	}

	return 0;
}

























				
