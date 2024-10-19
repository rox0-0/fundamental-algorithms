#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <limits.h> 
#include <math.h> 
#include <ctype.h> 
#include <unistd.h>

#define ll long int; 

typedef enum 
{
    OK,
    WRONG_VALUE_ERROR,
    MEMORY_ERROR,
    WRONG_INPUT_ERROR,
    OPEN_FILE_ERROR
} status;

status compare_paths(const char *path1, const char *path2)
{
    char real_path1[PATH_MAX];
    char real_path2[PATH_MAX];


    if (realpath(path1, real_path1) == NULL)
    {
        return OPEN_FILE_ERROR;
    }

    
    if (realpath(path2, real_path2) == NULL)
    {
        
        return OPEN_FILE_ERROR; 
    }

    return strcmp(real_path1, real_path2) == 0;
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



status minbase(char * s, int * base)
{
    int length = strlen(s);
    int osn=0;
    for(int i =0;i<length; ++i)
    {
        if (s[i]>='A'&&s[i]<='Z')
        {
            osn = (s[i]-'A'+11)<=osn?osn:s[i]-'A'+11;
        }
        else if (s[i]>='a' && s[i]<='z')
        {
            osn = (s[i]-'a'+11)<=osn?osn:s[i]-'a'+11;
        }
        else if (s[i]>='0'&&s[i]<='9')
        {
            osn = (s[i]-'0'+1)<=osn?osn:s[i]-'0'+1;
        }
        else return WRONG_INPUT_ERROR;
    }
   // if (osn<2) return WRONG_INPUT_ERROR;
    *base = osn;
    return OK;
}
char * zero_remove(char * s)
{int length = strlen(s);
    int i = 0;

    
    while (s[i] == '0' && i < length - 1) 
    {
        i++;
    }

    
    if (i > 0) 
    {
        int j = 0;
        
        while (s[i] != '\0') 
        {
            s[j++] = s[i++];
        }
        s[j] = '\0';  
    }

    

    return s;
}

status file_reading(const char *in, const char *out)
{
    FILE *f1 = fopen(in, "r");
    FILE *f2 = fopen(out, "w");
    if (!f1 || !f2)
    {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return OPEN_FILE_ERROR;
    }
    
    char * str;
    str = (char *)malloc(sizeof(char)*BUFSIZ);
    if (str == NULL){
        fclose(f1);
        fclose(f2);
        return MEMORY_ERROR;
    }
    int base =0;
    int st;
    int ans;
    while (fscanf(f1, "%s", str) != EOF)
    {
        str = zero_remove(str);

        st = minbase(str, &base);

        if (st == WRONG_INPUT_ERROR)
        {
            fprintf(f2, "число: %s - ОШИБКА: НЕВОЗМОЖНО ЗАПИСАТЬ ЧИСЛО В  ДАННОЙ СИСТЕМЕ СЧИСЛЕНИЯ\n", str);
        }
        else
        {
            st = base_2_ten(str, base, &ans);
            if (st == OK)
            fprintf(f2, "число: %s мин основание:%d в десятичной:%d\n", str, base, ans);
            else
            { 
            fprintf(f2, "число: %s - ОШИБКА:ЧИСЛЕННОЕ ПЕРЕПОЛНЕНИЕ\n",str);
            };
        }
    }
    free(str);
    fclose(f1);
    fclose(f2);
    return OK;

}


int main(int argc, char* argv[])
{
    if (argc !=3)
    {
        printf("INPUT ERROR\n");
        return WRONG_INPUT_ERROR;
    }

     char *in = argv[1];
    char *out =  argv[2];
    
    if (compare_paths(argv[1], argv[2])==1) 
    {
        printf("ОДИНАКОВЫЕ ИМЕНА ФАЙЛОВ\n"); 
        return WRONG_INPUT_ERROR;
    }

    printf("входной файл %s\n",in);
    printf("выходной файл %s\n", out);
    int st = file_reading(in, out);
    if (st==WRONG_INPUT_ERROR){ printf("НЕПРАВИЛЬНЫЙ ВВОД\n"); return WRONG_INPUT_ERROR;}
    else if (st==OPEN_FILE_ERROR){printf("ОШИБКА ОТКРЫТИЯ ФАЙЛОВ\n"); return OPEN_FILE_ERROR;}
    else if (st==MEMORY_ERROR) {printf("ПЕРЕПОЛНЕНИЕ\n"); return MEMORY_ERROR;}
    else if (st==OK) file_reading(in, out);
    return OK;
}
