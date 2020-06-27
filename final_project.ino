/***************************************************************************/
// File       [final_project.ino]
// Author     [Erik Kuo]
// Synopsis   [Code for managing main process]
// Functions  [setup, loop, Search_Mode, Hault_Mode, SetState]
// Modify     [2020/03/27 Erik Kuo]
/***************************************************************************/

//#define DEBUG // debug flag
#define testCar
// for BlueTooth
#include<SoftwareSerial.h>
// for RFID
#include <SPI.h>
#include <MFRC522.h>
// Import header files




/*===========================define pin & create module object================================*/
//0520

// BlueTooth
SoftwareSerial BT(2,3);   // TX,RX on bluetooth module, 請按照自己車上的接線寫入腳位

SoftwareSerial mp3(10, 10); // RX, TX
// L298N, 請按照自己車上的接線寫入腳位(左右不一定要跟註解寫的一樣)
#define MotorR_I1      4 //定義 I1 接腳（右）
#define MotorR_I2      9 //定義 I2 接腳（右）
#define MotorL_I3      7 //定義 I3 接腳（左）
#define MotorL_I4      8 //定義 I4 接腳（左）
#define MotorL_PWML    6 //定義 ENB (PWM調速) 接腳
#define MotorR_PWMR    5  //定義 ENA (PWM調速) 接腳
#define fsr_pin A5



// 循線模組, 請按照自己車上的接線寫入腳位
#define C0   A2  // Define Left Most Sensor Pin
#define L2   A1  // Define Left Middle Sensor Pin
#define R3   A3  // Define Middle Right Sensor Pin
#define R2   A4  // Define Right Middle Sensor Pin
#define L3   A0  // Define Right Middle Sensor Pin

// RFID, 請按照自己車上的接線寫入腳位
#define RST_PIN     0         // 讀卡機的重置腳位
#define SS_PIN      10        // 晶片選擇腳位
MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件

/*===========================define pin & create module object===========================*/
#include "track.h"
#include "bluetooth.h"
#include "node.h"
#include "mp3.h"

/*===========================declare function prototypes===========================*/

//0520

// search graph
void Search_Mode();
// wait for command
void Hault_Mode();
void SetState();
byte idSize;
byte* prfid;
char* command;
char tableChar = ' ';
char dishChar = ' ';
int sprint=700;
int tin1=175;//轉彎的時間長度
int tin2=175;
int tin3=205;
int uin=340;//回轉的時間長度
int buf=300;//碰到node先停下來緩衝
  

/*===========================declare function prototypes===========================*/

/*===========================define function===========================*/
void setup()
{



  //bluetooth initialization
  
   BT.begin(9600);
  
   mp3.begin(9600);
   
   mp3_set_serial (mp3); //set Serial for DFPlayer-mini mp3 module
   mp3_set_volume (100);
   BT.listen();
   
   //0520
   //Serial window
   Serial.begin(9600);
   //RFID initial
  

  

   //L298N pin
   pinMode(MotorR_I1,   OUTPUT);
   pinMode(MotorR_I2,   OUTPUT);
   pinMode(MotorL_I3,   OUTPUT);
   pinMode(MotorL_I4,   OUTPUT);
   pinMode(MotorL_PWML, OUTPUT);
   pinMode(MotorR_PWMR, OUTPUT);
   
   //tracking pin
   pinMode(C0, INPUT); 
   pinMode(R2, INPUT);
   pinMode(R3, INPUT);

   pinMode(L2, INPUT);
   pinMode(L3, INPUT);
   
   
  
  analogWrite(MotorR_PWMR,0);
  analogWrite(MotorL_PWML,0);

  command = new char [20];
   for(int i = 0; i < 20; i++)
    command[ i ] = ' ';
  SetState();
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


#ifdef testCar
const char test[100] ={'r','r','u','r','r','u','l','l','u','l','l','u','r','r','u','r','r','u','l','l','u','l','l','u','r','r','u','r','r','u','l','l','u','l','l','u','r','r','u','r','r','u','l','l','u','l','l','u','r','r','u','r','r','u','l','l','u','l','l','u','r','r','u','r','r','u','l','l','u','l','l','u'};
#endif

void loop()
{
//static makeaturn(command);
tracking();

if(checknode()){
  stopCar();
  delay(500);
  moveForward();
  delay(sprint);
    stopCar();
  delay(500);
  #ifndef testCar
   makeaturn(command);
   #endif
   #ifdef testCar
   makeaturn(test);
   #endif
   
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

  }// loop

void SetState()// Get command from bluetooth 
{
   char judge = ' ';
   

   # ifndef testCar
   while(judge != 's')
   {
    
    judge = ask_BT_begin();  
         
   }

   
  if(judge == 's'){
   ask_BT(command,dishChar, tableChar);
  }
   #endif
   
}

void Hault_Mode()
{stopCar();}

void Search_Mode()
{tracking();


}
/*===========================define function===========================*/
