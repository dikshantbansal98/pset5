#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>


// size of the hash table

#define maximumSizeOfHashTable 3500

// number of words loaded into the dictionary

int numberOfWords = 0;





typedef struct NODE

{

	char* word;

	struct NODE* NEXT_NODE;

}

// create an intitial linked list

NODE;

// create a hash table of linked lists

NODE* hashTable[maximumSizeOfHashTable];



/**

 * Returns the hash value of the word

 */

int hash(const char* word)

{

    int digitsOfWords = 0;

    digitsOfWords = strlen(word);

    int sum = 0;

    

    // calculates the sum of the numeric values of the characters in a 

    // specified word

    for(int i = 0; i < digitsOfWords; i++)

    {

    	sum += word[i];

    }

    return sum%maximumSizeOfHashTable;

}

	

/**

 * Returns true if word is in dictionary else false.

 */

bool check(const char* word)

{

    char UNVISITED_WORD[LENGTH+1];

    char lowerLetter;

    

    // convert all uppercase letters to lowercase

    for(int i = 0; i < strlen(word); i++)

    {

    	lowerLetter = tolower(word[i]);

    	UNVISITED_WORD[i] = (char)lowerLetter;

    }

    // terminate this word

    UNVISITED_WORD[strlen(word)] = '\0';

    

    int hashValue = hash(UNVISITED_WORD);

    // the temporary list which is used for checking

    NODE* TEMP = hashTable[hashValue];

    // if the temporary list is empty the word must be mispelled and it returns false

    if(TEMP == NULL)

    {

    	return false;

    }

    

    // if not null go through all the linked lists and if it matches word is correct and

    // it returns true

    while(TEMP != NULL)

    {

    	if(!strcmp(TEMP->word, UNVISITED_WORD))

    	{

    		return true;

    	}

    	TEMP = TEMP->NEXT_NODE;

    }

    return false;

    

}



/**

 * Loads dictionary into memory.  Returns true if successful else false

 */

bool load(const char* dictionary)

{

   FILE* fp = NULL;

   int hashValue = 0 ;

   char D_WORD[LENGTH+1];

   

   // open the dictionary

   fp = fopen(dictionary, "r");

   

   // if dictionary is empty return false

   if(fp == NULL)

   {

   	return false;

   }

   

   // read the dictionary and create the hash table

   while(fscanf(fp,"%s\n", D_WORD) != EOF)

   {

	   	// create new Node

	   	NODE* newNODE = malloc(sizeof(NODE));

         //providing maximum memory size
            	newNODE->word = malloc(strlen(D_WORD)+1);

            	// copy the new word into the linked list 

            	strcpy(newNODE->word,D_WORD);

           

           	hashValue = hash(D_WORD);

            	

            	numberOfWords++;

            	

	   	// giving node values to hash table

	   	// NODEs then the new list is made the head   	

	   	if(hashTable[hashValue] == NULL)

	   	{

	   		hashTable[hashValue] = newNODE;

	   		newNODE->NEXT_NODE = NULL;

	   	}else

	   	{

	   		newNODE->NEXT_NODE = hashTable[hashValue];

	   		hashTable[hashValue] = newNODE;

	   	}   	

   	

   }

    fclose(fp);

	return true;

}



/**

 * Returns number of words in dictionary if loaded else 0 if not yet loaded.

 */

unsigned int size(void)

{

    return numberOfWords;

}



/**

 * Unloads dictionary from memory.  Returns true if successful else false.

 */

bool unload(void)

{

	NODE* TEMP = NULL;

	NODE* TEMP2 = NULL;

	for(int i = 0; i < maximumSizeOfHashTable;i++)

	{

		TEMP = hashTable[i];

		// if there is only one linked list present free this linked list

		if(TEMP && !TEMP->NEXT_NODE)

		{

			free(TEMP->word);

			free(TEMP);

		}else

		{

			// goes through all the linked list and frees them one at a time

			while(TEMP)

			{

				TEMP2 = TEMP->NEXT_NODE;

				free(TEMP->word);

				free(TEMP);

				TEMP = TEMP2;

			}

		}

		hashTable[i] = NULL;

	}

	return true;

}