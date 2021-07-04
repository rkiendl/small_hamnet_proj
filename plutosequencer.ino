//pluto sequencer to control hf relais and hf amplifyer
int pinRelais1 = 2; //D2
int pinRelais2 = 3; //D3
int pinRelais3 = 4; //D4
int pinRelais4 = 5; //D5
int pinPTT = 7; //D7 as in

bool isPTTOn = false;
bool isPTTOff = false;
bool lastState = false;

void setup() {
  //init input
  pinMode(pinPTT, INPUT_PULLUP);
  
  // init outputs
  pinMode(pinRelais1, OUTPUT);
  pinMode(pinRelais2, OUTPUT);
  pinMode(pinRelais3, OUTPUT);
  pinMode(pinRelais4, OUTPUT);

  digitalWrite(pinRelais1, HIGH);
  digitalWrite(pinRelais2, HIGH);
  digitalWrite(pinRelais3, HIGH);
  digitalWrite(pinRelais4, HIGH);

  //bring relais defined state, set relay pin 1
  digitalWrite(pinRelais1, LOW);
  delay(200);
  digitalWrite(pinRelais1, HIGH);

  //init serial
  Serial.begin(9600);
  Serial.println("plutosequencer, V1.1,2021-07-04 v oe6rke\r\n");  
  Serial.println("start---"); 
  Serial.println("500ms entprellen\r\n");     
}

void loop() {
  // put your main code here, to run repeatedly:

  //valPTT = digitalRead(pinPTT);
  //Serial.println(valPTT);

  //0 am pin is pressed, 1 am pin is released
  if(digitalRead(pinPTT) == false) { //entprellen
    delay(500);
    
    if(digitalRead(pinPTT) == false) { //0 = pressed
      Serial.print("PTT ON\r\n");
      
      //PTT Off -> On
      if(isPTTOn == false) {
        Serial.print("Relais ON\r\n");
        
        digitalWrite(pinRelais2, LOW);
        delay(200);
        digitalWrite(pinRelais2, HIGH);
  
        //power via relay 3
        digitalWrite(pinRelais3, LOW);;        
        
        isPTTOn = true;
        isPTTOff = false;
      }
      lastState = true;
   
    }
  }
  else {
    lastState = false;
  }
  //PTT On -> Off
  if(isPTTOff == false && lastState == false) {  //entprellen
    delay(500);

    if(isPTTOff == false && lastState == false) {
      Serial.print("Relais OFF\r\n");
      
      digitalWrite(pinRelais1, LOW);
      delay(200);
      digitalWrite(pinRelais1, HIGH);
        
      //power via relay 3
      digitalWrite(pinRelais3, HIGH);
      
      isPTTOff = true;
      isPTTOn = false;
    }
  }
  
  //some delay
  delay(200);//delay to keep stuff smooth
}
