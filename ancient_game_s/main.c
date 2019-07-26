#include "headers.h"
int wii;
SDL_Thread *thr;
wiimote_t wiimote = WIIMOTE_INIT;// Wii�����R���̏�Ԋi�[�p 

int main(int argc, char *argv[])
{                    
startUp();             
 
  // ***** Wii�����R������ *****                                               
  if (argc < 2) {// Wii�����R�����ʏ�񂪃R�}���h�����ŗ^�����Ȃ����       
    printf("Designate the wiimote ID to the application.\n");
    exit(1);
  }
  // Wii�����R���̐ڑ��i�P�̂݁j                                            
  if (wiimote_connect(&wiimote, argv[1]) < 0) {// �R�}���h�����Ɏw�肵��Wii�����R�����ʏ���n���Đڑ�                                                      
 printf("unable to open wiimote: %s\n", wiimote_get_error());
 exit(1);
  }

  wiimote.mode.acc = 1;

  wiimote.led.one  = 1;// Wii�����R����LED�̈�ԍ���_��������i�ڑ���m�点�邽�߂Ɂj
                                                                      
thr = SDL_CreateThread(thread, NULL);

while(quits()!=1)
	{ 

	switch(games)
		{
		case 0://�^�C�g�����
		  backGraund();
		    startGame();
		    break;

		case 1://�X�e�[�W�P
		  backGraund2();
		  mapDrw();
          obj_main(212, 96);
		  me_main();
		  trap_X(480, 360);
		  trap_X(480, 144);
		  trap_X(480, 240);
          trap_X(480, 540);
			break;

        case 2://�X�e�[�W�Q
		  backGraund2();
		  mapDrw();
          obj_main(260, 48);
		  me_main();
          trap_Y(100, 0);
		  trap_Y(200, 0);
		  trap_Y(300, 0);
			break;

		case 3://�X�e�[�W�R
		  backGraund2();
		  mapDrw();
          obj_main(260,48);
		  me_main();
		  enemy_homing(96, 0);
          enemy_homing(336, 0);
			break;

		case 4://�X�e�[�W�S
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
			
		case 5://�X�e�[�W�T
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

		case 6://�Q�[���I�[�o�[
		  gameover();
		  backtitle();
			break;
		case 7://�N���A
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
