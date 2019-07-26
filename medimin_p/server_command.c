/*****************************************************************
�ե�����̾	: server_command.c
��ǽ		: �����С��Υ��ޥ�ɽ���
*****************************************************************/

#include"server.h"
#include<netinet/in.h>
#include<netdb.h>
#include<sys/socket.h>



/*****************************************************************
�ؿ�̾	: ExecuteCommand
��ǽ	: ���饤����Ȥ��������Ƥ������ޥ�ɤ򸵤ˡ�
		  ����������������¹Ԥ���
����	: char	command		: ���ޥ��
		  int	pos			: ���ޥ�ɤ����ä����饤������ֹ�
����	: �ץ���ཪλ���ޥ�ɤ������Ƥ������ˤ�0���֤���
		  ����ʳ���1���֤�
*****************************************************************/
int ExecuteCommand(char command,int pos)
{
    unsigned char	data[MAX_DATA];
    int			dataSize;
    SDL_Thread *thr2;
    int trap;
    /* �����������å� */
    assert(0<=pos && pos<MAX_CLIENTS);
    switch(command){
    case END_COMMAND:
                dataSize = 0;
                        /* ���ޥ�ɤΥ��å� */
                        SetCharData2DataBlock(data,command,&dataSize);
                        /* ���桼���������� */
                        SendData(ALL_CLIENTS,data,dataSize);
                        endFlag = 0;
                        break;
               case J_COMMAND:
                if(mes[pos].J_flag == 0){
                  mes[pos].J_flag = 1;
                  mes[pos].J_max = mes[pos].posY;
                 }
               if(mes[pos].J_flag == 2){
                if(hitChek_me_f(pos) == 1 || hitChek_me_f(pos) == 5){
                mes[pos].J_flag = 0;
                mes[pos].Bjanp = 0;
                }
             }
              if(mes[pos].Bjanp == 1){
                mes[pos].J_flag = 2;
             }
                           if(mes[pos].Bjanp == 2){
                mes[pos].J_flag = 2;
             }
             if(hitChek_me_f(pos) == 5){
                mes[pos].posX += 1;
              }
if(games == 2){
     if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[0].poX,enemys[0].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[1].poX,enemys[1].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[2].poX,enemys[2].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[3].poX,enemys[3].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[4].poX,enemys[4].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
if(enemys[0].change==0){//������
	enemys[0].poY-=0.5;
}
if(enemys[0].change==1){
	enemys[0].poY+=0.5;
}
if(enemys[0].poY<=120){
	enemys[0].change=1;
}
if(enemys[0].poY>=401){
	enemys[0].change=0;
}

if(enemys[1].change==0){//������
	enemys[1].poY-=0.5;
}
if(enemys[1].change==1){
	enemys[1].poY+=0.5;
}
if(enemys[1].poY<=10){
	enemys[1].change=1;
}
if(enemys[1].poY>=190){
	enemys[1].change=0;
}

if(enemys[2].change==0){//������
	enemys[2].poX-=0.5;
}
if(enemys[2].change==1){
	enemys[2].poX+=0.5;
}
if(enemys[2].poX<=1250){
	enemys[2].change=1;
}
if(enemys[2].poX>=1580){
	enemys[2].change=0;
}

if(enemys[3].change==0){//������
	enemys[3].poX-=0.5;
}
if(enemys[3].change==1){
	enemys[3].poX+=0.5;
}
if(enemys[3].poX<=1200){
	enemys[3].change=1;
}
if(enemys[3].poX>=1580){
	enemys[3].change=0;
}

if(enemys[4].change==0){//������
	enemys[4].poX-=0.5;
}
if(enemys[4].change==1){
	enemys[4].poX+=0.5;
}
if(enemys[4].poX<=338){
	enemys[4].change=1;
}
if(enemys[4].poX>=575){
	enemys[4].change=0;
}
}

                me_mg(pos);
                me_janp();
                me_move();
                me_revive();
                me_Bjanp();
                dataSize = 0;
                SetCharData2DataBlock(data,J_COMMAND,&dataSize);
                SetIntData2DataBlock(data,pos,&dataSize);        
                SetIntData2DataBlock(data,mes[0].posX,&dataSize);
                SetIntData2DataBlock(data,mes[0].posY,&dataSize);
                SetIntData2DataBlock(data,mes[1].posX,&dataSize);
                SetIntData2DataBlock(data,mes[1].posY,&dataSize);
                SetIntData2DataBlock(data,mes[2].posX,&dataSize);
                SetIntData2DataBlock(data,mes[2].posY,&dataSize);
                SetIntData2DataBlock(data,mes[3].posX,&dataSize);
                SetIntData2DataBlock(data,mes[3].posY,&dataSize);
                SetIntData2DataBlock(data,enemys[0].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[0].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[1].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[1].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[2].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[2].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[3].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[3].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[4].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[4].poY,&dataSize);
                /*SetIntData2DataBlock(data,mes[0].J_flag,&dataSize);
                SetIntData2DataBlock(data,mes[1].J_flag,&dataSize);
                SetIntData2DataBlock(data,mes[2].J_flag,&dataSize);
                SetIntData2DataBlock(data,mes[3].J_flag,&dataSize);*/
                SendData(ALL_CLIENTS,data,dataSize);
                       break;
              case R_COMMAND:
                mes[pos].posX += 1;
                mes[pos].dir = 5;
                               if(mes[pos].J_flag == 2){
                if(hitChek_me_f(pos) == 1 ||hitChek_me_f(pos) == 5){
                mes[pos].J_flag = 0;
                mes[pos].Bjanp = 0;
                }
             }
              if(mes[pos].Bjanp == 1){
                mes[pos].J_flag = 2;
             }
                           if(mes[pos].Bjanp == 2){
                mes[pos].J_flag = 2;
             }
             if(hitChek_me_f(pos) == 5){
                mes[pos].posX += 1;
              }
if(games == 2){
     if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[0].poX,enemys[0].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[1].poX,enemys[1].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[2].poX,enemys[2].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[3].poX,enemys[3].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[4].poX,enemys[4].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
 }

                me_mg(pos);
                me_janp();
                me_move();
                me_revive();
                me_Bjanp();
                dataSize = 0;
                SetCharData2DataBlock(data,R_COMMAND,&dataSize);
                SetIntData2DataBlock(data,pos,&dataSize);
                SetIntData2DataBlock(data,mes[0].posX,&dataSize);
                SetIntData2DataBlock(data,mes[0].posY,&dataSize);
                SetIntData2DataBlock(data,mes[0].dir,&dataSize);
                SetIntData2DataBlock(data,mes[1].posX,&dataSize);
                SetIntData2DataBlock(data,mes[1].posY,&dataSize);
                SetIntData2DataBlock(data,mes[1].dir,&dataSize);
                SetIntData2DataBlock(data,mes[2].posX,&dataSize);
                SetIntData2DataBlock(data,mes[2].posY,&dataSize);
                SetIntData2DataBlock(data,mes[2].dir,&dataSize);
                SetIntData2DataBlock(data,mes[3].posX,&dataSize);
                SetIntData2DataBlock(data,mes[3].posY,&dataSize);
                SetIntData2DataBlock(data,mes[3].dir,&dataSize);
                SetIntData2DataBlock(data,enemys[0].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[0].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[1].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[1].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[2].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[2].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[3].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[3].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[4].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[4].poY,&dataSize);
                /*SetIntData2DataBlock(data,mes[0].J_flag,&dataSize);
                SetIntData2DataBlock(data,mes[1].J_flag,&dataSize);
                SetIntData2DataBlock(data,mes[2].J_flag,&dataSize);
                SetIntData2DataBlock(data,mes[3].J_flag,&dataSize);*/
                SendData(ALL_CLIENTS,data,dataSize);
                        break;
               case L_COMMAND:
                mes[pos].posX -= 1;
                mes[pos].dir = 4;
                               if(mes[pos].J_flag == 2){
                if(hitChek_me_f(pos) == 1 || hitChek_me_f(pos) == 5){
                mes[pos].J_flag = 0;
                  mes[pos].Bjanp = 0;
                }
             }
              if(mes[pos].Bjanp == 1){
                mes[pos].J_flag = 2;
             }
                           if(mes[pos].Bjanp == 2){
                mes[pos].J_flag = 2;
             }
             if(hitChek_me_f(pos) == 5){
                mes[pos].posX += 1;
              }
 if(games == 2){
     if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[0].poX,enemys[0].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[1].poX,enemys[1].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[2].poX,enemys[2].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[3].poX,enemys[3].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[4].poX,enemys[4].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
 }

                me_mg(pos);
                me_janp();
                me_move();
                me_revive();
                me_Bjanp();
                dataSize = 0;
                SetCharData2DataBlock(data,L_COMMAND,&dataSize);
                SetIntData2DataBlock(data,pos,&dataSize);
                SetIntData2DataBlock(data,mes[0].posX,&dataSize);
                SetIntData2DataBlock(data,mes[0].posY,&dataSize);
                SetIntData2DataBlock(data,mes[0].dir,&dataSize);
                SetIntData2DataBlock(data,mes[1].posX,&dataSize);
                SetIntData2DataBlock(data,mes[1].posY,&dataSize);
                SetIntData2DataBlock(data,mes[1].dir,&dataSize);
                SetIntData2DataBlock(data,mes[2].posX,&dataSize);
                SetIntData2DataBlock(data,mes[2].posY,&dataSize);
                SetIntData2DataBlock(data,mes[2].dir,&dataSize);
                SetIntData2DataBlock(data,mes[3].posX,&dataSize);
                SetIntData2DataBlock(data,mes[3].posY,&dataSize);
                SetIntData2DataBlock(data,mes[3].dir,&dataSize);
                SetIntData2DataBlock(data,enemys[0].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[0].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[1].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[1].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[2].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[2].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[3].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[3].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[4].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[4].poY,&dataSize);
                /*SetIntData2DataBlock(data,mes[0].J_flag,&dataSize);
                SetIntData2DataBlock(data,mes[1].J_flag,&dataSize);
                SetIntData2DataBlock(data,mes[2].J_flag,&dataSize);
                SetIntData2DataBlock(data,mes[3].J_flag,&dataSize);*/
                SendData(ALL_CLIENTS,data,dataSize);
                       break;

                case N_COMMAND:
                mes[pos].J_flag = 2;
                   if(mes[pos].J_flag == 2){
                if(hitChek_me_f(pos) == 1 || hitChek_me_f(pos) == 5){
                mes[pos].J_flag = 0;
                mes[pos].Bjanp = 0;
                }
             }
              if(mes[pos].Bjanp == 1){
                mes[pos].J_flag = 2;
             }
                           if(mes[pos].Bjanp == 2){
                mes[pos].J_flag = 2;
             }
             if(hitChek_me_f(pos) == 5){
                mes[pos].posX += 1;
              }
 if(games == 2){
 	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[0].poX,enemys[0].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[1].poX,enemys[1].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[2].poX,enemys[2].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[3].poX,enemys[3].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
	if (hitChek_me_e(mes[pos].posX, mes[pos].posY, enemys[4].poX,enemys[4].poY)==1){
	mes[pos].flag-=1;
    SDL_Delay(300);
	}
if(enemys[0].change==0){  //�����ܤΰ�ư
	enemys[0].poY-=0.5;
}
if(enemys[0].change==1){
	enemys[0].poY+=0.5;
}
if(enemys[0].poY<=120){
	enemys[0].change=1;
}
if(enemys[0].poY>=401){
	enemys[0].change=0;
}
if(enemys[1].change==0){//������
	enemys[1].poY-=0.5;
}
if(enemys[1].change==1){
	enemys[1].poY+=0.5;
}
if(enemys[1].poY<=10){
	enemys[1].change=1;
}
if(enemys[1].poY>=190){
	enemys[1].change=0;
}

if(enemys[2].change==0){//������
	enemys[2].poX-=0.5;
}
if(enemys[2].change==1){
	enemys[2].poX+=0.5;
}
if(enemys[2].poX<=1250){
	enemys[2].change=1;
}
if(enemys[2].poX>=1580){
	enemys[2].change=0;
}

if(enemys[3].change==0){//������
	enemys[3].poX-=0.5;
}
if(enemys[3].change==1){
	enemys[3].poX+=0.5;
}
if(enemys[3].poX<=1200){
	enemys[3].change=1;
}
if(enemys[3].poX>=1580){
	enemys[3].change=0;
}

if(enemys[4].change==0){//������
	enemys[4].poX-=0.5;
}
if(enemys[4].change==1){
	enemys[4].poX+=0.5;
}
if(enemys[4].poX<=338){
	enemys[4].change=1;
}
if(enemys[4].poX>=575){
	enemys[4].change=0;
}
 }

                me_mg(pos);
                me_janp();
                me_move();
                me_revive();
                me_Bjanp();
                dataSize = 0;
                SetCharData2DataBlock(data,N_COMMAND,&dataSize);
                SetIntData2DataBlock(data,pos,&dataSize);
                SetIntData2DataBlock(data,mes[0].posX,&dataSize);
                SetIntData2DataBlock(data,mes[0].posY,&dataSize);
                SetIntData2DataBlock(data,mes[1].posX,&dataSize);
                SetIntData2DataBlock(data,mes[1].posY,&dataSize);
                SetIntData2DataBlock(data,mes[2].posX,&dataSize);
                SetIntData2DataBlock(data,mes[2].posY,&dataSize);
                SetIntData2DataBlock(data,mes[3].posX,&dataSize);
                SetIntData2DataBlock(data,mes[3].posY,&dataSize);
                SetIntData2DataBlock(data,enemys[0].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[0].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[1].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[1].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[2].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[2].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[3].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[3].poY,&dataSize);
		        SetIntData2DataBlock(data,enemys[4].poX,&dataSize);
                SetIntData2DataBlock(data,enemys[4].poY,&dataSize);
                /*SetIntData2DataBlock(data,mes[0].J_flag,&dataSize);
                SetIntData2DataBlock(data,mes[1].J_flag,&dataSize);
                SetIntData2DataBlock(data,mes[2].J_flag,&dataSize);
                SetIntData2DataBlock(data,mes[3].J_flag,&dataSize);*/
                SendData(ALL_CLIENTS,data,dataSize);
                       break;
     case V_COMMAND:
         resets();
         dataSize = 0;
         SetCharData2DataBlock(data,V_COMMAND,&dataSize);
         SetIntData2DataBlock(data,pos,&dataSize);
         SendData(ALL_CLIENTS,data,dataSize); 
           break;
           default:
           break;
    }
    return endFlag;
}

