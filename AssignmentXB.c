//Siddharth Thakur, 1601CS46
//Date - 23rd October, 2017
//AssignmentXB.c

#include <stdio.h> //including necessary header files
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct $ //structure definition of a city
{
	char name[20]; //name of city
	int srno;
	int parent;
	int seen;
	int key;
}CITY;

int findNearestCity(int distMatrix[8][8],int idx,CITY cityList[]){ //function to find nearest city to a given city

	int i;
	int min=INT_MAX,id;
	
	for(i=0;i<8;i++){ //checking nearest unseen city
		if(cityList[i].seen==1)
			continue;
		if(min>distMatrix[idx][i]){
			min=distMatrix[idx][i];
			id=i;
		}
	}
	return id;
}

int minDist(int distMatrix[8][8],int idx,CITY cityList[],int count){ 
//Recursive function to find total cost of complete traversal starting from a city

	if(count>=7)
		return 0;

	cityList[idx].seen=1;
	count++;
	int id=findNearestCity(distMatrix,idx,cityList);
	int val;

	cityList[idx].parent=id;
	val=distMatrix[idx][id];
	val+=minDist(distMatrix,id,cityList,count);

	return val;
}

void minCostSpanningTree(CITY cityList[],int distMatrix[8][8]){
//function to implement Prim's MST algorithm to find the most efficient and economical path  
	
	int queueSize=8;	
	int i;

	while(queueSize>0){
		
		int u;
		int key=INT_MAX;
		for(i=0;i<8;i++){
			if(cityList[i].seen==0&&cityList[i].key<key){
				key=cityList[i].key;
				u=i;
			}
		}
		queueSize--;

		cityList[u].seen=1;

		for(i=0;i<8;i++){ //looping for updating value of key
			if(cityList[i].seen==0){
				if(distMatrix[u][i]<=cityList[i].key){
					cityList[i].parent=u;
					cityList[i].key=distMatrix[u][i];
				}	
			}
		}
	}
} //end minCostSpanningTree function

void printPath(int idx,CITY cityList[]){
//Recursive function to print path of the economical complete traversal

	if(idx<0)
		return;

	printf("%s -> ",cityList[idx].name);
	printPath(cityList[idx].parent,cityList);
}

int main(){ //main method
	
	CITY cityList[8]; //list of 8 cities
	char* cities[8]={"Chennai","Kolkata","Indore","Bangalore","Nagpur","Ranchi","Guwahati","Hyderabad"};

	int i,j;
	for(i=0;i<8;i++){ //initialising all the cities

		strcpy(cityList[i].name,cities[i]);
		cityList[i].srno=i;
		cityList[i].parent=-1;
		cityList[i].seen=0;
		cityList[i].key=INT_MAX;
	}

	int distMatrix[8][8]={{0,1400,1200,300,900,1300,1900,500}, //distance matrix from Google
						  {1400,0,1300,1600,1000,300,500,1200},
						  {1200,1300,0,1100,400,1000,1600,700}, //all distances are in Km
						  {300,1600,1100,0,900,1400,2100,500},
						  {900,1000,400,900,0,700,1400,400},
						  {1300,300,1000,1400,700,0,700,1000},
						  {1900,500,1600,2100,1400,700,0,1700},
						  {500,1200,700,500,400,1000,1700,0}};

	
	cityList[4].key=0; //Generating the MST
	minCostSpanningTree(cityList,distMatrix);
	
	int cost=0; //displaying output
	printf("\nThe Minimum Cost Spanning Tree is : - \n\n");
	printf("	City	   :	 Parent \n\n");
	for(i=0;i<8;i++){
		if(cityList[i].parent>=0)
			printf("(%d) %s	   :	%s\n",cityList[i].srno,cityList[i].name,cityList[cityList[i].parent].name);
		else
			printf("(%d) %s	   :	%s\n",cityList[i].srno,cityList[i].name,"None");
		if(cityList[i].parent!=-1)
			cost+=distMatrix[i][cityList[i].parent];
	}
	printf("\nTotal Cost of the Minimum Spanning Tree of cities (Prims Algorithm used) = %d\n",cost);

	/*for(i=0;i<8;i++){
		for(j=0;j<8;j++)
			printf(" %d ",distMatrix[i][j]);
		putchar('\n');
	}*/

	//Converting the MST into shortest traversal
	int idx,min=INT_MAX,val;
	int count;
	for(i=0;i<8;i++){ //Using the greedy method
		count=0;
		for(j=0;j<8;j++){
			cityList[j].parent=-1;
			cityList[j].seen=0;
		}
		val=minDist(distMatrix,i,cityList,count);
		if(min>=val){
			min=val;
			idx=i;
		}
	}

	count=0;
	for(j=0;j<8;j++){
			cityList[j].parent=-1;
			cityList[j].seen=0;
		}
	min=minDist(distMatrix,idx,cityList,count);

	//displaying output
	printf("\nThe minimum distance required to travel to all the cities is = %d Km\n",min);
	printf("\nThe path for the same is:-\n\n");
	printPath(idx,cityList);
	printf("\b\b\b    ");
	putchar('\n');
	putchar('\n');

	return 0;
} //end main

