#include "headers.h"
int wii;
SDL_Thread *thr;
wiimote_t wiimote = WIIMOTE_INIT;// Wiiリモコンの状態格納用 

int main(int argc, char *argv[])
{                    
startUp();             
 
  // ***** Wiiリモコン処理 *****                                               
  if (argc < 2) {// Wiiリモコン識別情報がコマンド引数で与えられなければ       
    printf("Designate the wiimote ID to the application.\n");
    exit(1);
  }
  // Wiiリモコンの接続（１つのみ）                                            
  if (wiimote_connect(&wiimote, argv[1]) < 0) {// コマンド引数に指定したWiiリモコン識別情報を渡して接続                                                      
 printf("unable to open wiimote: %s\n", wiimote_get_error());
 exit(1);
  }

  wiimote.mode.acc = 1;

  wiimote.led.one  = 1;// WiiリモコンのLEDの一番左を点灯させる（接続を知らせるために）
                                                                      
thr = SDL_CreateThread(thread, NULL);

while(quits()!=1)
	{ 

	switch(games)
		{
		case 0://タイトル画面
		  backGraund();
		    startGame();
		    break;

		case 1://ステージ１
		  backGraund2();
		  mapDrw();
          obj_main(212, 96);
		  me_main();
		  trap_X(480, 360);
		  trap_X(480, 144);
		  trap_X(480, 240);
          trap_X(480, 540);
			break;

        case 2://ステージ２
		  backGraund2();
		  mapDrw();
          obj_main(260, 48);
		  me_main();
          trap_Y(100, 0);
		  trap_Y(200, 0);
		  trap_Y(300, 0);
			break;

		case 3://ステージ３
		  backGraund2();
		  mapDrw();
          obj_main(260,48);
		  me_main();
		  enemy_homing(96, 0);
          enemy_homing(336, 0);
			break;

		case 4://ステージ４
		  backGraund2();
		  mapDrw();
          obj_main(212,48);
		  me_main();
		  enemy_homing(96, 0);
          enemy_homing(288, 0);
	      trap_X(480, 288);
          trap_X(480, 400);
          trap_X(480, 150); 
			break;
			
		case 5://ステージ５
		  backGraund2();
		  mapDrw();
          me_main();
	      obj2_main(203, 10);
		  boss_main(240, 200);
          trap_X(480, 160);
          trap_X(480, 250);
		  trap_X(480, 544);
          trap_X(480, 360);
		  trap_X(480, 444);
		  break;

		case 6://ゲームオーバー
		  gameover();
		  backtitle();
			break;
		case 7://クリア
		  clear();  
		  backtitle();
		  break;	  
		default: break;
			}
	frames();
		}
SDL_Quit();
return 0;
}
