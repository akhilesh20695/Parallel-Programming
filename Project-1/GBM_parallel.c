#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "normsinv.h"

int main()
{
	int len;
    unsigned int myseed = rand();   
    int i;    
    long double randomnum[100000];
    long double mu,sigma,stockprice_initial,temp,temp2,stockprice[100000],time,dt;


	printf("Enter Initial stock price : $");
    scanf("%Lg",&stockprice_initial);

    printf("Enter the expected return: ");
    scanf("%Lg",&mu);

    printf("Enter the standard deviation of returns: ");
    scanf("%Lg",&sigma);

    printf("Enter the time: ");
    scanf("%Lg",&time);    

    printf("Enter number of simulations: ");
    scanf("%d",&len);
    dt=time/(len-1);
    stockprice[0]=stockprice_initial;


    #pragma omp parallel default(none) shared(randomnum,len,myseed,dt,stockprice,mu,sigma)
    {	
	    int i;    
		#pragma omp for
	    for(i=0; i<len; i++)
	    	{
	    		long double temp = ((long double)rand_r(&myseed))/((long double)RAND_MAX);
		   		randomnum[i] = normsinv(temp);	   		
	    	}       
    }
    #pragma omp parallel default(none) shared(randomnum,len,dt)
    {
    	int i;
    	#pragma omp for
    	for(i=1;i<len;i++)
    	{
    		 randomnum[i]=randomnum[i]+sqrt(dt)*randomnum[i-1];
    	}
    }


    #pragma omp parallel default(none) shared(randomnum,len,)
    {
    	int i;
    	#pragma omp for 
    	for(i = 1; i < len; ++i)
    	{
    		stockprice[i]=stockprice[0]*exp((mu-(pow(sigma,2))*0.5)*(i-1)*dt + sigma*randomnum[i]);
    	}
    }

    for(i=0;i<len;i++)
    {
        printf("%d : %Lg\n",i,stockprice[i]);
    }

    FILE *fp = fopen("StockPrice.txt", "w");
    for(i=0;i<len-1;i++)
    {
        fprintf(fp, "%Lg", stockprice[i]);
        fprintf(fp, "\n");
    }
    fprintf(fp, "%Lg", stockprice[len-1]);
    fclose(fp);
    return 0;
}