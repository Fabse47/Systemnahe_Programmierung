#include "input.h"

/**
 * @brief Liest eine einzelne Benutzereingabe (Buchstabe a–z oder A–Z) ohne Timeout.
 *
 * Diese Funktion blockiert so lange, bis der Benutzer eine gültige Eingabe tätigt.
 * Anschließend werden Großbuchstaben in Kleinbuchstaben umgewandelt.
 * Falls ein ungültiges Zeichen eingegeben wurde, wird dies ausgegeben
 * und erneut auf eine Eingabe gewartet (rekursiver Aufruf).
 *
 * @return Gültiger Kleinbuchstabe (a–z).
 */
char get_player_input() {
  char input;
  do {
    input = uart_readByte();  // Eingabe einlesen
  } while (input == 0);       // Warten, bis ein gültiger Wert empfangen wird

  while (uart_readByte() != 0);  // UART-Puffer leeren

  uart_writeByte(input);       // Echo der Eingabe
  uart_writeString("\n");

  // Prüfen, ob es ein gültiger Buchstabe ist (a-z oder A-Z)
  if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')) {
    // In Kleinbuchstaben umwandeln, falls Großbuchstabe
    if (input >= 'A' && input <= 'Z') {
      input += 32;
    }
    return input;
  } else {
    uart_writeString("Ungültige Eingabe! Bitte nur Buchstaben eingeben.\n");
    // Rekursiver Aufruf für eine neue Eingabe
    return get_player_input();
  }
}

/**
 * @brief Liest eine einzelne Benutzereingabe (Buchstabe a–z oder A–Z) mit Timeout.
 *
 * Diese Funktion blockiert bis ein Zeichen empfangen wurde,
 * erhöht den Antwortzähler (@ref response_count) bei jeder Eingabe und
 * konvertiert Großbuchstaben in Kleinbuchstaben. Ist die Eingabe ungültig,
 * wird ein Hinweis ausgegeben und wieder auf Eingabe gewartet.
 *
 * @note Das Timeout wird über die @c timer -Funktionen in anderen Teilen des Programms gesteuert.
 *       Sollte ein echter Timeout ablaufen, wird dies durch einen
 *       entsprechenden Interrupt oder eine andere Logik behandelt.
 *
 * @return Gültiger Kleinbuchstabe (a–z), wenn erfolgreich eingelesen.
 */
char get_player_input_with_timeout() {
  uart_writeString("\nGib einen Buchstaben ein: ");

  // Leere den UART-Puffer vor jeder Eingabe
  while (uart_readByte() != 0);

  char input = 0;

  while (1) {
    input = uart_readByteBlocking();  // Blockierende Leseoperation
    if (input != 0) {
      uart_writeByte(input);  // Echo der Eingabe
      uart_writeString("\n");

      // Puffer nach der Eingabe erneut leeren
      while (uart_readByte() != 0);

      // Antwortzähler erhöhen
      response_count++;

      // Prüfen, ob es ein gültiger Buchstabe ist (a-z oder A-Z)
      if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')) {
        // In Kleinbuchstaben umwandeln, falls Großbuchstabe
        if (input >= 'A' && input <= 'Z') {
          input += 32;
        }
        return input;
      } else {
        uart_writeString("Bitte nur Buchstaben eingeben.\n");
        // Erneut warten auf eine Eingabe (rekursiver Aufruf)
        return get_player_input_with_timeout();
      }
    }
  }
}
