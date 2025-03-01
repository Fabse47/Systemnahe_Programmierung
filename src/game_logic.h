#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../devices/uart.h"
#include "input.h"


void init_guessed_word(char *guessed, const char *word); // Ratewort initialisieren
int check_and_update_word(char letter, const char *word, char *guessed);  // Durchsucht das Ratewort nach der Eingabe
int word_guessed(const char *guessed);  // Prüft, ob noch Unterstriche im erratenen Wort sind
void input_menu();
void input_menu_after_game();

#endif //GAME_LOGIC_H