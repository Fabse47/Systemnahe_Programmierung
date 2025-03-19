#ifndef MAIN_H
#define MAIN_H

#include "game_logic.h"
#include "input.h"
#include "output.h"
#include "wordlist.h"
#include "hangman_timer.h"
#include "../devices/timer.h"
#include "../devices/uart.h"

#define MAX_ERRORS 6  // Maximale Anzahl an Fehlern
#define MAX_WORD_LENGTH 12  // Maximale Wortlänge (Anzahl Buchstaben)

extern uint32_t total_response_time; // gesamte Antwortezeit
extern uint32_t response_count;  // Anzahl der Versuche (getippte Buchstaben)
static uint32_t errors;

void reset_program(); // Spiel zurücksetzen
void inc_errors();  // Fehler erhöhen
int hangman();  // main
void check_gamestate();

#endif // MAIN_H