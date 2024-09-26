#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <limits.h> 
#include <math.h> 
#include <ctype.h> 
#define ll long int; 
#define PI 3.14159265358979323846 
#define E 2.718281828459045235360
typedef enum  
{ 
    OK, 
    WRONG_VALUE_ERROR, 
    MEMORY_ERROR, 
    WRONG_INPUT_ERROR 
} status; 
 
long int faq(int  n) 
{ 
    long int res = 1; 
    if (n==0 || n==1) return 1; 
    else  
    { 
    for (int i=2; i<=n; ++i) 
    { 
        res *= i; 
    }  
    return res; 
    } 
} 
int is_prime(int p)
{
    if (p==1 || p==2) return 1;
    else 
    {
        for (int i=2; i*i<=p; ++i)
        {
            if (p%i==0)return 0;
        }
        return 1;
    }
}

double sum(int n)
{
    double res = 1;
    for (int i=2; i<=n; ++i)
    {
        res += 1.0/i;
    }
    return res;
}
double limit_e(double eps) 
{ 
    double s1=0.0; 
    double s2= 1.0; 
    int n=0; 
    while (fabs(s2-s1)>=eps) 
    { 
        n++; 
        s1 = s2; 
        s2 = pow(1.0+(1.0/n),n); 
    } 
    return s2; 
} 
 
double limit_pi(double eps) 
{ 
    int n = 1; 
    double s1=0.0; 
    double s2= 4.0; 
    while (fabs(s2-s1)>eps) 
    { 
        n++; 
        s1 = s2; 
        s2 =s2*4 *(n-1)*n/((2*n-1)*(2*n-1)); 
    } 
    return s2; 
} 
 
double limit_ln2(double eps) 
{ 
    int n = 1; 
    double s1=0; 
    double s2= 1.0; 
    while (fabs(s2-s1)>eps) 
    { 
        s1 = s2; 
        n++; 
        s2 = n *(pow(2,1.0 / n) - 1); 
    } 
    return s2; 
} 
 
double limit_sqrt2(double eps) 
{ 
    int n =1; 
    double s1 =-0.5; 
    double s2 = 0.375; 
    while (fabs(s2-s1)>eps) 
    { 
         
        n++; 
        s1 = s2; 
        s2 = s2 - (s2*s2/2) + 1; 
         
    } 
    return s2; 
 
} 
 

 
double limit_gamma(double eps) 
{ 
    double s1  = 0;
    double s2  = 1;
    int n = 1;
    while(fabs(s2-s1) >= eps)
    {
        s1 = s2;
        n = n*2;
        s2 = sum(n) - log(n);
    }
    return s2; 
} 
 
double e_row(double eps) 
{ 
    double s2 = 1; 
    int n = 1; 
    double s1 = 0; 
    unsigned long int factorial = 1; 
    while (fabs(s2-s1)>eps) 
    {
        
        s1 = s2; 
        factorial *=n; 
        s2 = s2 + 1.0/factorial;
        n++;
    } 
    return s2; 
} 
 
double pi_row(double eps) 
{ 
    double s1 = 0; 
    double s2 = 1; 
    int n =1; 
    while (fabs(s2 - s1)>= eps) 
    { 
        
        n++;
        s1 = s2; 
        s2 = s2 + pow(-1, n-1)/(2*n-1); 
        
    } 
    return s2*4; 
} 
 
double ln2_row(double eps) 
{ 
    double s1 =0; 
    double s2 =1; 
    int n = 1; 
    while (fabs(s2-s1)>=eps) 
    { 
        n++;
        s1 =s2; 
        s2 = s2 + pow(-1,n-1)/n; 
    } 
    return s2; 
} 
 
