#include "input.h"


char get_player_input() { // Eingabe ohne Timer
  char input;
  do {
    input = uart_readByte();  // Nicht blockierende UART-Funktion
  } while (input == 0);  // Warten, bis ein gültiger Wert kommt
  while (uart_readByte() != 0);  // UART-Puffer leeren

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


char get_player_input_with_timeout() {  // Eingabe mit Timer
  uart_writeString("\nGib einen Buchstaben ein: ");

  while (uart_readByte() != 0); // Leere den UART-Puffer vor jeder Eingabe
  char input = 0;

  while (1) {

    input = uart_readByteBlocking();
    if (input != 0) {

      uart_writeByte(input);
      uart_writeString("\n");

      while (uart_readByte() != 0); // Erneut Puffer leeren nach der Eingabe
      response_count++;

      return input;
    }
  }
}