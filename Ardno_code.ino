#include <AFMotor.h>
int x;
AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);
void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  m1.setSpeed(255);
  m2.setSpeed(255);
  m3.setSpeed(255);
  m4.setSpeed(255);
  delay(2000);

}
void go_f()
{
  m1.run(FORWARD);
  m2.run(FORWARD);
  m3.run(FORWARD);
  m4.run(FORWARD);
  delay(100);
}
void go_b()
{
  m1.run(BACKWARD);
  m2.run(BACKWARD);
  m3.run(BACKWARD);
  m4.run(BACKWARD);
  delay(100);
}
void go_l()
{
  m2.run(BACKWARD);
  m3.run(BACKWARD);
  m1.run(FORWARD);
  m4.run(FORWARD);
  delay(100);
}
void go_r()
{
  m1.run(BACKWARD);
  m4.run(BACKWARD);
  m2.run(FORWARD);
  m3.run(FORWARD);
  delay(100);
}
void go_s()
{
  m1.run(RELEASE);
  m2.run(RELEASE);
  m3.run(RELEASE);
  m4.run(RELEASE);
  delay(100);
}


void loop() {
  // put your main code here, to run repeatedly:
  
    
   if(Serial.available())
   { 
     x=Serial.read();
     Serial.println(x);
   }
   
      if(x==2)
      {
        Serial.println("ford");
        go_f();
        delay(5);
      }
      if(x==8)
      {
        go_b();
        delay(5);
      }
      if(x==4)
      {
        Serial.println("leeee");
        go_l();
        delay(5);
      }
      if(x==6)
      {
        go_r();
        delay(5);
      }
      if(x==0)
      {
        go_s();
        delay(5);
      }
   
   
}
