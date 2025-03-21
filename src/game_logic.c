#include "game_logic.h"

/**
 * @brief Enthält das aktuell zu erratende Wort.
 */
char word[MAX_WORD_LENGTH] = {0};

/**
 * @brief Enthält den aktuellen Stand des erratenen Wortes.
 */
char guessed[MAX_WORD_LENGTH] = {0};

/**
 * @brief Enthält die gesamte Antwortzeit des Spielers.
 */
uint32_t total_response_time = 0;

/**
 * @brief Zählt alle Versuche, bei denen der Spieler Buchstaben eingibt.
 */
uint32_t response_count = 0;

/**
 * @brief Zählt die Anzahl an Fehlern im Spiel.
 */
uint32_t errors = 0;

/**
 * @brief Initialisiert das erratene Wort mit Unterstrichen.
 *
 * Diese Funktion schreibt für jeden Buchstaben im Ratewort (word)
 * einen Unterstrich ('_') in das @p guessed -Array. Damit wird
 * der Anfangszustand im Hangman-Spiel hergestellt.
 *
 * @param[in,out] guessed  Zeiger auf das Puffer-Array für das erratene Wort
 * @param[in]     word     Zeiger auf das zu erratende Wort
 */
void init_guessed_word(char *guessed, const char *word) {
  int i = 0;
  while (word[i] != '\0' && i < MAX_WORD_LENGTH - 1) {
    guessed[i] = '_';
    i++;
  }
  guessed[i] = '\0';
}

/**
 * @brief Überprüft das Ratewort auf einen Buchstaben und aktualisiert das erratene Wort.
 *
 * Diese Funktion durchläuft das @p word und überprüft, ob der übergebene
 * Buchstabe @p letter enthalten ist. Wenn ja, werden die entsprechenden
 * Unterstriche im @p guessed -Array durch den gefundenen Buchstaben ersetzt.
 *
 * @param[in]     letter   Der vom Spieler eingegebene Buchstabe
 * @param[in]     word     Zeiger auf das zu erratende Wort
 * @param[in,out] guessed  Zeiger auf das Puffer-Array für das erratene Wort
 *
 * @return 1, wenn der Buchstabe gefunden wurde; ansonsten 0
 */
int check_and_update_word(char letter, const char *word, char *guessed) {
  int found = 0;
  for (int i = 0; word[i] != '\0'; i++) {
    if (word[i] == letter) {
      guessed[i] = letter;
      found = 1;
    }
  }
  return found;
}

/**
 * @brief Prüft, ob das erratene Wort vollständig ist.
 *
 * Diese Funktion überprüft, ob das @p guessed -Array noch Unterstriche
 * enthält. Sind keine Unterstriche mehr vorhanden, gilt das Wort als
 * vollständig erraten.
 *
 * @param[in] guessed  Zeiger auf das Array mit dem aktuellen Stand des erratenen Wortes
 *
 * @return 1, wenn das Wort vollständig erraten wurde; ansonsten 0
 */
int word_guessed(const char *guessed) {
  for (int i = 0; guessed[i] != '\0'; i++) {
    if (guessed[i] == '_') {
      return 0;
    }
  }
  return 1;
}

/**
 * @brief Zeigt ein Menü zum Spielbeginn und verarbeitet Benutzereingaben.
 *
 * Diese Funktion bietet dem Spieler an, entweder das Spiel zu starten (Eingabe 's')
 * oder ein eigenes Wort zu einer Wortliste hinzuzufügen (Eingabe 'a').
 */
void input_menu() {
  uart_writeString("Willkommen zu hangman...\n");
  uart_writeString("Zum Spielen \"s\" drücken.\nEigenes Wort zur Wortliste hinzufügen \"a\" drücken.\n");
  while (1) {
    char input = get_player_input();
    if (input == 's') {
      uart_writeString("Starte Spiel\n");
      break;
    }
    if (input == 'a') {
      add_custom_word();
      uart_writeString("\nZum Spielen \"s\" drücken.\nWenn Sie ein weiteres Wort zur Liste hinzufügen möchten, dann drücken Sie \"a\".\n");
    }
    else {
      uart_writeString("Ungültige Eingabe\n");
    }
  }
}

/**
 * @brief Setzt das Spiel zurück und initialisiert benötigte Timer.
 *
 * Diese Funktion setzt die globalen Variablen für Zeit, Eingabeanzahl
 * und Fehler zurück und startet die Hangman- und Timeout-Timer neu.
 */
void reset_program() {
  start_hangman_timer();  // Timer für Gesamtzeit starten
  start_timeout_timer();  // Timer für Timout der Züge starten

  total_response_time = 0;
  response_count = 0;
  errors = 0;
}

/**
 * @brief Erhöht die Fehleranzahl und den Versuchszähler nach einem Timer-Interrupt.
 *
 * Diese Funktion wird im Timer-Interrupt aufgerufen, wenn ein Timeout
 * auftritt. Die Anzahl der Fehler und Versuche wird erhöht, der Spielstand
 * aktualisiert und anschließend der aktuelle Spielzustand geprüft.
 */
void inc_errors() {
  errors++;
  response_count++;
  display_game_state(guessed, errors);

  check_gamestate();

  // Eingabeaufforderung erneuern
  uart_writeString(RESET);
  uart_writeString("\nGib einen Buchstaben ein: ");
}

/**
 * @brief Überprüft den Spielstand und leitet ggf. das Spielende ein.
 *
 * Diese Funktion überprüft, ob die maximale Fehleranzahl (@ref MAX_ERRORS)
 * überschritten ist oder ob das Wort bereits vollständig erraten wurde.
 * Im Erfolgs- oder Misserfolgsfall wird der Spielstand angezeigt,
 * ein entsprechendes Ergebnis angezeigt und das Spiel beendet.
 */
void check_gamestate() {
  if (errors >= MAX_ERRORS) {
    // Spiel verloren
    display_game_state(guessed, errors);
    display_loser(word);
    display_statistics(errors);
  }
  else if (word_guessed(guessed)) {
    // Spiel gewonnen
    display_game_state(guessed, errors);
    display_winner();
    display_statistics(errors);
  }

  // Spiel beenden
  if (errors >= MAX_ERRORS || word_guessed(guessed)) {
    uart_writeString("Spiel beendet.");
    while (1) {
      __asm__("wfi");  // "Wait For Interrupt" - blockiert Eingaben
    }
  }
}
