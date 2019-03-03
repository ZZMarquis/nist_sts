/*
 * erf() and erfc() are not included into MSVC math library while they are part of GNU libm.
 * To compile STS using MSVC I had to add implementation of these functions below. Both
 * are taken from Numerical recipes in C.
 */
#include "include/erf.h"
#include <math.h>

double erf(double x) {
	// constants
	double t, y;
	double a1 =  0.254829592;
	double a2 = -0.284496736;     
	double a3 =  1.421413741;     
	double a4 = -1.453152027;     
	double a5 =  1.061405429;    
	double p  =  0.3275911;      
	// Save the sign of x     
	int sign = 1;     
	if (x < 0)         
		sign = -1;     
	x = fabs(x);      
	// A&S formula 7.1.26     

	t = 1.0/(1.0 + p*x);     
	y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);      
	return sign*y; 
}

double erfc(double x)
{
	double t, z, ans, result;
	z = fabs(x);
	t = 1.0 / (1.0 + 0.5 * z);

	ans=t*exp(-z*z-1.26551223+t*(1.00002368+t*(0.37409196+t*(0.09678418+
		t*(-0.18628806+t*(0.27886807+t*(-1.13520398+t*(1.48851587+
		t*(-0.82215223+t*0.17087277)))))))));

	if (x >= 0.0) {
		result = ans;
	} else {
		result = 2.0 - ans;
	}
	return result;
}
