#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <limits.h> 
#include <math.h> 
#include <ctype.h> 
#include <float.h> 
#include <stdarg.h>



typedef enum  
{ 
    OK, 
    WRONG_VALUE_ERROR, 
    MEMORY_ERROR, 
    WRONG_INPUT,
    ANY
} status; 



status average_geometric(double * res, int count, ...)
{
    va_list ptr;
    va_start(ptr, count);
    int i;
    double p =1.0;
    for (int i =0; i<count; ++i)
    {
        p *= va_arg(ptr, double);
    }
    va_end(ptr);
    if ( p <0 && !(count&1)) return WRONG_INPUT;
    *res = pow(p, 1.0/count);
    return OK;
}


status power(double number, int degree, double * res)
{
    if (degree == 0)
    {
        * res = 1.0;
        return OK;
    }
    else if (degree == 1)
    {
        *res = number;
        return OK;
    }
    if (number>sqrt(DBL_MAX)) return WRONG_INPUT;
    status stat=0.0;
    if (degree> 0)
    {
        if (stat!= WRONG_INPUT)
        {
            stat = power(number * number, degree/2, res);
        }
        if (stat == WRONG_INPUT) return WRONG_INPUT;
        if (degree & 1)
        {
            if (*res > DBL_MAX/number) return WRONG_INPUT;
            *res = *res * number;
        }
    }
    else
    {
        stat = power(number, -degree, res);
    
        *res = 1 / (*res);
        return OK;
    }
}

int main()
{
    double res_1;
    double res_2;
    if (average_geometric(&res_1, 4, 3.0, 5.0, 6.0, 7.0)==OK) printf ("среднее геометрическое чисел %lf\n", res_1);
    if (power(2, -2, &res_1)==OK) printf("степень числа %lf\n", res_1);

    return OK;
}
