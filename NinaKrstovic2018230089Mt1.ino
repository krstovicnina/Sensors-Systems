#include "TimerOne.h"
#include <OneWire.h> 
#include <DallasTemperature.h>

  #define temp_sensor 2
  OneWire oneWire(temp_sensor);
  DallasTemperature sensors(&oneWire);
  
  const int trigPin = 5; //for ultrasonic sensor 
  const int echoPin = 3;
  volatile unsigned long duration; 
  int distance;
  
  volatile float Temperature; //for temperature sensor

  unsigned int illumination; // for photosensor
  const int illuminationSensor = A0;

  int button1 = 4;
  int button2 = 7;
  int button1NumberOfPushes = 0; 
  int button2NumberOfPushes = 0;   
  int button1BeginningState = LOW;          
  int button2BeginningState = LOW;        
  int button1EndingState = LOW;      
  int button2EndingState = LOW;

  int interval = 5000; //5 seconds
  long timeOfLastIteration = 0.0;
  long timepassed;

   
  
void setup() {


  pinMode(trigPin, OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);

  pinMode(0,INPUT);
  pinMode(1,INPUT);
  
 pinMode(button1, INPUT);
 pinMode(button2, INPUT);

  
  sensors.begin(); 

}

void loop() {
 
  
    if((millis()%500 >= 0) && (millis()%500 <= 200)){ //modulo gives the ramainder of an integer division
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);  
        duration = pulseIn(echoPin, HIGH);
        distance= duration*0.034/2;   //calculating distance in centimeters
    
        sensors.requestTemperatures(); //using the DallasTemperature library
        Temperature = sensors.getTempCByIndex(0);
      
        illumination = analogRead(illuminationSensor);
    } 


   button1BeginningState = digitalRead(button1);
      //push the button1 to decrease time for one second
    if(button1BeginningState != button1EndingState){ 
      if(button1BeginningState == HIGH){
        button1NumberOfPushes++;
        Serial.println("on");
        Serial.print("The current number of times you have pushed the first button: ");
        Serial.println(button1NumberOfPushes);
        interval-=1000; // decrease interval for one second
      } else{
        Serial.println("off");
      }
      delay(500);     
    }
    button1EndingState = button1BeginningState;
    
   button2BeginningState = digitalRead(button2);
      //push the button2 to increase time for one second
    if(button2BeginningState != button2EndingState){
      if(button2BeginningState == HIGH){
        button2NumberOfPushes++;
        Serial.println("on");
        Serial.print("The current number of times you have pushed the second button: ");
        Serial.println(button2NumberOfPushes);
        interval+=1000;// increase interval for one second
      } else{
        Serial.println("off");
      }
      delay(50);  
    }
    button2EndingState = button2BeginningState;


    
    if(interval<1000){// to ensure that the interval is bounded on both sides 
      interval=1000;
      }
    if(interval>10000){
      interval=10000;
    }
    timepassed = millis(); //returns the number of milliseconds passed since the arduino board began running the current program

    if((timepassed-timeOfLastIteration)>=interval){
        timeOfLastIteration = timepassed;
        Serial.print("Distance measured in centimeters: ");
        Serial.print(distance);
        Serial.println();
        Serial.print("Temperature measured in Celsius: ");
        Serial.print(Temperature);
        Serial.println();
        Serial.print("Illuminance measured in lux: ");
        Serial.print(illumination);
        Serial.println();
        Serial.println();
        Serial.println();
    }
 // Serial.println(time);
  
}
