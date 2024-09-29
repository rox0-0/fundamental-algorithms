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

int main(int argc, char* argv[])
{
    int a,b;
    int N =  rand() % (10000 - 10 + 1) ;;
    int * array = malloc(sizeof(int)*N);
    
    //srand(time(NULL));
    
    for (int i=0; i<N; ++i)
    array[i] = rand() % (1000 + 1000 + 1) - 1000;
    
    for (int i=0; i<N; ++i) printf("%d ", array[i]);
    printf("\n");
    for (int i=0; i<N; ++i) printf("%d ", array[i]);
    return OK;
    
}
