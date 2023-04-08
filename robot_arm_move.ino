#include <HCPCA9685.h>
#define I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd); 
String str = "";
int angle[5];//order angle
int nangle[5];//now angle

void arm_mv(int num,int nang,int pang)//mapping and move with 1 degree !!nang=new angle(order angle),  pang=past angle(robot arm's now angle)!! 
                                      //**int pang->nangle[num], int nang->angle[num]**
{
  if(pang-nang<0){
    pang++;
  }
  else if(pang-nang>0){
    pang--;
  }
  else{}
  int mang=map(pang,0,180,0,420);
  HCPCA9685.Servo(num,mang);
  nangle[num]=pang;
  delay(30);//speed level
}

int check(int now[5],int goal[5])
{
  int ch=0;
  for(int i=0;i<5;i++)
  {
    ch=ch+goal[i]-now[i];
  }
  if(ch==0)
  {
    return 1;
  }
}



void angle_Set(String nstr)//get angle order from pyhton and save in angle[4]-> when this method activate arr angle is changed
{
  //val = str.substring(0, ).toInt();
  //Serial.println(val);
  int index1 = nstr.indexOf(' ');
  int index2 = nstr.indexOf(' ',index1+1);
  int index3 = nstr.indexOf(' ',index2+1);
  int index4 = nstr.indexOf(' ',index3+1);

  angle[0] = nstr.substring(0, index1).toInt();
  angle[1] = nstr.substring(index1+1, index2).toInt();
  angle[2] = nstr.substring(index2+1, index3).toInt();
  angle[3] = nstr.substring(index3+1, index4).toInt();
  angle[4] = nstr.substring(index4+1, (index4+1)*2).toInt();
}//plan to fix,


void setup() {
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  Serial.begin(9600);
  Serial.setTimeout(10);//addition code:if str reading error happen plus the timeout 50->100
  for(int k=0;k<5;k++){
    nangle[k]=0;
    angle[k]=0;
  }//clear the arr angle
}


void loop() {
  str = Serial.readString();
  if(check(nangle,angle))
  {
    if(str != ""){
      angle_Set(str);
    }
  }
  arm_mv(0,angle[0],nangle[0]);
  arm_mv(1,angle[1],nangle[1]);
  arm_mv(2,angle[2],nangle[2]);
  arm_mv(3,angle[3],nangle[3]);
  arm_mv(4,angle[4],nangle[4]);
  Serial.print(nangle[0]);
  Serial.print(nangle[1]);
  Serial.print(nangle[2]);
  Serial.print(nangle[3]);
  Serial.println(nangle[4]);//move order update and stall
  
}
