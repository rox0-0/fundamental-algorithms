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
 
long int comb(int m, int k) 
{ 
    if (k == 0 || k == m || m == 0) 
        return 1;
    return faq(m)/(faq(k)*faq(m-k)); 
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
                root = (int)pow(k, 1. / 2.0);
            }
        s2 += 1.0 / pow((int)root, 2.0) - 1.0 / k;
    } 
    return s2 -pow(PI, 2)/6; 
}

double eq_pi(double eps)
{
    
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
}
