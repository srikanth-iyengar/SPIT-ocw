#include<stdio.h>
#define N 20 // Define N as 20
#define M 10 // Define M as 10

// Function to calculate the cross-correlation of signals x[n] and h[n] and store the result in y[n]
void correlate(float* x,float* h,float* y,int lx,int lh)
{
	int i,j;
	float temp=0;
	int stx,sth;

	// Determine the start and length of non-zero elements in x[n] and h[n]
	stx=detect(x,&lx);
	sth=detect(h,&lh);

	// Print start and length of non-zero elements in x[n] and h[n]
	printf("stx = %d  lx = %d \n",stx,lx);
	printf("sth = %d  lh = %d \n",sth,lh);

	// Calculate the indices of y[n] where the cross-correlation starts and ends
	nneg=(sth-stx)+lh-1;
	npos=lx-(sth-stx);
	printf("nneg = %d  npos = %d \n\n",nneg,npos);

	// Calculate the cross-correlation of x[n] and h[n]
	for(i=-1*nneg;i<npos;i++)
	{
		temp=0;
		for(j=stx;j<(stx+lx);j++)
			temp+=x[j]*h[j-i]; // Calculate the dot product of x[n] and h[n] shifted by i samples
		y[M+i]=temp; // Store the result in y[n]
	}
}

// Function to determine the start and length of non-zero elements in a signal
int detect(float* a, int* len)
{
	int i=0,s=0;

	// Find the index of the first non-zero element in a[n]
	while(s==0 & i< *len)
	{
		if(a[M+i] != 0)
			s=1;
		i++;
	}

	// Update the length of a[n]
	*len=*len-i+1;

	// Return the start index of the non-zero elements in a[n]
	return(M+i-1);
}

// Main function
int main()
{
	int lx,lh,i;
	float x[N],h[N],y[N];

	// initialize arrays x, h, and y to 0
	for(i=0;i<N;i++)
	{
		x[i]=0;   h[i]=0;   y[i]=0;
	}

	// get the length of x[n] from the user
	printf("\nEnter the length of x[n]:");
	scanf("%d",&lx);

	// get the values of x[n] from the user
	printf("Enter values for x[n]: ");
	for(i=0;i<lx;i++)
		scanf("%f",&x[M+i]);

	// get the length of h[n] from the user
	printf("Enter the length of h[n]: ");
	scanf("%d",&lh);

	// get the values of h[n] from the user
	printf("Enter values for h[n]: ");
	for(i=0;i<lh;i++)
		scanf("%f",&h[M+i]);

	// call the correlate function to get the y[n] values
	correlate(x,h,y,lx,lh);

	// print the result y[n]
	printf("y=");
	for(i=M-nneg;i<(M+npos);i++)
		printf(" %6.2f ",y[i]);

	// print a newline to separate the result from the rest of the output
	printf("\n\n");

	return 0;
}
