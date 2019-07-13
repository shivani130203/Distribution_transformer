
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#define S0 D0
#define S1 D1
#define S2 D2
#define S3 D3
#define sensorOut D4

Adafruit_BMP085 bmp;
#define I2C_SCL 12
#define I2C_SDA 13
const int trigPin =D5;
const int echoPin= D8;
long duration;
int distance;
int frequency = 0;
int blue,green,red;
void sendSensor()
{

  if (!bmp.begin()) 
  {
           Serial.println("Could not find a valid BMP085 sensor, check wiring!");
              while (1) {}
        }

float bp = ( bmp.readPressure()/100)*0.001;
//float ba =  bmp.readAltitude();
//float bt =  bmp.readTemperature();
//float dst = bmp.readSealevelPressure()/100;
Serial.print(bp);//Serial.println(ba);Serial.println(bt);
Serial.println("bar");
}
  
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
   
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

 
  Wire.begin(I2C_SDA, I2C_SCL);
  delay(10);
  
  Serial.begin(9600);
}
void loop() {


  
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
delay(200);
  sendSensor();
  delay(200);
  
  // Setting red filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  red=frequency;
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  //frequency = map(frequency, 20,120,255,0);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  green=frequency;
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  //frequency = map(frequency, 100,300,255,0);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  blue=frequency;
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  //frequency = map(frequency, 80,260,255,0);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(100);
  Serial.println(" ");
  if (blue<red && blue<green)
  Serial.println("blue");
  else
  Serial.println("pink");
  delay(100);
 

}
