//Siddharth Thakur, 1601CS46
//Date - 14th August,2017
//assign3C.c

#include <stdio.h> 

long long int maxSubArraySum(long long int arr[],int ind1,int ind2){ //recursive function to find maximum sub-array sum

	if(ind2<=ind1) //base case
		return arr[ind1];

	int mid=(ind1+ind2)/2; //dividing array into two halves

	long long int sum1=maxSubArraySum(arr,ind1,mid-1); //(recursive call) whether max sub-array sum is in first half of array

	long long int sum2=maxSubArraySum(arr,mid+1,ind2); //(recursive call) whether max sub-array sum is in second half of array

	long long int sum3=arr[mid]; //whether max sub-array sum is across the mid boundary of array
	int i=mid;
	long long int asum=0; //buffer sum
	while(i>=ind1){ //checking max sum in left side of boundary
		asum+=arr[i];
		if(asum>sum3)
			sum3=asum;
		i--;
	}
	asum=sum3;
	i=mid+1;
	while(i<=ind2){ //checking max sum in right side of boundary
		asum+=arr[i];
		if(asum>sum3)
			sum3=asum;
		i++;
	}

	long long int max=sum1; //detecting the maximum of 3 sums
	if(max<sum2)
		max=sum2;
	if(max<sum3)
		max=sum3;
	
	return max;
}

int main(){ //main method

	int n; //to store total number of elements in array
	printf("\nEnter number of elements in array (> 0): ");
	scanf("%d",&n);
		
	long long int arr[n]; //our array
	printf("\nEnter the elements of array (space separated integers) : \n"); //taking input of elements
	int i; //for iterations
	for(i=0;i<n;i++)
		scanf("%lld",&arr[i]);
	
	long long int sum=maxSubArraySum(arr,0,n-1); //finding maximum sub-array sum
	printf("\nMaximum sub-array Sum : %lld\n\n",sum); //displaying output
	
	return 0;
} //end main
