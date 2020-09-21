#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"

/* Return true (non-zero) if c is a whitespace character ('\t' or ' ').
   Zero terminators are not printable (therefore false) */
int space_char(char c)
{
  if ((c == '\t' || c == ' ') && c != '\0')
  {
    return 1;
  }
  return 0;
}

/* Return true (non-zero) if c is a non-whitespace 
   character (not tab or space).  
   Zero terminators are not printable (therefore false) */
int non_space_char(char c)
{
  if (space_char(c) == 0 && c != '\0')
  {
    return 1;
  }
  return 0;
}

/* Returns a pointer to the first character of the next 
   space-separated word in zero-terminated str.  Return a zero pointer if 
   str does not contain any words. */
char *word_start(char *str)
{
  char *new_pointer = str;
  while(space_char(*new_pointer)) { new_pointer++; }
  return new_pointer;
}

/* Returns a pointer terminator char following *word */
char *word_terminator(char *word)
{
  char *new_terminator = word;
  while(non_space_char(*new_terminator)) { new_terminator++; }
  return new_terminator;
}

/* Counts the number of words in the string argument. */
int count_words(char *str)
{
  // Count the number of spaces in the string
  int spaces = 0;
  for (int i = 0; i < str[i] != '\0'; i++) {
    if (space_char(str[i])) { spaces++; }
  }
  return spaces + 1;
}

/* Returns a freshly allocated new zero-terminated string 
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len)
{
  char *c = malloc((len + 1) * sizeof(char));
  for (int i = 0; i < len; i++) { c[i] = inStr[i]; }
  c[len] = 0;
  return c;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" 
     tokens[3] = 0
*/
char **tokenize(char *str)
{
  // Tokens should be an array of pointers
  int num_words = count_words(str);
  char **tokens = malloc(sizeof(char*) * (num_words + 1));
  for (int i = 0; i < num_words; i++) {
    str = word_start(str);
    char *temp = word_terminator(str);
    tokens[i] = copy_str(str, (temp - str) / sizeof(char));
    str = temp;
  }
  tokens[num_words] = 0;
  return tokens;
}

/* Prints all tokens. */
void print_tokens(char **tokens)
{
  for (int i = 0; tokens[i] != 0; i++) {
    printf("%d = %s\n", i, tokens[i]);
  }
}

/* Frees all tokens and the vector containing them. */
void free_tokens(char **tokens)
{
  for (int i = 0; tokens[i] != 0; i++) {
    free(tokens[i]);
  }
  free(tokens);
}

