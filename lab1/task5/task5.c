#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <limits.h> 
#include <math.h> 
#include <ctype.h> 
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
    int n = 1;
    while (fabs(value) >= eps)
    {
        val = val * (x / n);
        if ( n == INT_MAX - 1|| sum > DBL_MAX - val ) return OVERFLOW;
        n++;
        sum += val;
        
    } 
    
    *res = sum;
    return OK;
}


int main() 
{ 
    double eps; 
    scanf("%lf", &eps); 
    
}
