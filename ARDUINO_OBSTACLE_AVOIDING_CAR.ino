#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN 10
#define ECHO_PIN 13
#define MAX_DISTANCE 200
#define MAX_SPEED 255// sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

int rcv = 0;
int flg = 3;
int at = 0;

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
Servo myservo;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

void setup() {

  myservo.attach(10);
  myservo.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  Serial.println("oook");
  if (Serial.available() > 0)
  {
    rcv = Serial.read();
    Serial.print(rcv);
    if (rcv == 'a')
    {
      Serial.println("AUTO");
      auto_drive();
    }
    else if (rcv == 'n')
    {
      Serial.println("Manu");
      manual();
    }
    else
    {
      Serial.print("Manu");
      manual();
    }
  }


  
}
void manual()
  {
    if (Serial.available() > 0)
    {
      rcv = Serial.read();

    }
    if (rcv == '2')
    {

      moveForward();
    }
    if (rcv == '8')
    {
      moveBackward();
    }
    if (rcv == '4')
    {
      turnLeft();
    }
    if (rcv == '6')
    {
      turnRight();
    }
    if (rcv == '0')
    {
      moveStop();
    }
    delay(100);
  }
  void auto_drive()
  {
    int distanceR = 0;
    int distanceL =  0;
    delay(40);

    if (distance <= 15)
    {
      moveStop();
      delay(100);
      moveBackward();
      delay(300);
      moveStop();
      delay(200);
      distanceR = lookRight();
      delay(200);
      distanceL = lookLeft();
      delay(200);

      if (distanceR >= distanceL)
      {
        turnRight();
        moveStop();
      } else
      {
        turnLeft();
        moveStop();
      }
    } else
    {
      moveForward();
    }
    distance = readPing();
  }


  int lookRight()
  {
    myservo.write(50);
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115);
    return distance;
  }

  int lookLeft()
  {
    myservo.write(170);
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115);
    return distance;
    delay(100);
  }

  int readPing() {
    delay(70);
    int cm = sonar.ping_cm();
    if (cm == 0)
    {
      cm = 250;
    }
    return cm;
  }

  void moveStop() {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }

  void moveForward() {

    if (!goesForward)
    {
      goesForward = true;
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
      {
        motor1.setSpeed(speedSet);
        motor2.setSpeed(speedSet);
        delay(5);
      }
    }
  }

  void moveBackward() {
    goesForward = false;
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);

    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
    {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);

      delay(5);
    }
  }

  int turnRight() {
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    delay(2000);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }

  int turnLeft() {
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    delay(2000);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }
