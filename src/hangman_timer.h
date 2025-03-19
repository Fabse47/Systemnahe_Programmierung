#ifndef HANGMAN_TIMER_H
#define HANGMAN_TIMER_H

#include "main.h" // für response_count() und total_response_time()
#include "output.h" // für correct_time()
#include "../devices/uart.h"
#include "../devices/timer.h"

#define TIMEOUT_THRESHOLD (5*488)  // Timeout in Timer-Ticks (5 Sekunden)

void start_timeout_timer(); // Timer für gesamte Spielzeit starten
void stop_timeout_timer();  // Timer für gesamte Spielzeit stoppen
void start_hangman_timer(); // Timer für zu langes Warten starten
uint32_t stop_hangman_timer();  // Timer für zu langes Warten stoppen

#endif // HANGMAN_TIMER_H