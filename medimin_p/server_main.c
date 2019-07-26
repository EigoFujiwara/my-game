/*****************************************************************
�ե�����̾	: server_main.c
��ǽ		: �����С��Υᥤ��롼����
*****************************************************************/

#include"server.h"

int endFlag = 1;

static int NetworkEvent(void* args);

int main(int argc,char *argv[])
{
	int	num;
    u_short port = DEFAULT_PORT;
	/* �����������å� */
	if(argc != 3){
		fprintf(stderr,"Usage: number of clients\n");
		exit(-1);
	}
	if((num = atoi(argv[1])) < 0 ||  num > me_max){
		fprintf(stderr,"clients limit = %d \n",me_max);
		exit(-1);
	}
    port = atoi(argv[2]);
	/* ���饤����ȤȤ���³ */
	if(SetUpServer(num) == -1){
		fprintf(stderr,"Cannot setup server\n");
		exit(-1);
	}
        startGame();
     	while(endFlag){
		endFlag = SendRecvManager();
	}  	
	/* ��λ���� */
	Ending();

	return 0;
}
