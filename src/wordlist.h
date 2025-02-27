#ifndef WORD_LIST_H
#define WORD_LIST_H

#include "../devices/random.h"
#include "../devices/uart.h"

#define MAX_WORDS 10
#define MAX_WORD_LENGTH 12

void my_strcpy(char *dest, const char *src);  // Eigene strcpy-Implementierung
void add_custom_word(); // eigenes Wort zur Wortliste hinzufügen
void select_random_word(char *word);  // zufälliges Wort auswählen

#endif // WORD_LIST_H