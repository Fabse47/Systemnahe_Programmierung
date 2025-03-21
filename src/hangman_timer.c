#include "hangman_timer.h"

/**
 * @brief Initialisiert und startet den Timer für den Timeout.
 *
 * Dieser Timer läuft, um einen Abbruch im Spiel auszulösen,
 * wenn der Spieler zu lange wartet oder keine Eingabe macht.
 */
void start_timeout_timer() {
  timer_init_detailed(TIMER0, 15, TIMER_MODE_TIMER, TIMER_BIT_MODE_32);
  timer_captureCompareSet(TIMER0, CC0, 1953, true);
  timer_start(TIMER0);
}

/**
 * @brief Stoppt den Timer, der für den Timeout zuständig ist.
 *
 * Nach dem Aufruf dieser Funktion läuft der Timer für zu langes Warten nicht mehr.
 */
void stop_timeout_timer() {
  timer_capture(TIMER0, CC0);
  timer_stop(TIMER0);
}

/**
 * @brief Initialisiert und startet den Timer für die gesamte Spielzeit.
 *
 * Dieser Timer dient zur Erfassung der im Spiel verbrachten Zeit.
 * Er wird genutzt, um Statistiken zu erfassen.
 */
void start_hangman_timer() {
  timer_init_detailed(TIMER1, 15, TIMER_MODE_TIMER, TIMER_BIT_MODE_32);
  timer_start(TIMER1);
}

/**
 * @brief Stoppt den Timer für die gesamte Spielzeit.
 *
 * Die Funktion liest den finalen Timerwert aus, stoppt den Timer und löscht diesen,
 * bevor sie den erfassten Wert zurückgibt.
 *
 * @return Der zuletzt erfasste Wert des Timers.
 */
uint32_t stop_hangman_timer() {
  timer_capture(TIMER1, CC1);
  timer_stop(TIMER1);

  uint32_t timer1_value = timer_captureCompareGet(TIMER1, CC1);
  timer_clear(TIMER1);

  return timer1_value;
}
