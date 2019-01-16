/*******************************************************************************
 * Copyright (c) 2018 Robert Kiendl, OE6RKE
 *
 *  A4 Si5351 SDA
 *  A5 Si5351 SCL
 *
 * si5351a + nano + txco 27.00 (ppm2.5) ->
 * https://github.com/etherkit/Si5351Arduino
 * Modul hier https://www.sv1afn.com/si5351a.html,
 * http://ak2b.blogspot.com/2015/01/installing-libraries-and-running-code.html
 *******************************************************************************/
#include "si5351.h"
#include "Wire.h"

Si5351 si5351;


void setup() {

  bool i2c_found;
  
  // Start serial and initialize the Si5351
  Serial.begin(57600);
  
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_8PF, 27000000,-19921 ); //init with 27 mhz XTO, cali laut programm -18021
  if(!i2c_found)
  {
    Serial.println("Device not found on I2C bus!");
  }
  si5351.set_phase(SI5351_CLK0, 0);
  si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_4MA); //5db Output

  // Set CLK0 to output 74.25 MHz
  si5351.set_freq(7425000000ULL, SI5351_CLK0);

  // Set CLK1 to output 175 MHz
  //si5351.set_ms_source(SI5351_CLK1, SI5351_PLLB);
  //si5351.set_freq_manual(17500000000ULL, 70000000000ULL, SI5351_CLK1);

  // Query a status update and wait a bit to let the Si5351 populate the
  // status flags correctly.

  si5351.update_status();
  delay(500);
 
}


void loop() {
 //noop
 /*
    for(int i = 0; i < 20 ; i++ )
    {
      unsigned long freq = 7425000000ULL + (10*i);
      si5351.set_freq(freq * SI5351_FREQ_MULT, SI5351_CLK0);
      //si5351.set_freq(freq, SI5351_CLK0);
      delay(200);
    }
    
  si5351.set_freq(7425000000ULL, SI5351_CLK0);
  */
  // Read the Status Register and print it every 10 seconds
  si5351.update_status();
  /*
  Serial.print("  SYS_INIT: ");
  Serial.print(si5351.dev_status.SYS_INIT);
  Serial.print("  LOL_A: ");
  Serial.print(si5351.dev_status.LOL_A);
  Serial.print("  LOL_B: ");
  Serial.print(si5351.dev_status.LOL_B);
  Serial.print("  LOS: ");
  Serial.print(si5351.dev_status.LOS);
  Serial.print("  REVID: ");
  Serial.println(si5351.dev_status.REVID);
  */
  delay(10000);




}
