// Implements a dictionary's functionality
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 190788;

// Number of words within the dictionnary
int words = 0;

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *list = table[index];
    while (list != NULL)
    {
        if (strcasecmp(word, list->word) == 0)
        {
            return true;
        }
        list = list->next;
    }
    return false;
}


// Hashes word to a number using djb2 function
unsigned int hash(const char *word)
{
    
    unsigned long hashvalue = 5381;
    int c;

    while ((c = tolower(*word++)))
    {
        hashvalue = ((hashvalue << 5) + hashvalue) + c; /* hash * 33 + c */
    }
    return hashvalue % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Setting head node
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        printf("Can't open dictionary");
        return false;
    }
    
    char buffer[LENGTH + 1];
    
    while (fscanf(file, "%s", buffer) != EOF)
    {
        words++;
        
        node *n = malloc(sizeof(node));
        
        if (n == NULL)
        {
            
            printf("Out of memory!");
            return false;
        }
        
        strcpy(n->word, buffer);
        n->next = NULL;
        unsigned int index = hash(buffer);
        
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        
        else
        {
            n->next = table[index]->next;
            table[index]->next = n;
        }
        
    }
    
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *list = table[i];
        while (list != NULL)
        {
            node *tmp = list->next;
            free(list);
            list = tmp;
        }
    }
    return true;
}
