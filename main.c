#include "usart.h"
#include <avr/io.h>
#include <util/delay.h>

char keypadScan();

int main(void) {
  usartInit(9600);

  unsigned char keyPressed = 0x00;
  unsigned char key = 0x00;

  while(1) {
    key = keypadScan();

    if(!keyPressed && key != 0) {
      usartPutChar(key);
      keyPressed = 0xff;
    }

    //Vazna stvar, funkcija keypadScan() vraca 0 u ASCII kodu kada
    //nista nije pritisnuto!
    if(key == 0) {
      keyPressed = 0x00;
    }

  }

  return 0;
}



char keypadScan() {
  unsigned char row, tmp;
  char key = 0;

  MCUCR &= ~0x10; //Ukljucenje PUD = 0
  tmp = UCSR0B;
  UCSR0B &= ~0x18;
  PORTD = 0x0f; //Ukljucenje pull-up otpornika

  for(row = 0x80; row != 0x08; row >>= 1) {
    DDRD = row;
    _delay_ms(2);

    switch(row | ((~PIND)&0x0f)) {
    case 0x88:
      key = '1';
      break;
    case 0x84:
      key = '2';
      break;
    case 0x82:
      key = '3';
      break;
    case 0x81:
      key = 'A';
      break;

    case 0x48:
      key = '4';
      break;
    case 0x44:
      key = '5';
      break;
    case 0x42:
      key = '6';
      break;
    case 0x41:
      key = 'B';
      break;

    case 0x28:
      key = '7';
      break;
    case 0x24:
      key = '8';
      break;
    case 0x22:
      key = '9';
      break;
    case 0x21:
      key = 'C';
      break;

    case 0x18:
      key = '*';
      break;
    case 0x14:
      key = '0';
      break;
    case 0x12:
      key = '#';
      break;
    case 0x11:
      key = 'D';
      break;
    }
  }

  UCSR0B = tmp;
  return key;
}
