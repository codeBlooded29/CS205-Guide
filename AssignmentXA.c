//Siddharth Thakur, 1601CS46
//Date - 23rd October, 2017
//AssignmentXA.c

#include <stdio.h> //including necessary header files
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

typedef struct $ //structure definition of a student
{
	char name[6]; //name of student
	int* alphaCount; //count of alphabets
	int ASCIIsum; 
	int srno; //serial number
	int parent; //parent in DFS tree
	int seen;
	int key;

}STUDENT;

void getAllPairsMinCostPath(int*** D,int*** PI,int** distMatrix,int N){ 
//function to implement the Floyd-Warshall algorithm and compute shortest time and path matrices
	
	D[0]=(int**)calloc(N+1,sizeof(int*)); //initializations
	PI[0]=(int**)calloc(N+1,sizeof(int*));
	
	int i,j,k;
	for(i=1;i<=N;i++){
		D[0][i]=(int*)calloc(N+1,sizeof(int));
		PI[0][i]=(int*)calloc(N+1,sizeof(int));
		for(j=1;j<=N;j++){
			D[0][i][j]=distMatrix[i][j];
			if(i==j)
				PI[0][i][j]=0;
			else
				PI[0][i][j]=i;
		}
	}

	for(k=1;k<=N;k++){ //Floyd-Warshall algorithm implementation

		D[k]=(int**)calloc(N+1,sizeof(int*));
		PI[k]=(int**)calloc(N+1,sizeof(int*));

		for(i=1;i<=N;i++){

			D[k][i]=(int*)calloc(N+1,sizeof(int));
			PI[k][i]=(int*)calloc(N+1,sizeof(int));

			for(j=1;j<=N;j++){

				int min=D[k-1][i][j];
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

void dfs(int idx,int** directAccessMatrix,int* seen,int N){
//recursive function to implement DFS algorithm
	
	seen[idx]=1;
	int i;
	for(i=1;i<=N;i++){
		if(directAccessMatrix[idx][i]==1){
			if(seen[i]==0)
				dfs(i,directAccessMatrix,seen,N);
		}
	}
}

int main(){ //main method
	
	int N; //total number of students
	int dTh; //Threshold distance

	printf("\nEnter total number of students:- \n");
	scanf("%d",&N);

	STUDENT* studentList=(STUDENT*)calloc(N+1,sizeof(STUDENT)); //list of students
	
	int i,j,k; //taking inputs
	printf("\nEnter the (5-letters) names (lower case) of %d students:-\n\n",N);
	for(i=1;i<=N;i++){ //taking inputs

		studentList[i].ASCIIsum=0;

		printf("(%d)  ",i);
		scanf("%s",studentList[i].name);
		studentList[i].alphaCount=(int*)calloc(26,sizeof(int));
		for(j=0;j<5;j++){
			studentList[i].ASCIIsum+=(int)studentList[i].name[j];
			studentList[i].alphaCount[studentList[i].name[j]-'a']++;
		}

		studentList[i].srno=i;
		studentList[i].seen=0;
	}

	int** distMatrix=(int**)calloc(N+1,sizeof(int*));
	for(i=1;i<=N;i++){ //creating direct distance between two words

		distMatrix[i]=(int*)calloc(N+1,sizeof(int));
		for(j=1;j<=N;j++){
			distMatrix[i][j]=0;
			
			for(k=0;k<5;k++)
				distMatrix[i][j]+=abs(studentList[i].name[k]-studentList[j].name[k]);
		}
	}

	/*printf("\n\nDistMatrix : \n");
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			printf(" %d ",distMatrix[i][j]);
		}
		putchar('\n');
	}*/
	
	int*** PI=(int***)calloc(N+1,sizeof(int**)); //to store PI(k)(preceding vertex) matrices
	int*** D=(int***)calloc(N+1,sizeof(int**)); //to store D(k)(shortest distance) matrices
	getAllPairsMinCostPath(D,PI,distMatrix,N); //function call
	int** minPathMatrix=D[N]; //minimum time matrix

	/*printf("\n\nminPathMatrix : \n");
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			printf(" %d ",minPathMatrix[i][j]);
		}
		putchar('\n');
	}*/

	printf("\nEnter the threshold distance:- ");
	scanf("%d",&dTh);

	int** directAccessMatrix=(int**)calloc(N+1,sizeof(int*));
	for(i=1;i<=N;i++){ //finding out who has direct access to whose accounts
		
		directAccessMatrix[i]=(int*)calloc(N+1,sizeof(int));
		for(j=1;j<=N;j++){

			if(i==j){
				directAccessMatrix[i][j]=1;
				continue;
			}
	
			int c=0;
			for(k=0;k<26;k++){
				if(studentList[i].alphaCount[k]!=studentList[j].alphaCount[k])
					c++;
			}
			if(c<=2){
				if(minPathMatrix[i][j]<dTh&&minPathMatrix[j][i]<dTh){
					if(studentList[i].ASCIIsum<studentList[j].ASCIIsum)
						directAccessMatrix[i][j]=1;
				}
			}
		}
	}

	/*printf("\n\ndirectAccessMatrix : \n");
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			printf(" %d ",directAccessMatrix[i][j]);
		}
		putchar('\n');
	}*/

	int** accessMatrix=calloc(N+1,sizeof(int*)); 
	for(i=1;i<=N;i++)
		accessMatrix[i]=calloc(N+1,sizeof(int));

	for(i=1;i<=N;i++){ //using dfs to find out passive account access authorisation

		int* seen=(int*)calloc(N+1,sizeof(int));
		dfs(i,directAccessMatrix,seen,N);
		for(j=1;j<=N;j++){
			if(seen[j]==1)
				accessMatrix[i][j]=1;
		}
	}

	/*printf("\n\naccessMatrix : \n");
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			printf(" %d ",accessMatrix[i][j]);
		}
		putchar('\n');
	}*/

	int n;
	printf("\nEnter the number of names in the set whose 'Access Analysis' is required:- ");
	scanf("%d",&n);
	char** namesSet=(char**)calloc(n,sizeof(char*));

	printf("\nEnter the %d names (5-letters) (lower case) in the set:- \n",n);
	for(i=0;i<n;i++){
		
		namesSet[i]=(char*)calloc(6,sizeof(char));
		printf("(%d) ",i+1);
		scanf("%s",namesSet[i]);
	}

	//displaying the output
	printf("\nAccounts Access Information:- \n");
	printf("\nName	 : 	 Accessors\n");
	for(i=0;i<n;i++){
		for(j=1;j<=N;j++){
			if(strcmp(namesSet[i],studentList[j].name)==0)
				break;
		}
		studentList[j].seen=1;
	}

	for(i=1;i<=N;i++){
		if(studentList[i].seen==1){
			printf("\n %s 	 :	 ",studentList[i].name);
			for(k=1;k<=N;k++){
				if(studentList[k].seen==1&&accessMatrix[i][k]==1)
					printf("%s , ",studentList[k].name);
			}
			printf("\b\b  ");
		}
	}
	printf("\n\n");

	return 0;
} //end main

