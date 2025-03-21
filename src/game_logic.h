#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../devices/uart.h"
#include "input.h"
#include "main.h"

/**
 * @brief Maximale Anzahl an Fehlern, die zum Verloren des Spiels führen.
 */
#define MAX_ERRORS 6

/**
 * @brief Maximale Länge des zu erratenden Wortes.
 */
#define MAX_WORD_LENGTH 12

/**
 * @brief Speicher für das zufällig oder benutzerdefiniert gewählte Ratewort.
 */
extern char word[MAX_WORD_LENGTH];

/**
 * @brief Speicher für den aktuellen Stand des erratenen Wortes.
 *
 * Unterstriche ('_') ersetzen unbekannte Buchstaben.
 */
extern char guessed[MAX_WORD_LENGTH];

/**
 * @brief Gesamtzeit, die der Spieler für Eingaben benötigt hat.
 */
extern uint32_t total_response_time;

/**
 * @brief Anzahl der getätigten Versuche (Eingaben).
 */
extern uint32_t response_count;

/**
 * @brief Aktuelle Anzahl der Fehler (z.B. Zeitüberschreitungen oder falsche Buchstaben).
 */
extern uint32_t errors;

/**
 * @brief Initialisiert das erratene Wort mit Unterstrichen.
 *
 * @param[out] guessed  Ziel-Array, in das die Unterstriche geschrieben werden.
 * @param[in]  word     Das aktuelle Ratewort.
 */
void init_guessed_word(char *guessed, const char *word);

/**
 * @brief Überprüft das eingegebene Zeichen im Ratewort und aktualisiert das erratene Wort.
 *
 * @param[in]  letter   Buchstabe, den der Spieler eingegeben hat.
 * @param[in]  word     Das zu erratende Wort.
 * @param[out] guessed  Das vom Spieler bisher erratene Wort.
 *
 * @return 1, wenn der Buchstabe im Wort enthalten ist; sonst 0.
 */
int check_and_update_word(char letter, const char *word, char *guessed);

/**
 * @brief Prüft, ob das Wort vollständig erraten wurde.
 *
 * @param[in] guessed  Das derzeitige, vom Spieler erratene Wort.
 *
 * @return 1, wenn das Wort vollständig erraten wurde; sonst 0.
 */
int word_guessed(const char *guessed);

/**
 * @brief Zeigt ein Eingabemenü zur Auswahl von Spieloptionen (Spiel starten, Wort hinzufügen) an.
 */
void input_menu();

/**
 * @brief Setzt das Spiel vor dem Start zurück und initialisiert relevante Timer.
 */
void reset_program();

/**
 * @brief Erhöht den Fehlerzähler und den Eingabezähler nach einem Timer-Interrupt.
 *
 * Diese Funktion wird im Interrupt-Kontext aufgerufen, wenn ein Timeout
 * oder eine ungültige Eingabe vorliegt.
 */
void inc_errors();

/**
 * @brief Überprüft den Spielstand und leitet ggf. das Spielende ein.
 *
 * Prüft, ob die maximale Fehleranzahl erreicht ist oder das Wort
 * vollständig erraten wurde, und zeigt das Resultat an.
 */
void check_gamestate();

#endif // GAME_LOGIC_H
