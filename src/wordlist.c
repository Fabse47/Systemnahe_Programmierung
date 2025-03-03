#include "wordlist.h"


void my_strcpy(char *dest, const char *src) { // Eigene strcpy-Implementierung
  while (*src) {
    *dest++ = *src++;
  }
  *dest = '\0';  // Null-Terminierung setzen
}


char word_list[MAX_WORDS][MAX_WORD_LENGTH] = {  // Wortliste
  "hangman", "computer", "cortex", "embedded", "hardware",
  "stack", "heap", "interrupt", "register", "kernel", "treiber"
};
int word_count = 11;  // Anzahl gespeicherter Wörter


void add_custom_word() {  // eigenes Wort zur Wortliste hinzufügen
  if (word_count >= MAX_WORDS) {
    uart_writeString("Wortliste ist voll! Kann keine weiteren Wörter hinzufügen.\n");
    return;
  }

  uart_writeString("Gib dein eigenes Wort ein: ");
  char new_word[MAX_WORD_LENGTH];
  int i = 0;

  while (i < MAX_WORD_LENGTH - 1) {
    char c = uart_readByteBlocking();
    if (c == '\n' || c == '\r') {
      break;
    }
    new_word[i++] = c;
    uart_writeByte(c);
  }
  new_word[i] = '\0';

  for (int j = 0; j < MAX_WORD_LENGTH; j++) {
    word_list[word_count][j] = new_word[j]; // Wort im RAM speichern (jedoch flüchtig)
  }
  word_count++;
  uart_writeString("\nNeues Wort: \"");
  uart_writeString(word_list[word_count-1]);
  uart_writeString("\"\n");
  uart_writeString("\nWort wurde im Speicher abgelegt!\n");
}


void select_random_word(char *word) { // zufälliges Wort auswählen
  if (word_count == 0) {
    uart_writeString("Keine Wörter verfügbar! Nutze Standardwörter.\n");
    my_strcpy(word, "hangman");
    return;
  }

  rng_init();
  int index = rng_getRandomValue_waiting();
  index = index % word_count;
  my_strcpy(word, word_list[index]);
}