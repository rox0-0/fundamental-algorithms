#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <limits.h> 
#include <math.h> 
#include <ctype.h> 
#include <stdarg.h>
#define ll long int; 

typedef enum  
{ 
    OK, 
    WRONG_VALUE_ERROR, 
    MEMORY_ERROR, 
    WRONG_INPUT,
    ANY
} status; 

typedef struct
{
    double x;
    double y;
} point;



status is_convex(int n, ...)
{
    va_list ptr;
    int a, b, c, xa, xb, xc, ya, yb, yc;
    if (n<=2) return WRONG_INPUT;
    va_start(ptr, n);
    point * dots;
    dots = va_arg(ptr,  point *);
    va_end(ptr);
    int sign =0;
    for (int i=0; i<n;++i)
    {
        a = i;
        b  =(a + 1)%n;
        c = (a + 2)%n;
        xa = dots[a].x;
        xb = dots[b].x;
        xc = dots[c].x;
        ya = dots[a].y;
        yb = dots[b].y;
        yc = dots[c].y;
        double turn = (xb - xa) * (yc - yb) - (yb - ya) * (xc - xb);

        if (turn > 0)
        {
            turn++;
        }
        else if (turn < 0)
        {
            sign++;
        }

        if (sign > 0 && turn > 0)
        {
            return WRONG_INPUT;
        }
    }
    return OK;
}
        
status poly(double * res,double point, int n, ...)
{
    
    va_list ptr;
    va_start(ptr, n);
    *res = 1.0;
    if (n >= 0)
    {
        for (int i = 0; i <= n; ++i)
        {
            *res = *res * point + va_arg(ptr, double);
        }
    }

    else if (n<0)
    {
        if (point == 0)
            return WRONG_INPUT;

        for (int i = 0; i >= n; --i)
        {
            *res = *res / point + va_arg(ptr, double);
        }
    }

    va_end(ptr);
    return OK;
}
status base_2_ten(char * num, int base, int * answer)
{
    int res = 0;
    int size = strlen(num);
     int power = 1;
    int sign = 1;
    if(num[0] == '-') sign = -1;
    for(int i = size - 1;  i>=0; i--){
        if(num[i] == '-' && i == 0){
            break;
        }
        if(isdigit(num[i])){
            if (res>INT_MAX - (num[i] - '0') * power || res < INT_MIN + (num[i] - '0') * power) return MEMORY_ERROR;
            res += (num[i] - '0') * power;
        }
        if(isalpha(num[i])){
            if (res>INT_MAX - (tolower(num[i]) - 'a' + 10) * power|| res < INT_MIN +(tolower(num[i]) - 'a' + 10) * power) return MEMORY_ERROR;

            res += (tolower(num[i]) - 'a' + 10) * power;
        }
        power *= base;
    }
    res *=sign;
    *answer = res;
    return OK;
}

