#ifndef MAIN_H
#define MAIN_H

#include "game_logic.h"
#include "input.h"
#include "output.h"
#include "wordlist.h"
#include "hangman_timer.h"
#include "../devices/timer.h"
#include "../devices/uart.h"

/**
 * @brief Startet das Hangman-Spiel.
 *
 * Diese Funktion initialisiert das Spiel, startet benötigte Timer,
 * zeigt das Eingabemenü an und läuft dann in einer Endlosschleife
 * zur Verarbeitung der Benutzereingaben. Sobald das Wort erraten
 * oder die maximale Fehlerzahl erreicht wurde, wird das Spiel
 * durch die entsprechende Auswertelogik in @ref check_gamestate
 * beendet.
 */
int hangman();

#endif // MAIN_H
