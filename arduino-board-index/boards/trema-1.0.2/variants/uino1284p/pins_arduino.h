/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

/*
Pin Mapping
-----------
*uino     ATmega1284p                     Function
A0  D26   32 - PA5 (PCINT5/ADC5)
A1  D27   33 - PA4 (PCINT4/ADC4)
A2  D28   34 - PA3 (PCINT3/ADC3)
A3  D29   35 - PA2 (PCINT2/ADC2)
A4  D30   36 - PA1 (PCINT1/ADC1)
A5  D31   37 - PA0 (PCINT0/ADC0)

D0        9  - PD0 (PCINT24/RXD0/T3)      UART RX0
D1        10 - PD1 (PCINT25/TXD0)         UART TX0
D2        11 - PD2 (PCINT26/RXD1/INT0)    IRQ2, UART RX1
D3        12 - PD3 (PCINT27/TXD1/INT1)    IRQ3, UART TX1
D4        13 - PD4 (PCINT28/XCK1/OC1B)    PWM
D5        14 - PD5 (PCINT29/OC1A)         PWM
D6        15 - PD6 (PCINT30/OC2B/ICP)     PWM
D7        16 - PD7 (PCINT31/OC2A)         PWM

D8        42 - PB2 (PCINT10/INT2/AIN0)  
D9        43 - PB3 (PCINT11/OC0A/AIN1)    PWM
D10       44 - PB4 (PCINT12/OC0B/SS)      PWM, SPI SS
D11       1  - PB5 (PCINT13/ICP3/MOSI)    SPI MOSI
D12       2  - PB6 (PCINT14/OC3A/MISO)    PWM, SPI MISO
D13       3  - PB7 (PCINT15/OC3B/SCK)     PWM, SPI SCK, LED

SCL D14   19 - PC0 (PCINT16/SCL)          SCL
SDA D15   20 - PC1 (PCINT17/SDA)          SDA
L1  D16   21 - PC2 (PCINT18/TCK)          L1
L2  D17   22 - PC3 (PCINT19/TMS)          L2

D18       23 - PC4 (PCINT20/TDO)
D19       24 - PC5 (PCINT21/TDI)
D20       25 - PC6 (PCINT22/TOSC1)
D21       26 - PC7 (PCINT23/TOSC2)
D22       40 - PB0 (PCINT8/T0/XCK0)
D23       41 - PB1 (PCINT9/T1/CLK0)
D24  A6   30 - PA7 (PCINT7/ADC7)
D25  A7   31 - PA6 (PCINT6/ADC6)

*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

#define NUM_DIGITAL_PINS      32
#define NUM_ANALOG_INPUTS      8

#define PIN_WIRE_SDA          (14)
#define PIN_WIRE_SCL          (15)

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

static const uint8_t LED_BUILTIN = 16;

#define PIN_SPI_SS            (31)
#define PIN_SPI_MOSI          (11)
#define PIN_SPI_MISO          (12)
#define PIN_SPI_SCK           (13)

static const uint8_t SS   = PIN_SPI_SS;
static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;

#define PIN_A0   (26)
#define PIN_A1   (27)
#define PIN_A2   (28)
#define PIN_A3   (29)
#define PIN_A4   (30)
#define PIN_A5   (31)
#define PIN_A6   (24)
#define PIN_A7   (25)

static const uint8_t A0 = PIN_A0;
static const uint8_t A1 = PIN_A1;
static const uint8_t A2 = PIN_A2;
static const uint8_t A3 = PIN_A3;
static const uint8_t A4 = PIN_A4;
static const uint8_t A5 = PIN_A5;
static const uint8_t A6 = PIN_A6;
static const uint8_t A7 = PIN_A7;

#define ifpin(p,what,ifnot)     (((p) >= 0 && (p) < NUM_DIGITAL_PINS) ? (what) : (ifnot))
#define PORT_NDX_TO_PCMSK(x)    ((x) == 0 ? &PCMSK0 : ((x) == 1 ? &PCMSK1 : ((x) == 2 ? &PCMSK2 : ((x) == 3 ? &PCMSK3 : (uint8_t )0))))


#define digitalPinToPCICR(p)    ifpin(p,&PCICR,(uint8_t *)0)
#define digitalPinToPCICRbit(p) ifpin(p,digital_pin_to_pcint[p] >> 3,0)
#define digitalPinToPCMSK(p)    ifpin(p,(uint8_t *)PORT_NDX_TO_PCMSK(digital_pin_to_pcint[p] >> 3),(uint8_t *)0)
#define digitalPinToPCMSKbit(p) ifpin(p,digital_pin_to_pcint[p] & 0x7,0)

#define analogInputToDigitalPin(p)  ((p) <= 5 ? (p) + 26 : ((p) <= 7 ? (p) + 24 - 6 : -1))
#define digitalPinToAnalogPin(p)    ((p) >= 24 && (p) <= 25 ? (p) - 24 + 6 : ((p) >= 26 && (p) <= 31 ? (p) - 26 : -1 ))
#define digitalPinHasPWM(p)         ifpin(p,pgm_read_byte(digital_pin_to_timer_PGM + (p)) != NOT_ON_TIMER,1==0)
#define analogPinToChannel(p)       ((p) <= 5 ? 5 - (p) : ((p) == 6 ? 7 : ((p) == 7 ? 6 : ((p) >= 26 && (p) <= 31 ? 31 - (p) : ((p) == 24 ? 7 : ((p) == 25 ? 6 : -1 ))))))

// return associated INTx number for associated/valid pins,
// otherwise NOT_AN_INTERRUPT
#define digitalPinToInterrupt(p) ((p) == 2 ? 0 : ((p) == 3 ? 1 : ((p) == 8 ? 2 : NOT_AN_INTERRUPT)))

#define PA 1
#define PB 2
#define PC 3
#define PD 4

// specify port for each pin D0-D31
#define PORT_D0 PD    // D0  - PD0
#define PORT_D1 PD    // D1  - PD1
#define PORT_D2 PD    // D2  - PD2
#define PORT_D3 PD    // D3  - PD3
#define PORT_D4 PD    // D4  - PD4
#define PORT_D5 PD    // D5  - PD5
#define PORT_D6 PD    // D6  - PD6
#define PORT_D7 PD    // D7  - PD7
#define PORT_D8 PB    // D8  - PB2
#define PORT_D9 PB    // D9  - PB3
#define PORT_D10 PB   // D10 - PB4
#define PORT_D11 PB   // D11 - PB5
#define PORT_D12 PB   // D12 - PB6
#define PORT_D13 PB   // D13 - PB7
#define PORT_D14 PC   // D14 - PC0
#define PORT_D15 PC   // D15 - PC1
#define PORT_D16 PC   // D16 - PC2
#define PORT_D17 PC   // D17 - PC3
#define PORT_D18 PC   // D18 - PC4
#define PORT_D19 PC   // D19 - PC5
#define PORT_D20 PC   // D20 - PC6
#define PORT_D21 PC   // D21 - PC7
#define PORT_D22 PB   // D22 - PB0
#define PORT_D23 PB   // D23 - PB1
#define PORT_D24 PA   // D24 - PA7
#define PORT_D25 PA   // D25 - PA6
#define PORT_D26 PA   // D26/A0 - PA5
#define PORT_D27 PA   // D27/A1 - PA4
#define PORT_D28 PA   // D28/A2 - PA3
#define PORT_D29 PA   // D29/A3 - PA2
#define PORT_D30 PA   // D30/A4 - PA1
#define PORT_D31 PA   // D31/A5 - PA0

// specify port bit for each pin D0-D31
#define BIT_D0 0    // D0  - PD0
#define BIT_D1 1    // D1  - PD1
#define BIT_D2 2    // D2  - PD2
#define BIT_D3 3    // D3  - PD3
#define BIT_D4 4    // D4  - PD4
#define BIT_D5 5    // D5  - PD5
#define BIT_D6 6    // D6  - PD6
#define BIT_D7 7    // D7  - PD7
#define BIT_D8 2    // D8  - PB2
#define BIT_D9 3    // D9  - PB3
#define BIT_D10 4   // D10 - PB4
#define BIT_D11 5   // D11 - PB5
#define BIT_D12 6   // D12 - PB6
#define BIT_D13 7   // D13 - PB7
#define BIT_D14 0   // D14 - PC0
#define BIT_D15 1   // D15 - PC1
#define BIT_D16 2   // D16 - PC2
#define BIT_D17 3   // D17 - PC3
#define BIT_D18 4   // D18 - PC4
#define BIT_D19 5   // D19 - PC5
#define BIT_D20 6   // D20 - PC6
#define BIT_D21 7   // D21 - PC7
#define BIT_D22 0   // D22 - PB0
#define BIT_D23 1   // D23 - PB1
#define BIT_D24 7   // D24 - PA7
#define BIT_D25 6   // D25 - PA6
#define BIT_D26 5   // D26/A0 - PA5
#define BIT_D27 4   // D27/A1 - PA4
#define BIT_D28 3   // D28/A2 - PA3
#define BIT_D29 2   // D29/A3 - PA2
#define BIT_D30 1   // D30/A4 - PA1
#define BIT_D31 0   // D31/A5 - PA0

// macro equivalents of PROGMEM arrays port_to_mode_PGM[] etc. below
#define PORT_TO_MODE(x)   (x == 1 ? &DDRA : (x == 2 ? &DDRB : (x == 3 ? &DDRC : (x == 4 ? &DDRD : NOT_A_PORT)))) 
#define PORT_TO_OUTPUT(x) (x == 1 ? &PORTA : (x == 2 ? &PORTB : (x == 3 ? &PORTC : (x == 4 ? &PORTD : NOT_A_PORT))))
#define PORT_TO_INPUT(x)  (x == 1 ? &PINA : (x == 2 ? &PINB : (x == 3 ? &PINC : (x == 4 ? &PIND : NOT_A_PORT)))) 

#ifndef ARDUINO_MAIN
extern const uint8_t digital_pin_to_pcint[];
#else
const uint8_t digital_pin_to_pcint[NUM_DIGITAL_PINS] =
{
  24,   // D0  - PD0
  25,   // D1  - PD1
  26,   // D2  - PD2
  27,   // D3  - PD3
  28,   // D4  - PD4
  29,   // D5  - PD5
  30,   // D6  - PD6
  31,   // D7  - PD7
  10,   // D8  - PB2
  11,   // D9  - PB3
  12,   // D10 - PB4
  13,   // D11 - PB5
  14,   // D12 - PB6
  15,   // D13 - PB7
  16,   // D14 - PC0
  17,   // D15 - PC1
  18,   // D16 - PC2
  19,   // D17 - PC3
  20,   // D18 - PC4
  21,   // D19 - PC5
  22,   // D20 - PC6
  23,   // D21 - PC7
  8,    // D22 - PB0
  9,    // D23 - PB1
  7,    // D24 - PA7
  6 ,   // D25 - PA6
  5,    // D26/A0 - PA5
  4,    // D27/A1 - PA4
  3,    // D28/A2 - PA3
  2,    // D29/A3 - PA2
  1,    // D30/A4 - PA1
  0,    // D31/A5 - PA0
};

// these arrays map port names (e.g. port B) to the
// appropriate addresses for various functions (e.g. reading
// and writing)
const uint16_t PROGMEM port_to_mode_PGM[] =
{
  NOT_A_PORT,
  (uint16_t) &DDRA,
  (uint16_t) &DDRB,
  (uint16_t) &DDRC,
  (uint16_t) &DDRD,
};

const uint16_t PROGMEM port_to_output_PGM[] =
{
  NOT_A_PORT,
  (uint16_t) &PORTA,
  (uint16_t) &PORTB,
  (uint16_t) &PORTC,
  (uint16_t) &PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] =
{
  NOT_A_PORT,
  (uint16_t) &PINA,
  (uint16_t) &PINB,
  (uint16_t) &PINC,
  (uint16_t) &PIND,
};


const uint8_t PROGMEM digital_pin_to_port_PGM[NUM_DIGITAL_PINS] =
{
  PORT_D0,
  PORT_D1,
  PORT_D2,
  PORT_D3,
  PORT_D4,
  PORT_D5,
  PORT_D6,
  PORT_D7,
  PORT_D8,
  PORT_D9,
  PORT_D10,
  PORT_D11,
  PORT_D12,
  PORT_D13,
  PORT_D14,
  PORT_D15,
  PORT_D16,
  PORT_D17,
  PORT_D18,
  PORT_D19,
  PORT_D20,
  PORT_D21,
  PORT_D22,
  PORT_D23,
  PORT_D24,
  PORT_D25,
  PORT_D26,
  PORT_D27,
  PORT_D28,
  PORT_D29,
  PORT_D30,
  PORT_D31
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[NUM_DIGITAL_PINS] =
{
  _BV(BIT_D0),
  _BV(BIT_D1),
  _BV(BIT_D2),
  _BV(BIT_D3),
  _BV(BIT_D4),
  _BV(BIT_D5),
  _BV(BIT_D6),
  _BV(BIT_D7),
  _BV(BIT_D8),
  _BV(BIT_D9),
  _BV(BIT_D10),
  _BV(BIT_D11),
  _BV(BIT_D12),
  _BV(BIT_D13),
  _BV(BIT_D14),
  _BV(BIT_D15),
  _BV(BIT_D16),
  _BV(BIT_D17),
  _BV(BIT_D18),
  _BV(BIT_D19),
  _BV(BIT_D20),
  _BV(BIT_D21),
  _BV(BIT_D22),
  _BV(BIT_D23),
  _BV(BIT_D24),
  _BV(BIT_D25),
  _BV(BIT_D26),
  _BV(BIT_D27),
  _BV(BIT_D28),
  _BV(BIT_D29),
  _BV(BIT_D30),
  _BV(BIT_D31)
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[NUM_DIGITAL_PINS] =
{
  NOT_ON_TIMER,   // D0  - PD0
  NOT_ON_TIMER,   // D1  - PD1
  NOT_ON_TIMER,   // D2  - PD2
  NOT_ON_TIMER,   // D3  - PD3
  TIMER1B,        // D4  - PD4
  TIMER1A,        // D5  - PD5
  TIMER2B,        // D6  - PD6
  TIMER2A,        // D7  - PD7
  NOT_ON_TIMER,   // D8  - PB2
  TIMER0A,        // D9  - PB3
  TIMER0B,        // D10 - PB4
  NOT_ON_TIMER,   // D11 - PB5
  TIMER3A,        // D12 - PB6
  TIMER3B,        // D13 - PB7
  NOT_ON_TIMER,   // D14 - PC0
  NOT_ON_TIMER,   // D15 - PC1
  NOT_ON_TIMER,   // D16 - PC2
  NOT_ON_TIMER,   // D17 - PC3
  NOT_ON_TIMER,   // D18 - PC4
  NOT_ON_TIMER,   // D19 - PC5
  NOT_ON_TIMER,   // D20 - PC6
  NOT_ON_TIMER,   // D21 - PC7
  NOT_ON_TIMER,   // D22 - PB0
  NOT_ON_TIMER,   // D23 - PB1
  NOT_ON_TIMER,   // D24 - PA7
  NOT_ON_TIMER,   // D25 - PA6
  NOT_ON_TIMER,   // D26/A0 - PA5
  NOT_ON_TIMER,   // D27/A1 - PA4
  NOT_ON_TIMER,   // D28/A2 - PA3
  NOT_ON_TIMER,   // D29/A3 - PA2
  NOT_ON_TIMER,   // D30/A4 - PA1
  NOT_ON_TIMER,   // D31/A5 - PA0
};

#endif // ARDUINO_MAIN

#endif // Pins_Arduino_h
// vim:ai:cin:sts=2 sw=2 ft=cpp