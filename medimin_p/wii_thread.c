#include "client.h"

int wii;
int gSocket;

int thread(void* args)
{
   Sint16 poY;
   // Wiiリモコンがオープン（接続状態）であればループ
	while (wiimote_is_open(&wiimote)) {
		// Wiiリモコンの状態を取得・更新する
		if (wiimote_update(&wiimote) < 0) {
			wiimote_disconnect(&wiimote);
          break;
		}
	  // ***** Wiiのキー（ボタン）ごとに処理 *****              
	  // HOMEボタンが押された時                                          
	if (wiimote.keys.home) {//終了処理
		Send_END_Command();
	} 
	if(wiimote.keys.up){//左移動
		Send_L_Command();
	}
	if(wiimote.keys.down){//右移動
		Send_R_Command();
	}
	//if(wiimote.keys.minus){
	//	wii = 6;
	//}
	//if (wiimote.keys.plus){
	//	wii = 1;
	//}
	if(wiimote.keys.two){//ジャンプ
		Send_J_Command();
	}
    else{
        Send_N_Command();
      }
   }
   return 0;
}

void Send_R_Command()//クライアントに右移動させるためにサーバにWiiリモコン下を押したことを通知
{
  unsigned char data[MAX_DATA];
  int datasize;

datasize = 0;

SetCharData2DataBlock(data,R_COMMAND,&datasize);
SendDataW(data,datasize);
}

void Send_L_Command()//クライアントに左移動させるためにサーバにWiiリモコン上を押したことを通知
{
  unsigned char data[MAX_DATA];
  int datasize;

datasize = 0;

SetCharData2DataBlock(data,L_COMMAND,&datasize);
SendDataW(data,datasize);
}

void Send_J_Command()//クライアントにジャンプさせるためにサーバにWiiリモコン②を押したことを通知
{
  unsigned char data[MAX_DATA];
  int datasize;

datasize = 0;

SetCharData2DataBlock(data,J_COMMAND,&datasize);
SendDataW(data,datasize);
}

void Send_END_Command()//プログラムを終了させるためにサーバにWiiリモコンHomeを押したことを通知
{
  unsigned char data[MAX_DATA];
  int datasize;

datasize = 0;

SetCharData2DataBlock(data,END_COMMAND,&datasize);
SendDataW(data,datasize);
}

void Send_N_Command()
{
  unsigned char data[MAX_DATA];
  int datasize;

datasize = 0;

SetCharData2DataBlock(data,N_COMMAND,&datasize);
SendDataW(data,datasize);
}

void SendDataW(void *data,int dataSize)
{
    /* 引き数チェック */
    assert(data != NULL);
    assert(0 < dataSize);

    write(gSocket,data,dataSize);
}

void SetCharData2DataBlock(void *data,char charData,int *dataSize)//char型のデータを送信用データの最後にセット
{
    /* 引き数チェック */
    assert(data!=NULL);
    assert(0<=(*dataSize));

    /* char 型のデータを送信用データの最後にコピーする */
    *(char *)(data + (*dataSize)) = charData;
    /* データサイズを増やす */
    (*dataSize) += sizeof(char);
}



