#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

#define MAX_LEN 200

int main()
{

  // Run until the user runs the !quit command
  while (1) {

    // Tell the user what they can enter
    printf("You can type anything really. Do !q to exit the program. Do !n where n is an integer to get that n-th entry you typed in earlier!\n");

    // Ask the user for input
    char input[MAX_LEN];
    int value = 0;
    printf("# ");
    fgets(input, MAX_LEN, stdin);
    sscanf(input, "%*c%d", &value); // Read the value from the input (if possible)
    
    // Check if the input starts with an !
    if (input[0] == '!') {

      // Check if the input has a q (quit)
      if (input[1] == 'q') {
	printf("Goodbye!\n");
	break;
      }

      // Check if the input is a number
      else if (value != 0) {
	printf("The number is %d! \n", value);
      }
    }

    // The input does not start with !
    else {
      printf("input: %s\n", input);
      printf("word_start: %s\n", word_start(input));
      printf("word_terminator: %s\n", word_terminator(input));
      char **tokens = tokenize(input);
      print_tokens(tokens);
    }

  }
}
