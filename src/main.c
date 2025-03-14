#include "main.h"

uint32_t response_count = 0; // Anzahl der Versuche (getippte Buchstaben)

// hangman vor dem Start zurücksetzen
void reset_program() {
  while (uart_readByte() != 0);  // UART-Puffer leeren
  response_count = 0;
}


// main
int hangman() {
  uart_init();  // Serielle Schnittstelle initialisieren

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
      char input = get_player_input(); // Spielereingabe einlesen

      if (!check_and_update_word(input, word, guessed)) {
        errors++;// Falls kein Buchstabe erraten wurde, Fehler erhöhen
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