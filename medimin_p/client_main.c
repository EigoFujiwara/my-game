/*****************************************************************
�ե�����̾	: client_main.c
��ǽ		: ���饤����ȤΥᥤ��롼����
*****************************************************************/

#include"client.h"
#include"SDL/SDL.h"

int clientID;
int endFlag =  1;
SDL_Thread *thr;
wiimote_t wiimote = WIIMOTE_INIT;// Wii��⥳��ξ��ֳ�Ǽ�� 

static int NetworkEvent(void* args);
int clientnum;

int main(int argc,char *argv[])
{
    char	name[MAX_CLIENTS][MAX_NAME_SIZE];
    char	localHostName[]="localhost";
    char	*serverName;
    u_short port = DEFAULT_PORT;
    SDL_Thread *thr2;
	  if (argc < 4) {// Wii��⥳���̾��󤬥��ޥ�ɰ�����Ϳ�����ʤ����       
    printf("Designate the wiimote ID to the application.\n");
    exit(1);
  }
    /* �����������å� */
    	serverName = argv[1];
   port = (u_short)atoi(argv[2]);
                                       
  // Wii��⥳�����³�ʣ��ĤΤߡ�                                            
  if (wiimote_connect(&wiimote, argv[3]) < 0) {// ���ޥ�ɰ����˻��ꤷ��Wii��⥳���̾�����Ϥ�����³                                                      
 printf("unable to open wiimote: %s\n", wiimote_get_error());
 exit(1);
  }

  wiimote.mode.acc = 1;

  wiimote.led.one  = 1;// Wii��⥳���LED�ΰ��ֺ����������������³���Τ餻�뤿��ˡ�
 thr = SDL_CreateThread(thread, NULL);//wii����å�
 
 thr2 = SDL_CreateThread(NetworkEvent, NULL);//�ͥåȥ�����٥�ȥ���å�

    /* �����С��Ȥ���³ */
    if(SetUpClient(serverName,&clientID,&clientnum,name)==-1){
		fprintf(stderr,"setup failed : SetUpClient\n");
		return -1;
	}
     
	 startGame();//�����

  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
Mix_Music *music;
music = Mix_LoadMUS("music.mp3");
Mix_PlayMusic(music,-1);
Mix_VolumeMusic(60);
	/* �ᥤ�󥤥٥�ȥ롼�� */
    while(endFlag){
	switch(games)
		{

		case 1://���ơ�����
		  backGraund2();
		  mapDrw();
		  me_main();
          continue_game();
			break;

        case 2://���ơ�����
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
/* ��λ���� */
    SDL_Quit();
    SDL_RemoveTimer(timer_id);
    return 0;
}


static int NetworkEvent(void *args)//�����С����饤����ȴ֤Τ����򥹥�åɲ�
{	
    while(endFlag){
        endFlag = SendRecvManager();
    }
	return 0;
}

