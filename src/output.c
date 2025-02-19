#include "output.h"
#include "../devices/uart.h"

const char *hangman_stages[] = {
  "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n", // 0 Fehler
  "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n", // 1 Fehler
  "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n", // 2 Fehler
  "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n", // 3 Fehler
  "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n", // 4 Fehler
  "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n", // 5 Fehler
  "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n"  // 6 Fehler (Game Over)
};

void display_game_state(const char *guessed, int errors) {
  uart_writeString("\nAktuelles Wort: ");
  uart_writeString(guessed);
  uart_writeString("\n");

  uart_writeString("Fehlversuche: ");
  char error_str[2];
  error_str[0] = '0' + errors;
  error_str[1] = '\0';
  uart_writeString(error_str);
  uart_writeString("\n");

  uart_writeString(hangman_stages[errors]);  // ASCII-Galgen ausgeben
}



void display_winner() {
  uart_writeString("\n🎉 Glückwunsch! Du hast das Wort erraten! 🎉\n");
}



void display_loser(const char *word) {
  uart_writeString("\n💀 Game Over! Du hast das Wort nicht erraten. 💀\n");
  uart_writeString("Das richtige Wort war: ");
  uart_writeString(word);
  uart_writeString("\n");
}
