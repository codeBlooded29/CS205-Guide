//Assignment8A.c
//Siddharth Thakur, 1601CS46
//Date - 9th October,2017

#include <stdio.h>
#include <stdlib.h>

typedef struct ${ //structure definition of a vertex
	int* list;
	char color;
	int count;
}GRAPH;

int colorGraph(GRAPH vertex[],int v){ //recursive function to attempt to color vertices of the graph with 
	//2 colors such that adjacent vertices have different colors

	char ocolor;
	if(vertex[v].color=='R')
		ocolor='B';
	else
		ocolor='R';

	int result=1;
	int i;
	for(i=0;i<vertex[v].count;i++){ //DFS type algorithm to detect if input graph is bipartite or not   
		
		if(vertex[vertex[v].list[i]].color==vertex[v].color){ //not bipartite
			result=0;
			break;
		}

		if(vertex[vertex[v].list[i]].color=='N'){ //coloring adjacent vertices
			vertex[vertex[v].list[i]].color=ocolor;
			result=colorGraph(vertex,vertex[v].list[i]); //recursive function call on colored vertices
		}
	}
	return result;
}

void generateTeams(GRAPH vertex[],int team1[],int team2[],int N){ //function to generate 2 teams with nill rivalry
	//within a team  
	
	int i;
	for(i=1;i<N+1;i++){ //dividing players into 2 teams based on color of vertices
		if(vertex[i].color=='R')
			team1[i]=i;
		else if(vertex[i].color=='B')
			team2[i]=i;
	}

	printf("\nTeam 1 : - { "); //displaying output
	for(i=1;i<N+1;i++){
		if(team1[i]!=0)
			printf("%d, ",i);
	}
	printf("\b\b }\n");
	
	printf("\nTeam 2 : - { ");
	for(i=1;i<N+1;i++){
		if(team2[i]!=0)
			printf("%d, ",i);
	}
	printf("\b\b }\n\n");		
}

int main(){ //main method
	
	srand(time(NULL));

	int N; //to store total number of players
	printf("\nEnter total number of players ( > 1) : ");
	scanf("%d",&N); 
	
	int R; //to store number pairs of players having rivalry
	printf("\nEnter the number of pairs of players having rivalry (non-negative integer) : ");
	scanf("%d",&R);
	
	GRAPH vertex[N+1]; //adjacency list representation of graph with players as vertices and edges exists
	//between players having rivalry

	int i,j;
	for(i=0;i<N+1;i++){ //intialising vertices
		vertex[i].color='N';
		vertex[i].count=0;
	}
	
	//taking inputs
	printf("\nNOTE:- Each player is denoted by a natural number (starting from 1).\n\nEnter the %d pairs of players having rivalry ( two distinct space separated natural numbers  ) :\n",R);
	
	int x,y;
	for(i=0;i<R;i++){
		printf("(%d) ",i+1);
		scanf("%d %d",&x,&y);
			
		if(vertex[x].count==0){
			vertex[x].list=(int*)calloc(1,sizeof(int));
			vertex[x].list[vertex[x].count]=y;
			vertex[x].count++;
		}
		else{
			vertex[x].list=(int*)realloc(vertex[x].list,(vertex[x].count+1)*sizeof(int));
			vertex[x].list[vertex[x].count]=y;
			vertex[x].count++;
		}
		
		if(vertex[y].count==0){
			vertex[y].list=(int*)calloc(1,sizeof(int));
			vertex[y].list[vertex[y].count]=x;
			vertex[y].count++;
		}
		else{
			vertex[y].list=(int*)realloc(vertex[y].list,(vertex[y].count+1)*sizeof(int));
			vertex[y].list[vertex[y].count]=x;
			vertex[y].count++;
		}
	}
	
	int team1[N+1],team2[N+1]; //to store 2 teams
	for(i=1;i<N+1;i++){
		team1[i]=0;
		team2[i]=0;
	}

	int result; //indicator of bipartite nature of graph
	for(i=1;i<N+1;i++){ //algorithm to color all the connected/disconnected vertices of the graph
		if(vertex[i].color=='N'){
			if(rand()%2)
				vertex[i].color='R';
			else
				vertex[i].color='B';
			result=colorGraph(vertex,i);
		}
		if(result==0){ //if the graph isn't bipartite
			printf("\nDivision into 2 teams based on the given condition isn't possible.\n\n");
			return 0;
		}
	}
	if(result==1) //displaying output
		generateTeams(vertex,team1,team2,N); //generating teams

	return 0;
} //end main

