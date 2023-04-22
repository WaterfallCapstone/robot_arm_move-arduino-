#include <HCPCA9685.h>
#define I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd); 
String str = "";
int angle[6];//order angle
int nangle[6];//now angle

void angle_Set(String nstr)//get angle order from pyhton and save in angle[4]-> when this method activate arr angle is changed
{
  //val = str.substring(0, ).toInt();
  //Serial.println(val);
  int index1 = nstr.indexOf(' ');
  int index2 = nstr.indexOf(' ',index1+1);
  int index3 = nstr.indexOf(' ',index2+1);
  int index4 = nstr.indexOf(' ',index3+1);
  int index5 = nstr.indexOf(' ',index4+1);
  int index6 = nstr.indexOf(' ',index5+1);

  angle[0] = nstr.substring(0, index1).toInt();
  angle[1] = nstr.substring(index1+1, index2).toInt();
  angle[2] = nstr.substring(index2+1, index3).toInt();
  angle[3] = nstr.substring(index3+1, index4).toInt();
  angle[4] = nstr.substring(index4+1, index5).toInt();
  angle[5] = nstr.substring(index5+1, (index5+1)*2).toInt();
  
  for(int i=0;i<6;i++)
  {
    angle[i]=map(angle[i],0,180,0,420);
  }
}//plan to fix,


void setup() {
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  Serial.begin(9600);
  //addition code:if str reading error happen plus the timeout 50->100
  for(int k=0;k<6;k++){
    nangle[k]=90;
    angle[k]=90;
  }//clear the arr angle
}


void loop() {
  if(Serial.available())
  {
    str = Serial.readString();
    angle_Set(str);
    HCPCA9685.Servo(0,angle[0]);
    HCPCA9685.Servo(1,angle[1]);
    HCPCA9685.Servo(2,angle[2]);
    HCPCA9685.Servo(3,angle[3]);
    HCPCA9685.Servo(4,angle[4]);
    HCPCA9685.Servo(5,angle[5]);
  }
}
