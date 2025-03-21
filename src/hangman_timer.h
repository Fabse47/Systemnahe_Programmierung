#ifndef HANGMAN_TIMER_H
#define HANGMAN_TIMER_H

#include "main.h"
#include "output.h"
#include "../devices/uart.h"
#include "../devices/timer.h"

/**
 * @brief Timeout in Timer-Ticks (5 Sekunden).
 *
 * Dieser Wert bestimmt die maximale Wartezeit, bevor ein Timeout-Ereignis
 * ausgelöst wird. 1 Sekunde entspricht hier 488 Ticks, daher 5 Sekunden = 5 * 488.
 */
#define TIMEOUT_THRESHOLD (5*488)

/**
 * @brief Initialisiert und startet den Timeout-Timer (TIMER0).
 *
 * Dieser Timer dient dazu, einen Abbruch im Spiel nach
 * einer bestimmten Zeit ohne Eingabe zu erzwingen.
 */
void start_timeout_timer();

/**
 * @brief Stoppt den Timeout-Timer (TIMER0).
 *
 * Hier wird der Timer beendet, falls eine Eingabe rechtzeitig
 * erfolgt oder das Spiel aus anderen Gründen fortgeführt werden soll.
 */
void stop_timeout_timer();

/**
 * @brief Initialisiert und startet den Hangman-Timer (TIMER1).
 *
 * Dieser Timer erfasst die Gesamtzeit, die der Spieler für das Spiel benötigt
 * oder kann verwendet werden, um lange Wartezeiten bei der Eingabe zu erkennen.
 */
void start_hangman_timer();

/**
 * @brief Stoppt den Hangman-Timer (TIMER1) und gibt den letzten erfassten Wert zurück.
 *
 * @return Timerwert (in Ticks), der bis zum Stopp des Timers gemessen wurde.
 */
uint32_t stop_hangman_timer();

#endif // HANGMAN_TIMER_H
