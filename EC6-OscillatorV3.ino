/*******************************************************************************
 * Copyright (c) 2018 Robert Kiendl, OE6RKE
 *
 *  A4 Si5351 SDA
 *  A5 Si5351 SCL
 *  RX is digital pin 10 (connect to TX of other device) for second serial of gps
 *
 * si5351a + nano + txco 27.00 (ppm2.5) ->
 * https://github.com/etherkit/Si5351Arduino
 * Modul hier https://www.sv1afn.com/si5351a.html,
 * http://ak2b.blogspot.com/2015/01/installing-libraries-and-running-code.html
 * http://www.knology.net/~gmarcus/
 * https://www.arduino.cc/en/Tutorial/SoftwareSerialExample
 *******************************************************************************/
#include "si5351.h"
#include "Wire.h"
#include <SoftwareSerial.h>

//my master working object
Si5351 si5351;

//Softserial Definition https://www.arduino.cc/en/Tutorial/SoftwareSerialExample
//D12 RX Softserial
//D06 TX Softserial  not needed but defined
SoftwareSerial mySerial(12, 5); // RX (D12)

unsigned long XtalFreq=27000000;

void setup() {

  bool i2c_found;

  // Start serial and initialize the Si5351
  Serial.begin(57600);
  
  mySerial.begin(19200); //set virtual port D9 RX for EC6 control

  XtalFreq = XtalFreq - 12; //offset calibration
  
  i2c_found = si5351.init(SI5351_CRYSTAL_LOAD_8PF, XtalFreq, 0 ); //init with 27 mhz XTO, cali presque le programm -18021
  if(!i2c_found)
  {
    Serial.println("Device not found on I2C bus!");
  }
  /*
  //Set CLK0 to 2.5 MHz, PLLA selected as default
  si5351.set_ms_source(SI5351_CLK0, SI5351_PLLA); //activate the left output line
  si5351.set_phase(SI5351_CLK0, 0);
  si5351.drive_strength(SI5351_CLK0, SI5351_DRIVE_4MA); //5db Output
  // Set CLK0 to 2.5 MHz
  si5351.set_freq(250000000ULL, SI5351_CLK0);
  */

  //set CLK1 to EC6 XTAL QRG
  si5351.set_ms_source(SI5351_CLK1, SI5351_PLLB); //activate the middle output line
  si5351.set_phase(SI5351_CLK1, 0);
  si5351.drive_strength(SI5351_CLK1, SI5351_DRIVE_4MA); //5db Output
  // Set CLK0 to 74.250 MHz - EC6 XTAL
  si5351.set_freq(7425000000ULL, SI5351_CLK1);

  // Query a status update and wait a bit to let the Si5351 populate the
  // status flags correctly.

  si5351.update_status();
  delay(500);
 
}




void loop() {
  /*  
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
  
  Serial.println(XtalFreq);
  
  delay(10000);

  */
  
  //copy data from virtual Serial - DEBUG pour foutu gens comme moi ;)
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  

}
