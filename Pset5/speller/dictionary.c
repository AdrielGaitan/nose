// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef struct  node
{
    char  word[LENGTH + 1];
    struct node *next;
}
node;
unsigned int hash(const char *word);
const unsigned  int N = (LENGTH + 1)  * 'z';
int totalwords = 0;
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //retorna a falso si no es entero
    int index = (int)(hash(word));
    // cursor
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }

    return false;
}

//de hashes de palabras a numeros
unsigned int hash(const char *word)
{
    unsigned int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }

    return (sum % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file  = fopen(dictionary, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Has tenido un error");
        return false;
    }
    //lista de matriz de caracteres de palabras
    char wordlist[LENGTH + 1];

    //el while se usara para imprimir laas palabras en la matriz
    while (fscanf(file, "%s", wordlist) != EOF)
    {
        //se crea un nuevo nodo
        node *nuevnode = malloc(sizeof(node));
        //revision de NULL
        if (nuevnode == NULL)
        {
            return false;
        }
        //se inicializa un nuevo nodo copianlo la palabra en otro nodo
        strcpy(nuevnode -> word, wordlist);
        nuevnode -> next = NULL;

        int index = hash(wordlist);
        // si el índice aún no está asignado, coloque el nodo más nuevo al principio de este índice.
        if (table [index] == NULL)
        {
            table [index] = nuevnode;
        }
        else
        {
            nuevnode -> next = table [index];
            table [index] = nuevnode;
        }
        totalwords++;

    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (totalwords > 0)
    {
        return totalwords;
    }
    //se le da seguimiento a la cantidad de nodos agregados
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int i = 0; i < N ; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;

        while (cursor != NULL)
        {
            cursor = cursor-> next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