/*****
static
*****/
/*****************************************************************
�ؿ�̾	: SetIntData2DataBlock
��ǽ	: int ���Υǡ����������ѥǡ����κǸ�˥��åȤ���
����	: void		*data		: �����ѥǡ���
		  int		intData		: ���åȤ���ǡ���
		  int		*dataSize	: �����ѥǡ����θ��ߤΥ�����
����	: �ʤ�
*****************************************************************/
void SetIntData2DataBlock(void *data,int intData,int *dataSize)
{
    int tmp;

    /* �����������å� */
    assert(data!=NULL);
    assert(0<=(*dataSize));

    tmp = htonl(intData);

    /* int ���Υǡ����������ѥǡ����κǸ�˥��ԡ����� */
    memcpy(data + (*dataSize),&tmp,sizeof(int));
    /* �ǡ��������������䤹 */
    (*dataSize) += sizeof(int);
}

/*****************************************************************
�ؿ�̾	: SetCharData2DataBlock
��ǽ	: char ���Υǡ����������ѥǡ����κǸ�˥��åȤ���
����	: void		*data		: �����ѥǡ���
		  int		intData		: ���åȤ���ǡ���
		  int		*dataSize	: �����ѥǡ����θ��ߤΥ�����
����	: �ʤ�
*****************************************************************/
void SetCharData2DataBlock(void *data,char charData,int *dataSize)
{
    /* �����������å� */
    assert(data!=NULL);
    assert(0<=(*dataSize));

    /* int ���Υǡ����������ѥǡ����κǸ�˥��ԡ����� */
    *(char *)(data + (*dataSize)) = charData;
    /* �ǡ��������������䤹 */
    (*dataSize) += sizeof(char);
}


