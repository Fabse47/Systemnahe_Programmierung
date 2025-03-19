#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../devices/uart.h"
#include "input.h"
#include "main.h"

#define MAX_ERRORS 6  // Maximale Anzahl an Fehlern
#define MAX_WORD_LENGTH 12  // Maximale Wortlänge (Anzahl Buchstaben)

// Spielvariablen deklarieren
extern char word[MAX_WORD_LENGTH];  // Ratewort
extern char guessed[MAX_WORD_LENGTH]; // Erratenes Wort
extern uint32_t total_response_time; // gesamte Antwortezeit
extern uint32_t response_count;  // Anzahl der Versuche (getippte Buchstaben)
extern uint32_t errors; // Anzahl Fehler

void init_guessed_word(char *guessed, const char *word); // Ratewort initialisieren
int check_and_update_word(char letter, const char *word, char *guessed);  // Durchsucht das Ratewort nach der Eingabe
int word_guessed(const char *guessed);  // Prüft, ob noch Unterstriche im erratenen Wort sind
void input_menu();  // Eingabemenü am Anfang des Spiels
void reset_program(); // hangman vor dem Start zurücksetzen
void inc_errors();  // Timer-Interrupt: Fehler erhöhen
void check_gamestate(); // Spielstand prüfen

#endif //GAME_LOGIC_H