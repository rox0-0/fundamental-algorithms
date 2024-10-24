#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdarg.h>
typedef enum
{
    OK,
    WRONG_INPUT_ERROR, 
    MEMORY_ERROR,
    EPSILON_ERROR
} status;

double func(double x)
{
   return 2.71*x - 1;
}

status solution(double lower_bound, double upper_bound, double eps, double (*f)(double), double *result)
{
    if (eps <= 0)
    {
        return EPSILON_ERROR;
    }
    if (f(lower_bound) * f(upper_bound) >= 0)
    {
        return WRONG_INPUT_ERROR;
    }

    double mid;
    while ((upper_bound - lower_bound) / 2.0 > eps)
    {
        mid = (lower_bound + upper_bound) / 2.0;

        if (f(mid) == 0.0)
        {
            *result = mid;
            return OK;
        }
        else if (f(mid) * f(lower_bound) < 0)
        {
            upper_bound = mid;
        }
        else
        {
            lower_bound = mid;
        }

        *result = mid;
    }

    return OK;
}

int main()
{

    double lower_bound;
    double upper_bound;
    double eps;
    
    double res = 0.0;
    printf("Введите нижнюю границу \n");
    scanf("%lf", &lower_bound);
    printf("Введите верхнюю границу\n");
    scanf("%lf", &upper_bound);
    printf("введите эпсилон \n");
    scanf("%lf", &eps);

    status st = solution(lower_bound, upper_bound, eps, func, &res);

    if (st==OK)
    {
        printf("Решение уравнения:  %lf\n", res);
    }

    else if (st == EPSILON_ERROR)
    {
        printf("Неправильное значение эпсилон\n");
    }
    else 
    {
        printf("Решений не найдено. \n");
    }

    return OK;
}
