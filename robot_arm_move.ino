#include <HCPCA9685.h>
#define I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd); 
String str = "";
int angle[6] = {90, 90, 90, 90, 90, 90};

void angle_Set(String nstr)//get angle order from pyhton and save in angle[4]-> when this method activate arr angle is changed
{
  int temp = 0;
  int index = nstr.indexOf(' ');
  for(int i = 0; i < 6; i++){
    angle[i] = nstr.substring(temp, index).toInt();
    temp = index + 1;
    index = nstr.indexOf(' ', temp);
  }
  for(int i=0;i<6;i++){
    if(i==3||i==5) angle[i]=map(angle[i],0,180,400,0);
    else angle[i]=map(angle[i],0,180,0,400);
  }
}


void setup() {
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  Serial.begin(9600);
}


void loop() {
  if(Serial.available()){
    str = Serial.readString();
    angle_Set(str);
    for(int i = 0; i < 6; i++)HCPCA9685.Servo(i, angle[i]);
  }
}
