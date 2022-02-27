// Corvette Digital Cluster Tester
//***************************************************************
//  Name    : Corvette Digital Cluster Tester                   *
//  Author  : Mikael Karlsson, Sweden                           *
//  Date    : 20 Feb, 2022                                      *
//  Version : 1.0                                               *
//  This code just walks through all bits one by one until all  *
//  bits have been sent out.                                    *
//  useful to test that all LCD segments works                  *
//***************************************************************

// Enable next line for serial output, used for debug
// #define SERIALPRINT 

// Pin connected to pin 5 of cluster
int strobePin = 8;
// Pin connected to pin 7 of cluster
int clockPin  = 9;
// Pin connected to pin 8 of cluster
int dataPin   = 10;
// Internal LED
int led = 13;

// Arrays for ic and bits
int lcdbitstream[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // 32 segments with 8 bits per segment
int lcdbits[] = {0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000}; // the bits for the segments

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

// This is the main routine, run once only
// loop through all positions
  for (int ic = 0; ic <= 31; ic++) {                // number of IC's
    for (int bitpos = 0; bitpos <= 7; bitpos++ ) {  // number of bits
      lcdbitstream[ic] = lcdbits[bitpos];           // set bit
      SendBitStream();                              // send it to the display
      lcdbitstream[ic] = 0;                         // reset the current position in the array to 0

      digitalWrite(led, HIGH);                      // turn on the LED
      delay(500);                                   // delay 0,5 second
      digitalWrite(led, LOW);                       // Turn of the LED
      delay(500); 
    } // bitpos
  } // ic
}


void loop()
{
  // Do nothing
}


// this function sends out the complete 256 bit stream from the lcdbitstream array
void SendBitStream()
{
#ifdef SERIALPRINT
  Serial.print("\nBits: ");
#endif

for (int i = 0; i <= 31; i++) // send out 8 bits at a time until we have sent all 256 bits
  {
#ifdef SERIALPRINT
    Serial.print(lcdbitstream[i], BIN);
    Serial.print("-");
#endif
    shiftOut(dataPin, clockPin, LSBFIRST, lcdbitstream[i]); // send out 8 bits with clock
  }
  digitalWrite(strobePin, HIGH);  // strobe after all 256 bits have been sent
  delayMicroseconds(5);           // 5 us delay
  digitalWrite(strobePin, LOW);   // strobe done
}
