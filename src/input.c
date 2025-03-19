#include "input.h"


// Eingabe ohne Timer
char get_player_input() {
  char input;
  do {
    input = uart_readByte();  // Eingabe einlesen
  } while (input == 0);  // Warten, bis gültiger Wert kommt
  while (uart_readByte() != 0);  // UART-Puffer leeren

  uart_writeByte(input);  // Echo der Eingabe
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


// Eingabe mit Timer
char get_player_input_with_timeout() {
  uart_writeString("\nGib einen Buchstaben ein: ");

  while (uart_readByte() != 0); // Leere den UART-Puffer vor jeder Eingabe
  char input = 0;

  while (1) {

    input = uart_readByteBlocking();  // Eingabe einlesen
    if (input != 0) { // Warten, bis gültiger Wert kommt

      uart_writeByte(input);  // Echo der Eingabe
      uart_writeString("\n");

      while (uart_readByte() != 0); // Erneut Puffer leeren nach der Eingabe
      response_count++; // Antwortzähler erhöhen

      // Prüfen, ob es ein gültiger Buchstabe ist (a-z oder A-Z)
      if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')) {
        if (input >= 'A' && input <= 'Z') {
          input += 32;  // In Kleinbuchstaben umwandeln
        }
        return input;
      }
      else
      {
        uart_writeString("Bitte nur Buchstaben eingeben.\n");
        return get_player_input_with_timeout();
      }
    }
  }
}