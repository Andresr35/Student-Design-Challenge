#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Arduino.h>

RF24 radio(9,A0);// CE, CSN

int speedPin = 10;
int mSpeed= 220;

struct Data_Package {// we can send up to 32 bytes
  byte j1PotX;
  byte j1PotY;

};

Data_Package data;
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);

 pinMode(speedPin, OUTPUT);
  pinMode(11, OUTPUT);


  radio.begin();//starting the radio
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  // needed only once for printing details
  // (smaller) function that prints raw register values
 
  // put your setup code here, to run once:
}
void resetData() {
  // Reset the values when there is no radio connection - Set initial default values
  data.j1PotX = 0;
  data.j1PotY = 0;

}
void loop() {
  if (radio.available()) {
    Serial.println("radio Avaiable");
    radio.read(&data, sizeof(Data_Package));
    
    Serial.println("start");
    Serial.println(data.j1PotY);
    Serial.println(data.j1PotX);
    Serial.println("end");
    
  } else {
    Serial.println("not availabe");
    Serial.println(data.j1PotY);
    Serial.println(data.j1PotX);
    resetData();
  }
  
 analogWrite(speedPin,250);
 analogWrite(11,250);
 
  
 
  // put your main code here, to run repeatedly:
}
