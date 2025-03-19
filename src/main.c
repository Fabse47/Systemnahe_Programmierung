#include "main.h"

char word[MAX_WORD_LENGTH]; // Ratewort initialisieren
char guessed[MAX_WORD_LENGTH];  // Erratenes Wort initialisieren

uint32_t total_response_time = 0;  // gesamte Antwortezeit
uint32_t response_count = 0; // Anzahl der Versuche (getippte Buchstaben)


// hangman vor dem Start zurücksetzen
void reset_program() {
  start_hangman_timer();  // Timer für Gesamtzeit starten
  start_timeout_timer();  // Timer für Timout der Züge starten

  total_response_time = 0;  // Gesamtzeit auf 0 setzen
  response_count = 0; // Anzahl der Züge auf 0 setzen
  errors = 0; // Fehler auf 0 setzten
}


// Timer-Interrupt: Fehler erhöhen
void inc_errors(){
  errors++; // Fehler erhöhen
  response_count++; // als Versuch zählen
  display_game_state(guessed, errors);  // Spielstand ausgeben

  check_gamestate();  // Abbruchbedingung

  // Nach Interrupt-Meldung muss das Eingabefeld wieder angezeigt werden:
  uart_writeString(RESET);  // Setzt die Standardfarbe zurück
  uart_writeString("\nGib einen Buchstaben ein: ");
}


void check_gamestate()
{
  if (errors >= MAX_ERRORS)
  {
    display_game_state(guessed, errors);
    display_loser(word);
    display_statistics(errors);
    uart_writeString("Spiel beendet.");
    while(1);
  }
  else if(word_guessed(guessed)) {  // Spiel gewonnen
    display_game_state(guessed, errors);
    display_winner();
    display_statistics(errors);
    uart_writeString("Spiel beendet.");
    while(1);
  }
}


// main
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