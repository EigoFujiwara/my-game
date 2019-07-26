/*****************************************************************
�ե�����̾	: client_command.c
��ǽ		: ���饤����ȤΥ��ޥ�ɽ���
*****************************************************************/

#include"client.h"
#include<netinet/in.h>
#include<netdb.h>
#include<sys/socket.h>

static void RecvRLdata(int num);
static void RecvJdata(int num);
static void RecvNdata(int num);
static void RecvSdata(int num);
static void RecvVdata(int num);

/*****************************************************************
�ؿ�̾	: ExecuteCommand
��ǽ	: �����С����������Ƥ������ޥ�ɤ򸵤ˡ�
		  ����������������¹Ԥ���
����	: char	command		: ���ޥ��
����	: �ץ���ཪλ���ޥ�ɤ��������Ƥ������ˤ�0���֤���
		  ����ʳ���1���֤�
*****************************************************************/
int ExecuteCommand(char command, int num)
{
    Sint16 poY;
    int	endFlag = 1;
    int pos = num - 1;
//#ifndef NDEBUG
   // printf("#####\n");
   // printf("ExecuteCommand()\n");
    //printf("command = %c\n",command);
//#endif
    
    switch(command){
		case END_COMMAND:
			endFlag = 0;
			break;
	        case R_COMMAND:
            RecvRLdata(num);
			break;
		case L_COMMAND:
            RecvRLdata(num);
			break;
		case J_COMMAND:
           RecvJdata(num);             
/*Mix_Chunk *chunk0;
            chunk0 = Mix_LoadWAV("chunk_jump.wav");
//if(Mix_Playing(5) == 0)
    if(mes[num].J_flag == 0)
            Mix_PlayChannel(5, chunk0, 0);
    else if(mes[num].J_flag == 0)
            Mix_PlayChannel(6, chunk0, 0);
    else if(mes[num].J_flag == 0)
            Mix_PlayChannel(7, chunk0, 0);
    else if(mes[num].J_flag == 0)
            Mix_PlayChannel(8, chunk0, 0);*/
            break;
        case N_COMMAND:
            RecvNdata(num);
            break;
        case S_COMMAND:
            RecvSdata(num);
            break;
        case V_COMMAND:
            RecvVdata(num);
            break;
    }
    return endFlag;
}

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

static void RecvRLdata(int num)
{
    int	x1,x2,x3,x4,y1,y2,y3,y4,dir1,dir2,dir3,dir4,eneX,eneY,ene2X,ene2Y,ene3X,ene3Y,ene4X,ene4Y,ene5X,ene5Y,j1,j2,j3,j4;

    RecvIntData(&x1);
    RecvIntData(&y1);
    RecvIntData(&dir1);
    RecvIntData(&x2);
    RecvIntData(&y2);
    RecvIntData(&dir2);
    RecvIntData(&x3);
    RecvIntData(&y3);
    RecvIntData(&dir3);
    RecvIntData(&x4);
    RecvIntData(&y4);
    RecvIntData(&dir4);     
    RecvIntData(&eneX);
    RecvIntData(&eneY);
    RecvIntData(&ene2X);
    RecvIntData(&ene2Y); 
    RecvIntData(&ene3X);
    RecvIntData(&ene3Y);  
    RecvIntData(&ene4X);
    RecvIntData(&ene4Y);  
    RecvIntData(&ene5X);
    RecvIntData(&ene5Y); 
    /*RecvIntData(&j1);
    RecvIntData(&j2);
    RecvIntData(&j3);
    RecvIntData(&j4);    */
    

     mes[0].posX = x1;
    mes[0].posY = y1;
    mes[0].dir = dir1;
    mes[1].posX = x2;
    mes[1].posY = y2;
    mes[1].dir = dir2;
    mes[2].posX = x3;
    mes[2].posY = y3;
    mes[2].dir = dir3;
    mes[3].posX = x4;
    mes[3].posY = y4;
    mes[3].dir = dir4;
    enemys[0].poX= eneX;
    enemys[0].poY= eneY;
    enemys[1].poX= ene2X;
    enemys[1].poY= ene2Y;
    enemys[2].poX= ene3X;
    enemys[2].poY= ene3Y;
    enemys[3].poX= ene4X;
    enemys[3].poY= ene4Y;
    enemys[4].poX= ene5X;
    enemys[4].poY= ene5Y;
    /*mes[0].J_flag = j1;
    mes[1].J_flag = j2;
    mes[2].J_flag = j3;
    mes[3].J_flag = j4;*/
}

