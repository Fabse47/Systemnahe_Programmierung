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
  uart_writeString("\nSpielen \"s\"\nOptionen \"o\"\n");
  while (1)
  {
    char input = get_player_input();
    if (input == 's')
    {
      break;
    }
    if (input == 'o')
    {
      option_menu();
      uart_writeString("\nSpielen \"s\"\nOptionen \"o\"\n");
    }
    else
    {
      uart_writeString("Ungültige Eingabe\n");
    }
  }
}


void input_menu_after_game()
{
  uart_writeString("\nSpielen \"s\"\nOptionen \"o\"\n\nAbbrechen \"x\"\n");
  while (true)
  {
    char input = get_player_input();
    if (input == 's') // Programm neu starten
    {
      break;
    }
    if (input == 'o') // Programm neu starten
    {
      option_menu();
    }
    if (input == 'x') // Programm mit Endlosschleife beenden
    {
      uart_writeString("Programm beendet");
      while (true){}
    }
  }
}


void option_menu()
{
  uart_writeString("\nWort hinzufügen \"a\"\nAntwortzeit anpassen \"t\"\nVerlassen \"x\"\n");
  while (1)
  {
    char input = get_player_input();
    if (input == 'a')
    {
      add_custom_word();
    }
    else if (input == 't')
    {
      change_timeout_time();
      return;
    }
    else if (input == 'x')
    {
      return;
    }
    else
    {
      uart_writeString("Ungültige Eingabe\n");
    }
  }
}


void change_timeout_time()
{
  uart_writeString("\nAntwortezeit in Sekunden: ");
  char input;
  while (1)
  {
    input = get_player_input();
    if (input != 0){ break; }
  }
    switch (input)  // string to int Umwandlung umgehen
    {
      case '1': timeout_time = 1; break;
      case '2': timeout_time = 2; break;
      case '3': timeout_time = 3; break;
      case '4': timeout_time = 4; break;
      case '5': timeout_time = 5; break;
      case '6': timeout_time = 6; break;
      case '7': timeout_time = 7; break;
      case '8': timeout_time = 8; break;
      case '9': timeout_time = 9; break;
      default: uart_writeString("Ungültige Eingabe!\n");
    }
  uart_writeString("Neue Antwortzeit gespeichert!\n");
  uart_writeNumber(timeout_time);
}