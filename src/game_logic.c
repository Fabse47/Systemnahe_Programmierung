#include "game_logic.h"


void init_guessed_word(char *guessed, const char *word) {  // Ratewort initialisieren
  int i = 0;
  while (word[i] != '\0' && i < MAX_WORD_LENGTH - 1) {
    guessed[i] = '_';  // Ersetze jeden Buchstaben mit "_"
    i++;
  }
  guessed[i] = '\0';  // Null-Terminierung
}


int check_and_update_word(char letter, const char *word, char *guessed) { // Durchsucht das Ratewort nach der Eingabe
  int found = 0;
  for (int i = 0; word[i] != '\0'; i++) {
    if (word[i] == letter) {
      guessed[i] = letter;  // Ersetze "_" mit dem erratenen Buchstaben
      found = 1;
    }
  }
  return found;  // 1, wenn Buchstabe gefunden wurde, sonst 0
}


int word_guessed(const char *guessed) { // Prüft, ob noch Unterstriche im erratenen Wort sind
  for (int i = 0; guessed[i] != '\0'; i++) {
    if (guessed[i] == '_') {
      return 0;  // Noch nicht erraten
    }
  }
  return 1;  // Alle Buchstaben wurden erraten
}


void input_menu() // Eingabemenü am Anfang bzw. zwischen den Spielen
{
  uart_writeString("Willkommen zu hangman...\n");
  uart_writeString("Zum Spielen \"s\" drücken.\nWenn Sie ein neues Wort zur Liste hinzufügen möchten dann drücken Sie \"a\".\n");
  while (1)
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
}


void input_menu_after_game()
{
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