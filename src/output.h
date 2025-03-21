#ifndef OUTPUT_H
#define OUTPUT_H

#include "main.h"       // für response_count und total_response_time
#include "hangman_timer.h"
#include "../devices/uart.h"
#include "../devices/timer.h"

/**
 * @brief ANSI-Farbcode für rote Ausgabe.
 */
#define RED     "\033[31m"

/**
 * @brief ANSI-Farbcode für grüne Ausgabe.
 */
#define GREEN   "\033[32m"

/**
 * @brief ANSI-Farbcode für gelbe Ausgabe.
 */
#define YELLOW  "\033[33m"

/**
 * @brief ANSI-Farbcode zum Zurücksetzen der Textfarbe.
 */
#define RESET   "\033[0m"

/**
 * @brief Gibt die Hangman-Figur basierend auf der aktuellen Fehleranzahl aus.
 *
 * Der angezeigte Hangman variiert mit jedem Fehlversuch.
 *
 * @param[in] errors Anzahl der bisher aufgetretenen Fehler.
 */
void display_hangman(int errors);

/**
 * @brief Zeigt den aktuellen Spielstatus an.
 *
 * Gibt das bisher erratene Wort, die Fehlerversuche und die Hangman-Grafik aus.
 *
 * @param[in] guessed String, der den aktuellen Fortschritt beim Erraten des Wortes enthält
 *                    (Unterstriche für nicht erratene Buchstaben).
 * @param[in] errors  Anzahl der aufgetretenen Fehler.
 */
void display_game_state(const char *guessed, uint32_t errors);

/**
 * @brief Gibt eine Meldung aus, wenn das Wort erfolgreich erraten wurde.
 */
void display_winner();

/**
 * @brief Zeigt eine Meldung, dass das Wort nicht erraten wurde, und gibt die richtige Lösung aus.
 *
 * @param[in] word Zeiger auf das nicht erratene Wort.
 */
void display_loser(const char *word);

/**
 * @brief Zeigt eine kurze Statistik zum abgeschlossenen Spiel an.
 *
 * Beendet zunächst die Timer (Timeout/Hangman), berechnet anschließend
 * die benötigte Gesamtzeit und zeigt neben Anzahl der Fehler und Versuche
 * auch die durchschnittliche Antwortzeit an.
 *
 * @param[in] errors Anzahl der aufgetretenen Fehler.
 */
void display_statistics(uint32_t errors);

/**
 * @brief Rechnet die im Timer gemessenen Ticks in Millisekunden um.
 *
 * @param[in] time Zeitwert in Ticks.
 * @return Zeit in Millisekunden, basierend auf 1 Sekunde = 488 Ticks.
 */
uint32_t correct_time(uint32_t time);

#endif // OUTPUT_H
