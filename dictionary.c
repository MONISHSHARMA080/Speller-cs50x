#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

const unsigned int N = 676;

node *h_t[676] = {NULL}; // Initialize the hash table with NULL pointers.

int prev = -1;

bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("FAILED TO OPEN YOUR FILE .");
        unload();
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        node *no = malloc(sizeof(node));
        if (no == NULL)
        {
            fclose(file);
            return false;
        }
        strcpy(no->word, word);
        int h = hash(word);
        no->next = h_t[h];
        h_t[h] = no;
        prev++;
    }
    fclose(file);
    return true;
}

unsigned int hash(const char *word)
{
    // You can use a more sophisticated hash function to distribute words evenly.
    // For example, you can implement a simple hash function based on the word's characters.
    unsigned int hash_val = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_val = (hash_val << 2) ^ word[i];
    }
    return hash_val % N;
}

unsigned int size(void)
{
    return prev + 1; // Add 1 to account for the loaded words.
}

bool unload(void)
{
    for (int p = 0; p < N; p++)
    {
        node *ptr = h_t[p];
        while (ptr != NULL)
        {
            node *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
    return true;
}

bool check(const char *word)
{
    int h = hash(word);
    node *m = h_t[h];
    char wrd[LENGTH + 1];
    int p = 0;
    while (word[p] != '\0')
    {
        wrd[p] = tolower(word[p]);
        p++;
    }
    wrd[p] = '\0';
    while (m != NULL)
    {
        if (strcmp(m->word, wrd) == 0)
        {
            return true;
        }
        m = m->next;
    }
    return false;
}
