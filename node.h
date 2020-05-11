/***************************************************************************/
// File			  [node.h]
// Author		  [Erik Kuo, Joshua Lin]
// Synopsis		[Code for managing car movement when encounter a node]
// Functions  [/* add on yout own! */]
// Modify		  [2020/03/027 Erik Kuo]
/***************************************************************************/

#include <SoftwareSerial.h>
#include <Wire.h>
#include "track.h"

/*===========================import variable===========================*/
int extern r1, l1, r2, l2, r3, l3;
int extern _Tp;
unsigned int extern counter;
/*===========================import variable===========================*/
// TODO: add some function to control your car when encounter a node
void makeaturn (char command[100] ){
  
  Serial.print("counter: ");
  Serial.println(counter);

if(command[counter]=='a')
{
  //Serial.print("counter0");
  moveForward();
  delay(200);
}
else if(command[counter]=='u')
{
  turnRightCenter();
  delay(790);
}
else if(command[counter]=='r')
{
   turnRightCenter();
  delay(500);
}
else if(command[counter]=='l')
{
  turnLeftCenter();
   delay(500);
   
}
else{
  ;
}

Serial.print("command[ ");
Serial.print(counter);
Serial.print(" ]: ");
Serial.println(command[counter]);

/*else if(command[i]==NULL);
{
  stopCar();
  exit;
}*/
if(counter<99)
  counter++;
if(counter==99)
  stopCar();
}
// here are something you can try: left_turn, right_turn... etc.
