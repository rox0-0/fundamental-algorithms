#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include <locale.h>
typedef enum
{
    OK,
    WRONG_INPUT_ERROR, 
    MEMORY_ERROR
} status;
status my_strlen(const char * s, int * length)
{
    *length = 0;
    int k =0;
    while (*s != '\0')
    {
        s++;
        k++;
    }
    *length = k;
    return OK;
}
int is_alpha(char c)
{
    if ((c>='a' && c<='z')||(c>='A' && c<='Z'))
    {
        return 1;
    }
    return 0;
}

int is_num(char c)
{
    if (c>='0' && c<='9')
    {
        return 1;
    }
    return 0;
}
status reverse(const char *s, char ** reversed)
{
    int length =0 ;
    if (my_strlen(s, &length)!=OK) return WRONG_INPUT_ERROR;
    char * s2;
    s2 = (char *)malloc(sizeof(char) * (length + 1));
    if (s2 ==NULL) return MEMORY_ERROR;
    for (int i =0; i<length; ++i)
    {
        s2[i]=s[length - i -1];
    }
    s2[length] = '\0';
    *reversed = s2;
    
    return OK;
}

status upper_for_odd(const char *s, char ** newstring)
{
    int length =0 ;
    if (my_strlen(s, &length)!=OK) return WRONG_INPUT_ERROR;
    char * odded;
    odded = (char *)malloc(sizeof(char) * (length + 1));
    if (odded == NULL) return MEMORY_ERROR;
    for (int i =0; i<length; ++i)
    {
        if (i&1)
        {
            if (s[i]>='a' && s[i]<='z')
            {
                odded[i]=s[i]-'a' +'A';
            }
            
            else odded[i] = s[i];
        }
        else odded[i] = s[i];
    }   
    odded[length]='\0';
    *newstring = odded;
    return OK;
}

status n_flag(const char * s, char ** newstring)
{
    int length =0 ;
    if (my_strlen(s, &length)!=OK) return WRONG_INPUT_ERROR;
    char * s2;
    s2 = (char *)malloc(sizeof(char) * (length + 1));
    if (s2 ==NULL) return MEMORY_ERROR;
    int j =0;
    for (int i=0; i<length; ++i) //числа
    {
        if (s[i]>='0' && s[i]<='9')
        {
            s2[j++] = s[i];
        }
    }
    
    for (int i=0; i<length; ++i) //буквы
    {
        if (is_alpha(s[i]))
        {
            s2[j++] = s[i];
        }
    }
    
    for (int i=0; i<length; ++i) //не буквы и не числа
    {
        if (!is_alpha(s[i]) && !is_num(s[i]))
        {
            s2[j++] = s[i];
        }
    }
    s2[length]='\0';
    *newstring = s2;
    return OK;
    
}
status shuffling(char ** strings, int count)
{
    char * temp;
    int index;
    for (int i=0;i<count;++i)
    {
        index = rand()%count;
        temp = strings[i];
        strings[i] = strings[index];
        strings[index]=temp;
    }
    
}

status concatination(char * s1, char * s2)
{
    while (*s1 != '\0') s1++;
    while(*s2 != '\0')
    {
        *s1 = *s2;
        s1++;
        s2++;
    }
    *s1 = '\0';
}


status concatenate(char **res,unsigned int seed,  int count, char **strings )
{
    srand(seed);
    int length = 0;
    char * result;
    for (int i = 0; i < count; ++i)
    {
        int current_length = 0;
        my_strlen(strings[i], &current_length);
        length += current_length;
    }

    result = (char*)malloc(sizeof(char) * (length + 1));
    if (result == NULL)
    {
        return MEMORY_ERROR;
    }
    result[0]='\0';
    shuffling(strings, count);
    for (int i = 0; i < count; ++i)
    {
        concatination(result, strings[i]);
    }

    *res = result;
    return OK;
}

int main(int argc, char * argv[])
{
    if (argc < 3 || !(argv[1][0] == '-')) 
    {
        printf("Неправильный ввод\n");
        return WRONG_INPUT_ERROR;
    }
    
    char flag;
    int count;
    int length;
    unsigned int seed;
    char *reversed, *upped, *newstring, *concatenated;
    char *s = argv[2];  
    my_strlen(argv[1], &length);
    if (length!=2) 
    {
        printf("Неправильный ввод\n");
        return WRONG_INPUT_ERROR;
    }
    flag = argv[1][1];
    switch (flag)
    {
        case 'l':
            if (my_strlen(s, &length) == OK) 
                printf("%d\n", length);
            break;
        
        case 'r':
            if (reverse(s, &reversed) == OK) 
            {
                printf("%s\n", reversed);
                free(reversed);
            }
            else 
            {
                printf("MEMORY_ERROR\n");
                return MEMORY_ERROR;
            }
            break;
        
        case 'u':
            if (upper_for_odd(s, &upped) == OK)
            {
                printf("%s\n", upped);
                free(upped);
            }
            else 
            {
                printf("MEMORY_ERROR\n");
                return MEMORY_ERROR;
            }
            break;
        
        case 'n':
            if (n_flag(s, &newstring) == OK)
            {
                printf("%s", newstring);
                free(newstring);
            }
            else 
            {
                printf("MEMORY_ERROR\n");
                return MEMORY_ERROR;
            }
            break;
        
        case 'c':
            if (argc < 4 || sscanf(argv[3], "%u", &seed) != 1 || argv[3][0]=='-')
            {
                
                printf("Неправильный ввод\n");
                return WRONG_INPUT_ERROR;
            }
            printf("seed: %u\n", seed );
            count = argc - 3;
            char **strings = (char**)malloc(sizeof(char*) * count);
            if (strings == NULL) 
            {
                printf("Ошибка выделения памяти\n");
                return MEMORY_ERROR;
            }
            strings[0] = argv[2];
            for (int i = 1; i < count; ++i)
            {
                strings[i] = argv[i + 3];
            }
            if (concatenate(&concatenated, seed, count, strings) == OK)
            {
                printf("%s", concatenated);
                free(concatenated);
            }
            else 
            {
                printf("MEMORY_ERROR\n");
                return MEMORY_ERROR;
            }
            free(strings);
            break;
        
        default:
            printf("Неправильный флаг\n");
            return WRONG_INPUT_ERROR;
    }

    return OK;
}
