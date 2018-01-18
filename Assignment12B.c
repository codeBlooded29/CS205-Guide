//Siddharth Thakur, 1601CS46
//Date - 6th November,2017
//Assignment12B.c

#include <stdio.h> //importing necessary header files
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int min(int a,int b){ //utility functiom to return minimum of two given values

	 return a>b?b:a;
}

void dischargeVertex(int idx,int** residualGraphAdjMatrix,int* heightFunction,int* excessFlow,int N){
//utility function to discharge an overflowing vertex by PUSH and RELABEL operations

	int i,value;
	
	while(excessFlow[idx]>0){
		
		for(i=0;i<N&&excessFlow[idx]>0;i++){ //trying for possible PUSH operations
			
			if(residualGraphAdjMatrix[idx][i]>0&&(heightFunction[i]+1)==heightFunction[idx]){	
				
				value=min(excessFlow[idx],residualGraphAdjMatrix[idx][i]); //PUSHING the flow
				excessFlow[idx]-=value;
				excessFlow[i]+=value;
				residualGraphAdjMatrix[idx][i]-=value;
				residualGraphAdjMatrix[i][idx]+=value;
			}
		}

		if(excessFlow[idx]>0){ //trying for possible RELABEL operation

			int minHeigth=INT_MAX;
			for(i=0;i<N;i++){
				if(residualGraphAdjMatrix[idx][i]>0&&heightFunction[idx]<=heightFunction[i])
					if(minHeigth>heightFunction[i])
						minHeigth=heightFunction[i];
			}

			heightFunction[idx]=minHeigth+1;
		}
	}
}

void push_relabel_MaxFlowAlgorithm(int** residualGraphAdjMatrix,int* heightFunction,int* excessFlow,int N){
//function to find maximum flow in the graph by using PUSH and RELABEL operations

	int queue[N]; //circular array implementation of queue
	int start=0,end=0;

	int queueSize=0;

	int i;
	heightFunction[0]=N; //initializing PREFLOW
	
	for(i=1;i<N;i++){
		if(residualGraphAdjMatrix[0][i]>0&&heightFunction[0]>heightFunction[i]){
			
			excessFlow[i]+=residualGraphAdjMatrix[0][i];
			excessFlow[0]-=residualGraphAdjMatrix[0][i];
			residualGraphAdjMatrix[i][0]+=residualGraphAdjMatrix[0][i];
			residualGraphAdjMatrix[0][i]=0;
			
			if(excessFlow[i]>0&&i<N-1){
				queue[end++]=i;
				queueSize++;
			}
		}
	}

	int c=0;
	while(queueSize>0){ //looping for overflowing vertices

		dischargeVertex(queue[start],residualGraphAdjMatrix,heightFunction,excessFlow,N);

		for(i=1;i<N-1;i++){ //adding to queue new overflowing vertices
			if(excessFlow[i]>0){
				queue[end++]=i;
				end%=N;
				queueSize++;
			}
		}

		start++;
		start%=N;
		queueSize--;
	}
}

