#include <stdio.h>
#include <stdlib.h>
#include "math.h"

#define TRUE  1
#define FALSE 0
#define MAXCOEFF 100

#include "ar.h"

int main(int argc,char **argv)
{
   int     length=0,degree;
   double  d,*data = NULL;
   double  *coefficients = NULL;
   FILE    *fptr;
   int     i,method=-1;

	/* Maximum number of coefficients */
	if ((coefficients = malloc(MAXCOEFF*sizeof(double))) == NULL) {
      fprintf(stderr,"Failed to allocate space for coefficients\n");
      exit(-1);
   }

   /* Check the arguments */
   if (argc != 4) {
      fprintf(stderr,"Usage: %s degree method[m,l] filename\n",argv[0]);
      exit(1);
   }
   if ((degree = atoi(argv[1])) >= MAXCOEFF) {
      fprintf(stderr,"Maximum degree is %d\n",MAXCOEFF-1);
      exit(-1);
   }
   if (argv[2][0] == 'm') {
      method = MAXENTROPY;
   } else if (argv[2][0] == 'l') {
      method = LEASTSQUARES;
   } else {
      fprintf(stderr,"Didn't get a valid method\n");
      exit(-1);
   }
   
   /* Open the file */
   if ((fptr = fopen(argv[3],"r")) == NULL) {
      fprintf(stderr,"Unable to open data file\n");
      exit(0);
   }

   /* Read as many points as we can */
   while (fscanf(fptr,"%lf",&d) == 1) {
		if ((data = realloc(data,(length+1)*sizeof(double))) == NULL) {
         fprintf(stderr,"Memory allocation for data failed\n");
         exit(-1);
      }
		data[length] = d;
      length++;
   }
   fclose(fptr);
	fprintf(stderr,"Read %d points\n",length);
      
   /* Calculate and print the coefficients */
   if (!AutoRegression(data,length,degree,coefficients,method)) {
      fprintf(stderr,"AR routine failed\n");
      exit(-1);
   }
   for (i=0;i<degree;i++)
      printf("%lf\n", coefficients[i]);

	exit(0);
}

#include "ar.c"


