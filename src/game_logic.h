#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

void init_guessed_word(char *guessed, const char *word, int MAX_WORD_LENGTH);
int check_and_update_word(char letter, const char *word, char *guessed);
int word_guessed(const char *guessed);

#endif GAME_LOGIC_H