#ifndef INPUT_H
#define INPUT_H

#include "main.h" // für response_count() und total_response_time()
#include "output.h" // für correct_time()
#include "game_logic.h"
#include "../devices/uart.h"
#include "../devices/timer.h"

#define TIMEOUT_THRESHOLD (5*488)  // Timeout in Timer-Ticks (5 Sekunden)

char get_player_input();  // Eingabe ohne Timer
char get_player_input_with_timeout(); // Eingabe mit Timer

#endif // INPUT_H