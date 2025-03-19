#include "wordlist.h"


// Eigene strcpy-Implementierung
void my_strcpy(char *dest, const char *src) {
  while (*src) {
    *dest++ = *src++;
  }
  *dest = '\0';  // Null-Terminierung setzen
}


char word_list[MAX_WORDS][MAX_WORD_LENGTH] = {  // Wortliste
  "hangman", "computer", "cortex", "embedded", "hardware"
};
int word_count = 5;  // Anzahl gespeicherter Wörter


// eigenes Wort zur Wortliste hinzufügen
void add_custom_word() {
  if (word_count >= MAX_WORDS) {
    uart_writeString("Wortliste ist voll! Kann keine weiteren Wörter hinzufügen.\n");
    return;
  }

  uart_writeString("Gib dein eigenes Wort ein: ");
  char new_word[MAX_WORD_LENGTH]; // Wort deklarieren
  int i = 0;

  while (i < MAX_WORD_LENGTH - 1) {
    char c = uart_readByteBlocking();
    if (c == '\n' || c == '\r') { // Eingabe von "Enter" bestätigt das Wort
      break;
    }
    new_word[i++] = c;
    uart_writeByte(c);
  }
  new_word[i] = '\0'; // \0 am Ende des char Arrays einfügen

  for (int j = 0; j < MAX_WORD_LENGTH; j++) {
    word_list[word_count][j] = new_word[j]; // Wort im RAM speichern
  }
  word_count++;
  uart_writeString("\nNeues Wort: \"");
  uart_writeString(word_list[word_count-1]);
  uart_writeString("\"\n");
  uart_writeString("\nWort wurde im Speicher abgelegt!\n");
}


// zufälliges Wort auswählen
void select_random_word(char *word) {
  if (word_count == 0) {  // Ausnahmefall, sollte nie auftreten
    uart_writeString("Keine Wörter verfügbar! Nutze Standardwörter.\n");
    my_strcpy(word, "hangman");
    return;
  }

  rng_init(); // Initialisierung des Zufalls
  int index = rng_getRandomValue_waiting(); // zufälligen Zahlenwert speichern
  index = index % word_count; // mithilfe von Modulo auf einen Indexwert im Bereich der Wortliste kommen
  my_strcpy(word, word_list[index]);  // Wort speichern
}