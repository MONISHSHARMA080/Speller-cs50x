// Implements a dictionary's functionality
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"
// node/linked list for hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

   const unsigned int N = 675;

 // Represents hash table
    node *h_t[N];

//tells if moving to a new place in hash table --> by --> if(hahs(word)!=prev) update prev
int prev = -1;

bool load(const char *dictionary)
{
  FILE *file = fopen(dictionary,"r");
   if(file == NULL)
   {
    printf("FAILED TO OPEN YOUR FILE .");
    unload();
    return false;
   }
   char word[LENGTH + 1];
 while(fscanf(file,"%s",word)!= EOF)
      {
        node *no = malloc(sizeof(node));
      if (no == NULL)
    {
        fclose(file);
        return false;
    }
    //entering word in link list
       strcpy(no->word,word);
       // this will happen when moving to a new place in hash table
       if (hash(word)> prev)
          {
            // if seg fault may be malloc next
           no->next=NULL;
           h_t[hash(word)]= no;
           prev++;
          }
       else
        {
           no->next=h_t[hash(word)];
           h_t[hash(word)]=no;
        }
      }
  fclose(file);
    if(N==prev)
    {
      return true;
    }
    else
    {
      return false;
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
int b = 26*(toupper(word[0])-'A') + toupper(word[1])-'A';
    return b;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return prev;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
int p =0;
while(p!=26*26 -1)
{
  // moving forward will be in while loop, but should work too as in last line ptr=temp
  node *ptr=h_t[p];
    while(ptr!=NULL)
    {
      node *temp = ptr->next;
      free(ptr);
      ptr=temp;
    }
 p+=1;
}
// free(n);
// don't free(h_t); as it is non-heap object
if (p!=prev)
    {
      return false;
    }
    else
    {
      return true;
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
  //go to hash table (by hash()) check all nodes in linked list to see if present ,if not (or pointed at null) return false
 node *m = h_t[hash(word)];
int p = 0;
char *wrd = malloc(sizeof(char)*(LENGTH +1));
//checking if at the end of
if (wrd == NULL)
{
  return false;
}
while(word[p]!='\0')
  {
   wrd[p]= tolower(word[p]);
   p+=1;
  }
  wrd[p] = '\0';
while(strcmp(m->word,wrd)!=0)
{
  if(m==NULL)
  {
    return false;
    free(wrd);
  }
  if (strcmp(m->word, wrd) == 0)
        {
            free(wrd);
            return true;
        }
 m=m->next;
  }
  return true;
  free(wrd);
}