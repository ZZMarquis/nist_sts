#include <math.h>
#include "include/stat_fncs.h"
#include "include/erf.h"

int BinaryDerivate(int k, int n, BitSequence *epsilon, int epsilon_l)
{
    int i = 0, j = 0;
    int Sn_k = 0;
    int n_k = n - k;
    double V = 0.0, p_value = 0.0, sqrt2 = 1.41421356237309504880;

    for (i = 0; i < k; ++i) {
        for (j = 0; j < epsilon_l - 1; ++j) {
            epsilon[j] = epsilon[j] ^ epsilon[j + 1];
        }
    }

    for (i = 0; i < n_k; ++i) {
        Sn_k += (2 * (int)epsilon[i]) - 1;
    }

    V = fabs(Sn_k) / sqrt(n_k);

    p_value = nist_erfc(fabs(V) / sqrt2);

    if (p_value < ALPHA) {
        return 0;
    } else {
        return 1;
    }
}