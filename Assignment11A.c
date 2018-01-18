//Siddharth Thakur, 1601CS46
//Date - 30th October,2017
//Assignment11A.c

#include <stdio.h> //importing necessary header files
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

struct EDGE;

typedef struct $ //structure definition of a locality
{
	int srNo; 
	char name[100]; //name of locality
	struct EDGE* adjList;
	int* alphaCount;
	int listSize;
    int key;
	struct $* parent;
    int seen;
}LOCALITY;

typedef struct EDGE //structure definition of an edge
{
        LOCALITY* address;
        int edgeWeight;
        int slope;
}EDGE;

int distanceCalculator(char* name1,char* name2){ 
//function to calculate distance between 2 localities based on give rule
        
        int l1=strlen(name1);
        int l2=strlen(name2);
        
        int limit=(l1>l2)?l1:l2;
        
        int dist=0;
        int i;
        for(i=0;i<limit;i++)
                dist+=abs(name1[i]-name2[i]);
                
        return dist;
}

void min_heapify(LOCALITY** minPriorityQueue,int N,int idx){
//function to implement min_priority queue through min-heap to make the impletation asymptotically faster

	int leftChild=2*idx+1;
	int rightChild=2*idx+2;

	int least=idx; //check of violation of min-heap rule
	if(leftChild<N && minPriorityQueue[least]->key>minPriorityQueue[leftChild]->key)
		least=leftChild;
	if(rightChild<N && minPriorityQueue[least]->key>minPriorityQueue[rightChild]->key)
		least=rightChild;

	if(least!=idx){ 
		LOCALITY* temp=minPriorityQueue[idx];
		minPriorityQueue[idx]=minPriorityQueue[least];
		minPriorityQueue[least]=temp;
		min_heapify(minPriorityQueue,N,least);
	}
}

void buildMinHeap(LOCALITY** minPriorityQueue,int N){
//function to implement min_priority queue through min-heap to make the implementation asymptotically faster

	int i=(N-1)/2;
	while(i>=0){
		min_heapify(minPriorityQueue,N,i);
		i--;
	}
}

void shortestPath(int source,LOCALITY* vertexList,int N){
//function to find the shortest distance strictly upward path from the given source 
	//to all the vertices using Dijkstra's algorithm 

	int queueSize=N;
	vertexList[source].key=0;
	vertexList[source].parent=NULL;
	
	//efficient implementation of min-priority queue by use of min-heap
    LOCALITY** minPriorityQueue=(LOCALITY**)calloc(N,sizeof(LOCALITY*));
    int i;
    for(i=0;i<N;i++)
            minPriorityQueue[i]=&vertexList[i];

    buildMinHeap(minPriorityQueue,queueSize);

	while(queueSize>0){ //looping for all the vertices

		LOCALITY* u=minPriorityQueue[0]; //minimum key value
		if(u->key==INT_MAX)
			break;
		u->seen=1;

		for(i=0;i<u->listSize;i++){ //relaxing all other edges
			if(u->adjList[i].slope>0&&u->adjList[i].address->seen==0){

		        if(u->adjList[i].address->key>(u->adjList[i].edgeWeight+u->key)){
			        u->adjList[i].address->key=u->adjList[i].edgeWeight+u->key;
			        u->adjList[i].address->parent=u;
		       }
		   }
		}

		LOCALITY* temp=minPriorityQueue[0]; //now remooving minimum value and again min_heapifying the heap
		minPriorityQueue[0]=minPriorityQueue[queueSize-1];
		minPriorityQueue[queueSize-1]=temp;
		queueSize--;
		min_heapify(minPriorityQueue,queueSize,0); //to min-heapify
	}
}

void printPath(LOCALITY* v){
//recursive function to print path followed from home to office

	if(v!=NULL){
		printPath(v->parent);
		printf("%s -> ",v->name);
	}
}

