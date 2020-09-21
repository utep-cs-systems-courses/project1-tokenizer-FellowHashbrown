#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

#define MAX_LEN 200

void clear_buffer() {
  char c;
  while((c = getchar()) != '\n' && c != EOF);
}

int main()
{

  // Keep track of the input string and input value
  char input[MAX_LEN];
  int value = 0;
  List *history = init_history();

  // Run until the user runs the !quit command
  while (1) {

    // Tell the user what they can enter and ask for input. Separate the integer from the command if given. 
    printf("You can type anything really. \n\tDo !q to exit the program.\n\tDo !a to see sentences you've previously entered :)\n\tDo !n where n is an integer to get that n-th entry you typed in earlier!\n");
    printf("# ");
    scanf("%[^\n]s", input);
    sscanf(input, "%*c%d", &value);
    clear_buffer(); // Clear the buffer so an infinite loop does not magically appear
    char **tokens;
    
    // Check if the input starts with an !
    if (input[0] == '!') {

      // Check if the input has a q (quit)
      if (input[1] == 'q') {
	printf("Goodbye!\n");
	break;
      }

      // Check if the input has an a (history)
      else if (input[1] == 'a') {
	print_history(history);
      }

      // Check if the input is a number
      else if (value != 0) {
	printf("%s\n", get_history(history, value));
	tokens = tokenize(get_history(history, value));
	print_tokens(tokens);
	free_tokens(tokens);
      }
    }

    // The input does not start with !
    else {
      tokens = tokenize(input);
      print_tokens(tokens);
      free_tokens(tokens);
      add_history(history, copy_str(input, MAX_LEN));
    }
  }
  free_history(history);
}
