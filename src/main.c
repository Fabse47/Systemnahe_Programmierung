//
// Created by mikaurban on 2/18/25.
//


#include "game_logic.h"
#include "input.h"
#include "output.h"
#include "wordlist.h"
#include "../devices/timer.h"
#include "../devices/uart.h"

#define MAX_ERRORS 6  // Maximale Anzahl an Fehlern
#define MAX_WORD_LENGTH 12  // Maximale Wortlänge (Anzahl Buchstaben)

int hangman() {
  uart_init();  // Serielle Schnittstelle initialisieren
  //timer_init(); // Timer initialisieren

  char word[MAX_WORD_LENGTH];
  char guessed[MAX_WORD_LENGTH];
  int errors = 0;

  select_random_word(word);  // Zufälliges Wort wählen
  uart_writeString(word);
  init_guessed_word(guessed, word, MAX_WORD_LENGTH);  // Leere Darstellung "_ _ _"

  // test
  char input = get_player_input();
  uart_writeString(input);
  //

  while (errors < MAX_ERRORS) {
    display_game_state(guessed, errors);

    char input = get_player_input();
    if (input == '\0') {  // Timeout-Fehleingabe
      errors++;
      continue;
    }

    if (!check_and_update_word(input, word, guessed)) {
      errors++;
    }

    if (word_guessed(guessed)) {
      display_winner();
      break;
    }
  }

  if (errors >= MAX_ERRORS) {
    display_game_state(guessed, errors);
    display_loser(word);
  }

  return 0;
}
