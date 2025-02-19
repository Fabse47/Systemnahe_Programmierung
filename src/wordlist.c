#include "wordlist.h"
#include "../devices/random.h"

// Wortliste, aus der ein Wort zufällig ausgewählt wird
const char *word_list[] = {
  "hangman", "programming", "cortex", "embedded", "hardware"
};

#define WORD_COUNT (sizeof(word_list) / sizeof(word_list[0]))

// Eigene strcpy-Implementierung
void my_strcpy(char *dest, const char *src) {
  while (*src) {
    *dest++ = *src++;
  }
  *dest = '\0';  // Null-Terminierung setzen
}

void select_random_word(char *word) {
  rng_init();
  int index = rng_getRandomValue_waiting();
  index = index % WORD_COUNT;
  my_strcpy(word, word_list[index]);  // Wort kopieren
}
