#ifndef OUTPUT_H
#define OUTPUT_H

#include "main.h" // für response_count und total_response_time
#include "../devices/uart.h"
#include "../devices/timer.h"

// Farben für die Ausgabe
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

void display_hangman(int errors); // Hangman-Figur ausgeben
void display_game_state(const char *guessed, uint32_t errors); // aktuellen Spielstatus anzeigen
void display_winner();  // Siegeserklärung
void display_loser(const char *word); // Auflösung nach der Niederlage
void display_statistics(uint32_t errors);  // rechnet die Timer-Ticks in Millisekunden um

#endif // OUTPUT_H