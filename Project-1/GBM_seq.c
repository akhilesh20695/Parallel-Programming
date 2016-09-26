#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "normsinv.h"
typedef long double ld;
int main()
{
	int len;
    unsigned int myseed = rand();   
    int i;    
    ld* randomnum=malloc(1000000*sizeof(ld));
    ld* stockprice=malloc(1000000*sizeof(ld));
    ld mu,sigma,stockprice_initial,temp,temp2,time,dt;
    


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

    stockprice[0]=stockprice_initial;

    
    for(i=0; i<len; i++)
    {
        long double temp = ((long double)rand_r(&myseed))/((long double)RAND_MAX);
        randomnum[i] = normsinv(temp);          
    }
     
    dt=time/(len-1); 

    for(i=1; i<len; i++)
    {
        randomnum[i]=randomnum[i]+sqrt(dt)*randomnum[i-1];
    }
    for(i=1;i<len;i++)
    {
        stockprice[i]=stockprice[0]*exp((mu-(pow(sigma,2))*0.5)*(i-1)*dt + sigma*randomnum[i]);
    }

    dt=time/(len-1);


    for(i=0; i<len; i++)
    {
        long double temp = ((long double)rand_r(&myseed))/((long double)RAND_MAX); //generating a random number between 0 to 65,535
                                                                                   //and dividing by 65,535
        randomnum[i] = normsinv(temp);                                             //taking the value from 'temp' and converting it into
                                                                                   //standard normal form
        randomnum[i]=randomnum[i-1]+sqrt(dt)*randomnum[i];                         //Calculating the standardized cumulative normal
                                                                                   //distribution
        stockprice[i]=stockprice[0]*exp((mu-(pow(sigma,2))*0.5)*(i-1)*dt + sigma*randomnum[i]); //putting the values in the formula
        printf("%d : %Lg\n",i,stockprice[i]);                                      //Value of the stock price after the entered profit
                                                                                   //percentage addition to previous value
    }

    FILE *fp = fopen("StockPrice.txt", "w");                                       //Storing the successive values in text file :StockPrice.txt
    for(i=0;i<len;i++)
    {
        fprintf(fp, "%Lg", stockprice[i]);
        fprintf(fp, "\n");
    }
    fclose(fp);
free(randomnum);
    
    return 0;
   }
