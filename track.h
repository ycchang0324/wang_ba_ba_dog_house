// File        [track.h]
// Author     [Erik Kuo]
// Synopsis   [Code used for tracking]
// Functions  [MotorWriting, tracking]
// Modify     [2020/03/27 Erik Kuo]
/***************************************************************************/

#ifndef _TRACK_H_
#define _TRACK_H_

#include <SoftwareSerial.h>
#include <Wire.h>
int old_err = 0;
int P_err;
int I_err = 0;
int D_err = 0;
double Kd;
double Ki = 1;
double Ratio=0.97;//左輪弱化以平衡
  int L3D;
  int L2D;
  int C0D;
  int R3D;
  int R2D;



  int L3A;
  int L2A;
  int C0A;

  int R2A;
  int R3A;

/*int MotorR_I1 = 6;
int MotorR_I2 = 7;
int MotorL_I3 = 8;
int MotorL_I4 = 9;
int MotorR_PWMR = 5;
int MotorL_PWML = 10; */
// initialize the left wheel
void conversion(){
  L3A = analogRead(L3);
  L2A = analogRead(L2);
  C0A = analogRead(C0);
  R2A = analogRead(R2);
  R3A = analogRead(R3);

if(L3A > 70){
    L3D = 1;
  }
  else{
    L3D = 0;
  }
  
  if(L2A > 70){
    L2D = 1;
  }
  else{
    L2D= 0;
  }
  if(C0A > 70){
    C0D = 1;
  }
  else{
    C0D = 0;
  }

  if(R2A > 70){
    R2D = 1;
  }
  else{
    R2D = 0;
  }
  
  if(R3A > 70){
    R3D = 1;
  }
  else{
    R3D = 0;
  }
  
}
void rightForward()
{
  digitalWrite(MotorR_I1,LOW);
  digitalWrite(MotorR_I2,HIGH);
  //Serial.println("Right forward");
}

void leftForward()
{
  digitalWrite(MotorL_I3,LOW);
  digitalWrite(MotorL_I4,HIGH);
  //Serial.println("Left forward");
}

void rightBackward()
{
  digitalWrite(MotorR_I1,HIGH);
  digitalWrite(MotorR_I2,LOW);
  //Serial.println("Right backward");
}

void leftBackward()
{
  digitalWrite(MotorL_I3,HIGH);
  digitalWrite(MotorL_I4,LOW);
  //Serial.println("Left backward");
}

void moveForward()
{
  analogWrite(MotorR_PWMR,78*0.98);
  analogWrite(MotorL_PWML,78);
  leftForward();
  rightForward();
}


void moveBackward()
{
  analogWrite(MotorR_PWMR,100);
  analogWrite(MotorL_PWML,98);
  leftBackward();
  rightBackward();
}

void turnLeftCenter()
{
  analogWrite(MotorR_PWMR,100);
  analogWrite(MotorL_PWML,120);
  leftBackward();
  rightForward();
}

void turnRightCenter()
{
  analogWrite(MotorR_PWMR,120);
  analogWrite(MotorL_PWML,100);
  leftForward();
  rightBackward();
}

void stopCar()
{
  analogWrite(MotorR_PWMR,0);
  analogWrite(MotorL_PWML,0);
  leftForward();
  rightForward();
}
/*if you have no idea how to start*/
/*check out what you have learned from week 1 & 6*/
/*feel free to add your own function for convenience*/

/*===========================import variable===========================*/
int extern _Tp;
/*===========================import variable===========================*/

// Write the voltage to motor.

void MotorWriting(double vL, double vR) {
  // TODO: use L298N to control motor voltage & direction

 /* if(error==666) //check if encounter node
    {
      stopCar;
      //TODO:read RFID
    
    }*/
    
    if( vR >= 0 )
        rightForward();
    else
    {
        rightBackward();
        vR = -vR;
    }

    if( vL >= 0 )
        leftForward();
    else
    {
        leftBackward();
        vL = -vL;
    }


  if(vR > 255)
    {
    vR = 255;
    }
  if(vL > 255)
    {
    vL = 255;
    }

  //Serial.print("vRAdj: ");
  //Serial.println(vRAdj);
  //Serial.print("vLAdj: ");
  //Serial.println(vLAdj);

  analogWrite(MotorR_PWMR,vR);
  analogWrite(MotorL_PWML, vL);

  //delay(2000);

}

// compute the error
int error(){



  #ifdef DEBUG
  Serial.print("L3A: ");
  Serial.println(L3A);
   Serial.print("L2A: ");
  Serial.println(L2A);
   Serial.print("C0A: ");
  Serial.println(C0A);
   Serial.print("R2A: ");
  Serial.println(R2A);
   Serial.print("R3A: ");
  Serial.println(R3A);
  
  
  #endif

  conversion();
  //int counter = L3D + L2D + C0D + R2D + R3D;
  P_err = L3D * (-2) + L2D * (-1) + R2D * 1 + R3D * 2;
  //I_err = I_err + P_err;
  D_err = P_err - old_err;

  old_err = P_err;
  Kd = P_err/4;
  //double power = Kp*P_err + Ki*I_err + Kd*D_err;
  double power = _Tp*P_err + Kd*D_err;

  return power;
  /*
  if( counter == 0 )
  {
    return 0;
  }
  else
    return sum / counter;
  */
}// MotorWriting

// P/PID control Trackingbj
void tracking(){
  //TODO: complete your P/PID tracking code
    
    int vRAdj = 0;
    int vLAdj = 0;
    int vR=75;
    int vL=75*Ratio;
    int Error=error()*0.80;

    vRAdj = vR - Error;
    vLAdj = vL + Error;
    #ifdef DEBUG
    Serial.print("left speed: ");
    Serial.println(vLAdj);
    Serial.print("right speed: ");
    Serial.println(vRAdj);
    #endif
    MotorWriting(vLAdj,vRAdj);
    
}// tracking
bool checknode(){
conversion();
  #ifdef DEBUG
  delay(1000);
    //Serial.print(L3D+L2D+L1D+R3D+R2D+R1D);
    Serial.print("L3D: ");
    Serial.println(L3D);
    Serial.print("L2D: ");
    Serial.println(L2D);
    Serial.print("R3D: ");
    Serial.println(R3D);
    Serial.print("R2D: ");
    Serial.println(R2D);
    Serial.print("C0D: ");
    Serial.println(C0D);
    
    #endif
  if((L3D+L2D+C0D+R3D+R2D)>=3)
    return true;

  else 
    return false;
}

bool findlineyet(char c){
conversion();
if(c=='R'){
  if((R3D+R2D)>=1)
    return false;
  else 
    return true;
}
if(c=='L'){
  if((L3D+L2D)>=1)
    return false;
  else 
    return true;
}
}
bool findlineyet(){
conversion();

  if((L3D+L2D+R3D+R2D+C0D)>=1)
    return false;
  else 
    return true;
}
#endif
