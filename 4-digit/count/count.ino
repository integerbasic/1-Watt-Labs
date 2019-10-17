#include <TimerOne.h>
#include <SPI.h>

int test_value = 90;

#define DISPLAY_LATCH_PIN 9
#define RUN_PIN 6

// the setup routine runs once when you press reset:
void setup() {

  pinMode(DISPLAY_LATCH_PIN, OUTPUT);
  Timer1.initialize(5000);
  Timer1.attachInterrupt(display_service); // runs every 5 msec
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
    display_update(10000, 3);
  } else {
    display_update(test_value, 3);
  }

  test_value = test_value + 1;
  if (test_value == 102) {
    test_value = 90;
  }

  delay(1000);   // wait for a second
}
