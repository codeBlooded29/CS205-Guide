//Siddharth Thakur, 1601CS46
//Date - 30th October,2017
//Assignment12A.c

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
				end%=N+2;
				seen[i]=1;
				queueSize++;
		    }
		}
		start++;
		start%=N+2;
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

	int Nc; //to store total number of companies
	int Ns; //to store total number of students

	//taking inputs
	printf("\nEnter total number of Companies (N) ( N > = 1) : ");
	scanf("%d",&Nc);
	
	printf("\nEnter the name of %d Companies (single word) : \n",Nc);
	int i,j,k;

	char** CompanyList=(char**)calloc(Nc,sizeof(char*));
	for(i=0;i<Nc;i++){
		printf("(%d) ",i+1);
		CompanyList[i]=(char*)calloc(100,sizeof(char));
		scanf("%s",CompanyList[i]);
	}

	//taking inputs
	printf("\nEnter total number of Students (N) ( N > = 1) : ");
	scanf("%d",&Ns);
	
	printf("\nEnter the name of %d Students (single word) : \n",Ns);

	char** StudentList=(char**)calloc(Ns,sizeof(char*));
	for(i=0;i<Ns;i++){
		printf("(%d) ",i+1);
		StudentList[i]=(char*)calloc(100,sizeof(char));
		scanf("%s",StudentList[i]);
	}

	//creating flow network to solve this "Maximum Bipartite Matching Problem"
	int** GraphAdjMatrix=(int**)calloc(Nc+Ns+2,sizeof(int*)); //adjacency matrix representation of flow network
	for(i=0;i<Nc+Ns+2;i++){
		GraphAdjMatrix[i]=(int*)calloc(Nc+Ns+2,sizeof(int));
		for(j=0;j<Nc+Ns+2;j++)
			GraphAdjMatrix[i][j]=INT_MIN;
	}

	int** residualGraphAdjMatrix=(int**)calloc(Nc+Ns+2,sizeof(int*)); //adjacency matrix representation of residual flow network
	for(i=0;i<Nc+Ns+2;i++){
		residualGraphAdjMatrix[i]=(int*)calloc(Ns+Nc+2,sizeof(int));
		for(j=0;j<Ns+Nc+2;j++)
			residualGraphAdjMatrix[i][j]=INT_MIN;
	}
	
	//creating graph and residual graph based on given conditions of connectivity
	int alphaCountC[26];
	int alphaCountS[26];
	for(i=1;i<=Nc;i++){
		
		for(k=0;k<26;k++)
			alphaCountC[k]=0;
		for(k=0;k<strlen(CompanyList[i-1]);k++)
			alphaCountC[toupper(CompanyList[i-1][k])-'A']++;
		
		for(j=Nc+1;j<=Nc+Ns;j++){
			
			for(k=0;k<26;k++)
				alphaCountS[k]=0;
			for(k=0;k<strlen(StudentList[j-Nc-1]);k++)
				alphaCountS[toupper(StudentList[j-Nc-1][k])-'A']++;

			int c=0;
			for(k=0;k<26;k++){
				if(alphaCountS[k]>0&&alphaCountC[k]>0)
					c++;
			}

			if(c>=2){
				GraphAdjMatrix[i][j]=residualGraphAdjMatrix[i][j]=1;
				residualGraphAdjMatrix[j][i]=0;
			}
		}
	}
	
	printf("\nExpected Offer List (on the basis of given constraint):- \n\n Comapany \t:\tCandidate\n\n");
	for(i=1;i<=Nc;i++){
		printf("(%d) %s \t:\t",i,CompanyList[i-1]);
		for(j=Nc+1;j<=Nc+Ns+1;j++){
			if(GraphAdjMatrix[i][j]==1)
				printf("%s , ",StudentList[j-Nc-1]);
		}
		printf("\b\b ");
		putchar('\n');
	}
	
	for(i=1;i<=Nc;i++){ //connecting super source
		GraphAdjMatrix[0][i]=residualGraphAdjMatrix[0][i]=1;
		residualGraphAdjMatrix[i][0]=0;
	}
	for(i=Nc+1;i<=Nc+Ns;i++){ //connecting super sink
		GraphAdjMatrix[i][Nc+Ns+1]=residualGraphAdjMatrix[i][Nc+Ns+1]=1;
		residualGraphAdjMatrix[Nc+Ns+1][i]=0;
	}
	
	int maximumFlow=FordFulkerson_EdmondKarpAlgorithm(residualGraphAdjMatrix,Nc+Ns); //determining maximum possible flow

	//displaying output
	printf("\nMaximum Possible Placements = %d\n",maximumFlow);

	printf("\nActual Offer List:- \n\n Comapany \t:\tCandidate\n\n");
	for(i=1;i<=Nc;i++){
		printf("(%d) %s \t:\t",i,CompanyList[i-1]);
		for(j=Nc+1;j<=Nc+Ns+1;j++){
			if(residualGraphAdjMatrix[i][j]==0&&residualGraphAdjMatrix[j][i]==1)
				printf("%s",StudentList[j-Nc-1]);
		}
		putchar('\n');
	}
	putchar('\n');
	
	return 0;
} //end main

