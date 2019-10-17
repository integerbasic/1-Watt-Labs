
byte current_digits[] = {10, 10, 10, 10}; //all blank
byte current_dp = 0;
byte current_on = 0;

/*

  left to right digit select map:
  02 16 08 04

*/
byte msel[] = {
  4, 8, 16, 2
};

/*
  map of LED segments to bit position

     5
   -----
  3|   |7
   |   |
   | 6 |
   -----
  1|   |4
   |   |
   | 0 |
   -----

  So, for example, to create the digit '1', turn on bits 7 and 4
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

void update(word val, byte dp) {
  // the current value to be displayed; the device is capable of expressing 0 to 9999.
  // 10000 or above is interpreted as 'blank' (no output illuminated).
  byte place, digit;

  for (place = 3; place >= 0; place--) {
    if (val > 9999) {
      current_digits[place] = 10; //blank
    } else {
      digit = val / pow(10, place);
      val = int(val) % int(pow(10, place));
      if (digit > 0) {
        current_digits[place] = digit;
      } else if (place <= dp) {
        current_digits[place] = 0;
      } else {
        current_digits[place] = 10; //blank
      }
    }
  }

  current_dp = dp;
  current_on = 0;
}

/*
   This method needs to be called at a rapid, regular interval,
   to strobe the display at a rate that is a comfortable 'frame rate'
   for the human eye.
*/
void displayService(void)
{
  if (current_dp == current_on) {
    dec_out(current_on, current_digits[current_on], 1);
  } else {
    dec_out(current_on, current_digits[current_on], 0);
  }
  current_on++;
  if (current_on == 4) {
    current_on = 0;
  }
}
