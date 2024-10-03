#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <limits.h> 
#include <math.h> 
#include <ctype.h> 
#include <float.h> 
#define PI 3.14159265358979323846 
#define E 2.718281828459045235360
typedef enum  
{ 
    OK, 
    WRONG_VALUE_ERROR, 
    OVERFLOW
} status; 
 
status a_sum(double eps,double x, double *res)
{
    double sum = 1.0;
    double val = 1.0;
    int n = 0;
    while (fabs(val) >= eps)
    {
        n++;
        val = val * (x / n);
        if ( n == INT_MAX|| sum > DBL_MAX - val ) return OVERFLOW;
        
        sum += val;
        
        
    } 
    
    *res = sum;
    return OK;
}

status b_sum(double eps,double x, double *res)
{
    double sum = 1.0;
    double val = 1.0;
    int n = 0;
    while (fabs(val) >= eps)
    {
        n += 2;
        val =  val * (x * x )/ (n * (n - 1));
        if (DBL_MAX - val < sum) return OVERFLOW;
        sum -= val;
        n += 2;
        val=val * x * x / (n * (n - 1));
        if ( n >= INT_MAX - 4|| sum > DBL_MAX - val) return OVERFLOW;
        sum += val;
    } 
    *res = sum;
    return OK;
}

status c_sum(double eps,double x, double *res)
{
    double sum = 1.0;
    double val = 1.0;
    int n = 0;
    while (fabs(val) >= eps)
    {
        n++;
        val = val *((27 *  pow(x, 2) * pow(n, 3))/( (3 * n - 1) / (3 * n - 2)));
        if ( n == INT_MAX || sum > DBL_MAX - val) return OVERFLOW;
        sum += val;
    } 
    *res = sum;
    return OK;
}

status d_sum(double eps,double x, double *res)
{
    double s1, s2;
    double val = 0.5 * pow(x, 2);
    s1 = -0.5 * pow(x, 2);
    int n = 1;
    while (fabs(s2 - s1) >= eps)
    {
        s2 = s1;
        n++;
        val = val*pow(x, 2) / (2 * n) * (2 * n - 1);
        if ( n == INT_MAX -1 || s1 > DBL_MAX - val) return OVERFLOW;
        s1 += val;
        n++;
        val = val * pow(x, 2) / (2 * n) * (2 * n - 1);
        if (DBL_MAX - val < s1) return OVERFLOW;
        s1 -= val;
    } 
    *res = s1;
    return OK;
}


int main() 
{ 
    double eps; 
    scanf("%lf", &eps); 
    
}
