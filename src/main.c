#include "main.h"


int hangman() {
  uart_init();  // Serielle Schnittstelle initialisieren

  input_menu(); // Eingabemenü am Anfang des Spiels
  reset_program();  // Timer starten, Variablen initialisieren

  select_random_word(word);  // Zufälliges Wort wählen
  init_guessed_word(guessed, word);  // Leere Darstellung "_ _ _"

  while (1) {
    check_gamestate(); // Abbruchbedingung

    display_game_state(guessed, errors);  // Spielstand anzeigen
    char input = get_player_input_with_timeout(); // Spielereingabe einlesen

    if (!check_and_update_word(input, word, guessed)) { // Falls kein Buchstabe erraten wurde, Fehler erhöhen
      errors++;
    }
  }

  return 0;
}