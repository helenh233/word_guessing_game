// This program allows you to play a custom word-guessing game interactively

#include <assert.h> # necessary????????
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word_guess.h"

int main(void) {

  int max_len = 1;
  // array of strings
  char **guesses = malloc(max_len * sizeof(char *));
  char **results = malloc(max_len * sizeof(char *));
  char alphabet[27] = "";

  // Fill in (can only contain lowercase, printable characters)
  char *secret_word = "";
  int secret_len = strlen(secret_word);

  // How many times the player has guess so far
  int num_guesses = 0;

  printf("Try to guess the %d-letter long secret word.\n(Note: neither the secret word nor your guesses are required to be valid English words).\nIf you would like to give up, enter ':('.\nGood luck!\n", secret_len);
  
  // Loops continously until the secret_word is guessed, or the player gives up
  while (1) {
    // Memory managment to enlarge array 
    if (num_guesses + 1 == max_len) {
      max_len *= 2; // double the capacity
      guesses = realloc(guesses, max_len * sizeof(char *));
      results = realloc(results, max_len * sizeof(char *));
    }
    // Initialize empty elements at the end of the arrays to NULL
    for (int i = num_guesses; i < max_len; ++i) {
      guesses[i] = NULL;
      results[i] = NULL;
    }
    // Allocate memory to store the next guess (can store double the length of the secret word to prevent accidental buffer overflow)
    guesses[num_guesses] = malloc((secret_len * 2) * sizeof(char));
    results[num_guesses] = malloc((secret_len * 2) * sizeof(char));

    printf("\n----------------------------------------------------\n");
    if (num_guesses) {
      printf("Guesses so far:\n([UPPERCASE] = correct position. [lowercase] = incorrect position. [_] = not in secret word)\n");
    }
    // Prints previous guesses and results at start of each turn
    for (int i = 0; i < num_guesses; ++i) {
      printf("  %d) %s => %s\n", i + 1, guesses[i], results[i]);
    }

    available_letters(guesses, results, num_guesses, alphabet);
    printf("\nLetters left (capital letters are in secret word):\n  %s\n", alphabet);

    printf("\nEnter your guess #%d (in lowercase):\n", num_guesses + 1);

    int result = scanf("%s", guesses[num_guesses]);
    // Ensure that guess was properly scanned; else program exit
    if (result != 1) {
      return -1;
    }

    // Player inputs ':('
    if (!strcmp(guesses[num_guesses], ":(")) {
      printf("\nAdmit defeat! The word was: %s\n", secret_word);
      break;
    }
    
    // Guess is not the same length as the secret word
    if (strlen(guesses[num_guesses]) != secret_len) {
      printf("Invalid guess. Guesses must be %d letters long\n", secret_len);
      char input = 0;
      while (input != 'k') {
        printf("Press the [k] key, then [enter] to try again\n");
        scanf(" %c", &input);
      }
      continue;
    }
    // Guess does not use all previous hints
    if (!valid_guess(guesses, results, num_guesses, guesses[num_guesses])) {
      printf("\nInvalid guess. Previous hints must be used\n");
      char input = 0;
      while (input != 'k') {
        printf("Press the [k] key, then [enter] to try again\n");
        scanf(" %c", &input);
      }
      continue;
    }

    // Correct guess
    if (evaluate_guess(secret_word, guesses[num_guesses], results[num_guesses])) {
      printf("\n%d tries - not bad! The word was indeed %s :)\n", num_guesses + 1, secret_word);
      break;
    }

    ++num_guesses;
  }

  // Free allocated memory
  for (int i = 0; i < max_len; ++i) {
    free(guesses[i]);
    free(results[i]);
  }
  free(guesses);
  free(results);

  char exit = 0;
  while (exit != 'x') {
        printf("Press the [x] key, then [enter] to exit game\n");
        scanf(" %c", &exit);
      }
}

