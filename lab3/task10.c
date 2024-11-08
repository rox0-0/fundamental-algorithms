#include <string.h>
#include <stdlib.h> 
#include <stdbool.h> 
#include <stdio.h>

typedef enum 
{
    OK,
    WRONG_VALUE_ERROR,
    MEMORY_ERROR,
    WRONG_INPUT_ERROR,
    OPEN_FILE_ERROR
} status;

typedef struct Node
{
    struct Node *parent;
    struct Node *bro;
    struct Node *child;
    char data;
} Node;

status Create_tree(Node **node, char data)
{
    *node = (Node *) malloc(sizeof(Node));
    if (*node == NULL)
    {
        return MEMORY_ERROR;
    }
    (*node)->data = data;
    (*node)->parent = NULL;
    (*node)->child = NULL;
    (*node)->bro = NULL;

    return OK;
}

void delete_tree(Node* node)
{
    if (!node)
    {
        return;
    }

    delete_tree(node->child);
    delete_tree(node->bro);
    free(node);
}

status add_child(Node *node, char data)
{
    Node *tmp = (Node *) malloc(sizeof(Node));
    if (tmp == NULL)
    {
        delete_tree(node);
        return MEMORY_ERROR;
    }
    tmp->parent = node;
    tmp->data = data;
    tmp->child = NULL;
    tmp->bro = NULL;
    node->child = tmp;
    return OK;
}

status add_bro(Node *node, char data)
{
    Node *tmp = (Node *) malloc(sizeof(Node));
    if (tmp == NULL)
    {
        delete_tree(node);
        return MEMORY_ERROR;
    }
    tmp->parent = node->parent;
    tmp->data = data;
    tmp->child = NULL;
    tmp->bro = NULL;
    node->bro = tmp;
    return OK;
}

status building(char *string, Node **tree)
{
    if (Create_tree(tree, string[0]) != OK)
    {
        return WRONG_INPUT_ERROR;
    }

    int count = strlen(string);
    Node *tmp = *tree;

    for (int i = 1; i < count; i++)
    {
        switch (string[i])
        {
            case '(':
                i++;
                if (add_child(tmp, string[i]) != OK)
                {
                    delete_tree(*tree);
                    return MEMORY_ERROR;
                }
                tmp = tmp->child;
                break;

            case ',':
                i++;
                if (add_bro(tmp, string[i]) != OK)
                {
                    delete_tree(*tree);
                    return MEMORY_ERROR;
                }
                tmp = tmp->bro;
                break;
            
            case ')':
                tmp = tmp->parent;
                break;
        }
    }

    return OK;
}

void print_tree(FILE *file, Node *tree, int tab)
{
    if (tree == NULL)
    {
        return;
    }

   
    for (int i = 0; i < tab; i++) 
    {
        fprintf(file, "   ");
    }

 
    fprintf(file, "%c\n", tree->data);

  
    if (tree->child)
    {
        print_tree(file, tree->child, tab + 1);
    }
    if (tree->bro)
    {
        print_tree(file, tree->bro, tab);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("НЕВЕРНОЕ ЧИСЛО АРГУМЕНТОВ\n");
        return WRONG_INPUT_ERROR;
    }

    FILE *in;
    FILE *out;
    char str[BUFSIZ];
    status st;
    Node *tree = NULL;

    in = fopen(argv[1], "r");
    if (!in)
    {
        printf("Ошибка открытия файла \n");
        return OPEN_FILE_ERROR;
    }

    out = fopen(argv[2], "w");
    if (!out)
    {
        fclose(in);
        printf("Ошибка открытия файла \n");
        return OPEN_FILE_ERROR;
    }

    fgets(str, BUFSIZ, in);
    fclose(in);

    st = building(str, &tree);
    if (st != OK)
    {
        delete_tree(tree);
        if (st == WRONG_INPUT_ERROR)
        {
            printf("Ошибка ввода\n");
        }
        else if (st == MEMORY_ERROR)
        {
            printf("Ошибка с памятью\n");
        }
        return st;
    }

 
    print_tree(out, tree, 0);
    delete_tree(tree);
    fclose(out);

    return OK;
}
