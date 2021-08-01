// Implements a dictionary's functionality
#include <cs50.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

#define LENGTH 45
int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int TABLE_SIZE = 1000;

// Hash table
node *table[TABLE_SIZE];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char temp[strlen(word)];
    strcpy(temp, word);
    for(int i = 0, n = strlen(temp); i < n; i++)
    {
        temp[i] = tolower(temp[i]);
    }
    unsigned int index = hash(temp);
    if(table[index] != NULL)
    {
        node *cursor = table[index];
        while(cursor != NULL)
        {
            if(strcmp(cursor->word, temp) == 0)
            {
                return true;
            }
            else
            {
                cursor = cursor->next;
            }
        }
    }
    return false;
}

//hash formula created by deliberate think for CS50 Pset5
unsigned int hash(const char *word)
{
    int hash = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (isalpha(word[i]))
        {
            n = word[i] - 'a' + 1;
        }
        else
        {
            n = 27;
        }
        hash = ((hash << 3) + n) % TABLE_SIZE;
    }
    return hash;
}



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *temp_dict = fopen(dictionary, "r");
    if (temp_dict == NULL)
    {
        printf("File not found\n");
        return 2;
    }

    char temp[LENGTH + 1];
    while (fscanf(temp_dict, "%s", temp) != EOF)
    {
        //increase node_count
        word_count++;
        ///create new node
        node *new_node = calloc(1, sizeof(node));

        if (new_node == NULL)
        {
            unload();
            return false;
        }
        /// link the word to the node
        strcpy(new_node->word, temp);
        /// hash the word
        unsigned int index = hash(temp);
        /// if is the first element in the linked list
        if (table[index] == NULL)
        {
            table[index] = new_node;
        }

        /// if isn't the first element
        else if (table[index] != NULL)
        {
            new_node->next = table[index];
            table[index] = new_node;
        }
    }
    fclose(temp_dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if(word_count != 0)
    {
        unsigned int size = word_count;
        return size;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if(table[i] != NULL)
        {
            node *cursor = table[i];
            while(cursor != NULL)
            {
                node *temp = cursor;
                cursor = cursor->next;
                free(temp);
            }
        }
    }
    return true;
}