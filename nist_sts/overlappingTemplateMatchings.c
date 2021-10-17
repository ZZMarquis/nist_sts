#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "include/externs.h"
#include "include/cephes.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
               O V E R L A P P I N G  T E M P L A T E  T E S T
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
double	Pr(int u, double eta);

int
OverlappingTemplateMatchings(int m, int n, BitSequence *epsilon)
{
    int ret = 0;
	int				i, k, match;
	double			W_obs, eta, sum, chi2, p_value, lambda;
	int				M, N, j, K = 5;
	unsigned int	nu[6] = { 0, 0, 0, 0, 0, 0 };
	double			pi[6] = { 0.143783, 0.139430, 0.137319, 0.124314, 0.106209, 0.348945 };
	BitSequence		*sequence;

	M = 1032;
	N = n/M;
	
	if ( (sequence = (BitSequence *) calloc(m, sizeof(BitSequence))) == NULL ) {
        return 0;
	}
	else {
        for (i = 0; i < m; i++)
            sequence[i] = 1;
    }
	
	lambda = (double)(M-m+1)/pow(2,m);
	eta = lambda/2.0;
	sum = 0.0;
	for ( i=0; i<K; i++ ) {			/* Compute Probabilities */
		pi[i] = Pr(i, eta);
		sum += pi[i];
	}
	pi[K] = 1 - sum;

	for ( i=0; i<N; i++ ) {
		W_obs = 0;
		for ( j=0; j<M-m+1; j++ ) {
			match = 1;
			for ( k=0; k<m; k++ ) {
				if ( sequence[k] != epsilon[i*M+j+k] )
					match = 0;
			}
			if ( match == 1 )
				W_obs++;
		}
		if ( W_obs <= 4 )
			nu[(int)W_obs]++;
		else
			nu[K]++;
	}
	sum = 0;
	chi2 = 0.0;                                   /* Compute Chi Square */
	for ( i=0; i<K+1; i++ ) {
		chi2 += pow((double)nu[i] - (double)N*pi[i], 2)/((double)N*pi[i]);
		sum += nu[i];
	}
	p_value = cephes_igamc(K/2.0, chi2/2.0);

	if ( isNegative(p_value) || isGreaterThanOne(p_value) ) {
        goto end;
    }
    if (p_value < ALPHA) {
        goto end;
    }

    ret = 1;

    end:
	free(sequence);
    return ret;
}

double
Pr(int u, double eta)
{
	int		l;
	double	sum, p;
	
	if ( u == 0 )
		p = exp(-eta);
	else {
		sum = 0.0;
		for ( l=1; l<=u; l++ )
			sum += exp(-eta-u*log(2)+l*log(eta)-cephes_lgam(l+1)+cephes_lgam(u)-cephes_lgam(l)-cephes_lgam(u-l+1));
		p = sum;
	}
	return p;
}
