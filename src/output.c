#include "output.h"


const char *hangman_stages[] = {
  "  +---+\n"
  "  |   |\n"
  "      |\n"
  "      |\n"
  "      |\n"
  "      |\n"
  "=========\n", // 0 Fehler

  "  +---+\n"
  "  |   |\n"
  "  O   |\n"
  "      |\n"
  "      |\n"
  "      |\n"
  "=========\n", // 1 Fehler

  "  +---+\n"
  "  |   |\n"
  "  O   |\n"
  "  |   |\n"
  "      |\n"
  "      |\n"
  "=========\n", // 2 Fehler

  "  +---+\n"
  "  |   |\n"
  "  O   |\n"
  " /|   |\n"
  "      |\n"
  "      |\n"
  "=========\n", // 3 Fehler

  "  +---+\n"
  "  |   |\n"
  "  O   |\n"
  " /|\\  |\n"
  "      |\n"
  "      |\n"
  "=========\n", // 4 Fehler

  "  +---+\n"
  "  |   |\n"
  "  O   |\n"
  " /|\\  |\n"
  " /    |\n"
  "      |\n"
  "=========\n", // 5 Fehler

  "  +---+\n"
  "  |   |\n"
  "  O   |\n"
  " /|\\  |\n"
  " / \\  |\n"
  "      |\n"
  "=========\n"  // 6 Fehler (Game Over)
};


void display_hangman(int errors) {  // Hangman-Figur ausgeben
  if (errors == 0) {
    uart_writeString(RESET);  // Setzt die Standardfarbe zurück
  }
  else if (errors > 0 && errors < 3) {
    uart_writeString(GREEN);  // grüne Ausgabe
  }
  else if (errors > 2 && errors < 5) {
    uart_writeString(YELLOW); // gelbe Ausgabe
  }
  else {
    uart_writeString(RED);  // rote Ausgabe
  }

  uart_writeString(hangman_stages[errors]);
  uart_writeString(RESET);
}


void display_game_state(const char *guessed, int errors) {  // aktuellen Spielstatus anzeigen
  uart_writeString("\nAktuelles Wort: ");
  uart_writeString(guessed);
  uart_writeString("\n");

  uart_writeString("Fehlversuche: ");
  char error_str[2];
  error_str[0] = '0' + errors;
  error_str[1] = '\0';
  uart_writeString(error_str);
  uart_writeString("\n");

  display_hangman(errors);
}


void display_winner() { // Siegeserklärung
  uart_writeString("\nGlückwunsch! Du hast das Wort erraten!\n");
}


void display_loser(const char *word) {  // Auflösung nach der Niederlage
  uart_writeString("\nGame Over! Du hast das Wort nicht erraten.\n");
  uart_writeString("Das richtige Wort war: ");
  uart_writeString(word);
  uart_writeString("\n");
}


uint32_t correct_time(uint32_t time){ // rechnet die Timer-Ticks in Millisekunden um
  return (time * 1000) / 488; // Berechnet die korrekte Zeit --> Timer-Ticks in ms
}


void display_statistics(int errors) { // Spielstatistik ausgeben
  uart_writeString("\nSpielstatistik\n");

  if (response_count > 0) {
    total_response_time = correct_time(total_response_time);  // Umrechnung auf Millisekunden
    uint32_t average_time = total_response_time / response_count;

    uart_writeString("Durchschnittliche Antwortzeit: ");
    uart_writeNumber(average_time/1000);
    uart_writeString(",");
    uart_writeNumber(average_time%1000);
    uart_writeString(" s\n");
    uart_writeString("Gesamtzeit: ");
    uart_writeNumber(total_response_time/1000);
    uart_writeString(",");
    uart_writeNumber(total_response_time%1000);
    uart_writeString(" s\n");
    uart_writeString("Anzahl Fehler: ");
    uart_writeNumber(errors);
    uart_writeString("\n");
    uart_writeString("Anzahl Versuche: ");
    uart_writeNumber(response_count);
    uart_writeString("\n\n");

  } else {
    uart_writeString("Keine gültigen Eingaben.\n");
  }
}