#include<Servo.h>
#include<Wire.h>

Servo gripper;
Servo arm;


int ADXL345 = 0x53; //I2C address of accelerometer. Think of it as the ECS practical to set addres for keypad etc.
int angle;
//DO NOT CHANGE CALLIBRATION VALUES
int const min_flex_val= 900;//analog input value for straight sensor
int const max_flex_val= 980;

void setup() {
  //Initialize 
  Serial.begin(9600);
  Wire.begin(ADXL345);
  Wire.beginTransmission(ADXL345);//initialize  comm
  Wire.write(0x2D);//rate bit to enable power cntrl(read/write). Basically ecs. pretty ez stuff
  Wire.write(8);//just enabling measurement(bit 3) bit in 0x2D or in other words, the read/write instruction abv.
  Wire.endTransmission();
  //i'll send table if im not lazy

  //pin attach
  gripper.attach(5); //5 is pwm
  arm.attach(10);

  //pin assignment role
  pinMode(A0,INPUT); //set pinmode to read in analog data 0 to 1024 or 10 bits

  //Note no pin attachment needed to declare/initialize for acc because i am connectiong to scl and sda 

}

void loop() {
  
  float x = analogRead(A0);
  float y = ((x-min_flex_val)/(max_flex_val - min_flex_val)); //basicaly a y axis. See the conversion in a graph format
  angle = ((y*180));//convert in terms of angle
  Serial.println(angle);
  gripper.write(angle);

}
void checkzaxis(){
  Wire.beginTransmission(ADXL345);
}
