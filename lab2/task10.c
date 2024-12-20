#include <stdio.h> 
#include <stdlib.h> 
#include <stdarg.h>

typedef enum  
{ 
    OK, 
    WRONG_VALUE_ERROR, 
    MEMORY_ERROR, 
    WRONG_INPUT,
    ANY
} status; 


status horner_method(double x, int degree, double* coeffs, double* res)
{
    if (coeffs == NULL || res == NULL)
    {
        return MEMORY_ERROR;
    }
    *res = 0;
    for (int i = degree; i >= 0; i--)
    {
        *res = *res * x + coeffs[i];
    }
    return OK;
}


status decompose(double eps, double a, double** res, int degree, ...)
{
    if (res == NULL)
    {
        return MEMORY_ERROR;
    }

    double* coeffs = (double*)malloc((degree + 1) * sizeof(double));
    if (coeffs == NULL)
    {
        return MEMORY_ERROR;
    }
    *res = (double*)malloc((degree + 1) * sizeof(double));
    if (*res == NULL)
    {
        free(coeffs);
        return MEMORY_ERROR;
    }

    
    va_list args;
    va_start(args, degree);
    for (int i = 0; i <= degree; ++i)
    {
        coeffs[i] = va_arg(args, double);
    }
    va_end(args);

    
    double factorial = 1.0;
    int current_degree = degree;

    for (int i = 0; i <= degree; ++i)
    {
        
        status calc_status = horner_method(a, current_degree, coeffs, *res + i);
        if (calc_status != OK)
        {
            free(coeffs);
            free(*res);
            return calc_status;
        }

        
        (*res)[i] /= factorial;
        
        
        factorial *= (i + 1);
        for (int j = 0; j < current_degree; ++j)
        {
            coeffs[j] = (j + 1) * coeffs[j + 1];
        }
        coeffs[current_degree] = 0; 
        current_degree--;
    }

    free(coeffs);
    return OK;
}

int main()
{
    double* result;
    int degree = 2;
    status st = decompose(0.00001, 3.0, &result, degree, 1.0, 2.0, 3.0);
    if (st != OK)
    {
        printf("ошибка\n");
        return st;
    }
    for (int i = 0; i <= degree; ++i) {
        printf("g%d = %f\n", i, result[i]);
    }

    // Проверка
    double x = 1.9;
    for (int i=0; i<=5; ++i)
    {
        
        x +=1.0;
        double res1 = 3.0 * x * x + 2.0 * x + 1.0;
        double res2 = 0.0;
        double gg = 1.0;
        for (int i = 0; i <= degree; ++i) {
            res2 += gg * result[i];
            gg *= (x - 3.0);
        }
        printf("при x = %lf f(x) = %lf, g(x) = %lf\n",x,  res1, res2);
    }
    free(result);
    return 0;
}
