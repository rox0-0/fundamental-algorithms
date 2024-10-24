#include <stdarg.h>
#include <stdio.h>
//#include <string.h>
#include <stdlib.h>

typedef enum
{
    OK,
    WRONG_INPUT_ERROR, 
    MEMORY_ERROR,
    FILE_OPEN_ERROR
} status;

int mystrlen(const char * s)
{
    int k =0;
    while (*s != '\0')
    {
        s++;
        k++;
    }
    return k;
}

// префикс функция
void computeLPSArray(char* pattern, int M, int* lps)
{
    int length = 0;  
    lps[0] = 0; 
    int i = 1;

    while (i < M)
    {
        if (pattern[i] == pattern[length])
        {
            length++;
            lps[i] = length;
            i++;
        }
        else  
        {
            if (length != 0)
            {
            
                length = lps[length - 1];
            }
            else  
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// КМП
char* KMPsearch(char* pattern, char* text)
{
    int M = mystrlen(pattern);  
    int N = mystrlen(text);     
    int* lps = (int*)malloc(M * sizeof(int));
    if (!lps)
    {
        return NULL;  
    }


    computeLPSArray(pattern, M, lps);

    int i = 0;  
    int j = 0;  
    while (i < N)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        if (j == M)
        {
            
            free(lps);
            return &text[i - j];
        }
        else if (i < N && pattern[j] != text[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    
    free(lps);
    return NULL;
}

status finding_substr(char *substring, FILE* file, char *file_name)
{

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);  


    char *file_content = (char *)malloc(file_size + 1);
    if (!file_content) {
        return MEMORY_ERROR;
    }

    
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0';  

    
    char *current_pos = file_content;
    int found = 0;
    int line = 1;  
    long global_offset = 0;  
    char *line_start = file_content;  

    
    while ((current_pos = KMPsearch(substring, current_pos)) != NULL)
    {
        found = 1;

        
        while (line_start < current_pos)
        {
            if (*line_start == '\n') {
                line++;
                global_offset = line_start - file_content + 1; 
            }
            line_start++;
        }

        
        int position_in_line = (current_pos - (file_content + global_offset)) + 1;

        
        printf("Файл %s: подстрока найдена в строке %d на позиции %d\n", file_name, line, position_in_line);

        
        current_pos++;
    }

    free(file_content);

    if (!found) {
        printf("В файле %s подстрока не найдена\n", file_name);
        return WRONG_INPUT_ERROR;
    }

    return OK;
}

status files_reading(char *substring, int count, ...)
{
    va_list ptr;
    va_start(ptr, count);

    for (int i = 0; i < count; i++)
    {
        char *file_name = va_arg(ptr, char*);
        FILE *file = fopen(file_name, "r");
        if (!file)
        {
            return FILE_OPEN_ERROR;
        }

        if (finding_substr(substring, file, file_name) != OK)
        {
            fclose(file);
            return WRONG_INPUT_ERROR;
        }
        fclose(file);
    }
    va_end(ptr);
    
    return OK;
}

int main()
{
    char *sub = "aaa";  
    char *file_1 = "file1";  

    int count = 1;  // Количество файлов

    status result = files_reading(sub, count, file_1);

    if (result == WRONG_INPUT_ERROR)
    {
        printf("Внимание, есть файл(ы), где заданная подстрока не найдена\n");
        return WRONG_INPUT_ERROR;
    }
    else if (result == FILE_OPEN_ERROR)
    {
        printf("Ошибка открытия файла\n");
        return FILE_OPEN_ERROR;
    }
    else 
    {
        printf("Збс\n");
    }

    return OK;
}
