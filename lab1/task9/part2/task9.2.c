#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#define ll long int;
#define PI 3.14159265358979323846
typedef enum 
{
    OK,
    WRONG_VALUE_ERROR,
    MEMORY_ERROR,
    WRONG_INPUT_ERROR
} status;

int compare(const void * x1, const void * x2)   
{
  return ( *(int*)x1 - *(int*)x2 );            
}
int main()
{
    int * a;
    int * b;
    int * c;
     int a_size = rand()%(10001 - 10) + 10 ;
    int b_size = rand()%(10001 - 10) + 10 ; 

    
    a = malloc(sizeof (int)*(a_size));
    if (a == NULL)
    {
        printf("ошибка памяти\n");
        return MEMORY_ERROR;

    }
    b = malloc(sizeof (int)*(b_size));
     if (b == NULL)
    {
        printf("ошибка памяти\n");
        return MEMORY_ERROR;
        
    }
    
    c = malloc(sizeof(int) * (a_size));
    if (c == NULL)
    {
        printf("ошибка памяти\n");
        return MEMORY_ERROR;
        
    }
    printf("массив a\n");
    for (int i = 0; i< a_size; ++i)
    {
        a[i] = rand()%2001 - 1000;
    
        c[i] = a[i];
        printf("%d ", a[i]);
    }
    printf("\n");
    printf("массив b: ");
    for (int i= 0; i< b_size; ++i)
    {
        
        b[i] = rand()%2001 - 1000;
        printf("%d ", b[i]);
    }
    printf("\n");



    qsort(b, b_size, sizeof(int), compare);
    printf("Сортировка:");
    for (int i= 0; i< b_size; ++i)
    {
    
        printf("%d ", b[i]);
    }
    printf("\n");
    int l_bound, r_bound, t;
    for (int i = 0; i < a_size; ++i)
{
    l_bound = 0;
    r_bound = b_size - 1;
    while (l_bound <= r_bound)
    {
        t = (l_bound + r_bound) / 2;
        if (b[t] == a[i]) 
        {
            break;
        }
        else if (b[t] < a[i])
        {
            l_bound = t + 1;
        }
        else
        {
            r_bound = t - 1;
        }
    }

    if (r_bound >= 0 && abs(a[i] - b[r_bound]) <= abs(a[i] - b[l_bound]))
    {
        a[i] += b[r_bound]; 
    }
    else
    {

        a[i] += b[l_bound];
    }
}

    printf("Результат: ");
    for (int i= 0; i< a_size; ++i)
    {
    
        printf("%d ", c[i]);
    }
    printf("\n");
    free(a);
    free(b);
    free(c);
    return OK;

}
