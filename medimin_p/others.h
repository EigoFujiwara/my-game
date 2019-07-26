#include <libcwiimote/wiimote.h>// Wiiリモコンを用いるために必要なヘッダファイル
#include <libcwiimote/wiimote_api.h>// Wiiリモコンを用いるために必要なヘッダファイル

#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#include"SDL/SDL_mixer.h"
//#include"SDL/SDL_ttf.h"

extern int games;//ステージ移動用変数
extern SDL_Surface *mWIN;
extern int wii;//wiiコマンド変数
extern int finish;//１なら終了
extern SDL_Thread *thr;//wiiスレッド
extern wiimote_t wiimote;// Wiiリモコンの状態格納用 
extern SDL_Rect R1UB;//バネジャンで共有変数にしようとした
extern int endFlag;
extern SDL_TimerID timer_id;
extern int clientnum;
extern int clear1,clear2;

void startUp();//初期化等
//int thread(void* args);//wiiスレッド
void frames();//無視
void clear();//ゲームクリア
Uint32 Etimer(Uint32 interval);
//効果音
//void LoadSound();
//void playSE(int num);
//画像読み込み
void imageLoad();//画像読み込み
//背景表示関数
void backGraund();//タイトル
void backGraund2();//ゲーム背景
void backGraund3();//次ステージ遷移背景
void backGraund4();//クリア背景

//マップチップ表示関数
void mapSrc(Sint16 num, Sint16 poX, Sint16 poY);//マップチップをサーフェイスに
void mapDrw();//実際にマップチップ実費
void map_reset();
Uint32 damage(Uint32 interval);
Uint32 move_r(Uint32 interval);
//ステージ移動の時使う
void resets();//ステージ移動のとき自機位置などリセット
void startGame();//初期化
void continue_game();//次のステージへ進むよう
//時期の関数
void me_src(Sint16 posX, Sint16 posY, int lop);//自機サーフェイス
void me_move();//はみ出さないよう
void me_mg(int lop);//重力
void me_janp();
void me_revive();//復活
void me_Bjanp();
//メインに組み込む最終的な自機関数
void me_main();//自機まとめ
//トラップ関数
void trap_srcY(Sint16 posX, Sint16 posY);
void trap_init(Sint16 posX,Sint16 posY);
void trap_main_y();
//ゲームオーバーの時
void gameover();
void backtitle();
//メインに組み込む最終的なトラップ関数
void trap_Y(Sint16 posX, Sint16 posY);
//色々な当たり判定
int hitChek_me_t();//胃酸と自機の判定予定
int hitChek_me_f(int lop);//自機とマップ判定
int hitChek_t_f(int lop);//胃酸と床の判定
int hitChek_me_e(Sint16 posX, Sint16 posY, double poX, double poY);//自機と敵判定予定
//敵の関数
void enemys_src(double posX, double posY, int lop);
void enemys_mainY(double posX,double posY);//敵のまとめ

#define me_max 4
#define t_max 6
#define en_max 5
#define img_max 26
#define REC 48 //マップチップ大きさ
#define SIZE_Y 20//マップチップ配置の最大値ｙ
#define SIZE_X 35//x
#define PAI 3.1415926f//無視
#define txt_max 7//無視
#define M_max 7//無視

typedef struct
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
         J_max,//ジャンプ限界
         dir,//方向
         S_move,//ステージ移動用
         flag,//自機フラグ
         BJ_max,
         Bjanp,//無視
         clear1,
         clear2;
}ziki;
extern ziki mes[me_max];

typedef struct //敵用の変数
{
  double flg,cnt;//フラグ、再検出のカウンタ
  double poX,poY,//現在地
    moX,moY,//移動量
    spd,rot,//スピードと弾の角度
    tar,
    change;    //ターゲットの方向
}enemy;
extern enemy enemys[en_max];


typedef struct//胃酸
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
extern object obj;






