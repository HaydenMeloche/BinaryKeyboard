/*
    Hayden Meloche
*/

#include "Keyboard.h"

bool MODE1001 = true;
String binary = "";

void setup() {
  //Pin modes
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  // initialize keyboard and serial for testing
  Serial.begin(9600);
  Keyboard.begin();
  if (digitalRead(A2) == LOW) {
    MODE1001 = false;
  }
}

void binaryConvert(long binary) {
  long dec = 0, rem, base = 1;
  while (binary > 0)
  {
    rem = binary % 10;
    dec = dec + rem * base;
    base = base * 2;
    binary = binary / 10;
  }
  binary = "";
  Keyboard.print(char(dec));
}


void loop() {
  if (MODE1001) {
    if (digitalRead(A1) == LOW) {
      delay(200);
      //Serial.write('0');
      Keyboard.write("0");
    }
    if (digitalRead(A0) == LOW) {
      delay(200);
      //Serial.write(97);
      Keyboard.write("1");
    }
    if (digitalRead(A2) == LOW) {
      delay(200);
      //Serial.write(' ');
      Keyboard.write(" ");
    }
  } else {
    if (digitalRead(A1) == LOW) {
      delay(200);
      Serial.write('0');
      binary += "0";
    }
    if (digitalRead(A0) == LOW) {
      delay(200);
      Serial.write("1");
      binary += "1";
    }
    if (digitalRead(A2) == LOW) {
      delay(200);
      if (binary.length() == 8) {
        binaryConvert(atol(binary.c_str()));
      } else {
        //Acts as spacebar if not long enough
        Keyboard.print(" ");
      }
    }
  }
}



