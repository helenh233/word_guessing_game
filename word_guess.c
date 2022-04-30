// this module contains the implementations of all functions provided in word_guess.h

#include "word_guess.h" 
#include <string.h> 
#include <stdio.h> 
#include <assert.h> 
#include <limits.h> 
#include <stdbool.h> 
#include <stdlib.h> 


// see word_guess.h
bool evaluate_guess(const char *secret, const char *guess, char *result) {
  assert(secret);
  assert(guess);
  assert(result);
  assert(strlen(secret) == strlen(guess));

  bool char_in_secret[127] = {false};
  for (int element = 'a'; element <= 'z'; ++element) {
    char_in_secret[element] = false; // initialize
  }

  for (int index = 0; secret[index]; ++index) {
    int ascii_value = secret[index];
    char_in_secret[ascii_value] = true;
  }

  bool correct_guess = true;
  int index = 0;
  while (guess[index]) {
    int ascii_value = guess[index];

    if (guess[index] == secret[index]) { // letter in correct spot
      result[index] = guess[index] - 'a' + 'A'; // UPPERCASE
    } else if (char_in_secret[ascii_value]) { // incorrect spot
      result[index] = guess[index]; // lowercase
      correct_guess = false;
    } else { // not in secret word
      result[index] = '.';
      correct_guess = false;
    }
    ++index;
  }
  result[index] = '\0';

  return correct_guess;
}


// see word_guess.h
void available_letters(char *guesses[], char *results[], int num_guesses,
                       char *alphabet) {
  assert(guesses);
  assert(results);
  assert(alphabet);
  assert(num_guesses >= 0);
  bool same_length = true;
  for (int i = 0; i < num_guesses; ++i) {
    if (strlen(guesses[i]) != strlen(results[i])) {
      same_length = false;
    }
  }
  assert(same_length);

  // fill alphabet with lowercase letters
  for (int i = 0; i < 26; ++i) {
    alphabet[i]= i + 'a';
  }
  alphabet[26] = '\0';

  for (int cur_str = 0; cur_str < num_guesses; ++cur_str) {
    for (int cur_char = 0; results[cur_str][cur_char]; ++cur_char) {
      int ascii_value = guesses[cur_str][cur_char];
      
      if ('.' == results[cur_str][cur_char]) { // letter DNE in secret word
        alphabet[ascii_value - 'a'] = '.';
        
      } else { // letter exists
        if ('a' <= alphabet[ascii_value - 'a'] &&
            alphabet[ascii_value - 'a'] <= 'z') { // if lowercase, make UPPER
          alphabet[ascii_value - 'a'] = alphabet[ascii_value - 'a'] - 'a' + 'A';
        }
      }
    }
  }
}


// see word_guess.h
bool valid_guess(char *guesses[], char *results[], int num_guesses,
                      const char *next_guess) {
  assert(guesses);
  assert(results);
  assert(num_guesses >= 0);
  bool same_length = true;
  for (int i = 0; i < num_guesses; ++i) {
    if (strlen(guesses[i]) != strlen(results[i])) {
      same_length = false;
    }
  }
  assert(same_length);
  assert(strlen(guesses[0]) == strlen(next_guess));

  bool next_guess_chars[127] = {false};
  for (int element = 'a'; element <= 'z'; ++element) {
    next_guess_chars[element] = false; // initialize
  }

  for (int index = 0; next_guess[index]; ++index) {
    int ascii_value = next_guess[index];
    next_guess_chars[ascii_value] = true;
  }

  for (int cur_str = 0; cur_str < num_guesses; ++cur_str) {
    for (int cur_char = 0; results[cur_str][cur_char]; ++cur_char) {
      int result = results[cur_str][cur_char];
      int guess = guesses[cur_str][cur_char];

      if ('.' == result) {
        if (next_guess_chars[guess]) { // can't use again
          return false;
        }
      } else if ('a' <= result && result <= 'z') { // lowercase
        if (!next_guess_chars[guess] ||
            next_guess[cur_char] == guess) {
          return false;
        }
      } else { // UPPERcase, use in same spot
        if (next_guess[cur_char] != guess) {
          return false;
        }
      }
    }
  }
  return true;
}
