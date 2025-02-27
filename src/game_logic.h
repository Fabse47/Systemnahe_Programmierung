#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

void init_guessed_word(char *guessed, const char *word, int MAX_WORD_LENGTH); // Ratewort initialisieren
int check_and_update_word(char letter, const char *word, char *guessed);  // Durchsucht das Ratewort nach der Eingabe
int word_guessed(const char *guessed);  // Prüft, ob noch Unterstriche im erratenen Wort sind

#endif //GAME_LOGIC_H