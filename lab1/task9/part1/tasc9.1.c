#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <limits.h> 
#include <math.h> 
#include <ctype.h> 

typedef enum  
{ 
    OK, 
    WRONG_VALUE_ERROR, 
    MEMORY_ERROR, 
    WRONG_INPUT_ERROR,
    ANY
} status; 
status swapping(int * array, int N)
{
    int min = 0, max = 0, t;
    if (N < 1) return WRONG_INPUT_ERROR;
    for (int i = 0; i < N; ++i)
    {
        if (array[i] > array[max]) max = i;
        if (array[i] < array[min]) min = i;
    }

    t = array[max];
    array[max] = array[min];
    array[min] = t;

    return OK;
}
int main(int argc, char* argv[])
{
    int a,b;
    int N = 10;
    int static_array[N];
    if (argc!=3||sscanf(argv[1], "%d", &a) != 1||(sscanf(argv[2], "%d", &b) != 1))
    {
        printf("Неправильный ввод\n" );
        return WRONG_INPUT_ERROR;
    }
    if (a>b) 
    {
        printf("Неправильный ввод\n");
        return WRONG_INPUT_ERROR;
    }
    //srand(time(NULL));
    
    for (int i=0; i<N; ++i)
    static_array[i] = rand() % (b - a + 1) + a;
    
    for (int i=0; i<N; ++i) printf("%d ", static_array[i]);
    printf("\n");
    if (swapping(static_array, N)==OK)
    for (int i=0; i<N; ++i) printf("%d ", static_array[i]);
    else  
    {
        printf("Неправильный ввод\n");
        return WRONG_INPUT_ERROR;
    }
    return OK;
    
}
