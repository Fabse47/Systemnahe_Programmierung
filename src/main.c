#include "main.h"


uint32_t total_response_time = 0;  // gesamte Antwortezeit
uint32_t response_count = 0; // Anzahl der Versuche (getippte Buchstaben)


// hangman vor dem Start zurücksetzen
void reset_program() {
  start_hangman_timer();
  start_timeout_timer();

  total_response_time = 0;
  response_count = 0;
}


// Fehler erhöhen
void inc_errors(){
  errors++;
  display_hangman(errors);
}


// main
int hangman() {
  uart_init();  // Serielle Schnittstelle initialisieren
  timeout_time = 4; // Standard Antwortzeit auf 4s setzen

  while (true)  // Hauptschleife
  {
    input_menu(); // Eingabemenü am Anfang bzw. zwischen den Spielen
    uart_writeString("Starte Spiel\n");
    reset_program();

    char word[MAX_WORD_LENGTH]; // Ratewort initialisieren
    char guessed[MAX_WORD_LENGTH];  // Erratenes Wort initialisieren
    errors = 0; // Fehler auf 0 setzten

    select_random_word(word);  // Zufälliges Wort wählen
    init_guessed_word(guessed, word);  // Leere Darstellung "_ _ _"

    while (errors < MAX_ERRORS) { // Abbruchbedingung bei Fehleranzahl

      display_game_state(guessed, errors);  // Spielstand anzeigen
      char input = get_player_input_with_timeout(); // Spielereingabe einlesen

      if (!check_and_update_word(input, word, guessed)) { // Falls kein Buchstabe erraten wurde, Fehler erhöhen
        errors++;
      }


      if (word_guessed(guessed)) {  // Spiel gewonnen
        display_game_state(guessed, errors);
        display_winner();
        display_statistics(errors);
        break;
      }
    }

    if (errors >= MAX_ERRORS) { // Spiel verloren
      display_game_state(guessed, errors);
      display_loser(word);
      display_statistics(errors);
    }

    input_menu_after_game();

  }
  return 0;
}