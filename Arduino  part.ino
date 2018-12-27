#include <DHT.h>


// Auxiliar variables to store the current output state
float humidity_ = 0.0;  
float temperature_ = 0.0; 
String cmd;

// Assign output variables to GPIO pins
const int PIN_LIGHT_TOW =  5;
const int PIN_LIGHT_ONE =  4;
const int PIN_HEATER = 7;
const int PIN_DHT22 = 8;


#define DHTTYPE DHT22
DHT dht(PIN_DHT22, DHT22); 

void setup() {
  Serial1.begin(115200);
  // Initialize the output variables as outputs
  pinMode(PIN_LIGHT_TOW, OUTPUT);
  pinMode(PIN_LIGHT_ONE, OUTPUT);
  pinMode(PIN_HEATER, OUTPUT);
 
 
  // Set outputs to LOW
  digitalWrite(PIN_LIGHT_TOW, LOW);
  digitalWrite(PIN_LIGHT_ONE, LOW);
  digitalWrite(PIN_HEATER, LOW);
    
  dht.begin();  
}

void loop(){
  humidity_ = dht.readHumidity();
  temperature_ = dht.readTemperature();
  String request_ = (String) humidity_+"b"+(String) temperature_  ;
 
 if(Serial1.available()){
  cmd = Serial1.readStringUntil('\n');
  switch(cmd.toInt()){
     //Light one is OFF.
    case 10:
    digitalWrite(PIN_LIGHT_ONE,LOW);
    break;
    
    //Light one is ON.
    case 11:
    digitalWrite(PIN_LIGHT_ONE,HIGH);
    break;

    //Light tow is OFF.
    case 20:
    digitalWrite(PIN_LIGHT_TOW,LOW);
    break;
    
    //Light tow is ON.
    case 21:
    digitalWrite(PIN_LIGHT_TOW,HIGH);
    break;
    
    //Heater is OFF.
    case 30:
    digitalWrite(PIN_HEATER,LOW);
    break;
    
    //Heater is ON.
    case 31:
    digitalWrite(PIN_HEATER,HIGH);
    break;

  }
 }
 
 // clear all data in the port.
 Serial1.flush();
 
 //Send Data to Web page 
 if (request_ != ""){
 Serial1.println(request_);
 request_ ="";
 }
 
}
