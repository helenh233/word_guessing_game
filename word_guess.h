// this module provides functions that can be used to play a word-guessing game

#include <stdbool.h>

// the secret word and all guesses are lowercase, and must be of the same length
// all chars in "result" are either:
//   lowercase: letter exists in secret, but not in correct position
//   UPPERCASE: letter in correct position
//   _ (underscore): letter does not exist in secret word


// evaluate_guess(secret, guess, result) returns whether or not secret is equal
//   to guess and modifies result as described above
// example:
//   evaluate_guess("apple", "paper", result) => false; result -> "paPe_"
// requires: result is sufficiently large [not asserted]
//           secret and guess are same length
// effects: result will be modified
// time: O(n)
bool evaluate_guess(const char *secret, const char *guess, char *result);


// available_letters(guesses, results, num_guesses, alphabet) determines the
//   status of letters 'a'...'z' in the secret word, based on results
//   of existing guesses; the result is stored in alphabet as an string, where each of 'a'...'z' is:
//     _ (underscore), if the letter does not exist in secret word
//     lowercase letter, if the status of the letter is unknown
//     UPPERCASE letter, if the letter exists in secret word
// example: char *guesses[2] = { "apple", "touch" };
//          char *results[2] = { "_pp__", "_OUCH" };
//          available_letters(guesses, results, 2, alphabet);
//          alphabet -> "_bCd_fgHijk_mnOPqrs_Uvwxyz"
// requires: first "num_guesses" elements in guesses and results are valid
//           strings of the same length
//           alphabet is sufficiently large [not asserted]
//           num_guesses >= 0
// effects: alphabet is modified
// time: O(num_guesses * m) where m is the length of each guess
void available_letters(char *guesses[], char *results[], int num_guesses,
                       char *alphabet);


// valid_guess(guesses, results, num_guesses, next_guess) evaluates
//    whether or not next_guess is a valid attempt, given that
//    a previously correctly positioned letter must be used in the same spot,
//    an incorrectly positioned letter should be used but not in the same spot, and
//    a letter that was previous identified as not part of the secret word
//    cannot be used in next_guess.
// examples: char *guesses[1] = { "apple" };
//           char *results[1] = { "_pp__" };
//           valid_guess(guesses, results, 1, "touch") => false
//           valid_guess(guesses, results, 1, "pouch") => true
//           valid_guess(guesses, results, 1, "spout") => false
// requires: first "num_guesses" elements in guesses and results are valid
//              strings of the same length
//           length of next_guess matches length of strings in guesses
//           num_guesses >= 0
// time: O(num_guesses * m^2) where m is the length of each guess
bool valid_guess(char *guesses[], char *results[], int num_guesses,
                      const char *next_guess);
