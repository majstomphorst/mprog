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

// the max size of an unsigned int 
#define SIZEHASHTABLE 65536

// making a stuct for a node and make linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
node *hashtable[SIZEHASHTABLE] = {NULL};

// a word_counter 
int word_counter = 0;

// void printlist (node *head);
int deload(node *head);
int hash(const char *str);
int hash2(const char *key);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // hashing the word
    int hashed = hash2(word);
    // assing the bucket to look in thanks to the hash
    node *bucket = hashtable[hashed];
    
    // while the bucket is not empty keep looking
    while (bucket != NULL)
    {
        // if the word in de node is the word found.
        if (strcasecmp(bucket->word, word) == 0)
        {
            return true;
        }
        // if not found look in next node 
        else 
        {
            bucket = bucket->next;
        }
    }
    // if not found 
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // making pointer to the dictionary word (+ 1 room for /0)
    char read_word[LENGTH + 1];
    
    // opening the dictionary
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return 1;
    }
    
    // readding the dictionary word for word
    while (fscanf(fp,"%s",read_word) != EOF)
    {
        // hashing the word to determen bucket
        int hashed = hash2(read_word);
        
        // making a pointer to node and allocating space
        node *new_head = malloc(sizeof(node));
        if (new_head == NULL)
        {
            fprintf(stderr, "Could not allocate space\n");
            unload();
            return 2;
        }
        
        // filling de value with a the read word
        strcpy(new_head->word, read_word);
        // head is pointing to the next
        new_head->next = hashtable[hashed];
        // returing the new start of the linklist
        hashtable[hashed] = new_head;
        // counting loaded words 
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
    // going thought all the buckets and emptying them with deload
    for (int i = 0;i < SIZEHASHTABLE; i++)
    {
        // delaods delets the node conected to a bucket
        deload(hashtable[i]);
    }
    // when done
    return true;
}

int deload(node *head)
{
    // making a new pointer
    node *delete_me = head;
    
    // to this until end is found.
    while(head != NULL)
    {
        // update head to point at next in line
        head = head->next;
        // free the old head 
        free(delete_me);
        // update delete me
        delete_me = head;
  }
    // delete the last node 
    free(head);
    return 0;
}

int hash(const char *word)
{
    // taking a random priem
    int sum = 11;
    int strl = strlen(word);
    
    // summing the asscii value's and the sum value 
    for (int i = 0; i < strl; i++)
    {
        sum = sum + tolower(word[i]);
    }
    // checking if not greather than max int 
    
    if (sum < SIZEHASHTABLE)
    {
        return sum;
    }
    else 
    {
        sum = sum % SIZEHASHTABLE;
        return sum;
    }
}

//www.reddit.com/r/cs50/comments/24b3sj/hash_function_httpsstudycs50nethashtables_question/
int hash2(const char* key)
{
   int index = 6;

    for (int i = 0; tolower(key[i]) != '\0'; i++)
    {
        index += tolower(key[i]);
    }

    if (index < SIZEHASHTABLE)
    {
        return index;
    }
    
    index = index % SIZEHASHTABLE;
    return index;
}