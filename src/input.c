#include "input.h"
#include "../devices/uart.h"

char get_player_input() {
  uart_writeString("\nGib einen Buchstaben ein: ");

  char input;
  do {
    input = uart_readByte();  // Nicht blockierende UART-Funktion
  } while (input == 0);  // Warten, bis ein gültiger Wert kommt

  // Echo der Eingabe (falls gewünscht)
  uart_writeByte(input);
  uart_writeString("\n");

  // Prüfen, ob es ein gültiger Buchstabe ist (a-z oder A-Z)
  if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')) {
    if (input >= 'A' && input <= 'Z') {
      input += 32;  // In Kleinbuchstaben umwandeln
    }
    return input;
  } else {
    uart_writeString("Ungültige Eingabe! Bitte nur Buchstaben eingeben.\n");
    return get_player_input();  // Rekursiver Aufruf für eine neue Eingabe
  }
}
