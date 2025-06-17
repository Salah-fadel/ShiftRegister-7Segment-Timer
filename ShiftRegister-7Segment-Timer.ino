// Arduino 4-Digit Counter using Shift Registers and 7-Segment Displays
// Author: [Salah-fadel]
// Description: Displays a 4-digit count using 7-segment displays updated every second.

#define SER 9   // Serial data input for shift register
#define ST 8    // Storage register clock pin (latch)
#define SH 10   // Shift register clock pin

const int seg[] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11100110  // 9
};

int count = 0;
unsigned long T1;

void setup() {
  DDRD = B11111110;         // Set PORTD as output (excluding RX)
  pinMode(SER, OUTPUT);
  pinMode(ST, OUTPUT);
  pinMode(SH, OUTPUT);
  T1 = millis();            // Initialize timer
}

void loop() {
  if (millis() - T1 >= 1000) {
    count++;                // Increase count every second
    T1 = millis();
  }

  // Display digits from right to left
  shiftR(count % 10, 4);           // Units
  delay(1); MR();

  shiftR((count % 100) / 10, 3);   // Tens
  delay(1); MR();

  shiftR((count / 100) % 10, 2);   // Hundreds
  delay(1); MR();

  shiftR((count / 1000) % 10, 1);  // Thousands
  delay(1); MR();
}

// Function to shift digit value to corresponding display
void shiftR(int digit, int position) {
  digitalWrite(ST, LOW);

  // Select the digit position using bitmask
  switch (position) {
    case 1: shiftOut(SER, SH, LSBFIRST, B01111111); break;
    case 2: shiftOut(SER, SH, LSBFIRST, B10111111); break;
    case 3: shiftOut(SER, SH, LSBFIRST, B11011111); break;
    case 4: shiftOut(SER, SH, LSBFIRST, B11101111); break;
  }

  // Send the digit's segment data
  shiftOut(SER, SH, LSBFIRST, seg[digit]);

  digitalWrite(ST, HIGH);
}


void MR() {
  digitalWrite(ST,LOW);
  shiftOut(SER,SH,LSBFIRST,B00000000);
  digitalWrite(ST,HIGH);
}
