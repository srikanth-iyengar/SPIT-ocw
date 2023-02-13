#include<stdio.h>
#include<math.h>

#define max 64  // Define the maximum length of the signals

void Circular(float *x, int N, float *h, float *y);  // Prototype for the circular convolution function

int main()
{
    int i,j,k,L,M,N;  // Variables for looping
    float x[max],y[max];  // Arrays to store the signals
    float h[max];

    // Initialize the arrays to zero
    for(i=0;i<max;i++)
    {
        x[i]=0; h[i]=0; y[i]=0;
    }
  
    // Get the length of the first signal
    printf("Enter the length of x[n] L = : ");
    scanf("%d",&L);
    
    // Get the values of the first signal
    printf( "Enter the values of x[n] : ");
    for(i=0;i<L;i++)
    {
		scanf("%f",&x[i]);
    }
    
    // Get the length of the second signal
    printf("Enter the length of h[n] M = : ");
    scanf("%d",&M);
    
    // Get the values of the second signal
    printf( "Enter the values of h[n] : ");
    for(i=0;i<M;i++)
    {
	scanf("%f",&h[i]);
    }

    // Determine the length of the result
    if( L > M )
        N = L;
    else 
        N = M;
    
    // Call the circular convolution function
    Circular(x, N, h, y);

    // Print the signals and the result
    printf("\n\n x[n] = " );
    for(i=0;i<N;i++)	
    	printf("  %4.2f  ",x[i]);

    printf("\n\n h[n] = " );
    for(i=0;i<N;i++)    
    	printf("  %4.2f  ",h[i]);

    printf("\n\n y[n] = " );
    for(i=0;i<N;i++)    
    	printf("  %4.2f  ",y[i]);
    	
    printf("\n\n");

}

/**************************************************************************/

void Circular(float *x, int N, float *h, float *y)
{
     
        int i,j,k,p,q,s,t;
        float sum=0,temp[1024],signal[1024];

  	// reverse the signal h[] 
	j=0;
	for(i=0;i<N;i++) {
	    j = N-1-i;
	    temp[i]=h[j];
  	}

  	// calculate the circular convolution of x and h
  	for(s=0;s<N;s++)
  	{
		p=0;
		for(t=0;t<N;t++)
		{
	   		if(t<=s) {
	      			q=t-s+N-1;
	      			signal[t]=temp[q];
	   		}
	   		else {
	       			signal[t]=temp[p];
	       			p++;
	   		}
		}
		sum=0;
		for(i=0;i<N;i++) {
	     		sum += x[i] * signal[i];
		}
		y[s]=sum;
  	} 
}