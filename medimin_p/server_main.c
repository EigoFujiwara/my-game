/*****************************************************************
ファイル名	: server_main.c
機能		: サーバーのメインルーチン
*****************************************************************/

#include"server.h"

int endFlag = 1;

static int NetworkEvent(void* args);

int main(int argc,char *argv[])
{
	int	num;
    u_short port = DEFAULT_PORT;
	/* 引き数チェック */
	if(argc != 3){
		fprintf(stderr,"Usage: number of clients\n");
		exit(-1);
	}
	if((num = atoi(argv[1])) < 0 ||  num > me_max){
		fprintf(stderr,"clients limit = %d \n",me_max);
		exit(-1);
	}
    port = atoi(argv[2]);
	/* クライアントとの接続 */
	if(SetUpServer(num) == -1){
		fprintf(stderr,"Cannot setup server\n");
		exit(-1);
	}
        startGame();
     	while(endFlag){
		endFlag = SendRecvManager();
	}  	
	/* 終了処理 */
	Ending();

	return 0;
}
