#include <stdlib.h> 
#include <stdbool.h> 
#include <limits.h> 
#include <math.h> 
#include <ctype.h> 
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
typedef enum 
{
    OK,
    WRONG_VALUE_ERROR,
    MEMORY_ERROR,
    WRONG_INPUT_ERROR,
    OPEN_FILE_ERROR
} status;

typedef struct
{
    int size;
    double * coords;

} vector;

status norm_one(vector *vector, int n, double *res)
{
    
    *res = 0.0;
    double tmp;
    

    for (int i = 0; i < n; i++)
    {

        tmp = fabs(vector->coords[i]);
        if (tmp > *res)
        {
            *res = tmp;
        }
    }
    return OK;
}

status norm_two(vector *vector, int n, double *res, int p) 
{
    if (p < 1) 
    {
        return WRONG_INPUT_ERROR;
    }

    double sum = 0.0;
    double tmp;

    for (int i = 0; i < n; i++) 
    {
        sum += pow(fabs(vector->coords[i]), p);
    }

    double sum_result;

    *res = pow(sum, 1.0 / p);
    return OK;
}

status matrix(int n, double ***result)
{
    double **matrix = (double**)malloc(sizeof(double*) * n);

    if (!matrix)
    {
        return MEMORY_ERROR;
    }

    for (int i = 0; i < n; i++)
    {
        matrix[i] = (double*)malloc(sizeof(double) * n);

        if (!matrix[i])
        {
            return MEMORY_ERROR;
        }

        for (int j = 0; j < n; j++)
        {
            if (j == i)
            {
                matrix[i][j] = 1;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }
    *result = matrix;
    return OK;
}

status product(int n, double *vector, double **matrix,  double **result)
{
    *result = (double*)malloc(sizeof(double) * n);

    if (!*result)
    {
        return MEMORY_ERROR;
    }

    for (int i = 0; i < n; i++)
    {
        (*result)[i] = 0.0;

        for (int j = 0; j < n; j++)
        {
            (*result)[i] += matrix[i][j] * vector[j];
        }
    }
    return OK;
}

status norm_three(int n, vector *vector, int p, double *result)
{
    double ** matr;
    double * product_res;

    status st = matrix(n, &matr);

    if (st == MEMORY_ERROR)
    {
        return MEMORY_ERROR;
    }

    st = product(n, vector->coords, matr,  &product_res);

    if (st == MEMORY_ERROR)
    {
        return MEMORY_ERROR;
    }

    for (int i = 0; i < n; i++)
    {
        *result += pow(product_res[i] * product_res[i], 1.0 / 2.0);
    }
    return OK;
}

status the_longest_vector(
    vector *max_vectors, double *res,
    status (*norm1)(vector *vector, int n, double *result),
    status (*norm2)(vector *vector, int n, double *result, int p),
    status (*norm3)(int n, vector *vector, int p, double *result),
    int dimension, int p, int count_of_vectors, ...
)
{
    double eps = __DBL_EPSILON__;
    va_list args;
    va_start(args, count_of_vectors);

    double max_res[3] = {INT_MIN, INT_MIN, INT_MIN};

    for (int i = 0; i < count_of_vectors; i++)
    {
        vector vectorr = va_arg(args, vector);
        double result[3] = {0};

        if (norm1(&vectorr, dimension, &result[0]) != OK ||
            norm2(&vectorr, dimension, &result[1], p) != OK ||
            norm3(dimension, &vectorr, p, &result[2]) != OK)
        {
            va_end(args);
            return WRONG_INPUT_ERROR;
        }

        for (int j = 0; j < 3; j++)
        {
            if (result[j] - max_res[j] > eps)
            {
                max_res[j] = result[j];
                max_vectors[j] = vectorr;
            }
        }
    }

    for (int i = 0; i < 3; i++)
    {
        res[i] = max_res[i];
    }

    va_end(args);
    return OK;
}


int main()
{
    vector v1 = {3, (double[]){1.0, -2.0, 3.0}};
    vector v2 = {3, (double[]){4.0, 5.0, -6.0}};
    vector v3 = {3, (double[]){-7.0, 8.0, 9.0}};

    vector max_vectors[3];
    double res[3];

    status st = the_longest_vector(max_vectors, res, norm_one, norm_two, norm_three, 3, 2, 3, v1, v2, v3);

    if (st == OK)
    {
        printf("Максимальные векторы для норм:\n");
        for (int i = 0; i < 3; i++)
        {
            printf("Норма №%d: %lf, вектор: {", i + 1, res[i]);
            for (int j = 0; j < max_vectors[i].size; j++)
            {
                printf("%lf ", max_vectors[i].coords[j]);
            }
            printf("}\n");
        }
    }
    else
    {
        printf("Ошибка №: %d\n", st);
        return st;
    }

    return 0;
}
