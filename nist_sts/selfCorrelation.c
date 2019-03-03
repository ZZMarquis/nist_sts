#include <math.h>
#include "include/stat_fncs.h"
#include "include/erf.h"

int SelfCorrelation(int d, int n, BitSequence *epsilon)
{
    int i = 0;
    int n_d = n - d;
    int Ad = 0;
    double V = 0.0, p_value = 0.0, sqrt2 = 1.41421356237309504880;

    for (i = 0; i < n_d - 1; ++i) {
        Ad += (epsilon[i] ^ epsilon[i + d]);
    }

    V = 2 * ((double)Ad - ((double)n_d / 2)) / sqrt(n_d);

    p_value = nist_erfc(fabs(V) / sqrt2);

    if (p_value < ALPHA) {
        return 0;
    } else {
        return 1;
    }
}

