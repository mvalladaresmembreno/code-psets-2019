// Implements a dictionary's functionality

#include <stdbool.h>//permite usar bool como un tipo de datos, true evalua como 1 y false como 0
#include <stdio.h>//biblioteca estandar
#include <stdlib.h>//fopen, malloc, free, fscanf
#include <ctype.h>//tolower

#include "dictionary.h"

typedef struct node// el nodo funciona de manera que podamos identificar los indices de las palabras
{
    bool es_pal;
    struct node* children[27];
}
node;

node* raiz;
int tamano;
/* private functions*/
int get_char_index(char c)//evalua la palabra que recibe para poder analizar por caracteres
{
    if(c == '\'')
    {
        return 26;
    }
    else
    {
        return tolower(c) - 'a';//usamos tolower para convertir las mayusculas a minusculas
    }
}

void clean(node* x)//liberas la memoria
{
    for(int i = 0 ; i < 27 ; i++)
    {
        if(x->children[i] != NULL)
        {
            clean(x->children[i]);
        }
    }
    free(x);
}

/*public functions*/

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node* pt = raiz;
    int index;
    for (int k = 0; word[k]!='\0'; k++)
    {
        index = get_char_index(word[k]);
        pt = pt->children[index];
        if(pt == NULL)
        {
            return false;
        }
    }
    return pt->es_pal;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE* diccionario = fopen(dictionary, "r");

    if(diccionario == NULL)
    {
        return false;
    }

    raiz = malloc(sizeof(node));
    raiz->es_pal = false;

    for(int i = 0 ; i < 27 ; i++)
    {
        raiz->children[i] = NULL;
    }

    int index=0;
    char word[LENGTH+1];

    while(fscanf(diccionario, "%s\n", word) != EOF)
    {
        node* pt = raiz;
        for(int i = 0 ; word[i] != '\0'; i++)
        {
            index = get_char_index(word[i]);
            if(pt->children[index] == NULL)
            {
                node* newnode = malloc(sizeof(node));
                newnode->es_pal = false;

                for(int j = 0; j < 27; j++)
                {
                    newnode->children[j] = NULL;
                }
                pt->children[index] = newnode;
            }
            pt = pt->children[index];
        }
        pt-> es_pal = true;
        tamano++;
    }
    fclose(diccionario);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return tamano;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node* pt = raiz;
    clean(pt);
    return !false;
}
