/***************************************************************************/
// File        [node.h]
// Author     [Erik Kuo, Joshua Lin]
// Synopsis   [Code for managing car movement when encounter a node]
// Functions  [/* add on yout own! */]
// Modify     [2020/03/027 Erik Kuo]
/***************************************************************************/
//#include "final_project"
#include <SoftwareSerial.h>
#include <Wire.h>
#include "track.h"
#include "mp3.h"

/*===========================import variable===========================*/
int extern r1, l1, r2, l2, r3, l3;
int extern _Tp;
int extern  tin1;
int extern  tin2;
int extern  tin3;
int extern  uin;
void extern SetState();
/*===========================import variable===========================*/
// TODO: add some function to control your car when encounter a node

void makeaturn (char command[100]){

  unsigned static int counter = 0;
  # ifdef DEBUG
  Serial.println("makeaturn");
  .
  Serial.print("command[ ");
  Serial.print(counter);
  Serial.print(" ]: ");
  Serial.println(command[counter]);
  
 
  Serial.print("counter: ");
  Serial.println(counter);

  #endif
  
if(command[counter]=='a')//往前
{
  counter++;
  //mp3Play(7);
  //Serial.print("counter0");

  moveForward();
  delay(200);

       while(findlineyet()){
        static int N=4;
    stopCar();
    delay(50);
    for(int i=0;i<N;i++)
    {
    turnRightCenter();
    delay(50);
    stopCar();
    delay(50);
    if(!findlineyet())
    break;
    }
    N+=4;
    if(!findlineyet())
    break;
    for(int j=0;j<N;j++)
    {
    turnLeftCenter();
    delay(50);
    stopCar();
    delay(50);
    if(!findlineyet())
    break;
    }
    N+=4;
  }
 
}
else if(command[counter]=='u')//迴轉
{
  counter++;
  //mp3Play(5);
  turnRightCenter();
  delay(uin);
  stopCar();
  delay(100);
  turnRightCenter();
  delay(uin);
    stopCar();
  delay(100); 
   while(findlineyet()){
    stopCar();
    delay(40);
    turnRightCenter();
    delay(40);
}
}
else if(command[counter]=='r')// 右轉
{
  counter++;
  #ifdef DEBUG
  Serial.println("right eight");
  #endif

 
   turnRightCenter();
    delay(tin1);
    
    
    stopCar();
    delay(100);
    
    turnRightCenter();
    delay(tin2);
    
    
    stopCar();
    delay(100);
    if(!findlineyet()){
    
    return;
    }
    
    turnRightCenter();
    delay(tin3);
    
    stopCar();
    delay(100);
    
    while(findlineyet()){
    stopCar();
    delay(40);
    turnRightCenter();
    delay(40);
  }
}
else if(command[counter]=='l')//左轉
{
  counter++;
  //mp3Play(6);
    turnLeftCenter();
    delay(tin1);
   
    
    stopCar();
    delay(100);
    
    turnLeftCenter();
    delay(tin2);
    
    
    stopCar();
    delay(100);
    if(!findlineyet()){
    
    return;
    }
   
    turnLeftCenter();
    delay(tin3);
    
    stopCar();
    delay(100);
    
    while(findlineyet()){
    stopCar();
    delay(40);
    turnLeftCenter();
    delay(40); 
  }
}
else if(command[counter]=='x')//送達
{
  counter++;
  stopCar();
  delay(3000);
  command[counter];
  
}
else if(command[counter]=='y')//回去
{
SetState();
counter++;}

else {
;

}

#ifdef DEBUG
Serial.print("command[ ");
Serial.print(counter);
Serial.print(" ]: ");
Serial.println(command[counter]);

#endif
/*else if(command[i]==NULL);
{
  stopCar();
  exit;
}*/

if(counter==499)
{  stopCar();
  delay(10000);}
}
// here are something you can try: left_turn, right_turn... etc.
