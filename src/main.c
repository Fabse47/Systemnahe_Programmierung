#include "main.h"


int total_response_time = 0;  // gesamte Antwortezeit
int response_count = 0; // Anzahl der Versuche (getippte Buchstaben)


// hangman vor dem Start zurücksetzen
void reset_program() {
  timer_stop(TIMER0);
  timer_clear(TIMER0);

  //timer_init(TIMER0);

  while (uart_readByte() != 0);  // UART-Puffer leeren

  total_response_time = 0;
  response_count = 0;
}


// main
int hangman() {
  uart_init();  // Serielle Schnittstelle initialisieren

  while (true)  // Hauptschleife
  {
    uart_writeString("Willkommen zu hangman...\n");
    uart_writeString("Zum Spielen \"s\" drücken.\nWenn Sie ein neues Wort zur Liste hinzufügen möchten dann drücken Sie \"a\".\n");
    while (true)
    {
      char input = get_player_input();
      if (input == 's')
      {
        break;
      }
      if (input == 'a')
      {
        add_custom_word();
        uart_writeString("\nZum Spielen \"s\" drücken.\nWenn Sie ein weiteres Wort zur Liste hinzufügen möchten dann drücken Sie \"a\".\n");
      }
      else
      {
        uart_writeString("Ungültige Eingabe\n");
      }
    }

    uart_writeString("Starte Spiel\n");
    reset_program();

    char word[MAX_WORD_LENGTH]; // Ratewort initialisieren
    char guessed[MAX_WORD_LENGTH];  // Erratenes Wort initialisieren
    errors = 0; // Fehler auf 0 setzten

    select_random_word(word);  // Zufälliges Wort wählen
    init_guessed_word(guessed, word, MAX_WORD_LENGTH);  // Leere Darstellung "_ _ _"

    while (errors < MAX_ERRORS) { // Abbruchbedingung bei Fehleranzahl

      display_game_state(guessed, errors);  // Spielstand anzeigen
      char input = get_player_input_with_timeout(); // Spielereingabe einlesen

      if (input == '\0') {  // Timeout-Fehleingabe
        errors++;
        continue;
      }

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

    uart_writeString("Um erneut zu spielen \"r\" drücken.\nZum Abbrechen \"x\" drücken.\n");
    while (true)
    {
      char input = get_player_input();
      if (input == 'r') // Programm neu starten
      {
        break;
      }
      if (input == 'x') // Programm mit Endlosschleife beenden
      {
        uart_writeString("Programm beendet");
        while (true){}
      }
    }
  }
  return 0;
}