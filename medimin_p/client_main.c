/*****************************************************************
ファイル名	: client_main.c
機能		: クライアントのメインルーチン
*****************************************************************/

#include"client.h"
#include"SDL/SDL.h"

int clientID;
int endFlag =  1;
SDL_Thread *thr;
wiimote_t wiimote = WIIMOTE_INIT;// Wiiリモコンの状態格納用 

static int NetworkEvent(void* args);
int clientnum;

int main(int argc,char *argv[])
{
    char	name[MAX_CLIENTS][MAX_NAME_SIZE];
    char	localHostName[]="localhost";
    char	*serverName;
    u_short port = DEFAULT_PORT;
    SDL_Thread *thr2;
	  if (argc < 4) {// Wiiリモコン識別情報がコマンド引数で与えられなければ       
    printf("Designate the wiimote ID to the application.\n");
    exit(1);
  }
    /* 引き数チェック */
    	serverName = argv[1];
   port = (u_short)atoi(argv[2]);
                                       
  // Wiiリモコンの接続（１つのみ）                                            
  if (wiimote_connect(&wiimote, argv[3]) < 0) {// コマンド引数に指定したWiiリモコン識別情報を渡して接続                                                      
 printf("unable to open wiimote: %s\n", wiimote_get_error());
 exit(1);
  }

  wiimote.mode.acc = 1;

  wiimote.led.one  = 1;// WiiリモコンのLEDの一番左を点灯させる（接続を知らせるために）
 thr = SDL_CreateThread(thread, NULL);//wiiスレッド
 
 thr2 = SDL_CreateThread(NetworkEvent, NULL);//ネットワークイベントスレッド

    /* サーバーとの接続 */
    if(SetUpClient(serverName,&clientID,&clientnum,name)==-1){
		fprintf(stderr,"setup failed : SetUpClient\n");
		return -1;
	}
     
	 startGame();//初期化

  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
Mix_Music *music;
music = Mix_LoadMUS("music.mp3");
Mix_PlayMusic(music,-1);
Mix_VolumeMusic(60);
	/* メインイベントループ */
    while(endFlag){
	switch(games)
		{

		case 1://ステージ１
		  backGraund2();
		  mapDrw();
		  me_main();
          continue_game();
			break;

        case 2://ステージ２
		  backGraund2();
		  mapDrw();
          trap_Y(1200,730);
          trap_Y(1250,730);
          trap_Y(1300,730);
          trap_Y(1350,730);
        enemys_mainY(enemys[0].poX,enemys[0].poY);
		enemys_mainY(enemys[1].poX,enemys[1].poY);
		enemys_mainY(enemys[2].poX,enemys[2].poY);
		enemys_mainY(enemys[3].poX,enemys[3].poY);
		enemys_mainY(enemys[4].poX,enemys[4].poY);
         me_main();
          clear();
			break;  
		default: break;
			}
	frames();
		}
/* 終了処理 */
    SDL_Quit();
    SDL_RemoveTimer(timer_id);
    return 0;
}


static int NetworkEvent(void *args)//サーバークライアント間のやり取りをスレッド化
{	
    while(endFlag){
        endFlag = SendRecvManager();
    }
	return 0;
}