static void RecvJdata(int num)
{
    int x1,x2,x3,x4,y1,y2,y3,y4,eneX,eneY,ene2X,ene2Y,ene3X,ene3Y,ene4X,ene4Y,ene5X,ene5Y,j1,j2,j3,j4;

    RecvIntData(&x1);
    RecvIntData(&y1);
    RecvIntData(&x2);
    RecvIntData(&y2);
    RecvIntData(&x3);
    RecvIntData(&y3);
    RecvIntData(&x4);
    RecvIntData(&y4);
    RecvIntData(&eneX);
    RecvIntData(&eneY); 
    RecvIntData(&ene2X);
    RecvIntData(&ene2Y); 
    RecvIntData(&ene3X);
    RecvIntData(&ene3Y);  
    RecvIntData(&ene4X);
    RecvIntData(&ene4Y);  
    RecvIntData(&ene5X);
    RecvIntData(&ene5Y);  
    /*RecvIntData(&j1);
    RecvIntData(&j2);
    RecvIntData(&j3);
    RecvIntData(&j4);*/
 
  
    mes[0].posX = x1;
    mes[0].posY = y1;
    mes[1].posX = x2;
    mes[1].posY = y2;
    mes[2].posX = x3;
    mes[2].posY = y3;
    mes[3].posX = x4;
    mes[3].posY = y4;
    enemys[0].poX= eneX;
    enemys[0].poY= eneY;
    enemys[1].poX= ene2X;
    enemys[1].poY= ene2Y;
    enemys[2].poX= ene3X;
    enemys[2].poY= ene3Y;
    enemys[3].poX= ene4X;
    enemys[3].poY= ene4Y;
    enemys[4].poX= ene5X;
    enemys[4].poY= ene5Y;
   /* mes[0].J_flag = j1;
    mes[1].J_flag = j2;
    mes[2].J_flag = j3;
    mes[3].J_flag = j4;*/
}

static void RecvNdata(int num)
{
    int x1,x2,x3,x4,y1,y2,y3,y4,eneX,eneY,ene2X,ene2Y,ene3X,ene3Y,ene4X,ene4Y,ene5X,ene5Y,j1,j2,j3,j4,tx1;

    RecvIntData(&x1);
    RecvIntData(&y1);
    RecvIntData(&x2);
    RecvIntData(&y2);
    RecvIntData(&x3);
    RecvIntData(&y3);
    RecvIntData(&x4);
    RecvIntData(&y4);
    RecvIntData(&eneX);
    RecvIntData(&eneY); 
    RecvIntData(&ene2X);
    RecvIntData(&ene2Y); 
    RecvIntData(&ene3X);
    RecvIntData(&ene3Y);  
    RecvIntData(&ene4X);
    RecvIntData(&ene4Y);  
    RecvIntData(&ene5X);
    RecvIntData(&ene5Y);  
    /*RecvIntData(&j1);
    RecvIntData(&j2);
    RecvIntData(&j3);
    RecvIntData(&j4);*/


    mes[0].posX = x1;
    mes[0].posY = y1;
    mes[1].posX = x2;
    mes[1].posY = y2;
    mes[2].posX = x3;
    mes[2].posY = y3;
    mes[3].posX = x4;
    mes[3].posY = y4;
    enemys[0].poX= eneX;
    enemys[0].poY= eneY;
    enemys[1].poX= ene2X;
    enemys[1].poY= ene2Y;
    enemys[2].poX= ene3X;
    enemys[2].poY= ene3Y;
    enemys[3].poX= ene4X;
    enemys[3].poY= ene4Y;
    enemys[4].poX= ene5X;
    enemys[4].poY= ene5Y;
    /*mes[0].J_flag = j1;
    mes[1].J_flag = j2;
    mes[2].J_flag = j3;
    mes[3].J_flag = j4;*/
}

static void RecvSdata(int num)
{
  if(clientnum == 1){
   mes[0].S_move = 1;
 }
  if(clientnum == 2){
  mes[0].S_move = 1;
  mes[1].S_move = 1;
  }
 if(clientnum == 3){
  mes[0].S_move = 1;
  mes[1].S_move = 1;
  mes[2].S_move = 1;
 }
 if(clientnum == 4){
  mes[0].S_move = 1;
  mes[1].S_move = 1;
  mes[2].S_move = 1;
  mes[3].S_move = 1;
 }
}

static void RecvVdata(int num)
{   
  resets();
  map_reset();
}


  
