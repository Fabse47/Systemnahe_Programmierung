#include "hangman_timer.h"


void start_hangman_timer() {  // Timer für gesamte Spielzeit starten
  timer_init_detailed( TIMER0, 15, TIMER_MODE_TIMER, TIMER_BIT_MODE_32 );  // timer0 initialisieren
  timer_start( TIMER0 );  // timer0 starten
}


uint32_t stop_hangman_timer() {  // Timer für gesamte Spielzeit stoppen
  timer_capture( TIMER0, CC0 );
  timer_stop( TIMER0 );  // timer0 stoppen

  uint32_t timer0_value = timer_captureCompareGet( TIMER0, CC0 );  // Wert aus timer0 speichern
  timer_clear( TIMER0);  // timer0 leeren

  return timer0_value;
}


void start_timeout_timer() {  // Timer für zu langes Warten starten
  timer_init_detailed( TIMER1, 15, TIMER_MODE_TIMER, TIMER_BIT_MODE_32 );  // timer1 initialisieren
  timer_start( TIMER1 );  // timer1 starten
}


uint32_t stop_timeout_timer() {  // Timer für zu langes Warten stoppen
  timer_capture( TIMER1, CC1 );
  timer_stop( TIMER1 );  // timer1 stoppen

  uint32_t timer1_value = timer_captureCompareGet( TIMER1, CC1 );// Wert aus timer1 speichern
  timer_clear( TIMER1);  // timer1 leeren

  return timer1_value;
}