#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <limits.h> 
#include <math.h> 
#include <ctype.h> 
#define ll long int; 
//sscanf - проверка целочисленного введенного числа 
//if (sscanf("-123.45", "%lf", &d)==1) то корректно иначе нет; 
// %g экспоненциальный ввод числа %e 
typedef enum  
{ 
    OK, 
    WRONG_VALUE_ERROR, 
    MEMORY_ERROR, 
    WRONG_INPUT_ERROR,
    ANY
} status; 
 
status solution(double eps, double a, double b, double c, double * x1, double * x2)
{
    if (a < eps)
    {
        if(fabs(b)<eps && fabs(c)< eps) return ANY;
        else if (fabs(b)<eps && fabs(c)>= eps ) return WRONG_INPUT_ERROR;
        else
        {
            *x1 = -c/b;
            *x2 = -c/b;
            return OK;
        }
    }
    else 
    {
    double D=b*b-4*a*c;
    if (D<eps) return WRONG_INPUT_ERROR;
    else 
    {
        *x1 = (-b + sqrt(D))/(2*a);
        *x2 = (-b - sqrt(D))/(2*a);
        return OK;
    }
    }
}
 
int main(int argc, char*argv[]) 
{ 
    
 
    if (!(argv[1][2] =='\0' &&(argv[1][0] == '/' || argv[1][0] == '-'))) 
    { 
        printf("Неправильный ввод\n"); 
        return WRONG_INPUT_ERROR; 
    }; 
 
    double eps,a,b, c;
    long int first_number, second_number;
    switch (argv[1][1]) 
    { 
    case 'h':
    
    if (argc!=6 || (sscanf(argv[2], "%lf", &eps) != 1)||(sscanf(argv[3], "%lf", &a) != 1)||(sscanf(argv[4], "%lf", &b) != 1)
    ||(sscanf(argv[5], "%lf", &c) != 1)) return WRONG_INPUT_ERROR;
    if (eps<0)return WRONG_INPUT_ERROR;
    double x1=0, x2=0;
    printf("a=%lf, b=%lf, c=%lf\n", a, b, c);
    if (solution(eps, a, b, c, &x1, &x2) == WRONG_INPUT_ERROR) printf("Решений нет\n") ;
    else if (solution(eps, a, b, c, &x1, &x2) == ANY){ printf("Решением является любое вещественное число\n");}
    else if (solution(eps, a, b, c, &x1, &x2) == OK)
    {
        if (fabs(x1-x2)<eps) printf("x=%lf\n", x1);
        else printf("x1=%lf, x2=%lf\n", x1,x2);
    }
    
   
    printf("a=%lf, b=%lf, c=%lf\n", a, c, b);
    if (solution(eps, a, c, b, &x1, &x2) == WRONG_INPUT_ERROR) printf("Решений нет\n") ;
    else if (solution(eps, a, c, b, &x1, &x2) == ANY){ printf("Решением является любое вещественное число\n");}
    else if (solution(eps, a, c, b, &x1, &x2) == OK)
    {
        if (fabs(x1-x2)<eps) printf("x=%lf\n", x1);
        else printf("x1=%lf, x2=%lf\n", x1,x2);
    }
    
     
    printf("a=%lf, b=%lf, c=%lf\n", b, a, c);
    if (solution(eps, b, a, c, &x1, &x2) == WRONG_INPUT_ERROR) printf("Решений нет\n") ;
    else if (solution(eps, b, a, c, &x1, &x2) == ANY){ printf("Решением является любое вещественное число\n");}
    else if (solution(eps, b, a, c, &x1, &x2) == OK)
    {
        if (fabs(x1-x2)<eps) printf("x=%lf\n", x1);
        else printf("x1=%lf, x2=%lf\n", x1,x2);
    }
    
   
    printf("a=%lf, b=%lf, c=%lf\n", b, c, a);
    if (solution(eps, b, c, a, &x1, &x2) == WRONG_INPUT_ERROR) printf("Решений нет\n") ;
    else if (solution(eps, b, c, a, &x1, &x2) == ANY){ printf("Решением является любое вещественное число\n");}
    else if (solution(eps, b, c, a, &x1, &x2) == OK)
    {
        if (fabs(x1-x2)<eps) printf("x=%lf\n", x1);
        else printf("x1=%lf, x2=%lf\n", x1,x2);
    }
   
    printf("a=%lf, b=%lf, c=%lf\n", c, a, b);
    if (solution(eps, c, a, b, &x1, &x2) == WRONG_INPUT_ERROR) printf("Решений нет\n") ;
    else if (solution(eps, c, a, b, &x1, &x2) == ANY){ printf("Решением является любое вещественное число\n");}
    else if (solution(eps, c, a, b, &x1, &x2) == OK)
    {
        if (fabs(x1-x2)<eps) printf("x=%lf\n", x1);
        else printf("x1=%lf, x2=%lf\n", x1,x2);
    }
    
   
    printf("a=%lf, b=%lf, c=%lf\n", c, b, a);
    if (solution(eps, c, b, a, &x1, &x2) == WRONG_INPUT_ERROR) printf("Решений нет\n") ;
    else if (solution(eps, c, b, a, &x1, &x2) == ANY){ printf("Решением является любое вещественное число\n");}
    else if (solution(eps, c, b, a, &x1, &x2) == OK)
    {
        if (fabs(x1-x2)<eps) printf("x=%lf\n", x1);
        else printf("x1=%lf, x2=%lf\n", x1,x2);
    }
    break;
    case 'm':
    
    if (argc!=4 || (sscanf(argv[2], "%ld", &first_number) != 1) || (sscanf(argv[3], "%ld", &second_number) != 1)) return WRONG_INPUT_ERROR;
    if (first_number==0 || second_number == 0) return WRONG_INPUT_ERROR;
    if (first_number%second_number==0 && first_number>=second_number)
    {
    
        printf("Число a=%ld кратно b=%ld\n", first_number, second_number );
    }
    else
    {
        printf("Введенные числа не кратны друг другу\n");
    }
    
    break;
    
    }
    
}
