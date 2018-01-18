//Siddharth Thakur, 1601CS46
//Date - 16th October,2017
//Assignment9C.c

#include <stdio.h> //importing necessary header files
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct $ //structure definition of a locality
{
	int reachability; //whether the locality is reachable within 30 mins from any restaurant
	int domino; //whether the locality is having any restaurant
	int srNo; 
	char name[100]; //name of locality
}LOCALITY;

int maxServing(float** minTimeMatrix,LOCALITY* vertexList,int N){ 
//function to find the locality reachable within 30 mins from most other localities 
	
	int i,j;
	int max=INT_MIN;
	int idx;
	for(i=1;i<=N;i++){ //looping to count
		if(vertexList[i].domino==0){
			int c=0;
			for(j=1;j<=N;j++){ //seeing who covers maximum localities which are not covered till now
				if(minTimeMatrix[i][j]<=30.0&&vertexList[j].reachability==0)
					c++;
			}
			if(max<c){
				max=c;
				idx=i;
			}
		}
	}
	return idx;
}

void getAllPairsMinTime(float*** D,int*** PI,float** timeMatrix,int N){ 
//function to implement the Floyd-Warshall algorithm and compute shortest time and path matrices
	
	D[0]=(float**)calloc(N+1,sizeof(float*)); //initializations
	PI[0]=(int**)calloc(N+1,sizeof(int*));
	
	int i,j,k;
	for(i=1;i<=N;i++){
		D[0][i]=(float*)calloc(N+1,sizeof(float));
		PI[0][i]=(int*)calloc(N+1,sizeof(int));
		for(j=1;j<=N;j++){
			D[0][i][j]=timeMatrix[i][j];
			if(i==j)
				PI[0][i][j]=0;
			else
				PI[0][i][j]=i;
		}
	}

	for(k=1;k<=N;k++){ //Floyd-Warshall algorithm implementation

		D[k]=(float**)calloc(N+1,sizeof(float*));
		PI[k]=(int**)calloc(N+1,sizeof(int*));

		for(i=1;i<=N;i++){

			D[k][i]=(float*)calloc(N+1,sizeof(float));
			PI[k][i]=(int*)calloc(N+1,sizeof(int));

			for(j=1;j<=N;j++){

				float min=D[k-1][i][j];
				if(min>(D[k-1][i][k]+D[k-1][k][j]))
					min=D[k-1][i][k]+D[k-1][k][j];
				D[k][i][j]=min;

				if(D[k-1][i][j]<=(D[k-1][i][k]+D[k-1][j][k]))
					PI[k][i][j]=PI[k-1][i][j];
				else
					PI[k][i][j]=PI[k-1][k][j];
			}
		}
	}
}

