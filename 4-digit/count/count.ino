#include <TimerOne.h>
#include <SPI.h>

int test_value = 0;

#define DISPLAY_LATCH_PIN 9

// the setup routine runs once when you press reset:
void setup() {
  pinMode(DISPLAY_LATCH_PIN, OUTPUT);
  Timer1.initialize(5000);
  Timer1.attachInterrupt(displayService); // runs every 5 msec
  SPI.begin();
}

// the loop routine runs over and over again forever:
void loop() {

  /*
    Count from 0 to 100 at a one-second pace.
    Show blank for one second after 100, then restart.
    Show one fractional digit.
  */

  if (test_value == 101) {
    update(10000, 1);
  } else {
    update(test_value, 1);
  }
  
  test_value = test_value + 1;
  if (test_value == 102) {
    test_value = 0;
  }
  
  delay(1000);   // wait for a second
}
