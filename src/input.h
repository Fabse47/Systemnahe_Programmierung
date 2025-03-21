#ifndef INPUT_H
#define INPUT_H

#include "main.h"
#include "output.h"
#include "game_logic.h"
#include "../devices/uart.h"
#include "../devices/timer.h"

/**
 * @brief Liest einen einzelnen Buchstaben (a–z oder A–Z) vom UART ohne Timeout.
 *
 * Die Funktion blockiert, bis ein gültiges Zeichen empfangen wurde, und wandelt
 * Großbuchstaben in Kleinbuchstaben um. Bei ungültigen Eingaben wird eine
 * Fehlermeldung ausgegeben und erneut auf eine Eingabe gewartet (rekursiver Aufruf).
 *
 * @return Gültiger Buchstabe im Kleinbuchstabenformat (a–z).
 */
char get_player_input();

/**
 * @brief Liest einen einzelnen Buchstaben (a–z oder A–Z) vom UART mit Timeout-Unterstützung.
 *
 * Diese Funktion kann in Kombination mit Timer-Funktionen verwendet werden,
 * um Eingaben nur für eine begrenzte Zeit zuzulassen. Sobald ein gültiges Zeichen
 * empfangen wurde, wird der Antwortzähler (@ref response_count) erhöht,
 * Großbuchstaben werden in Kleinbuchstaben umgewandelt. Ungültige Eingaben
 * rufen eine Fehlermeldung hervor, anschließend wird erneut eine Eingabe verlangt.
 *
 * @return Gültiger Buchstabe im Kleinbuchstabenformat (a–z).
 */
char get_player_input_with_timeout();

#endif // INPUT_H