double sqrt2_row(double eps) 
{ 
    int k = 2; 
    double s1= pow(2,pow(2,-k)); 
    k++; 
    double s2 =s1*pow(2.0, 0.125); 
    double degree= 0.125; 
    while (fabs(s2- s1) >= eps) 
    { 
        s1 =s2; 
        k++; 
        degree = pow(degree,1/2); 
        s2 *= degree;  
    } 
    return s2; 
} 
 
double gamma_row(double eps) 
{ 
    double s1 = 0.0; 
    double s2 = 0.5; 
    int k = 2; 
    double root = 0.0;
    while (fabs(s2 - s1) >= eps) 
    { 

        s1 = s2;
        k++;
        root = sqrt(k);
        if (fmod(root,1.0) == 0)
            {
                k++;
                root = (int)pow(k, 1.0 / 2.0);
            }
        s2 += 1.0 / pow((int)root, 2.0) - 1.0 / k;
    } 
    return s2 -pow(PI, 2)/6; 
}

double e_eqt(double eps)
{
    double mid = 0.0;
    double left_bound = 2.0;
    double right_bound = 3.0;
    mid = (left_bound + right_bound) / 2;

    while (fabs(log(mid) - 1) > eps)
    {
        mid = (left_bound + right_bound) / 2;
        if (log(mid) < 1)
            left_bound = mid;
        else
            right_bound = mid;
    }
    return mid;
}

double pi_eqt(double eps)
{
    double mid = 0.0;
    double left_bound = 3.0;
    double right_bound = 4.0;
    mid = (left_bound + right_bound) / 2;

    while (fabs(cos(mid) + 1) > eps)
    {
        mid = (left_bound + right_bound) / 2;
        if (sin(mid) >0 )
            left_bound = mid;
        else
            right_bound = mid;
    }
    return mid;
}

double ln2_eqt(double eps)
{
    double mid = 0.0;
    double left_bound = 0.0;
    double right_bound = 1.0;
    mid = (left_bound + right_bound) / 2;

    while (fabs(pow(E, mid) -2) > eps)
    {
        mid = (left_bound + right_bound) / 2;
        if (pow(E, mid) <2 )
            left_bound = mid;
        else
            right_bound = mid;
    }
    return mid;
}

double sqrt2_eqt(double eps)
{
    double mid = 0.0;
    double left_bound = 1.0;
    double right_bound = 2.0;
    mid = (left_bound + right_bound) / 2;

    while (fabs(pow(mid, 2) -2) > eps)
    {
        mid = (left_bound + right_bound) / 2;
        if (pow(mid, 2) <2 )
            left_bound = mid;
        else
            right_bound = mid;
    }
    return mid;
}

double gamma_eqt(double eps)
{
    int p = 2;
    double s1 = 0.0;
    double s2 = log(2) * 0.5;
    double product = 0.5;
    while (fabs(s2-s1)>eps)
    {
        s1 = s2;
        while (!is_prime(p))p++;
        
        product *= (p - 1.0) / (double)p;
        s2 = log(p) * product;
    } 
    return (-log(s2));
}


int main() 
{ 
    double eps; 
    //scanf("%lf", &eps); 
    printf("%lf\n", limit_e(0.000001)); 
    printf("%lf\n", limit_pi(0.000001)); 
    printf("%lf\n", limit_ln2(0.000001)); 
    printf("%lf\n", limit_sqrt2(0.000001)); 
    printf("%lf\n", limit_gamma(0.0001)); 
    printf("%lf\n", e_row(0.000001)); 
    printf("%lf\n", pi_row(0.000001)); 
    printf("%lf\n", ln2_row(0.000001)); 
    printf("%lf\n", sqrt2_row(0.000001)); 
    printf("%lf\n", gamma_row(0.000001)); 
    printf("%lf\n", e_eqt(0.000001)); 
    printf("%lf\n", pi_eqt(0.000001));
    printf("%lf\n", ln2_eqt(0.000001));
    printf("%lf\n", sqrt2_eqt(0.000001));
    printf("%lf\n", gamma_eqt(0.000001));
}
