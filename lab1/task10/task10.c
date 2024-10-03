#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <limits.h> 
#include <math.h> 
#include <ctype.h> 
#define ll long int; 

typedef enum  
{ 
    OK, 
    WRONG_VALUE_ERROR, 
    MEMORY_ERROR, 
    WRONG_INPUT_ERROR,
    ANY
} status; 
 
status checking_input(const char * s, const int base)
{
    if (!s) return MEMORY_ERROR;
    int i = 0;
    if (s[0]=='-')
    {   
        if (s[0]=='-' && s[1]=='\0') return WRONG_INPUT_ERROR;
        i++;
    }

   
    
    if (base>10)
    {
        while(s[i]!='\0')
        {
            if (s[i] - 'a' + 10 >= base || (s[i]<='Z' && s[i] >= 'A')||((s[i]>'z' || s[i] < 'a') && !(s[i]>='0' && s[i]<='9')) ) return WRONG_INPUT_ERROR;
            i++;
        }
    }
    else 
    {
        while (s[i]!='\0')
        {
            if (s[i]-'0'>=base||(s[i]<'0' || s[i]>'9')) return WRONG_INPUT_ERROR;
            i++;
            
        }
    }
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


int main(int argc, char*argv[]) 
{ 
    int base;
    scanf("%d", &base);
    char  s[BUFSIZ];
    if (base<2 || base>36)
    {
        printf("неправильное основание \n");
        return WRONG_INPUT_ERROR;
    }
    int max = INT_MIN;
    int ans;
    while(1) 
    {
        scanf("%s", s);
        if (strcmp(s, "stop") == 0)
        {
            break;
        }
        if (checking_input(s, base)==WRONG_INPUT_ERROR){printf("вронг инпут\n"); return WRONG_INPUT_ERROR;}
        if (base_2_ten(s, base, &ans)==OK)
        max = abs(ans)>abs(max)? ans:max;
        else {printf("ошибка с памятью\n"); return MEMORY_ERROR;}
    }

    
    
    char * res;
    if (ten_2_base(max, base, &res) == OK) 
    {
        
        printf("%s\n", res);
        free(res);
    }

    if (ten_2_base(max, 9, &res) == OK) 
    {
        
        printf("%s\n", res);
        free(res);
    }
    if (ten_2_base(max, 18, &res) == OK) 
    {
        
        printf("%s\n", res);
        free(res);
    }
    if (ten_2_base(max, 36, &res) == OK) 
    {
        
        printf("%s\n", res);
        free(res);
    }

    else if(ten_2_base(max,16,&res)==MEMORY_ERROR){ printf("многа букф\n");return MEMORY_ERROR;}
    return OK;
    
}
