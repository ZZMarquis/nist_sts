#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "include/externs.h"
#include "include/cephes.h"

double psi2(int m, int n, BitSequence *epsilon);

int
Serial(int m, int n, BitSequence *epsilon)
{
	double	p_value1, p_value2, psim0, psim1, psim2, del1, del2;
	
	psim0 = psi2(m, n, epsilon);
	psim1 = psi2(m - 1, n, epsilon);
	psim2 = psi2(m - 2, n, epsilon);
	del1 = psim0 - psim1;
	del2 = psim0 - 2.0*psim1 + psim2;
	p_value1 = cephes_igamc(pow(2, m-1)/2, del1/2.0);
	p_value2 = cephes_igamc(pow(2, m-2)/2, del2/2.0);

	if (p_value1 < ALPHA || p_value2 < ALPHA) {
        return 0;
	} else {
        return 1;
	}
}

double
psi2(int m, int n, BitSequence *epsilon)
{
	int				i, j, k, powLen;
	double			sum, numOfBlocks;
	unsigned int	*P;
	
	if ( (m == 0) || (m == -1) )
		return 0.0;
	numOfBlocks = n;
	powLen = (int)pow(2, m+1)-1;
	if ( (P = (unsigned int*)calloc(powLen,sizeof(unsigned int)))== NULL ) {
//		fprintf(stats[TEST_SERIAL], "Serial Test:  Insufficient memory available.\n");
//		fflush(stats[TEST_SERIAL]);
		return 0.0;
	}
	for ( i=1; i<powLen-1; i++ )
		P[i] = 0;	  /* INITIALIZE NODES */
	for ( i=0; i<numOfBlocks; i++ ) {		 /* COMPUTE FREQUENCY */
		k = 1;
		for ( j=0; j<m; j++ ) {
			if ( epsilon[(i+j)%n] == 0 )
				k *= 2;
			else if ( epsilon[(i+j)%n] == 1 )
				k = 2*k+1;
		}
		P[k-1]++;
	}
	sum = 0.0;
	for ( i=(int)pow(2, m)-1; i<(int)pow(2, m+1)-1; i++ )
		sum += pow(P[i], 2);
	sum = (sum * pow(2, m)/(double)n) - (double)n;
	free(P);
	
	return sum;
}
