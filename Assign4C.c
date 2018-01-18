//Siddharth Thakur, 1601CS46
//Date - 21st August, 2017
//Assign4C.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int** createMatrix(int** matrix,int flag,int** submatrix,int dim){ //function to create submatrices of required quadrant

	int i,j,ii,jj,k,l,m,n; //for iterations

	submatrix=calloc(dim/2,sizeof(int*)); //allocating space for submatrix
	for(i=0;i<dim;i++)
		submatrix[i]=calloc(dim/2,sizeof(int));

	if(flag==11){ //identifying quadrant of matrix according to flag
		i=j=0;
		ii=jj=dim/2-1;
	}
	else if(flag==12){ //setting limits of indices referring to the quadrant 
		i=0;
		ii=dim/2-1;
		j=dim-(dim+1)/2;
		jj=dim-1;	
	}
	else if(flag==21){
		i=dim/2;
		ii=dim-1;
		j=0;
		jj=dim/2-1;	
	}
	else if(flag==22){
		i=j=dim/2;
		ii=jj=dim-1;
	}

	k=l=0; //creating submatrix from required quadrant
	for(m=i;m<=ii&&k<dim/2;m++){
		l=0;
		for(n=j;n<=jj&&l<dim/2;n++){
			submatrix[k][l]=matrix[m][n];
			l++;
		}
		k++;
	}

	return submatrix; //returning submatrix
}

void printMatrix(int** matrix,int dim){ //function to print the matrix

	putchar('\0');
	
	int i,j;
	for(i=0;i<dim;i++){ //printing the matrix
		for(j=0;j<dim;j++)
			printf("%d ",matrix[i][j]);
		printf("\n");
	}
	putchar('\n');
}

int** matrixAddition(int** matrixA,int** matrixB,int** matrixC,int dim){ //function to add two matrices

	matrixC=calloc(dim,sizeof(int*)); //matrixC to store sum of matrixA & matrixB

	int i,j;
	for(i=0;i<dim;i++){ //creating matrixC
		matrixC[i]=calloc(dim,sizeof(int));
		for(j=0;j<dim;j++)
			matrixC[i][j]=matrixA[i][j]+matrixB[i][j];
	}

	return matrixC; //returning sum-matrix
}

int** matrixMultiplication(int** matrixA,int **matrixB,int** matrixC,int dim){
	//recursive function to multiply two square matrices of using divide and conquer paradigm
	
	int i,j; //for iterations

	matrixC=calloc(dim,sizeof(int*)); //to store product of two matrices
	for(i=0;i<dim;i++)
		matrixC[i]=calloc(dim,sizeof(int));

	if(dim==1){ //base case (matrix of order 1)
		matrixC[0][0]=matrixA[0][0]*matrixB[0][0];
		return matrixC;
	}

	//now dividing original matrices into 4 quadrants
	int** A11=createMatrix(matrixA,11,A11,dim); //creating quadrant submatrices
	int** A12=createMatrix(matrixA,12,A12,dim);
	int** A21=createMatrix(matrixA,21,A21,dim);
	int** A22=createMatrix(matrixA,22,A22,dim);

	int** B11=createMatrix(matrixB,11,B11,dim);
	int** B12=createMatrix(matrixB,12,B12,dim);
	int** B21=createMatrix(matrixB,21,B21,dim);
	int** B22=createMatrix(matrixB,22,B22,dim);

	int** p1; //to store products of quadrants
	int** p2;

	//now recursively multiplying quadrants and combining them to create product matrixC's quadrants
	int** C11=matrixAddition(matrixMultiplication(A11,B11,p1,dim/2),matrixMultiplication(A12,B21,p2,dim/2),C11,dim/2);
	int** C12=matrixAddition(matrixMultiplication(A11,B12,p1,dim/2),matrixMultiplication(A12,B22,p2,dim/2),C12,dim/2);
	int** C21=matrixAddition(matrixMultiplication(A21,B11,p1,dim/2),matrixMultiplication(A22,B21,p2,dim/2),C21,dim/2);
	int** C22=matrixAddition(matrixMultiplication(A21,B12,p1,dim/2),matrixMultiplication(A22,B22,p2,dim/2),C22,dim/2);
	
	//combining the 4 quadrants of matrixC together 
	int k=0,l=0;
	for(i=0;i<dim/2&&k<dim/2;i++){
		l=0;
		for(j=0;j<dim/2&&l<dim/2;j++){
			matrixC[i][j]=C11[k][l];
			l++;
		}
		k++;
	}
	k=l=0;
	for(i=0;i<dim/2&&k<dim/2;i++){
		l=0;
		for(j=dim/2;j<dim&&l<dim/2;j++){
			matrixC[i][j]=C12[k][l];
			l++;
		}
		k++;
	}
	k=l=0;
	for(i=dim/2;i<dim&&k<dim/2;i++){
		l=0;
		for(j=0;j<dim/2&&l<dim/2;j++){
			matrixC[i][j]=C21[k][l];
			l++;
		}
		k++;
	}
	k=l=0;
	for(i=dim/2;i<dim&&k<dim/2;i++){
		l=0;
		for(j=dim/2;j<dim&&l<dim/2;j++){
			matrixC[i][j]=C22[k][l];
			l++;
		}
		k++;
	}

	return matrixC; //returning the product matrixC
}
	
int main(){ //main method

	int N; //to store order of the two square matrices
	
	int** matrixA;
	int** matrixB;
	int** matrixC; //to store product of matrixA & matrixB

	int i,j; //for iterations

	printf("\nEnter the order (only one number which is some +ve integral power of '2') of square matrices to be multiplied : "); //taking inputs
	scanf("%d",&N);

	matrixA=calloc(N,sizeof(int*)); //allocating memory for matrices
	matrixB=calloc(N,sizeof(int*));

	printf("\nEnter the Matrix A (%d by %d)(conventional format) :\n\n",N,N); //taking input of matrices
	for(i=0;i<N;i++){
		matrixA[i]=calloc(N,sizeof(int));
		for(j=0;j<N;j++)
			scanf("%d",&matrixA[i][j]);
	}
	printf("\nEnter the Matrix B (%d by %d)(conventional format) : \n\n",N,N);
	for(i=0;i<N;i++){
		matrixB[i]=calloc(N,sizeof(int));
		for(j=0;j<N;j++)
			scanf("%d",&matrixB[i][j]);
	}

	matrixC=matrixMultiplication(matrixA,matrixB,matrixC,N); //function call to multiply the two matrices 

	printf("\nMatrixA * MatrixB = \n\n"); //displaying output
	printMatrix(matrixC,N);
	putchar('\n');

	return 0; //end main
}

