#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "include/externs.h"
#include "include/cephes.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
                A P P R O X I M A T E  E N T R O P Y   T E S T
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int
ApproximateEntropy(int m, int n, BitSequence *epsilon)
{
	int				i, j, k, r, blockSize, seqLength, powLen, index;
	double			sum, numOfBlocks, ApEn[2], apen, chi_squared, p_value;
	unsigned int	*P;

	seqLength = n;
	r = 0;
	
	for ( blockSize=m; blockSize<=m+1; blockSize++ ) {
		if ( blockSize == 0 ) {
			ApEn[0] = 0.00;
			r++;
		}
		else {
			numOfBlocks = (double)seqLength;
			powLen = (int)pow(2, blockSize+1)-1;
			if ( (P = (unsigned int*)calloc(powLen,sizeof(unsigned int)))== NULL ) {
				return 0;
			}
			for ( i=1; i<powLen-1; i++ )
				P[i] = 0;
			for ( i=0; i<numOfBlocks; i++ ) { /* COMPUTE FREQUENCY */
				k = 1;
				for ( j=0; j<blockSize; j++ ) {
					k <<= 1;
					if ( (int)epsilon[(i+j) % seqLength] == 1 )
						k++;
				}
				P[k-1]++;
			}
			/* DISPLAY FREQUENCY */
			sum = 0.0;
			index = (int)pow(2, blockSize)-1;
			for ( i=0; i<(int)pow(2, blockSize); i++ ) {
				if ( P[index] > 0 )
					sum += P[index]*log(P[index]/numOfBlocks);
				index++;
			}
			sum /= numOfBlocks;
			ApEn[r] = sum;
			r++;
			free(P);
		}
	}
	apen = ApEn[0] - ApEn[1];
	
	chi_squared = 2.0*seqLength*(log(2) - apen);
	p_value = cephes_igamc(pow(2, m-1), chi_squared/2.0);

	if ( m > (int)(log(seqLength)/log(2)-5) ) {
        return 0;
	}

    if (p_value < ALPHA) {
        return 0;
    } else {
        return 1;
    }
}