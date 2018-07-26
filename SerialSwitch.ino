//serial switch for ptt. acting as bi stable relais triggered by serial interface
//2018-07-11, oe6rke

int inByte = 0;         // incoming serial byte
int pttPin = 2;         // pin5 , D2 as PTT Relais
int buggi = 0;       // 0 no debug out, 1 debug out
//ptt relais placed on D2


void setup() {
  // put your setup code here, to run once:
  pinMode(pttPin, OUTPUT);      // sets the digital pin as output for relais
  digitalWrite(pttPin, LOW);        // sets the pin to low = rx
  
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
      digitalWrite(pttPin, HIGH);        // sets the pin to low = tx
      if(buggi==1) Serial.println("PTT ON");
     }

     //ptt off: r or R; acsi 82, 114
     if(inByte == 82 || inByte == 114) {
      //fire TX Relais off
      digitalWrite(pttPin, LOW);        // sets the pin to low = rx
      if(buggi==1) Serial.println("PTT OFF");
     }

     //help state, char h, H, more or like debug state
     if(inByte == 72 || inByte == 104) {
      //returns state of ptt pin = PD2, pin2 = bit5 of PORTD
      Serial.println(bitRead(PORTD,2));      
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
      Serial.println("Serial 9k6 PTT Switch, OE6RKE, 2018-07-10, relais on D2");      
      Serial.println("r/R switches to rx=relais0, r/T switches to tx=relais1, h/H Pinstate D2, d/D triggers debug messages.");      
     }
     
   }
}

