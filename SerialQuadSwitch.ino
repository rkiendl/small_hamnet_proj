//serial switch for ptt. acting as bi stable relais triggered by serial interface
//uses conrad quad relais card
//2018-07-12, oe6rke

int inByte = 0;         // incoming serial byte
int buggi = 0;       // 0 no debug out, 1 debug out
//relais 1, D2, CO = 12V, RX Preamp on
//relais 2, D3, CO = 12V, TX PA on
//relais 3, D4, CO = 0V, RX HF relais gegen low (1)
//relais 4, D5, CO = 0V, TX HF relais gegen low (2)


void setup() {
  // init output pins for card
  pinMode(2, OUTPUT);   //D2
  digitalWrite(2, HIGH); // preamp default auf on  
  pinMode(3, OUTPUT);   //D3 
  digitalWrite(3, LOW);  // pa
  pinMode(4, OUTPUT);   //D4 
  digitalWrite(4, LOW);  //rx state birelais
  pinMode(5, OUTPUT);   //D5    
  digitalWrite(5, LOW);  //tx state birelais
  
  //sets rx relais to correct position
  digitalWrite(4, HIGH);
  delay(250); //wait 250ms
  digitalWrite(4, LOW);
  
  // start serial port at 9600 bps and wait for port to open:
   Serial.begin(9600);
   while (!Serial) {
       ; // wait for serial port to connect. Needed for native USB port only
   }
}

void loop() {
  // if we get a valid byte, read analog ins:
   if (Serial.available() > 0) { //we have data
     // get incoming byte:
     inByte = Serial.read();
     
     //ptt on: t or T; acsi 84, 116
     if(inByte == 84 || inByte == 116) {
      //fire TX Relais on
      digitalWrite(2, LOW);  //Relais 1 off - preamp
      digitalWrite(3, HIGH); //Relais 2 on - pa

      //sets flipps bi state relais - tx side
      digitalWrite(5, HIGH);
      delay(250); //wait 250ms
      digitalWrite(5, LOW);
            
      if(buggi==1) Serial.println("PTT ON");
     }

     //ptt off: r or R; acsi 82, 114
     if(inByte == 82 || inByte == 114) {
      //fire TX Relais off
      digitalWrite(2, HIGH);  //Relais 1 off - preamp
      digitalWrite(3, LOW); //Relais 2 on - pa

      //sets flipps bi state relais - rx side
      digitalWrite(4, HIGH);
      delay(250); //wait 250ms
      digitalWrite(4, LOW);
      
      if(buggi==1) Serial.println("PTT OFF");
     }

     //help state, char h, H, more or like debug state
     if(inByte == 72 || inByte == 104) {
      //returns state of ptt pin = PD2, pin2 = bit5 of PORTD
      Serial.println(bitRead(PORTD,2));      
      Serial.println(bitRead(PORTD,3));
      Serial.println(bitRead(PORTD,4));
      Serial.println(bitRead(PORTD,5));
     }

     //debug state, char d, D, more or like debug state
     if(inByte == 68 || inByte == 100) {
      if(buggi == 0) {
         buggi = 1;
         Serial.println("debug on");
      }
      else if(buggi == 1) {
         buggi = 0;
         Serial.println("debug off");
      }      
     }

     //info ?
     if(inByte == 63 ) {
      Serial.println("Serial 9k6 PTT Switch, OE6RKE, 2018-07-11, quad relais");      
      Serial.println("r/R switches to rx=relais0, r/T switches to tx=relais1, h/H Pinstate D2, d/D triggers debug messages.");      
     }
     
   }
}


