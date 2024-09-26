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
 
status checking_imput(char * s, int base)
{
    if (!s) return MEMORY_ERROR;
    int i = 0;
    if (s[0]=='-')
    {   
        if (s[0]=='-' && s[1]=='\0') return WRONG_INPUT_ERROR;
        i++;
    }

    
    if (base>=10)
    {
        while(s[i]!='\0')
        {
            if (s[i] - 'a' + 10 >= base || (s[i]<='Z' && s[i] >= 'A')) return WRONG_INPUT_ERROR;
            i++;
        }
    }
    else 
    {
        while (s[i]!='\0')
        {
            if (s[i]-'0'>=base) return WRONG_INPUT_ERROR;
            i++;
            
        }
    }
    return OK;
} 

long long int base_2_ten(char * num, int base)
{
    long long int res = 0;
    int size = strlen(num);
    long long int power = 1;
    int sign = 1;
    if(num[0] == '-') sign = -1;
    for(int i = size - 1;  i>=0; i--){
        if(num[i] == '-' && i == 0){
            break;
        }
        if(isdigit(num[i])){
            res += (num[i] - '0') * power;
        }
        if(isalpha(num[i])){
            res += (tolower(num[i]) - 'a' + 10) * power;
        }
        power *= base;
    }
    res *=sign;
    return res;
}

status ten_2_base(int num, int base, char  * res[])
{
    int sign =1;
    if (num<0) sign = -1;
    int b = num*sign;
    int k=0;
    int a = num*sign;
    while (a>0){a /= base; k++;}
    if (sign==-1) k++;
    *res=malloc(sizeof(char)*(k+1));
    (*res)[k]='\0';
    if (*res)
    {
    int i=0;
    if (sign==-1){(*res)[0]='-'; i++;}
    while(i<k)
    {
        if (b%base<=9) (*res)[i]=b%base + '0';
        else (*res)[i]=b%base + 'a'-10;
        b/=base;
        i++;
    }
    return OK;
    }
    else return MEMORY_ERROR;
}


int main(int argc, char*argv[]) 
{ 
    int base;
    scanf("%d", &base);
    char  s[100];
    if (base<2 || base>36) return WRONG_INPUT_ERROR;
    int max = INT_MIN;
    while(1) 
    {
        scanf("%s", s);
        if (strcmp(s, "stop") == 0)
        {
            break;
        }
        if (checking_imput(s, base)==WRONG_INPUT_ERROR) return WRONG_INPUT_ERROR;
        max = abs(base_2_ten(s, base))>abs(max)? base_2_ten(s, base):max;
    }
    printf("%d\n", max);
    char * res;
    if (ten_2_base(max, 9, &res) == OK) 
    {
        
        printf("%s", res);
        free(res);
    }
    else if(ten_2_base(max,9,&res)==MEMORY_ERROR) return MEMORY_ERROR;
    return OK;
    
}
