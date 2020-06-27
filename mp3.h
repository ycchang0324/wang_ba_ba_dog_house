#ifndef _MP3_H_
#define _MP3_H_

#include <softwareserial.h>
#include <DFPlayer_Mini_Mp3.h>  //要用這個之前要去網路把.h檔匯入

void mp3Play(int no){
  mp3.listen();
  mp3_play(no);
  delay(35000);
  BT.listen();
}


#endif
