#include "game_logic.h"

// globale Initialisierungen
char word[MAX_WORD_LENGTH] = {0}; // Ratewort
char guessed[MAX_WORD_LENGTH] = {0};  // Erratenes Wort
uint32_t total_response_time = 0;  // gesamte Antwortzeit
uint32_t response_count = 0; // Anzahl der Versuche (getippte Buchstaben)
uint32_t errors = 0;  // Anzahl Fehler


// Ratewort initialisieren
void init_guessed_word(char *guessed, const char *word) {
  int i = 0;
  while (word[i] != '\0' && i < MAX_WORD_LENGTH - 1) {
    guessed[i] = '_';  // Ersetze jeden Buchstaben mit "_"
    i++;
  }
  guessed[i] = '\0';  // Null-Terminierung
}


// Durchsucht das Ratewort nach der Eingabe
int check_and_update_word(char letter, const char *word, char *guessed) {
  int found = 0;
  for (int i = 0; word[i] != '\0'; i++) {
    if (word[i] == letter) {
      guessed[i] = letter;  // Ersetze "_" mit dem erratenen Buchstaben
      found = 1;
    }
  }
  return found;  // 1, wenn Buchstabe gefunden wurde, sonst 0
}


// Prüft, ob noch Unterstriche im erratenen Wort sind
int word_guessed(const char *guessed) {
  for (int i = 0; guessed[i] != '\0'; i++) {
    if (guessed[i] == '_') {
      return 0;  // Noch nicht erraten
    }
  }
  return 1;  // Alle Buchstaben wurden erraten
}


// Eingabemenü am Anfang des Spiels
void input_menu()
{
  uart_writeString("Willkommen zu hangman...\n");
  uart_writeString("Zum Spielen \"s\" drücken.\nEigenes Wort zur Wortliste hinzufügen \"a\" drücken.\n");
  while (1)
  {
    char input = get_player_input();
    if (input == 's')
    {
      uart_writeString("Starte Spiel\n");
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
}


// hangman vor dem Start zurücksetzen
void reset_program() {
  start_hangman_timer();  // Timer für Gesamtzeit starten
  start_timeout_timer();  // Timer für Timout der Züge starten

  total_response_time = 0;  // Gesamtzeit auf 0 setzen
  response_count = 0; // Anzahl der Züge auf 0 setzen
  errors = 0; // Fehler auf 0 setzten
}


// Timer-Interrupt: Fehler erhöhen (wird im Interrupt 8 handler aufgerufen)
void inc_errors(){
  errors++; // Fehler erhöhen
  response_count++; // als Versuch zählen
  display_game_state(guessed, errors);  // Spielstand ausgeben

  check_gamestate();  // Abbruchbedingung

  // Nach Interrupt-Meldung muss das Eingabefeld wieder angezeigt werden:
  uart_writeString(RESET);  // Setzt die Standardfarbe zurück
  uart_writeString("\nGib einen Buchstaben ein: ");
}


// Spielstand prüfen
void check_gamestate()
{
  if (errors >= MAX_ERRORS) // Spiel verloren
  {
    display_game_state(guessed, errors);
    display_loser(word);
    display_statistics(errors);
    uart_writeString("Spiel beendet.");
  }
  else if(word_guessed(guessed)) {  // Spiel gewonnen
    display_game_state(guessed, errors);
    display_winner();
    display_statistics(errors);
  }
  if (errors >= MAX_ERRORS || word_guessed(guessed)) // Ende des Spiels
  {
    uart_writeString("Spiel beendet.");
    while(1)
    {
      __asm__("wfi");  // "Wait For Interrupt" - blockiert Eingaben
    };
  }
}