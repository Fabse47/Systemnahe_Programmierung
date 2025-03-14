#include <stdint.h>

#include "uart.h"
#include "timer.h"
#include "register_access.h"
#include "nvic.h"
#include "string.h"

void Interrupt2_Handler(void);

void Interrupt2_Handler(void)
{
  register_write(UART_BASE_ADDRESS | UART_RXDRDY, 0 );
  register_write( Interrupt_ICPR, Interrupt_ID2 );

  uart_readByte();
}

void uart_init()
{

  // set Flow-Controll and/or Parity (see Table 288, page 156) --------------X
  // Hardware flow control: Disabled = 0 (default)
  // Parity: Exclude parity bit = 0x0    (default)
  // register_write((UART_BASE_ADDRESS + UART_CONFIG), 0); // Optional

  // set PSELRXD, PSELRTS, PSELTRTS and PSELTXD -----------------------------

  // PSELRTS - disconnected (default)
  // register_write((UART_BASE_ADDRESS + UART_PSELRTS), 0xFFFFFFFF); // Optional

  // configure GPIO Pins to RXD, TXD ----------------------------------------

  // Set Interrupts on RX ---------------------------------------------------
  // RXDRDY = enabled (..000100)
  // register_write((UART_BASE_ADDRESS + UART_INTEN), 4);

  // set baudrate (see Table 287 on page 156) -------------------------------
  // Baud9600   = 0x00275000
  // Baud19200  = 0x004EA000
  // Baud115200 = 0x01D7E000
  // Baud250000 = 0x04000000 (default)

  // register_write((UART_BASE_ADDRESS + UART_BAUDRATE), 0x01D7E000);

  // Enable UART ------------------------------------------------------------
  register_write( ( UART_BASE_ADDRESS + UART_ENABLE ), 4 );


  // Fire the START event for the Transmitter: ------------------------------
  register_write( ( UART_BASE_ADDRESS + UART_STARTTX ), UART_TASK_START );

  // Fire the START event for the Receiver: ---------------------------------
  register_write( ( UART_BASE_ADDRESS + UART_STARTRX ), UART_TASK_START );


  // Enable Interrupt
  register_write((UART_BASE_ADDRESS | UART_INTENSET), UART_INT_RXDRDY ); // Interrupt on Compare[0]

  // Enable User-Interrupt from Cortex-M0
  // ID2 ist der UART
  register_write( Interrupt_Set_Enable, Interrupt_ID2 );
}

void uart_writeByte( uint8_t data )
{
  // write the data to the TXD register
  register_write( ( UART_BASE_ADDRESS + UART_TXD ), data );

  // need to "wait" until its transmitted
}

uint8_t uart_readByte()
{

  // if not ready, return 0
  uint32_t receiveIsReady =
    register_read( ( UART_BASE_ADDRESS + UART_RXDRDY ) );

  if ( receiveIsReady )
  {

    // we have to CLEAR the event before reading out from RXD
    register_write( ( UART_BASE_ADDRESS + UART_RXDRDY ), UART_EVENT_CLEAR );

    // FIFO is ready to read something out of it
    return register_read( ( UART_BASE_ADDRESS + UART_RXD ) );
  }
  else
  {

    // FIFO is not ready to read,
    // so return 0 instead
    return 0;
  }
}


char uart_readByteBlocking() {
  char input = 0;
  while (input == 0) {
    input = uart_readByte();
  }
  return input;
}


void uart_writeString( const char * string )
{
  while ( *string != '\0' )
  {
    uart_writeByte( *string );
    ++string;
  }
}

void uart_writeNumber(uint32_t num) {
  char str[12];  // Platz für bis zu 10 Ziffern + Nullterminierung
  int i = 0;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
  } else {
    while (num > 0) {
      str[i++] = (num % 10) + '0';  // Letzte Ziffer extrahieren
      num /= 10;
    }
    str[i] = '\0';

    // Zeichenkette umdrehen
    for (int j = 0; j < i / 2; j++) {
      char temp = str[j];
      str[j] = str[i - j - 1];
      str[i - j - 1] = temp;
    }
  }

  uart_writeString(str);
}