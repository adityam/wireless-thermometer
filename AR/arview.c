#include "stdio.h"
#include "stdlib.h"
#include "math.h"

/*
   Determine various stats for AR models 
*/

#define TRUE  1
#define FALSE 0
#define MAXORDER 100
#define MAXLENGTH 10000

int main(int argc,char **argv)
{
   int i,j;
   int length=0;
   double *series = NULL;
   int order=0;
   double arcoeff[MAXORDER];
   double est;
   double mean=0,rmserror=0;
   FILE *fptr;

   series = malloc(MAXLENGTH*sizeof(double));

   /* Check arguments */
   if (argc < 3) {
      fprintf(stderr,"Usage: %s seriesfile arfile\n",argv[0]);
      exit(0);
   }

   /* Read the series file */
   if ((fptr = fopen(argv[1],"r")) == NULL) {
      fprintf(stderr,"Unable to open series file\n");
      exit(0);
   }
   while (fscanf(fptr,"%lf",&(series[length])) == 1) {
      mean += series[length];
      length++;
   }
   fclose(fptr);
   mean /= length;
   for (i=0;i<length;i++)
      series[i] -= mean;

   /* Read the coefficient file */
   if ((fptr = fopen(argv[2],"r")) == NULL) {
      fprintf(stderr,"Unable to open ar coefficient file\n");
      exit(0);
   }
   while (fscanf(fptr,"%lf",&(arcoeff[order])) == 1)
      order++;
   fclose(fptr);

   /* Generate a series of the same length from the coefficients */
   rmserror = 0;
   for (i=0;i<length;i++) {
      est = 0;
      if (i > order) {
         for (j=0;j<order;j++) 
            est += arcoeff[j] * series[i-j-1];
         rmserror += (est - series[i]) * (est - series[i]);
      }
      printf("%g %g\n",series[i],est);
   }

   fprintf(stderr,"%d %d %g\n",length,order,sqrt(rmserror/length));

	exit(0);
}









