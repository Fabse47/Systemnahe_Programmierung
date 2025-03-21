#include "wordlist.h"

/**
 * @brief Eigene Implementierung der Funktion strcpy.
 *
 * Diese Funktion kopiert den Inhalt von @p src in @p dest,
 * inklusive der Nullterminierung.
 *
 * @param[out] dest Zielpuffer, in den die Zeichen kopiert werden.
 * @param[in]  src  Quell-String, der kopiert wird.
 */
void my_strcpy(char *dest, const char *src) {
  while (*src) {
    *dest++ = *src++;
  }
  *dest = '\0';  // Null-Terminierung setzen
}

/**
 * @brief Hauptspeicherort für alle Wörter, die im Hangman-Spiel genutzt werden können.
 *
 * @note In dieser Liste können bis zu @ref MAX_WORDS Wörter
 *       gespeichert werden, wobei jedes Wort maximal
 *       @ref MAX_WORD_LENGTH Zeichen (inkl. Nullterminierung) haben darf.
 */
char word_list[MAX_WORDS][MAX_WORD_LENGTH] = {
  "hangman", "computer", "cortex", "embedded", "hardware"
};

/**
 * @brief Aktuelle Anzahl der gespeicherten Wörter in @ref word_list.
 *
 * Wird um 1 erhöht, wenn über @ref add_custom_word
 * ein neues Wort hinzugefügt wird.
 */
int word_count = 5;

/**
 * @brief Liest ein benutzerdefiniertes Wort über UART ein und speichert es in @ref word_list.
 *
 * Die Funktion fragt den Benutzer nach einem Wort, das über das UART-Interface
 * eingegeben wird. Wird 'Enter' gedrückt, endet der Lesevorgang. Das neue Wort wird
 * anschließend in @ref word_list abgelegt, sofern die maximale Anzahl an Wörtern
 * (@ref MAX_WORDS) nicht überschritten ist.
 *
 * Falls die maximale Anzahl bereits erreicht ist, wird eine Fehlermeldung ausgegeben.
 */
void add_custom_word() {
  if (word_count >= MAX_WORDS) {
    uart_writeString("Wortliste ist voll! Kann keine weiteren Wörter hinzufügen.\n");
    return;
  }

  uart_writeString("Gib dein eigenes Wort ein: ");
  char new_word[MAX_WORD_LENGTH];
  int i = 0;

  while (i < MAX_WORD_LENGTH - 1) {
    char c = uart_readByteBlocking();
    if (c == '\n' || c == '\r') { // Eingabe von "Enter" beendet das Wort
      break;
    }
    new_word[i++] = c;
    uart_writeByte(c);
  }
  new_word[i] = '\0'; // Nullterminierung

  // Speichere das neue Wort in der Liste
  for (int j = 0; j < MAX_WORD_LENGTH; j++) {
    word_list[word_count][j] = new_word[j];
  }
  word_count++;

  uart_writeString("\nNeues Wort: \"");
  uart_writeString(word_list[word_count - 1]);
  uart_writeString("\"\n\nWort wurde im Speicher abgelegt!\n");
}

/**
 * @brief Wählt ein zufälliges Wort aus @ref word_list aus und kopiert es in @p word.
 *
 * Die Funktion initialisiert einen Zufallszahlengenerator,
 * wählt basierend auf dem Ergebnis einen Index innerhalb der vorhandenen
 * Wörter (@ref word_count) aus und kopiert das entsprechende Wort in @p word.
 *
 * @param[out] word Speicherziel, in das das zufällig gewählte Wort kopiert wird.
 */
void select_random_word(char *word) {
  if (word_count == 0) {  // Ausnahmefall, sollte nie auftreten
    uart_writeString("Keine Wörter verfügbar! Nutze Standardwörter.\n");
    my_strcpy(word, "hangman");
    return;
  }

  rng_init(); // Initialisierung des Zufallszahlengenerators
  int index = rng_getRandomValue_waiting(); // zufällige Zahl abwarten
  index = index % word_count; // Modulo, um einen gültigen Index zu erhalten
  my_strcpy(word, word_list[index]);
}
