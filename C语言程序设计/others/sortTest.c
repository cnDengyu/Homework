#include <stdio.h>

int sortTest(int argc, char** argv)
{
	int num[] = {5,8,5,2,9,1};
	int n = 6;
	int i,j,k,temp;
	printf("≈≈–Ú≤‚ ‘\n");
	errno_t err; 
	
	for(i=0; i<n-1; i++)
	{
		for(j=i+1; j<n; j++)
		{
			if(num[j]<num[i])
			{
				temp = num[j];
				num[j]=num[i];
				num[i]=temp;
			}
			
		}
	}
	
	for(i=0; i<n; i++)
	{
		printf("%d ", num[i]);
	}
	
}
