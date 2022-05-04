// Corvette Digital Cluster Tester
//**************************************************************//
//  Name    : Corvette Digital Cluster Tester                   //
//  Author  : Mikael Karlsson, Sweden                           //
//  Date    : 20 Feb, 2022                                      //
//  Version : 2.2                                               //
//****************************************************************

#include "Corvette-LCD-Tester.h" // all definitions for the 256 data bits are in this file

// Enable next line for serial output, used for debug output
//#define SERIALPRINT 

// Pin connected to pin 5 of cluster
int strobePin = 8;
// Pin connected to pin 7 of cluster
int clockPin  = 9;
// Pin connected to pin 8 of cluster
int dataPin   = 10;
// Internal LED
int led = 13;

// the delay between each 256 bits, value is milliseconds
int displaydelay = 500;

// the delay between each test, value is milliseconds
int testdelay = 1000;

void setup() {
  // enable and set up pins
  pinMode(strobePin, OUTPUT);   // strobe pin
  digitalWrite(strobePin, LOW); // set low
  pinMode(clockPin, OUTPUT);    // clock pin
  digitalWrite(clockPin, LOW);  // set low
  pinMode(dataPin, OUTPUT);     // data pin
  digitalWrite(dataPin, LOW);   // set low
  pinMode(led, OUTPUT);         // enable LED pin
  delay(2000);                  // wait 2 seconds so that pins really go low

#ifdef SERIALPRINT
  Serial.begin(115200);
  Serial.println("Start testing");
#endif

} // setup

void loop()
{
  // Count from 0-9 on all digits, digits with 1 and 2 shift each count
  // decimal points shift every other digit from on to off
  SendBitStream(allDigits, digit);
  delay(testdelay);
  // Speed up, from 5 to 85 alternating MPH and KM/H each segment
  SendBitStream(speedGauge, speedometer);
  delay(testdelay);
  // Go from E to F on the gas meter, alternating RESERVE every other segment
  SendBitStream(gasGauge, gasmeter);
  delay(testdelay);
  // display all text and symbols on the info LCD
  SendBitStream(allInfotext, allinfotext);
  delay(testdelay);
  // rev up from 0 to 60 on the tachometer
  SendBitStream(tachGauge, tachgauge);
  delay(testdelay);
}


//*********************************************
//* This function send out the 256 bit burst. *
//* Accepts two parameters:                   *
//* #1 an array with bit definitions          *
//* #2 number of rows in the array            *
//*********************************************

void SendBitStream( const int myarray[][bitstream], int size ) 
{
#ifdef SERIALPRINT
  Serial.print("\nBits: ");
#endif
   // loop through number of rows in the array
   for ( int i = 0; i < size; ++i ) 
    {
    // loop through bitstream
    for ( int j = 0; j < bitstream; ++j )
      {
#ifdef SERIALPRINT
    Serial.print(pgm_read_byte_near(&myarray[i][j]));
    Serial.print("-");
#endif
      shiftOut(dataPin, clockPin, LSBFIRST, pgm_read_byte_near(&myarray[i][j])); // send out 8 bits with clock
      } // end shiftOut loop
    digitalWrite(strobePin, HIGH);  // strobe after all 256 bits have been sent
    delayMicroseconds(5);           // 5 us delay
    digitalWrite(strobePin, LOW);   // strobe done
    delay(displaydelay);            // delay between each 256 bits
#ifdef SERIALPRINT
    Serial.print("\n");
#endif
   } // end size loop
} 
