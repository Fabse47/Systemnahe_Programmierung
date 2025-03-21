#include "main.h"

/**
 * @brief Hauptfunktion für das Hangman-Spiel.
 *
 * Diese Funktion initialisiert die serielle Schnittstelle, zeigt ein Eingabemenü,
 * setzt das Spiel zurück und wählt ein zufälliges Wort. Anschließend läuft eine
 * Endlosschleife, in der die Spiellogik verarbeitet wird:
 * - Es wird ständig geprüft, ob das Spiel noch läuft (@ref check_gamestate).
 * - Der aktuelle Spielstand wird angezeigt (@ref display_game_state).
 * - Eine Benutzereingabe wird eingelesen (@ref get_player_input_with_timeout).
 * - Die Eingabe wird auf das aktuelle Wort angewandt (@ref check_and_update_word).
 * - Falls der Buchstabe nicht im Wort enthalten ist, wird die Fehleranzahl erhöht.
 *
 * Sobald das Spiel vorbei ist (maximale Fehlerzahl oder das Wort ist erraten),
 * wird dies in @ref check_gamestate erkannt und entsprechende Rückmeldungen
 * (gewonnen/verloren) werden angezeigt. Die Funktion kehrt danach nicht mehr zurück.
 */
int hangman() {
  uart_init();                // Serielle Schnittstelle initialisieren
  input_menu();               // Eingabemenü am Anfang des Spiels
  reset_program();            // Timer starten, Variablen initialisieren

  select_random_word(word);   // Zufälliges Wort wählen
  init_guessed_word(guessed, word);  // Leere Darstellung "_ _ _"

  while (1) {
    check_gamestate();                     // Abbruchbedingung prüfen
    display_game_state(guessed, errors);   // Spielstand anzeigen

    char input = get_player_input_with_timeout(); // Spielereingabe einlesen

    // Falls der eingegebene Buchstabe nicht im Wort vorkommt, Fehler erhöhen
    if (!check_and_update_word(input, word, guessed)) {
      errors++;
    }
  }

  return 0;
}
