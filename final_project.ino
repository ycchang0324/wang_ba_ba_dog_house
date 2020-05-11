/***************************************************************************/
// File       [final_project.ino]
// Author     [Erik Kuo]
// Synopsis   [Code for managing main process]
// Functions  [setup, loop, Search_Mode, Hault_Mode, SetState]
// Modify     [2020/03/27 Erik Kuo]
/***************************************************************************/
/*
#define DEBUG // debug flag
*/
// for BlueTooth
#include<SoftwareSerial.h>
// for RFID
#include <SPI.h>
#include <MFRC522.h>
// Import header files




/*===========================define pin & create module object================================*/
// BlueTooth
SoftwareSerial BT(2,1);   // TX,RX on bluetooth module, 請按照自己車上的接線寫入腳位
// L298N, 請按照自己車上的接線寫入腳位(左右不一定要跟註解寫的一樣)
#define MotorR_I1      3 //定義 I1 接腳（右）
#define MotorR_I2      4 //定義 I2 接腳（右）
#define MotorL_I3      7 //定義 I3 接腳（左）
#define MotorL_I4      8 //定義 I4 接腳（左）
#define MotorL_PWML    6 //定義 ENA (PWM調速) 接腳
#define MotorR_PWMR    5  //定義 ENB (PWM調速) 接腳
// 循線模組, 請按照自己車上的接線寫入腳位
#define L1   A2  // Define Left Most Sensor Pin
#define L2   A1  // Define Left Middle Sensor Pin
#define L3   A0  // Define Middle Left Sensor Pin
#define R3   A5  // Define Middle Right Sensor Pin
#define R2   A4  // Define Right Middle Sensor Pin
#define R1   A3  // Define Right Most Sensor Pin
// RFID, 請按照自己車上的接線寫入腳位
#define RST_PIN     9         // 讀卡機的重置腳位
#define SS_PIN      10        // 晶片選擇腳位
MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件

/*===========================define pin & create module object===========================*/
#include "RFID.h"
#include "track.h"
#include "bluetooth.h"
#include "node.h"
/*===========================declare function prototypes===========================*/
// search graph
void Search_Mode();
// wait for command
void Hault_Mode();
void SetState();
byte idSize;
byte* prfid;
char* command;
unsigned int counter = 0;

/*===========================declare function prototypes===========================*/

/*===========================define function===========================*/
void setup()
{
   //bluetooth initialization
   BT.begin(9600);
   //Serial window
   Serial.begin(9600);
   //RFID initial
   SPI.begin();
   mfrc522.PCD_Init();
   //L298N pin
   pinMode(MotorR_I1,   OUTPUT);
   pinMode(MotorR_I2,   OUTPUT);
   pinMode(MotorL_I3,   OUTPUT);
   pinMode(MotorL_I4,   OUTPUT);
   pinMode(MotorL_PWML, OUTPUT);
   pinMode(MotorR_PWMR, OUTPUT);
   
   //tracking pin
   pinMode(R1, INPUT); 
   pinMode(R2, INPUT);
   pinMode(R3, INPUT);
   pinMode(L1, INPUT);
   pinMode(L2, INPUT);
   pinMode(L3, INPUT);
   
    SetState();
    
   
   
 
   
#ifdef DEBUG
  Serial.println("Start!");
#endif
  analogWrite(MotorR_PWMR,0);
  analogWrite(MotorL_PWML,0);
}// setup


// initalize parameter
// variables for 循線模組
int r2=0,r1=0,r3=0,l3=0,l1=0,l2=0;
// variable for motor power
int _Tp=30;
// enum for car states, 不懂得可以自己google C++ enum
enum ControlState
{
   HAULT_STATE,
   SEARCH_STATE,
};
ControlState _state=HAULT_STATE;
// enum for bluetooth message, reference in bluetooth.h line 2
BT_CMD _cmd = NOTHING;
const char test1 ={'w'};
const char test2 ={'u'};
const char test3 ={'d'};
const char test4 ={'a'};
const char test[100] ={'w','u','d','a','w','u','d','a'};


void loop()
{
   // search graph
   
    Search_Mode();
    if(int(rfid(idSize))!=0){
    Hault_Mode();
    prfid = rfid(idSize);
    send_byte(prfid,idSize);


      delay(2000);
      //Serial.print("counter: ");
      //Serial.print(counter);
     makeaturn(command);
    }
    
    
    
  /* if(_state == SEARCH_STATE) Search_Mode();
   // wait for command
   else if(_state == HAULT_STATE) Hault_Mode();
   SetState();
   */

  
   
  
/*   
makeaturn(test);
stopCar();
delay (3000);
makeaturn(test);
stopCar();
delay (3000);
makeaturn(test);
stopCar();
delay (3000);
makeaturn(test);
stopCar();
delay (3000);
makeaturn(test);
stopCar();
delay (3000);
makeaturn(test);
stopCar();
delay (3000);
makeaturn(test);
stopCar();
delay (3000);
makeaturn(test);
stopCar();
delay (3000);
*/

 /* moveForward();
  delay(500);
    turnRightCenter();
  delay(1000);
     turnRightCenter();
  delay(500);
    turnLeftCenter();
   delay(500);
     moveForward();
  delay(500);
    turnRightCenter();
  delay(1000);
     turnRightCenter();
  delay(500);
    turnLeftCenter();
   delay(500);*/
   //tracking();
   
   }// loop

void SetState()
{
  // TODO:
  // 1. Get command from bluetooth 
  // 2. Change state if need
   command = new char [100];
   for(int i = 0; i < 100; i++)
    command[ i ] = ' ';

   char judge = "";
   
   while(judge != 's')
   {
    judge = ask_BT_begin();
    
      
   }
   
   //Serial.println(judge); 
   //Serial.println("I'm here!");
   ask_BT(command);
}// SetState

void Hault_Mode()
{
  stopCar();

  // TODO: let your car stay still
}// Hault_Mode

void Search_Mode()
{
  makeaturn(command);
  // TODO: let your car search graph(maze) according to bluetooth command from computer(python code)
}// Search_Mode
/*===========================define function===========================*/
