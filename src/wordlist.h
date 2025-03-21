#ifndef WORD_LIST_H
#define WORD_LIST_H

#include "../devices/random.h"
#include "../devices/uart.h"

/**
 * @brief Maximale Anzahl an Wörtern, die gespeichert werden können.
 */
#define MAX_WORDS 16

/**
 * @brief Maximale Länge eines einzelnen Wortes (inklusive Nullterminierung).
 */
#define MAX_WORD_LENGTH 12

/**
 * @brief Kopiert den Inhalt von @p src in @p dest.
 *
 * Diese Funktion setzt nach dem Kopieren eine Nullterminierung.
 *
 * @param[out] dest  Zielpuffer, in den die Zeichen kopiert werden.
 * @param[in]  src   Der Quell-String, der kopiert wird.
 */
void my_strcpy(char *dest, const char *src);

/**
 * @brief Ermöglicht dem Benutzer, ein eigenes Wort über UART einzugeben
 *        und fügt es zur internen Wortliste hinzu.
 *
 * Prüft, ob die maximale Anzahl an Wörtern (@ref MAX_WORDS) bereits erreicht ist.
 * Ist dies der Fall, wird eine Fehlermeldung ausgegeben. Ansonsten wird das Wort
 * eingelesen und an die Liste angehängt.
 */
void add_custom_word();

/**
 * @brief Wählt zufällig ein Wort aus der gespeicherten Liste aus und kopiert es in @p word.
 *
 * Verwendet eine Zufallszahl (@c rng_getRandomValue_waiting) zur Bestimmung
 * eines Index in der Wortliste und führt anschließend eine Kopie des ausgewählten Wortes
 * in den Puffer @p word durch.
 *
 * @param[out] word  Puffer, in den das ausgewählte Wort kopiert wird.
 */
void select_random_word(char *word);

#endif // WORD_LIST_H
