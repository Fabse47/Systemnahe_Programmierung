#ifndef MAIN_H
#define MAIN_H

#include "game_logic.h"
#include "input.h"
#include "output.h"
#include "wordlist.h"
#include "../devices/timer.h"
#include "../devices/uart.h"

#define MAX_ERRORS 6  // Maximale Anzahl an Fehlern
#define MAX_WORD_LENGTH 12  // Maximale Wortlänge (Anzahl Buchstaben)

extern int total_response_time; // gesamte Antwortezeit
extern int response_count;  // Anzahl der Versuche (getippte Buchstaben)
static int errors;

void reset_program(); // Spiel zurücksetzen
int hangman();  // main

#endif // MAIN_H