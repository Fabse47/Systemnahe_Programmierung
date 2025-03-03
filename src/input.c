#include "input.h"


char get_player_input() { // Eingabe ohne Timer
  char input;
  do {
    input = uart_readByteBlocking();
  } while (input == 0);  // Warten, bis ein gültiger Wert kommt
  //uart_writeString(input + "\n");
  while (uart_readByte() != 0);  // UART-Puffer leeren

  // Echo der Eingabe (falls gewünscht)
  uart_writeByte(input);
  uart_writeString("\n");

  // Prüfen, ob es ein gültiger Buchstabe ist (a-z oder A-Z)
  if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')) {
    if (input >= 'A' && input <= 'Z') {
      input += 32;  // In Kleinbuchstaben umwandeln
    }
    response_count++;
    return input;
  } else {
    uart_writeString("Ungültige Eingabe! Bitte nur Buchstaben eingeben.\n");
    return get_player_input();  // Rekursiver Aufruf für eine neue Eingabe
  }
}