status ten_2_base(int num, int base, char  * res[])
{
    if (num == 0)
    {
        char * mas = (char *)malloc(2*sizeof(char));
        if (res== NULL) return MEMORY_ERROR;
        mas[0] = '0';
        mas[1]='\0';
        *res = mas;
        return OK;
    }
    else 
    {
    int sign =1;
    if (num<0) sign = -1;
    int b = num*sign;
    int k=0;
    int a = b;
    while (a>0){a /= base; k++;}
    if (sign==-1) k++;


    char * mas =(char *) malloc(sizeof(char)*(k+1));
    
    
    if (mas)
    {
    mas[k]='\0';
    int i=0;
    if (sign==-1){mas[0]='-';}
    while(i<k && b>0)
    {
        if (b%base<10) mas[k-i-1]=b%base + '0';
        else mas[k-i-1]=b%base + 87;
        b/=base;
        i++;
    }
    *res = mas;
    return OK;
    }

    else
    {
        
        return MEMORY_ERROR;
    }
    }
}   
status caprecar(char ***res, int base, int n, ...)
{
    va_list ptr;
    int decade_res = 0;
    int square = 0;
    int length, mid;
    char *lside = NULL;
    char *rside = NULL;
    status st;

    *res = (char **)malloc(sizeof(char *) * n);
    if (*res == NULL)
    {
        return MEMORY_ERROR;
    }

    va_start(ptr, n);
    char **numbers = va_arg(ptr, char **);
    va_end(ptr);

    for (int i = 0; i < n; ++i)
    {
        st = base_2_ten(numbers[i], base, &decade_res);
        if (st != OK)
        {
            for (int j = 0; j < i; j++)
            {
                free((*res)[j]);
            }
            free(*res);
            return MEMORY_ERROR;
        }

    
        if (decade_res > sqrt(INT_MAX))
        {
            for (int j = 0; j < i; j++)
            {
                free((*res)[j]);
            }
            free(*res);
            return WRONG_INPUT;
        }


        square = decade_res * decade_res;

        char *square_res = NULL;
        st = ten_2_base(square, base, &square_res);
        if (st != OK)
        {
            for (int j = 0; j < i; j++)
            {
                free((*res)[j]);
            }
            free(*res);
            return MEMORY_ERROR;
        }

        
        length = strlen(square_res);

        
        int is_caprecar = 0;
        for (mid = 1; mid < length; ++mid)  
        {
            
            lside = (char *)malloc(sizeof(char) * (mid + 1));
            if (lside == NULL)
            {
                free(square_res);
                for (int j = 0; j < i; j++)
                {
                    free((*res)[j]);
                }
                free(*res);
                return MEMORY_ERROR;
            }

            rside = (char *)malloc(sizeof(char) * (length - mid + 1));
            if (rside == NULL)
            {
                free(square_res);
                free(lside);
                for (int j = 0; j < i; j++)
                {
                    free((*res)[j]);
                }
                free(*res);
                return MEMORY_ERROR;
            }

    
            strncpy(lside, square_res, mid);
            lside[mid] = '\0';
            strcpy(rside, square_res + mid);

            
            int l_val = 0, r_val = 0;
            st = base_2_ten(lside, base, &l_val);
            if (st != OK)
            {
                free(lside);
                free(rside);
                free(square_res);
                for (int j = 0; j < i; j++)
                {
                    free((*res)[j]);
                }
                free(*res);
                return MEMORY_ERROR;
            }

            st = base_2_ten(rside, base, &r_val);
            if (st != OK)
            {
                free(lside);
                free(rside);
                free(square_res);
                for (int j = 0; j < i; j++)
                {
                    free((*res)[j]);
                }
                free(*res);
                return MEMORY_ERROR;
            }

            
            if (l_val + r_val == decade_res)
            {
                is_caprecar = 1;
                break;
            }

            
            free(lside);
            free(rside);
        }

        free(square_res);

        
        if (is_caprecar == 1)
        {
            (*res)[i] = (char *)malloc(sizeof(char) * (strlen(numbers[i]) + 1));
            if ((*res)[i] == NULL)
            {
                for (int j = 0; j < i; j++)
                {
                    free((*res)[j]);
                }
                free(*res);
                return MEMORY_ERROR;
            }
            strcpy((*res)[i], numbers[i]);
        }
        else
        {
            (*res)[i] = NULL;
        }
    }

    return OK;
}

int main(int argc, char * argv[])
{
    double result3;
    double p = 2.0;
    printf("полиномы\n");
    if (poly(&result3, p, 2, 1.0, -2.0, 1.0) == OK) // x^2 - 2x + 1
    {
        printf("Полином для x=%lf f = %lf\n", p, result3);
    }
    else
    {
        printf(" Ошибка вычисления полинома\n");
    }

    
    char *numbers[] = {"9", "45", "297", "4879"};
    int base3 = 10;
    char **caprecar_res = NULL;
    if (caprecar(&caprecar_res, base3, 4, numbers) == OK)
    {
        printf(" капрекар числа:\n");
        for (int i = 0; i < 4; ++i)
        {
            if (caprecar_res[i] != NULL)
            {
                printf("%s является числом Капрекара\n", caprecar_res[i]);
                free(caprecar_res[i]);
            }
            else
            {
                printf("%s не является числом Капрекара\n", numbers[i]);
            }
        }
        free(caprecar_res);
    }
    else
    {
        printf(" Ошибка выполнения функции\n");
    }

    
    printf("многоугольник: \n");
    point polygon[] = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    if (is_convex(4, polygon) == OK)
    {
        printf("Многоугольник выпуклый\n");
    }
    else
    {
        printf(" Многоугольник невыпуклый\n");
    }

    return OK;

    
}
