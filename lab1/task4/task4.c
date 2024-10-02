#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum 
{
    OK,
    WRONG_VALUE_ERROR,
    MEMORY_ERROR,
    WRONG_INPUT_ERROR,
    OPEN_FILE_ERROR
} status;

status delete_arabics(const char *in, const char *out)
{
    FILE *f1 = fopen(in, "r");
    FILE *f2 = fopen(out, "w");
    if (!f1 || !f2)
    {
    
    if (f1) fclose(f1);
    if (f2) fclose(f2);
    return OPEN_FILE_ERROR;
    }


    char c;
    while ((c = fgetc(f1)) != EOF)
    {
        if (c < '0' || c > '9') fputc(c, f2);
    }

    fclose(f1);
    fclose(f2);
    return OK;
}

status count_of_latin(const char *in, const char *out)
{
    FILE *f1 = fopen(in, "r");
    FILE *f2 = fopen(out, "w");
    char c;
    int k = 0;
    if (!f1 || !f2)
    {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return OPEN_FILE_ERROR;
    }
    while ((c = fgetc(f1)) != EOF)
    {
        if (isalpha(c))
        {
            k++;
        }
        if (c == '\n')
        {
            fprintf(f2, "%d\n", k);
            k = 0;
        }
    }

    fclose(f1);
    fclose(f2);
    return OK;
}

status other_symbols(const char *in, const char *out)
{
    FILE *f1 = fopen(in, "r");
    FILE *f2 = fopen(out, "w");
    char c;
    int k = 0;
    if (!f1 || !f2)
    {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return OPEN_FILE_ERROR;
    }
    while ((c = fgetc(f1)) != EOF)
    {
        fputc(c, f2);
        if (!isalpha(c) && !isdigit(c) && c != ' ')
        {
            k++;
        }
        if (c == '\n')
        {
            fprintf(f2, "%d\n", k);
            k = 0;
        }
    }

    fclose(f1);
    fclose(f2);
    return OK;
}

status ascee(const char *in, const char *out)
{
    FILE *f1 = fopen(in, "r");
    FILE *f2 = fopen(out, "w");
    char c;
    if (!f1 || !f2)
    {
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        return OPEN_FILE_ERROR;
    }
    while ((c = fgetc(f1)) != EOF)
    {
        if ((c >= '0' && c <= '9') || c == '\n')
        {
            fputc(c, f2);
        }
        else
        {
            fprintf(f2, "%X", c);
        }
    }

    fclose(f1);
    fclose(f2);
    return OK;
}

int main(int argc, char* argv[])
{
    if (argc < 3 || (argv[1][0] != '-' && argv[1][0] != '/'))
    {
        printf("INPUT ERROR\n");
        return WRONG_INPUT_ERROR;
    }

    const char *in = argv[2];
    char *out = NULL;
    char flag;
    int free_out=0;
    if (argv[1][1] == 'n' && (argc < 4 || strlen(argv[1]) != 3 || (strcmp(argv[2], argv[3]) == 0)))
    {
        printf("Неправильный ввод1\n"); 
        return WRONG_INPUT_ERROR;
    }
    else if (argv[1][1] != 'n' &&(argc != 3 || strlen(argv[1]) != 2))
    {
        printf("Неправильный ввод2\n"); 
        return WRONG_INPUT_ERROR;
    }

    if (argv[1][1] == 'n')
    {
        flag = argv[1][2];
        out = argv[3];
        if (strcmp(in, out)==0) {printf("Неправильный ввод3\n"); return WRONG_INPUT_ERROR;}
    }
    else
    {
        flag = argv[1][1];
        char *name = strrchr(in, '/');
        if (name == NULL) name = (char*)in;
        else name++;
        free_out = 1;
        out = (char*)malloc(sizeof(char) * (strlen(name) + 5));
        if (out == NULL)
        {
            printf("MEMORY ERROR\n");
            return MEMORY_ERROR;
        }
        sprintf(out, "out_%s", name);
    }
    printf("%s\n",in);
    printf("%s\n", out);
    switch (flag)
    {
    case 'd':
        if (delete_arabics(in, out) != OK){ printf("Ошибка открытия файла\n");return OPEN_FILE_ERROR;}
        break;
    case 'i':
        if (count_of_latin(in, out) != OK) { printf("Ошибка открытия файла\n");return OPEN_FILE_ERROR;}
        break;
    case 's':
        if (other_symbols(in, out) != OK) { printf("Ошибка открытия файла\n");return OPEN_FILE_ERROR;}
        break;
    case 'a':
        if (ascee(in, out) != OK) { printf("Ошибка открытия файла\n");return OPEN_FILE_ERROR;}
        break;
    default:
        printf("Неправильный ввод\n");
        return WRONG_INPUT_ERROR;
        break;
    }

    if (free_out) free(out);
    return OK;
}