int main(){ //main method
	
	srand(time(NULL));

	int N; //to store total number of localities

	//taking inputs
	printf("\nEnter total number of localities ( > 0) : ");
	scanf("%d",&N);
	
	LOCALITY* vertexList=(LOCALITY*)calloc(N,sizeof(LOCALITY)); //list of localities as vertices

	printf("\nEnter the name of the %d localities : \n",N);
	int i,j,k;
	char name[100];
	for(i=0;i<N;i++){ //intialising list of vertices
		
		for(j=0;j<100;j++)
		        vertexList[i].name[j]='\0';
		        
		printf("(%d) ",i+1);
		scanf("%s",name);
		strcpy(vertexList[i].name,name);
		vertexList[i].srNo=i;
		vertexList[i].listSize=1;
        vertexList[i].key=INT_MAX;
        vertexList[i].parent=NULL;
        vertexList[i].seen=0;

		vertexList[i].alphaCount=(int*)calloc(26,sizeof(int));
		for(j=0;j<strlen(vertexList[i].name);j++)
		    vertexList[i].alphaCount[toupper(vertexList[i].name[j])-'A']++;
		
		vertexList[i].adjList=(EDGE*)calloc(1,sizeof(EDGE));
		vertexList[i].adjList[vertexList[i].listSize-1].address=&vertexList[i];
		vertexList[i].adjList[vertexList[i].listSize-1].edgeWeight=0;
		vertexList[i].adjList[vertexList[i].listSize-1].slope=0;
	}


	for(i=0;i<N;i++){ //looping through all the localities to look for possible upwards edges between them
        for(j=0;j<N;j++){
            if(i==j)
               	continue;
            
            if(abs(strlen(vertexList[j].name)-strlen(vertexList[i].name))==1){
                int flag=0;
                for(k=0;k<26;k++){
                    if(vertexList[i].alphaCount[k]>0&&vertexList[j].alphaCount[k]>0){
                        flag=1;
                        break;
                    }
                }

                if(flag==1){
                    vertexList[i].listSize++;
                    vertexList[i].adjList=(EDGE*)realloc(vertexList[i].adjList,vertexList[i].listSize*sizeof(EDGE));
                    vertexList[i].adjList[vertexList[i].listSize-1].address=&vertexList[j];
                	vertexList[i].adjList[vertexList[i].listSize-1].edgeWeight=distanceCalculator(vertexList[i].name,vertexList[j].name);
                	vertexList[i].adjList[vertexList[i].listSize-1].slope=strlen(vertexList[j].name)-strlen(vertexList[i].name);
                }
     		}

            else if(abs(strlen(vertexList[j].name)-strlen(vertexList[i].name))==2){
                int flag=0;
                int c=0;
                for(k=0;k<26;k++){
                    if(vertexList[i].alphaCount[k]>0&&vertexList[j].alphaCount[k]>0)
                            c++;
                    if(c>=2){
                            flag=1;
                            break;
                    }
                }

                if(flag==1||c>=2){
                    vertexList[i].listSize++;
                   	vertexList[i].adjList=(EDGE*)realloc(vertexList[i].adjList,vertexList[i].listSize*sizeof(EDGE));
                    vertexList[i].adjList[vertexList[i].listSize-1].address=&vertexList[j];
                	vertexList[i].adjList[vertexList[i].listSize-1].edgeWeight=distanceCalculator(vertexList[i].name,vertexList[j].name);
                	vertexList[i].adjList[vertexList[i].listSize-1].slope=strlen(vertexList[j].name)-strlen(vertexList[i].name);
                }
            }
        }
    }

	char home[100]; //randomly choosing home and office
	char office[100];

	printf("\nEnter randomly choosen home location : ");
	scanf("%s",home);
	printf("\nEnter randomly choosen office location (different from home) : ");
	scanf("%s",office);

	int homeSrNo,officeSrNo;
	for(i=0;i<N;i++){
		if(strcasecmp(vertexList[i].name,home)==0)
			homeSrNo=i;
		if(strcasecmp(vertexList[i].name,office)==0)
			officeSrNo=i;
	}
  
    shortestPath(homeSrNo,vertexList,N); //determinig strictly upwards shortest path between the localities

    if(vertexList[officeSrNo].key<INT_MAX){ //displaying output
    	printf("\n\nStrictly Upwards path exists between the randomly choosen home and office.\n\nThe path for the same is:-\n");
    	printPath(&vertexList[officeSrNo]);
    	printf("\b\b\b  \n\nTotal minimum distance travelled = %d\n\n",vertexList[officeSrNo].key);
    }
    else
    	printf("\n\nNo required path exists between randomly choosen pairs of home and office.\n\n");

	return 0;
} //end main

