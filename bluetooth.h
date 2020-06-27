/***************************************************************************/
// File        [bluetooth.h]
// Author     [Erik Kuo]
// Synopsis   [Code for bluetooth communication]
// Functions  [ask_BT, send_msg, send_byte]
// Modify     [2020/03/27 Erik Kuo]
/***************************************************************************/

/*if you have no idea how to start*/
/*check out what you have learned from week 2*/

#include<SoftwareSerial.h>
extern SoftwareSerial BT;
enum BT_CMD {
    FORWARD,
    LEFT,
    BACKWARD,
    RIGHT,
  NOTHING,
  // TODO: add your own command type here
};

char ask_BT_begin(){
  char val = ' ';

  if(BT.available()){
    val = BT.read();

    return val;
  }

  return val;
}
BT_CMD ask_BT(char* command,char &dishNum, char &tableNum){
    Serial.println("送餐囉");
    BT_CMD message=NOTHING;
    char val = ' ';
    for(int i = 0; i < 20 ; i++){
      command[i] = ' ';
    }
     dishNum = ' ';
     tableNum = ' ';
    unsigned int j = 0;
    unsigned int k = 0;
    Serial.print("餐點數量: ");
    while (!BT.available()){
      ;
    }
    dishNum = BT.read();
    BT.write('r');
    
    Serial.print(dishNum);
    Serial.println("個");
    Serial.print("過去路徑: ");
      while(val != 'x'){
        if (BT.available()) {
          val = BT.read();
          command[ j ] = val;
          Serial.print(val);
          Serial.print(" ");
          j++;
          
        }
      }
      Serial.println();
      val = ' ';
      
      BT.write('r');
      Serial.print("桌號: ");
      while (!BT.available()){
      ;
    }
        tableNum = BT.read();
      
      Serial.print(tableNum);
      Serial.println("號桌");
      BT.write('r');
      Serial.print("回來路徑: ");
      k=j;
      while(val != 'y'){
        if (BT.available()) {
          val = BT.read();
          command[ k ] = val;
          Serial.print(val);
          Serial.print(" ");
          
          k++;
        }
      }
      Serial.println();
      Serial.println();
      val = ' ';  
    BT.write('r');  
     

}// ask_BT

// send msg back through SoftwareSerial object: BT
// can use send_byte alternatively to send msg back
// (but need to convert to byte type)
void send_msg(const char& msg)
{
    BT.print(msg);
     // TODO:
}// send_msg

// send UID back through SoftwareSerial object: BT
void send_byte(byte *id, byte& idSize) {

  
  for (byte i = 0; i < idSize; i++) {  // Send UID consequently.
    BT.write(id[i]);
    
    Serial.print(id[i], HEX);
  }
  
  #ifdef DEBUG
  Serial.print("Sent id: ");
  for (byte i = 0; i < idSize; i++) {  // Show UID consequently.
    Serial.print(id[i], HEX);
  }
  Serial.println();
  
  #endif
  for (byte i = 0; i < idSize; i++) {  // Send UID consequently.
    id[ i ] = 0;
  }
}// send_byte
