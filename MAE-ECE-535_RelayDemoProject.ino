// Nolan Canegallo
// MAE/ECE 535 Relay Demo Project
// Due 26 June 2023

#include "IRremote.hpp"

/*-----( Global Constants )-----*/
const int receiver = 11;      // Signal Pin of IR receiver to Arduino Digital Pin 11
const int demoRelay = 12;     // Signal Pin to send voltage to demo relay
const int openRelay = 13;     // Signal Pin to send voltage to open relay

/*-----( Variables )-----*/
bool demoOn = false;        // Variable to store state of demo relay
bool openOn = false;        // Variable to store state of open relay
bool playin = false;        // Variable to keep track of playing state
int t = 60;

/*-----( Function )-----*/
void translateIR() {          // takes action based on IR code received
// describing Remote IR codes 

  switch(IrReceiver.decodedIRData.decodedRawData){
    case 0xBA45FF00: //0xD52AFF: //0xFFA25D: 
      //Serial.println("POWER");
      if (demoOn){
        // Turn demo relay off
        digitalWrite(demoRelay, LOW);
        demoOn = false;
      }
      else{
        // Turn demo relay on
        digitalWrite(demoRelay, HIGH);
        demoOn = true;
      }
      break;
    case 0xB847FF00:
      //Serial.println("FUNC/STOP");
      if (openOn){
        // Turn open relay off
        digitalWrite(openRelay, LOW);
        openOn = false;
      }
      else{
        // Turn demo relay on
        digitalWrite(openRelay, HIGH);
        openOn = true;
      } 
      break;
    case 0xB946FF00: 
      //Serial.println("VOL+"); 
      break;
    case 0xBB44FF00: 
      //Serial.println("FAST BACK");  
      if (t > 40){
        t = t - 10;  
      }
      break;
    case 0xBF40FF00: 
      //Serial.println("PAUSE");
      //MAE/ECE
      dah(); eh(); dah(); en(); dih(); eh(); dah(); en(); dih(); en(); 
      dah(); eh(); dih(); eh(); dih(); eh(); dah(); eh(); dih(); en();
      dih(); en(); dah(); eh(); dih(); eh(); dah(); eh(); dih(); en(); dih(); em();
      //535
      dih(); eh(); dih(); eh(); dih(); eh(); dih(); eh(); dih(); en();
      dih(); eh(); dih(); eh(); dih(); eh(); dah(); eh(); dah(); en();
      dih(); eh(); dih(); eh(); dih(); eh(); dih(); eh(); dih(); em();
      //RELAY
      dih(); eh(); dah(); eh(); dih(); en(); dih(); en(); dih(); eh(); dah(); eh(); dih(); eh(); dih(); en(); 
      dih(); eh(); dah(); en(); dah(); eh(); dih(); eh(); dah(); eh(); dah(); em();
      //DEMO
      dah(); eh(); dih(); eh(); dih(); en(); dih(); en(); dah(); eh(); dah(); en(); dah(); eh(); dah(); eh(); dah(); em();
      //PRO
      dih(); eh(); dah(); eh(); dah(); eh(); dih(); en(); dih(); eh(); dah(); eh(); dih(); en(); dah(); eh(); dah(); eh(); dah(); en();
      //JE
      dih(); eh(); dah(); eh(); dah(); eh(); dah(); en(); dih(); en();
      //CT
      dah(); eh(); dih(); eh(); dah(); eh(); dih(); en(); dah(); em();

      break;
    case 0xBC43FF00: 
      //Serial.println("FAST FORWARD");
      if (t < 80){
        t = t + 10;   
      }
      break;
    case 0xF807FF00: 
      //Serial.println("DOWN"); 
      // SOS
      dih(); eh(); dih(); eh(); dih(); en();
      dah(); eh(); dah(); eh(); dah(); en();
      dih(); eh(); dih(); eh(); dih(); en();   
      break;
    case 0xEA15FF00: 
      //Serial.println("VOL-");    
      break;
    case 0xF609FF00: 
      //Serial.println("UP");    
      // HELLO!
      dih(); eh(); dih(); eh(); dih(); eh(); dih(); en();
      dih(); en();
      dih(); eh(); dah(); eh(); dih(); eh(); dih(); en();
      dih(); eh(); dah(); eh(); dih(); eh(); dih(); en();
      dah(); eh(); dah(); eh(); dah(); en();
      dah(); eh(); dih(); eh(); dah(); eh(); dih(); eh(); dah; eh(); dah(); em();
      break;
    case 0xE619FF00: 
      //Serial.println("EQ");    
      break;
    case 0xF20DFF00: 
      //Serial.println("ST/REPT");    
      break;
    case 0xE916FF00: 
      //Serial.println("0"); 
      dah(); eh(); dah(); eh(); dah(); eh(); dah(); eh(); dah(); en();   
      break;
    case 0xF30CFF00: 
      //Serial.println("1"); 
      dih(); eh(); dah(); eh(); dah(); eh(); dah(); eh(); dah(); en();           
      break;
    case 0xE718FF00: 
      //Serial.println("2");    
      dih(); eh(); dih(); eh(); dah(); eh(); dah(); eh(); dah(); en();        
      break;
    case 0xA15EFF00: 
      //Serial.println("3"); 
      dih(); eh(); dih(); eh(); dih(); eh(); dah(); eh(); dah(); en();        
      break;
    case 0xF708FF00: 
      //Serial.println("4"); 
      dih(); eh(); dih(); eh(); dih(); eh(); dih(); eh(); dah(); en();        
      break;
    case 0xE31CFF00: 
      //Serial.println("5");
      dih(); eh(); dih(); eh(); dih(); eh(); dih(); eh(); dih(); en();      
      break;
    case 0xA55AFF00:
      //Serial.println("6");  
      dah(); eh(); dih(); eh(); dih(); eh(); dih(); eh(); dih(); en();   
      break;
    case 0xBD42FF00:
      //Serial.println("7"); 
      dah(); eh(); dah(); eh(); dih(); eh(); dih(); eh(); dih(); en();  
      break;
    case 0xAD52FF00:
      //Serial.println("8");    
      dah(); eh(); dah(); eh(); dah(); eh(); dih(); eh(); dih(); en();  
      break;
    case 0xB54AFF00: 
      //Serial.println("9"); 
      dah(); eh(); dah(); eh(); dah(); eh(); dah(); eh(); dih(); en();  
      break;

  default: 
    //Serial.print(" other button   ");
    //Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    break;
    
  }// End Case

} //END translateIR

void dih(){
  digitalWrite(demoRelay, HIGH);
  delay(t);
  digitalWrite(demoRelay, LOW);
}

void dah(){
  digitalWrite(demoRelay, HIGH);
  delay(3*t);
  digitalWrite(demoRelay, LOW);
}

void eh(){
  delay(t);
}

void en(){
  delay(3*t);
}


void em(){
  delay(7*t);
}

void setup(){   /*----( SETUP: RUNS ONCE )----*/
  pinMode(receiver, INPUT);
  pinMode(demoRelay, OUTPUT);
  pinMode(openRelay, OUTPUT);
  //Serial.begin(9600);
  //Serial.println("IR Receiver Button Decode"); 
  IrReceiver.begin(receiver, DISABLE_LED_FEEDBACK);           // Start the receiver

}/*--(end setup )---*/

void loop(){   /*----( LOOP: RUNS CONSTANTLY )----*/
  if (IrReceiver.decode())   // have we received an IR signal?
  {
    translateIR(); 
    if (IrReceiver.decodedIRData.decodedRawData != 0xBF40FF00){
      delay(500);                 // Do not get immediate repeat
    }
    IrReceiver.resume();            // receive the next value
  }  
}/* --(end main loop )-- */
