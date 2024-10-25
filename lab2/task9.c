#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define ll long int

typedef enum  
{ 
    OK, 
    MEMORY_ERROR, 
    WRONG_INPUT,
    ANY
} status;

int find_nod(int a, int b);
int prime(int x);
status is_prime_in_base(int num, int denum, int base);

int find_nod(int a, int b)
{
    a = abs(a);
    b = abs(b);
    
    while (a != 0 && b != 0)
    {
        if (a > b)
        {
            a = a % b;
        }
        else
        {
            b = b % a;
        }
    }
    
    return (a == 0) ? b : a;
}

status is_prime_in_base(int num, int denum, int base)
{
    int factor = 2;
    while (factor <= base) {
        if (base % factor == 0) {
            while (base % factor == 0)
                base /= factor;
            while (denum % factor == 0)
                denum /= factor;
        }
        factor++;
    }
    return (denum == 1) ? OK : WRONG_INPUT;
}

int prime(int x)
{
    if (x <= 1) 
        return 0;
    for (int i = 2; i * i <= x; ++i) 
        if (x % i == 0) 
            return 0;
    return 1;
}

status final_repr(double*** res, int base, int count, ...)
{
    if (base < 2 || base > 36 || count < 1)
        return WRONG_INPUT;

    *res = (double**)malloc(sizeof(double*) * count);
    if (*res == NULL)
        return MEMORY_ERROR;

    va_list ptr;
    va_start(ptr, count);
    
    for (int i = 0; i < count; i++) {
        (*res)[i] = (double*)malloc(sizeof(double) * 2);
        if ((*res)[i] == NULL) {
            for (int j = 0; j < i; j++)
                free((*res)[j]);
            free(*res);
            return MEMORY_ERROR;
        }
        
        double x = va_arg(ptr, double);
        (*res)[i][0] = x;

        int num = 1, denum = 1;
        while(x > (int)x) {
            x *= 10;
            denum *= 10;
        }
        num = (int)x;
        int nod = find_nod(num, denum);
        num /= nod;
        denum /= nod;

        status st = is_prime_in_base(num, denum, base);
        (*res)[i][1] = (st == OK) ? 1 : 0;
    }
    
    va_end(ptr);
    return OK;
}

int main()
{
    double** result;
    int base = 10;
    
    status res_status = final_repr(&result, base, 3, 1.25, 2.5, 3.75);
    
    if (res_status == OK) {
        printf("Результат:\n");
        for (int i = 0; i < 3; i++) {
            printf("Число: %lf  может иметь конечное представление в СС с основанием %d? : %s\n", result[i][0], base, result[i][1] == 1 ? "Да" : "Нет");
            free(result[i]);
        }
        free(result);
    } else {
        printf("ОШИБКА");
    }

    return 0;
}
