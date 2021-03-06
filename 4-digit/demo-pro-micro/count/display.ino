// -*- mode: c++ -*-

byte display_digits[4];
byte display_dpoints[4];
byte current_on;

/*
  Left to right (most significant to least significant) digit select map:
  0x02 0x10 0x08 0x04

  Codes sent to the device must be inverted.  In same order:
  0xFD 0xEF 0xF7 0xFB

*/
byte msel[] = {4, 8, 16, 2};

/*
   decimal significance of each place.
   for this limited range, a lookup is faster than using exponentiation math (pow)
*/
word psig[] = {1, 10, 100, 1000};

/*
  map of LED segments to bit position

          5(0x20)
         ---------
  3(0x08)|       |7(0x80)
         |       |
         |6(0x40)|
         ---------
  1(0x02)|       |4(0x10)
         |       |
         |0(0x01)|
         ---------

  So, for example, to create the digit '7',
  turn on bits 5, 7, and 4.  The necesary byte  value is
  0x20 + 0x80 + 0x10 = 0xB0

*/
byte dmap[] = {
  (1 << 5) + (1 << 3) + (1 << 1) + (1 << 0) + (1 << 4) + (1 << 7),
  (1 << 7) + (1 << 4),
  (1 << 5) + (1 << 7) + (1 << 6) + (1 << 1) + (1 << 0),
  (1 << 5) + (1 << 6) + (1 << 0) + (1 << 7) + (1 << 4),
  (1 << 3) + (1 << 7) + (1 << 6) + (1 << 4),
  (1 << 0) + (1 << 4) + (1 << 6) + (1 << 3) + (1 << 5),
  (1 << 5) + (1 << 3) + (1 << 1) + (1 << 0) + (1 << 4) + (1 << 6),
  (1 << 5) + (1 << 7) + (1 << 4),
  (1 << 0) + (1 << 1) + (1 << 3) + (1 << 4) + (1 << 5) + (1 << 6) + (1 << 7),
  (1 << 0) + (1 << 3) + (1 << 4) + (1 << 5) + (1 << 6) + (1 << 7)
};

/*
  dec_out:
  Illuminate one digit in the bank of four, with a given value.

  pos = 3|2|1|0, left to right
  val = 0-9 ; 10 or above implies _blank_
  dp = boolean; turn on decimal point, or don't

*/
void dec_out(byte pos, byte val, byte dp) {
  byte code;
  if (val >= 10) {
    // consider out-of-range as code for blank
    code = 0;
  }
  else {
    code = dmap[val];
  }
  if (dp) {
    code = code + 4;
  }

  digitalWrite(DISPLAY_LATCH_PIN, LOW);
  SPI.transfer(255 - msel[pos]); // digit select
  SPI.transfer(code);  //display value
  digitalWrite(DISPLAY_LATCH_PIN, HIGH);

}

void display_blank(void) {
  display_digits[0] = 10;
  display_digits[1] = 10;
  display_digits[2] = 10;
  display_digits[3] = 10;
  display_dpoints[0] = 1;
  display_dpoints[1] = 1;
  display_dpoints[2] = 1;
  display_dpoints[3] = 1;
  current_on = 0;
}

/*
  Set the current value to be displayed (val); the device is capable of expressing 0 to 9999.
  10000 or above is interpreted as 'blank' (no output illuminated).

  dp == the number of digits right of the decimal point.
*/
void display_update(word val, byte dp) {
  byte pp, place, digit;
  byte bok = 1;
  
  if (val > 9999) {
    display_blank();
  } else {

    for (pp = 4; pp >= 1; pp--) {
      place = pp - 1;

      // set/clear dp flag
      display_dpoints[place] = (place == dp) ? 1:0;

      digit = val / psig[place];
      val = val % psig[place];
      if (digit > 0) {
	display_digits[place] = digit;
	bok = 0;
      } else if (place <= dp) {
	display_digits[place] = 0;
      } else if ( bok != 1 ) {
	display_digits[place] = 0;      
      } else {
	display_digits[place] = 10; //blank
      }
    }
  }
}

/*
   This method needs to be called at a rapid, regular interval,
   to strobe the display at a rate that is a comfortable 'frame rate'
   for the human eye.
*/
void display_service(void)
{
  dec_out(current_on, display_digits[current_on], display_dpoints[current_on]);
  current_on++;
  if (current_on == 4) {
    current_on = 0;
  }
}
