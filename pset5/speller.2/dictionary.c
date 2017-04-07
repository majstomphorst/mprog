/**
 * Implements a dictionary's functionality.
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

#define SIZEHASHTABLE 26

// making a stuct for a node and make linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
node *hashtable[SIZEHASHTABLE] = {NULL};

int word_counter = 0;

// void printlist (node *head);
int deload (node *head);

/**
 * Returns true if word is in dictionary else false.
 */
bool check (const char *word)
{
    int hash = tolower(word[0]) - 'a';
    node *cursor = hashtable[hash];
    
    char word_lower[LENGTH + 1];
    strncpy(word_lower, word, LENGTH + 1);
    
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else 
        {
            cursor = cursor->next;
        }
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load (const char *dictionary)
{
    // making pointer to the dictionary word
    // room for /0 
    char read_word[LENGTH + 1];
    
    // opening the dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        // unload();
        return 1;
    }
    
    while (fscanf(fp,"%s",read_word) != EOF)
    {
        // simpel hash function
        int hash = tolower(read_word[0]) - 'a';
        
        // making a pointer to node
        node *new_head = malloc(sizeof(node));
        // filling de value with a the read word
        strcpy(new_head->word, read_word);
        // head is pointing to the next
        new_head->next = hashtable[hash];
        // returing the new start of teh linklist
        hashtable[hash] = new_head;
        word_counter++;
    }
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{ 
    return word_counter;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0;i < SIZEHASHTABLE; i++)
    {
        deload(hashtable[i]);
    }
    return true;
}

int deload (node *head)
{
    // making a new pointer
    node *delete_me = head;
    
    while(head != NULL)
    {
        head = head->next;
        free(delete_me);
        delete_me = head;
  }
  free(head);
  return 0;
}