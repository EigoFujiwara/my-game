#ifndef HEAD_H
#define HEAD_H

#include<sys/types.h>
#include<assert.h>
#include<unistd.h>

#include<math.h>
#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define PORT          (u_short)8888
#define MAX_CLIENTS   4
#define MAX_NAME_SIZE 10
#define MAX_DATA      200
#define DEFAULT_PORT 51000

#define END_COMMAND   'E'
#define R_COMMAND     'R'
#define L_COMMAND     'L'
#define J_COMMAND     'J'
#define N_COMMAND     'N'
#define S_COMMAND     'S'
#define V_COMMAND     'V'
#define B_COMMAND     'B'

//#define	BUF_SIZE	100
//#define t_max 6
#define me_max 4
/*#define img_max 26
#define REC 48
#define SIZE_Y 20
#define SIZE_X 35
#define PAI 3.1415926f
#define txt_max 7
#define M_max 7*/

/*extern int change;
extern int finish;
extern int wii;
extern int games;*/
extern int clientID;
extern int endFlag;

/*typedef enum {
    CT_Player1 = 0,  
    CT_Player1 = 1, 
    CT_Player1 = 2, 
    CT_Player1 = 3; 
} CharaType;*/

/*typedef struct
{
Uint32 now,//現在時間
    wit,//待ち時間
    lev;//経過時間
}timers;
extern timers timer;

typedef struct//自機用の変数
{
  Sint16 posX,//自機の位置Ｘ
         posY,//自機の位置Ｙ
         J_flag,//ジャンプフラグ
         flag;//自機フラグ
}ziki;
extern ziki mes[me_max];

typedef struct //敵用の変数
{
  Sint16 flg,cnt;//フラグ、再検出のカウンタ
  double poX,poY,//現在地
    moX,moY,//移動量
    spd,rot,//スピードと弾の角度
    tar;    //ターゲットの方向
}enemy;
extern enemy enemys;*/

/*typedef struct //ボス用の変数                                                  
{
  Sint16 hp,cnt;//フラグ、再検出のカウンタ                                    
  double poX,poY,//現在地                                                      
    moX,moY,//移動量                                                           
    spd,rot,//スピードと弾の角度                                             
    tar;    //ターゲットの方向                                                 
}bos;
extern bos boss;*/


/*ypedef struct//胃酸
{
  Sint16 flg,
    posX,
    posY,
    spd;
}trap;
extern trap traps[t_max];

typedef struct//扉の変数
{
  Sint16 posX,//像の位置Ｘ
    posY,//像の位置Ｙ
    hp;
}zou;
extern zou zous;

typedef struct//物の変数
{
  Sint16 posX,//位置Ｘ
    posY,//位置Ｙ
    flg;
}object;
extern object obj;*/
#endif
