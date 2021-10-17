#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "include/externs.h"
#include "include/cephes.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
          N O N O V E R L A P P I N G  T E M P L A T E  T E S T
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int
NonOverlappingTemplateMatchings(int m, int n, BitSequence *epsilon)
{
    int ret = 0;
	int		numOfTemplates[100] = {0, 0, 2, 4, 6, 12, 20, 40, 74, 148, 284, 568, 1116,
						2232, 4424, 8848, 17622, 35244, 70340, 140680, 281076, 562152};
	/*----------------------------------------------------------------------------
	NOTE:  Should additional templates lengths beyond 21 be desired, they must 
	first be constructed, saved into files and then the corresponding 
	number of nonperiodic templates for that file be stored in the m-th 
	position in the numOfTemplates variable.
	----------------------------------------------------------------------------*/
	unsigned int	bit, W_obs, nu[6], *Wj = NULL; 
	FILE			*fp = NULL;
	double			sum, chi2, p_value, lambda, pi[6], varWj;
	int				i, j, jj, k, match, SKIP, M, N, K = 5;
	char			directory[100];
	BitSequence		*sequence = NULL;

	N = 8;
	M = n/N;

	if ( (Wj = (unsigned int*)calloc(N, sizeof(unsigned int))) == NULL ) {
		return 0;
	}
	lambda = (M-m+1)/pow(2, m);
	varWj = M*(1.0/pow(2.0, m) - (2.0*m-1.0)/pow(2.0, 2.0*m));
	sprintf(directory, "templates/template%d", m);

	if ( ((isNegative(lambda)) || (isZero(lambda))) ||
		 ((fp = fopen(directory, "r")) == NULL) ||
		 ((sequence = (BitSequence *) calloc(m, sizeof(BitSequence))) == NULL) ) {
		goto end;
	}
	else {
		if ( numOfTemplates[m] < MAXNUMOFTEMPLATES )
			SKIP = 1;
		else
			SKIP = (int)(numOfTemplates[m]/MAXNUMOFTEMPLATES);
		numOfTemplates[m] = (int)numOfTemplates[m]/SKIP;
		
		sum = 0.0;
		for ( i=0; i<2; i++ ) {                      /* Compute Probabilities */
			pi[i] = exp(-lambda+i*log(lambda)-cephes_lgam(i+1));
			sum += pi[i];
		}
		pi[0] = sum;
		for ( i=2; i<=K; i++ ) {                      /* Compute Probabilities */
			pi[i-1] = exp(-lambda+i*log(lambda)-cephes_lgam(i+1));
			sum += pi[i-1];
		}
		pi[K] = 1 - sum;

		for( jj=0; jj<MIN(MAXNUMOFTEMPLATES, numOfTemplates[m]); jj++ ) {
			sum = 0;

			for ( k=0; k<m; k++ ) {
				fscanf(fp, "%d", &bit);
				sequence[k] = bit;
//				fprintf(stats[TEST_NONPERIODIC], "%d", sequence[k]);
			}
//			fprintf(stats[TEST_NONPERIODIC], " ");
			for ( k=0; k<=K; k++ )
				nu[k] = 0;
			for ( i=0; i<N; i++ ) {
				W_obs = 0;
				for ( j=0; j<M-m+1; j++ ) {
					match = 1;
					for ( k=0; k<m; k++ ) {
						if ( (int)sequence[k] != (int)epsilon[i*M+j+k] ) {
							match = 0;
							break;
						}
					}
					if ( match == 1 )
						W_obs++;
				}
				Wj[i] = W_obs;
			}
			sum = 0;
			chi2 = 0.0;                                   /* Compute Chi Square */
			for ( i=0; i<N; i++ ) {
//				if ( m == 10 )
//					fprintf(stats[TEST_NONPERIODIC], "%3d  ", Wj[i]);
//				else
//					fprintf(stats[TEST_NONPERIODIC], "%4d ", Wj[i]);
				chi2 += pow(((double)Wj[i] - lambda)/pow(varWj, 0.5), 2);
			}
			p_value = cephes_igamc(N/2.0, chi2/2.0);
		
			if ( isNegative(p_value) || isGreaterThanOne(p_value) ) {
//                fprintf(stats[TEST_NONPERIODIC], "\t\tWARNING:  P_VALUE IS OUT OF RANGE.\n");
                goto end;
            }

//			fprintf(stats[TEST_NONPERIODIC], "%9.6f %f %s %3d\n", chi2, p_value, p_value < ALPHA ? "FAILURE" : "SUCCESS", jj);
			if ( SKIP > 1 )
				fseek(fp, (long)(SKIP-1)*2*m, SEEK_CUR);
//			fprintf(results[TEST_NONPERIODIC], "%f\n", p_value); fflush(results[TEST_NONPERIODIC]);
			if (p_value < ALPHA) {
			    goto end;
			}
		}
	}

	ret = 1;
//	fprintf(stats[TEST_NONPERIODIC], "\n"); fflush(stats[TEST_NONPERIODIC]);

	end:
    if (Wj != NULL) {
        free(Wj);
    }
    if (fp != NULL) {
        fclose(fp);
    }
    if (sequence != NULL) {
        free(sequence);
    }
    return ret;
}