int main(){ //main method

	int N=71; //to store total number of cities

	char* cities[71]={"Goa","Mumbai", "Delhi", "Bangalore", "Hyderabad", "Ahmedabad", "Chennai", "Kolkata", "Surat",
					"Pune", "Jaipur", "Lucknow", "Kanpur", "Nagpur", "Visakhapatnam", "Indore", "Thane", "Bhopal", "Patna",
					"Vadodara", "Ghaziabad", "Ludhiana", "Coimbatore", "Agra", "Madurai", "Nashik", "Faridabad", "Meerut",
					"Rajkot", "Varanasi", "Srinagar", "Aurangabad", "Dhanbad", "Amritsar", "NaviMumbai", "Allahabad",
					"Ranchi", "Howrah", "Jabalpur", "Gwalior", "Vijayawada", "Jodhpur", "Raipur", "Kota", "Guwahati",
					"Chandigarh", "Solapur", "Tiruchirappalli", "Bareilly", "Moradabad", "Mysore",
					"Tiruppur", "Gurgaon", "Aligarh", "Jalandhar", "Bhubaneswar", "Salem", "Warangal", "Guntur", "Bhiwandi",
					"Saharanpur", "Gorakhpur", "Bikaner", "Amravati", "Noida", "Jamshedpur", "Bhilai", "Cuttack", "Firozabad",
					"Kochi","Thiruvananthapuram"}; //predefined list of cities

	int i,j,k;
	int** residualGraphAdjMatrix=(int**)calloc(N,sizeof(int*)); //residual graph adjacency matrix
	for(i=0;i<N;i++){
		residualGraphAdjMatrix[i]=(int*)calloc(N,sizeof(int));
		for(j=0;j<N;j++)
			residualGraphAdjMatrix[i][j]=INT_MIN;
	}
	
	int* heightFunction=(int*)calloc(N,sizeof(int)); //to store height of vertices
	int* excessFlow=(int*)calloc(N,sizeof(int)); //to store excess flow in vertices

	int* arr1=(int*)calloc(N,sizeof(int)); //counting of incoming edges
	int* arr2=(int*)calloc(N,sizeof(int)); //counting of outgoing edges

	int alphaCountI[26];
	int alphaCountJ[26];

	for(i=0;i<N;i++){ //looping through all the cities to look for possible edges between them

		for(k=0;k<26;k++)
			alphaCountI[k]=0;
		for(k=0;k<strlen(cities[i]);k++)
			alphaCountI[toupper(cities[i][k])-'A']++;
        
        for(j=0;j<N;j++){
            if(i==j)
               	continue;
        
        	for(k=0;k<26;k++)
				alphaCountJ[k]=0;
        	for(k=0;k<strlen(cities[j]);k++)
				alphaCountJ[toupper(cities[j][k])-'A']++;

            if((strlen(cities[j])-strlen(cities[i]))==1){
                int c=0;
                for(k=0;k<26;k++){
                    if(alphaCountI[k]>0&&alphaCountJ[k]>0)
                        c++;
                }

                if(c>0){ //creating edges
                    residualGraphAdjMatrix[i][j]=2*c;
                    residualGraphAdjMatrix[j][i]=0;
                    arr2[i]++;
                    arr1[j]++;
                }
     		}
        }
    }

    //int maxS=0,maxT=0;

    for(i=0;i<N;i++){ //connecting Source Goa to other cities based on give condition

    	if(arr1[i]==0){
    		residualGraphAdjMatrix[0][i]=20;
            residualGraphAdjMatrix[i][0]=0;
            arr2[0]++;
            arr1[i]++;
    	}
    }

    for(i=0;i<N;i++){ //connecting other cities to Sink Thiruvananthapuram based on give condition
    	if(arr2[i]==0){
    		residualGraphAdjMatrix[i][N-1]=20;
            residualGraphAdjMatrix[N-1][i]=0;
            arr2[i]++;
            arr1[N-1]++;
    	}
    }
  	
  	/*for(i=0;i<N;i++){
    	if(residualGraphAdjMatrix[0][i]>0)
    		maxS+=residualGraphAdjMatrix[0][i];
    	if(residualGraphAdjMatrix[i][N-1]>0)
    		maxT+=residualGraphAdjMatrix[i][N-1];
  	}*/

  	printf("\nConnected from Source Goa:- ");
    for(i=0;i<N;i++){
    	if(residualGraphAdjMatrix[0][i]>0)
    		printf("%s , ",cities[i]);
    }

    printf("\n\nConnected to Sink Thiruvananthapuram:- ");
    for(i=0;i<N;i++){
    	if(residualGraphAdjMatrix[i][N-1]>0)
    		printf("%s , ",cities[i]);
    }

  	//printf("\n\nmaxS = %d && maxT = %d\n\n",maxS,maxT);

  	/*for(i=0;i<N;i++){
  		for(j=i+1;j<N;j++){
  			if(residualGraphAdjMatrix[i][j]>INT_MIN)
  				printf("%d ",residualGraphAdjMatrix[i][j]);
  			else
  				printf("-1 ");
  		}
  		putchar('\n');
  	}
    putchar('\n');*/

    push_relabel_MaxFlowAlgorithm(residualGraphAdjMatrix,heightFunction,excessFlow,N);
    //determinig maximum flow between Goa and Thiruvananthapuram
    
    int maxFlow1=0,maxFlow2=0;
    for(i=0;i<N;i++){
    	//printf("(%d) height= %d && ",i,heightFunction[i]);
    	//printf("excessFlow= %d\n",excessFlow[i]);
    	if(residualGraphAdjMatrix[i][0]>INT_MIN)
    		maxFlow1+=residualGraphAdjMatrix[i][0];
    	if(residualGraphAdjMatrix[N-1][i]>INT_MIN)
    		maxFlow2+=residualGraphAdjMatrix[N-1][i];
    }

    //printf("\nmaxFlow1 = %d && maxFlow2 = %d\n",maxFlow1,maxFlow2);
    //printf("\nexcessFlow[0] = %d && excessFlow[N-1] = %d\n",excessFlow[0],excessFlow[N-1]);
   	
   	printf("\n\nThe maximum possible flow between Goa and Thiruvananthapuram = %d\n\n",excessFlow[N-1]);

	return 0;
} //end main