void locateDominos(float** minTimeMatrix,LOCALITY* vertexList,int N){
//function to greedily find the minimum locations of Dominos restaurants 


	int i;
	int listSize=N;
	while(listSize>0){

		int u=maxServing(minTimeMatrix,vertexList,N); //greedily selecting restaurants
		vertexList[u].domino=1;
		int c=0;
		for(i=1;i<=N;i++){
			if(minTimeMatrix[u][i]<=30.0){
				vertexList[i].reachability=1;
				c++;
			}
		}
		listSize-=c;
	}

	//displaying list of restaurants' locations
	printf("\nMinimum of number of required Dominos restaurants found.\n");
	printf("\nDominos restaurants are locted in the following greedily selected localities:- \n");
	int c=0;
	for(i=1;i<=N;i++){
		if(vertexList[i].domino==1){
			c++;
			printf("(%d) %s\n",c,vertexList[i].name);
		}
	}
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

void printPath(int source,int destination,LOCALITY* vertexList,int*** PI,int N){
//recursive funtion to print the most time efficient path from given source to given destination

	if(N>0){

		if(PI[N][source][destination]!=0){

			printPath(source,PI[N][source][destination],vertexList,PI,N-1); //recursive function call
			printf(" %s ->",vertexList[PI[N][source][destination]].name);
		}
	}
}

int findPath(int*** PI,float** minTimeMatrix,char locality[],LOCALITY* vertexList,int N){
//function to find the most time efficient path from a pizza restaurant to a locality  

	int queueSize=N;
	int i;
	for(i=1;i<=N;i++){
		if(strcasecmp(locality,vertexList[i].name)==0)
			break;
	}
	if(i>N){
		printf("\nLocality not found!\n\n");
		return -1;
	}
	int destination=i;
	
	int min=INT_MAX;
	int source;
	for(i=1;i<=N;i++){ //determining the restaurant reachable in least time
		if(vertexList[i].domino==1){
			if(min>minTimeMatrix[destination][i]){
				min=minTimeMatrix[destination][i];
				source=i;
			}
		}
	}
	
	//displaying the corresponding least time path
	printPath(source,destination,vertexList,PI,N);
	printf(" %s ->",vertexList[destination].name);
	printf("\b\b  \n");

	printf("Time Taken = %.2f\n\n",minTimeMatrix[source][destination]);
}

int main(){ //main method
	
	int N; //to store total number of localities

	//taking inputs
	printf("\nEnter total number of localities ( > 0) : ");
	scanf("%d",&N);
	
	LOCALITY* vertexList=(LOCALITY*)calloc(N+1,sizeof(LOCALITY)); //list of localities as vertices
	float** timeMatrix=(float**)calloc(N+1,sizeof(float*)); //edge-time matrix
	float** trafficMatrix=(float**)calloc(N+1,sizeof(float*)); //edge-traffic matrix
	int** distMatrix=(int**)calloc(N+1,sizeof(int*)); //edge-edit_distance matrix

	printf("\nEnter the name of the %d localities (to find \" Edit Distance\" between them) : \n",N);
	int i,j;
	for(i=1;i<N+1;i++){ //intialising list of vertices
		
		printf("(%d) ",i);
		scanf("%s",vertexList[i].name);
		
		vertexList[i].srNo=i;
		vertexList[i].reachability=0;
		vertexList[i].domino=0;

		timeMatrix[i]=(float*)calloc(N+1,sizeof(float));
		trafficMatrix[i]=(float*)calloc(N+1,sizeof(float));
		distMatrix[i]=(int*)calloc(N+1,sizeof(int));
	}

	//taking inputs	
	printf("\nNote:- Localities are numbered from 1 to %d and 0.5 < = traffic(i,j) < = 2 .\n",N);
	printf("\nNote:- Traffic within a locality is considered as 0.\n");
	printf("\nEnter the Traffic Matrix [m(i,j) = m(j,i)] & [m(i,i) = 0] in conventional format:-\n\n");

	for(i=1;i<=N;i++){ //filling the adjacency matrices
		for(j=1;j<=N;j++){

			scanf("%f",&trafficMatrix[i][j]);
			distMatrix[i][j]=findEditDistance(vertexList[i].name,vertexList[j].name);
			timeMatrix[i][j]=distMatrix[i][j]*trafficMatrix[i][j];
		}
	}

	printf("\nDistance Matrix:-\n   ");
	for(i=1;i<=N;i++)
		printf(" (%d)",i);
	putchar('\n');
	for(i=1;i<=N;i++){
		printf("(%d) ",i);
		for(j=1;j<=N;j++){
			printf(" %d ",distMatrix[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');

	printf("\nTime Matrix:-\n     ");
	for(i=1;i<=N;i++)
		printf(" (%d)   ",i);
	putchar('\n');
	for(i=1;i<=N;i++){
		printf("(%d) ",i);
		for(j=1;j<=N;j++)
			printf(" %.2f ",timeMatrix[i][j]);
		putchar('\n');
	}
	putchar('\n');

	int*** PI=(int***)calloc(N+1,sizeof(int**)); //to store PI(k)(preceding vertex) matrices
	float*** D=(float***)calloc(N+1,sizeof(float**)); //to store D(k)(shortest time) matrices
	getAllPairsMinTime(D,PI,timeMatrix,N); //function call
	float** minTimeMatrix=D[N]; //minimum time matrix

	printf("\nMinimum Time Matrix:-\n    ");
	for(i=1;i<=N;i++)
		printf(" (%d)   ",i);
	putchar('\n');
	for(i=1;i<=N;i++){
		printf("(%d) ",i);
		for(j=1;j<=N;j++){
			printf(" %.2f ",minTimeMatrix[i][j]);
		}
		putchar('\n');
	}
	putchar('\n');

	locateDominos(minTimeMatrix,vertexList,N); //finding out location of restaurants

	//displaying outputs
	char name[100];
	printf("\nEnter the locality name to get the most efficient pizza delivery path for it:-\n\n");
	scanf("%s",name);
	findPath(PI,minTimeMatrix,name,vertexList,N);

	return 0;
} //end main

