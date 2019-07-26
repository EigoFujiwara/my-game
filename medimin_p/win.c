#include "client.h"
#include "headers.h"
//ここで宣言
int games;//ステージ移動変数
int wii;//wiiリモコン変数
SDL_Rect R1UB;//バネじゃん用
SDL_Surface *mWIN;//ウインドウ
SDL_Surface *image[img_max];//画像格納
SDL_Thread *thr2;//使ってないから無視
SDL_TimerID timer_id;
//構造体宣言
ziki mes[];
trap traps[];
enemy enemys[en_max];
zou zous;
timers timer;
int clientnum;
int clear1 , clear2;

//0=空白
//1=床、壁
//2=即死床
//3=ボタン
//4=押されたボタン
//5=3を押している間消えるブロック
//6=3を押している間出現するブロック
//7=ばね
//8=ゴール
//9=鍵のかかったゴール
//12=移動する床
//14=15=鍵
Sint16 maps1[SIZE_Y][SIZE_X]=
{
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,6,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,3,0,0,0,0,0,0,0,5,5,5,0,5,5,0,0,0,0,8,0},
 {2,2,1,5,5,5,0,0,1,1,1,1,2,1,1,1,1,1,5,5,5,5,1,2,2,2,2,2,2,2,1,1,1,1,1},
 {2,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,2,1,1,1,0,0,0,0},
 {2,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,7,0,0,0,0,0,2,2,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,2,0,0,0},
 {0,0,0,0,0,5,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,5,0,0,0},
 {0,0,0,0,5,5,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,3,5,5,5,1,1,1,2,1,0,0,0,0,0,0,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0},
 {2,1,1,2,2,2,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,3,0},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,7,0,0,0,5,5,1,5},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,0,0,0,6,0,0,0,0,1,1,0,0,1,2,2,2},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,1,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,0,0,1,0,0,0,0,0,0,1,2,1,1,1,0,0,0,0,0,0,0,6,0,0,0,0,0,0,7,0,0,0,0,0},
 {1,1,1,1,2,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,1,1,1,1,2,2,1,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};
Sint16 maps2[SIZE_Y][SIZE_X]=
{
 {0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {15,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,14,0},
 {1,1,1,0,0,0,0,0,0,0,0,1,0,1,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
 {0,0,0,6,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,12,12,0,1,0,1},
 {0,0,0,0,6,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,12,12,12,0,0,0,0,0,0,1},
 {0,0,0,0,0,6,0,0,0,1,1,1,0,9,0,0,1,1,1,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1},
 {1,0,1,0,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
 {1,0,0,0,0,0,0,0,0,1,1,0,0,0,6,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
 {1,1,0,0,0,0,0,0,0,1,1,0,0,0,6,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1},
 {1,1,0,0,0,0,0,0,0,1,1,0,0,0,6,0,0,0,0,0,0,0,3,1,1,0,0,1,1,0,0,0,0,0,1},
 {1,1,1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,1,1,1,0,0,0,0,0,1,1,0,0,1},
 {1,1,1,0,0,0,1,0,0,0,0,0,0,1,0,5,5,5,5,5,5,5,5,1,1,0,0,0,0,0,0,0,0,0,1},
 {1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,6,6,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,0,0,0,0,1,1,2,1,1,1,1,1,0,0,0,1},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,0,0,0,0,1,5,5,5,5,5,5,0,0,0,1},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
 {0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,6,6,0,0,0,0,0,0,0,0,0,0,0,0,1},
 {0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,3,0,1},
 {1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1},
};
void startUp()//画像読み込み等,初期化
{
if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO) < 0)
SDL_Quit();
Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
mWIN=SDL_SetVideoMode(1680,960,32,SDL_SWSURFACE);
SDL_WM_SetCaption("actiongame",NULL);
games=1;
imageLoad();
//LoadSound();
backGraund();
SDL_UpdateRect(mWIN,0,0,0,0);
timer_id = SDL_AddTimer(500,damage,NULL);
}

void frames()//無視
{
timer.now=SDL_GetTicks();//現在時間を取得
timer.wit=timer.now-timer.lev;//待ち時間を計算

if(timer.wit<16)
   SDL_Delay(16-timer.wit);//16以下ならCPUを休ませる

timer.lev=SDL_GetTicks();//経過時間を更新
SDL_UpdateRect(mWIN,0,0,0,0);//画面を更新
}

void clear()//ゲームクリア時
{
   switch(clientnum){
     case 1:
    if(mes[0].S_move == 1){
  //SDL_FillRect(mWIN,NULL,SDL_MapRGB(mWIN->format,0,0,0));
  //メッセージ
  //ステージ移動音(ファンファーレ)
Mix_HaltMusic();
Mix_Chunk *chunk2;
chunk2 = Mix_LoadWAV("chunk_clear.wav");
if(Mix_Playing(2) == 0)
	Mix_PlayChannel(2, chunk2, 0);
  backGraund4();
  SDL_UpdateRect(mWIN,0,0,0,0);
  SDL_Delay(2000);
  endFlag = 0;
 }
  break;
    case 2:
    if(mes[0].S_move == 1 && mes[1].S_move == 1){
  //SDL_FillRect(mWIN,NULL,SDL_MapRGB(mWIN->format,0,0,0));
  //メッセージ
  //ステージ移動音(ファンファーレ)
Mix_HaltMusic();
Mix_Chunk *chunk2;
chunk2 = Mix_LoadWAV("chunk_clear.wav");
if(Mix_Playing(2) == 0)
	Mix_PlayChannel(2, chunk2, 0);
  backGraund4();
  SDL_UpdateRect(mWIN,0,0,0,0);
  SDL_Delay(2000);
  endFlag = 0;
 }
  break;
    case 3:
    if(mes[0].S_move == 1 && mes[1].S_move == 1 && mes[2].S_move == 1){
  //SDL_FillRect(mWIN,NULL,SDL_MapRGB(mWIN->format,0,0,0));
  //メッセージ
  //ステージ移動音(ファンファーレ)
Mix_HaltMusic();
Mix_Chunk *chunk2;
chunk2 = Mix_LoadWAV("chunk_clear.wav");
if(Mix_Playing(2) == 0)
	Mix_PlayChannel(2, chunk2, 0);
  backGraund4();
  SDL_UpdateRect(mWIN,0,0,0,0);
  SDL_Delay(2000);
  endFlag = 0;
 }
  break;
    case 4:
    if(mes[0].S_move == 1 && mes[1].S_move == 1 && mes[2].S_move == 1 && mes[3].S_move == 1){
  //SDL_FillRect(mWIN,NULL,SDL_MapRGB(mWIN->format,0,0,0));
  //メッセージ
  //ステージ移動音(ファンファーレ)
Mix_HaltMusic();
Mix_Chunk *chunk2;
chunk2 = Mix_LoadWAV("chunk_clear.wav");
if(Mix_Playing(2) == 0)
	Mix_PlayChannel(2, chunk2, 0);
  backGraund4();
  SDL_UpdateRect(mWIN,0,0,0,0);
  SDL_Delay(2000);
  endFlag = 0;
 }
  break;
  default:
  break;
 }
}
 

void imageLoad()//画像読み込み
{
image[0] = IMG_Load("map.png");
if(!image[0])   printf("IMG_Load: %s\n", IMG_GetError());
image[1] = IMG_Load("Image_kapuseru_l.png");
if(!image[1])   SDL_Quit();
image[2] = IMG_Load("Image_kapuseru.png");
if(!image[2])   SDL_Quit();
image[3] = IMG_Load("med.jpg");
if(!image[3])   SDL_Quit();
image[4] = IMG_Load("haikei.png");
if(!image[4])   SDL_Quit();
image[5] = IMG_Load("file1-2.png");
if(!image[5])   printf("IMG_Load: %s\n", IMG_GetError());
image[6] = IMG_Load("file-3.png");
if(!image[6])   SDL_Quit();
image[7] = IMG_Load("file5.png");
if(!image[7])   printf("IMG_Load: %s\n", IMG_GetError());
image[8] = IMG_Load("file4.png");
if(!image[8])   SDL_Quit();
image[9] = IMG_Load("file7.png");
if(!image[9])   SDL_Quit();
image[10] = IMG_Load("file6.png");
if(!image[10])   SDL_Quit();
image[11] = IMG_Load("nextstage.png");
if(!image[11])   SDL_Quit();
image[12] = IMG_Load("Image-7.png");
if(!image[12])   SDL_Quit();
image[13] = IMG_Load("enemy.png");
if(!image[13])   SDL_Quit();
image[14] = IMG_Load("clear.png");
if(!image[14])   SDL_Quit();
image[15] = IMG_Load("dead.png");
if(!image[15])   SDL_Quit();
}


void backGraund()//タイトル背景
{
SDL_Rect src_rect = {0, 0, 1680, 960};
SDL_Rect dst_rect = {0, 0};
SDL_BlitSurface(image[3], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}

void backGraund2()//ゲーム背景
{
SDL_Rect src_rect = {0, 0, 1680, 960};
SDL_Rect dst_rect = {0, 0};
SDL_BlitSurface(image[4], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}

void backGraund3()//ゲーム背景
{
SDL_Rect src_rect = {0, 0, 1680, 960};
SDL_Rect dst_rect = {0, 0};
SDL_BlitSurface(image[11], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}

void backGraund4()//クリア背景
{
SDL_Rect src_rect = {0, 0, 1680, 960};
SDL_Rect dst_rect = {0, 0};
SDL_BlitSurface(image[14], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}


void mapSrc(Sint16 num,Sint16 poX,Sint16 poY)//マップチップ読み込み,サーフェイスに貼り付け
{
  SDL_Rect src,drw;
  src.x=num*REC;  src.y=0;      
  src.w=REC; src.h=REC;
  drw.x=poX;      drw.y=poY;
  SDL_BlitSurface(image[0],&src,SDL_GetVideoSurface(),&drw);
}

void mapDrw()//実際に配置
{
  Sint16 poX,poY;
  if(games == 1){
  for(poY=0;  poY<SIZE_Y;  poY++)
    for(poX=0;  poX<SIZE_X;  poX++)
      mapSrc(maps1[poY][poX], poX*REC, poY*REC);
  }
  if(games == 2){
    for(poY=0;  poY<SIZE_Y;  poY++)
      for(poX=0;  poX<SIZE_X;  poX++)
	mapSrc(maps2[poY][poX], poX*REC, poY*REC);
  }

}

void resets()//ステージ移動のときリセット
{
  int trap, lop;
  int num = 60;
  for(lop=0; lop<me_max; lop++){
  mes[lop].posX=num; mes[lop].posY=860;//自機の初期座標
  mes[lop].J_flag = 0;
  mes[lop].flag = 1;
  mes[lop].Bjanp = 0;
  mes[lop].S_move = 0;
  mes[lop].clear1 = 0;
  mes[lop].clear2 = 0;
  num += 5;
  }
  clear1 = 0;
  clear2 = 0;
  for(trap=0; trap<t_max; trap++){
    traps[trap].flg=0;
  }
  map_reset();
  //change = 0;
   enemys[0].flg=0;//1体目
  enemys[0].change = 0;
  //change = 0;
 enemys[0].poX=90;
 enemys[0].poY=350;
enemys[1].flg=0;//２体目
  enemys[1].change = 0;
  //change = 0;
 enemys[1].poX=340;
 enemys[1].poY=10;
enemys[2].flg=0;//３体目
  enemys[2].change = 0;
  //change = 0;
 enemys[2].poX=1500;
 enemys[2].poY=390;
enemys[3].flg=0;//４体目
  enemys[3].change = 0;
  //change = 0;
 enemys[3].poX=1500;
 enemys[3].poY=520;
enemys[4].flg=0;//５体目
  enemys[4].change = 0;
  //change = 0;
 enemys[4].poX=380;
 enemys[4].poY=480;
}

void startGame()//ゲーム開始初期化
{
  int lop;
    games = 1;
    for(lop=0; lop<me_max; lop++){
    mes[lop].J_flag = 0;
    me_src(mes[lop].posX, mes[lop].posY, lop);
    mes[lop].dir = 1;
   }
   backGraund2();
  resets();
}

void continue_game()//ステージ移動のとき
{
  switch(clientnum){
    case 1:
  if(mes[0].S_move == 1){
  //メッセージ
  //ステージ移動音(ファンファーレ)
Mix_HaltMusic();
Mix_Chunk *chunk2;
chunk2 = Mix_LoadWAV("chunk_clear.wav");
if(Mix_Playing(2) == 0)
	Mix_PlayChannel(2, chunk2, 0);
  backGraund3();
  SDL_UpdateRect(mWIN,0,0,0,0);//画面を更新
   SDL_Delay(2000);
  resets();
  games += 1;

 Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
Mix_Music *music;
music = Mix_LoadMUS("music.mp3");
Mix_PlayMusic(music,-1);
Mix_VolumeMusic(60);
  }
  break;
  case 2:
  if(mes[0].S_move == 1 && mes[1].S_move == 1){
  //メッセージ
  //ステージ移動音(ファンファーレ)
Mix_HaltMusic();
Mix_Chunk *chunk2;
chunk2 = Mix_LoadWAV("chunk_clear.wav");
if(Mix_Playing(2) == 0)
	Mix_PlayChannel(2, chunk2, 0);
  backGraund3();
  SDL_UpdateRect(mWIN,0,0,0,0);//画面を更新
   SDL_Delay(2000);
  resets();
  games += 1;
Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
Mix_Music *music;
music = Mix_LoadMUS("music.mp3");
Mix_PlayMusic(music,-1);
Mix_VolumeMusic(60);
  }
  break;
   case 3:
  if(mes[0].S_move == 1 && mes[1].S_move == 1 && mes[2].S_move == 1){
  //メッセージ
  //ステージ移動音(ファンファーレ)
Mix_HaltMusic();
Mix_Chunk *chunk2;
chunk2 = Mix_LoadWAV("chunk_clear.wav");
if(Mix_Playing(2) == 0)
	Mix_PlayChannel(2, chunk2, 0);
  backGraund3();
  SDL_UpdateRect(mWIN,0,0,0,0);//画面を更新
   SDL_Delay(2000);
  resets();
  games += 1;
Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
Mix_Music *music;
music = Mix_LoadMUS("music.mp3");
Mix_PlayMusic(music,-1);
Mix_VolumeMusic(60);
  }
 break;
   case 4:
  if(mes[0].S_move == 1 && mes[1].S_move == 1 && mes[2].S_move == 1 && mes[3].S_move == 1){
  //メッセージ
  //ステージ移動音(ファンファーレ)
Mix_HaltMusic();
Mix_Chunk *chunk2;
chunk2 = Mix_LoadWAV("chunk_clear.wav");
if(Mix_Playing(2) == 0)
	Mix_PlayChannel(2, chunk2, 0);
  backGraund3();
  SDL_UpdateRect(mWIN,0,0,0,0);//画面を更新
   SDL_Delay(2000);
  resets();
  games += 1;
Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
Mix_Music *music;
music = Mix_LoadMUS("music.mp3");
Mix_PlayMusic(music,-1);
Mix_VolumeMusic(60);
  }
 break;
 default:
 break;
 }
}
    

void me_src(Sint16 posX, Sint16 posY, int lop)//自機サーフェイス貼り付け
{
  SDL_Rect src_rect = {0, 0, 50, 50};
  SDL_Rect dst_rect = {posX, posY};
  if(mes[lop].flag == 1){
  switch (lop){
  case 0:
  switch (mes[lop].dir){//wiiコマンド右のとき左のときで右向き左向き決定
  case 1: SDL_BlitSurface(image[1], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 4: SDL_BlitSurface(image[1], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 5: SDL_BlitSurface(image[2], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  }break;
  case 1:
  switch (mes[lop].dir){//wiiコマンド右のとき左のときで右向き左向き決定
  case 1: SDL_BlitSurface(image[5], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 4: SDL_BlitSurface(image[5], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 5: SDL_BlitSurface(image[6], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
   }break;
    case 2:
  switch (mes[lop].dir){//wiiコマンド右のとき左のときで右向き左向き決定
  case 1: SDL_BlitSurface(image[7], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 4: SDL_BlitSurface(image[7], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 5: SDL_BlitSurface(image[8], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
   }break;
    case 3:
  switch (mes[lop].dir){//wiiコマンド右のとき左のときで右向き左向き決定
  case 1: SDL_BlitSurface(image[9], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 4: SDL_BlitSurface(image[9], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 5: SDL_BlitSurface(image[10], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  }break;
 }
}
 if(mes[lop].flag <= 0){
  SDL_BlitSurface(image[15], &src_rect, SDL_GetVideoSurface(), &dst_rect);
  }
}

void me_move()//ウインドウからはみ出さないように+地面に着地したらジャンプできるように
{
 int lop;
    for(lop=0; lop<me_max; lop++){
  if(mes[lop].posX<=0)
    mes[lop].posX=0;//画面からはみ出さないようにする
  else if(mes[lop].posX>=1640)
    mes[lop].posX=1640;
  if(mes[lop].posY<=0){
    mes[lop].posY=0;//画面からはみ出さないようにする   
     mes[lop].J_flag = 2;
   }                           
  else if(mes[lop].posY>=912)
    mes[lop].posY=900;
  if(mes[lop].posY == 900)
     mes[lop].J_flag = 0;
 }
}


Uint32 damage(Uint32 interval){//床のアニメーション
 Sint16 poX,poY;
for(poY=0;  poY<SIZE_Y;  poY++){
    for(poX=0;  poX<SIZE_X;  poX++){
if(maps1[poY][poX] == 2)
maps1[poY][poX] = 16;
else if(maps1[poY][poX] == 16 )
maps1[poY][poX] = 17 ;
else if(maps1[poY][poX] == 17 )
maps1[poY][poX] = 18 ;
else if(maps1[poY][poX] == 18)
maps1[poY][poX] = 2;

else if(maps1[poY][poX] == 12)
maps1[poY][poX] = 19;
else if(maps1[poY][poX] == 19)
maps1[poY][poX] = 20;
else if (maps1[poY][poX] == 20)
maps1[poY][poX] = 21;
else if (maps1[poY][poX] == 21)
maps1[poY][poX] = 12;

if(maps2[poY][poX] == 2)
maps2[poY][poX] = 16;
else if(maps2[poY][poX] == 16 )
maps2[poY][poX] = 17 ;
else if(maps2[poY][poX] == 17 )
maps2[poY][poX] = 18 ;
else if(maps2[poY][poX] == 18)
maps2[poY][poX] = 2;

else if(maps2[poY][poX] == 12)
maps2[poY][poX] = 19;
else if(maps2[poY][poX] == 19)
maps2[poY][poX] = 20;
else if (maps2[poY][poX] == 20)
maps2[poY][poX] = 21;
else if (maps2[poY][poX] == 21)
maps2[poY][poX] = 12;
}

}
return interval;
}

int hitChek_me_f(int lop)//マップチップと自機との判定色々
{
  Sint16 poX,poY;
 if(games == 1){//ステージ１
  for(poY=0;  poY<SIZE_Y;  poY++)
    for(poX=0;  poX<SIZE_X;  poX++)
 if(maps1[poY][poX] == 1 || maps1[poY][poX] == 6 || maps1[poY][poX] == 11 || maps1[poY][poX] == 26){//床のとき
   SDL_Rect R1L,R1R,R1U,R1D,R2L,R2R,R2U,R2D;
  R1L.x=poX*REC;      R1L.y=poY*REC;      R1L.w=10;  R1L.h=REC;//左側の細胞の位置
  R1R.x=poX*REC + 38;      R1R.y=poY*REC;      R1R.w=10;  R1R.h=REC;//右側の細胞の位置
  R1U.x=poX*REC;      R1U.y=poY*REC;      R1U.w=48;  R1U.h=20;//上側の細胞の位置
  R1D.x=poX*REC + 1;      R1D.y=poY*REC + 38;      R1D.w=46;  R1D.h=10;//下側の細胞の位置
  R2L.x=mes[lop].posX+20;  R2L.y=mes[lop].posY+15;  R2L.w=10;  R2L.h=25;//自分の位置
  R2R.x=mes[lop].posX+20;  R2R.y=mes[lop].posY+15;  R2R.w=10;  R2R.h=25;//自分の位置
  R2U.x=mes[lop].posX+20;  R2U.y=mes[lop].posY+40;  R2U.w=10;  R2U.h=10;//自分の位置
  R2D.x=mes[lop].posX+20;  R2D.y=mes[lop].posY+5;  R2D.w=10;  R2D.h=15;//自分の位置
  if( (R1L.x<(R2L.x+R2L.w)) && (R2L.x<(R1L.x+R1L.w)) &&
      (R1L.y<(R2L.y+R2L.h)) && (R2L.y<(R1L.y+R1L.h)) ) {
     mes[lop].posX = R1L.x - 30;
       }
  if( (R1R.x<(R2R.x+R2R.w)) && (R2R.x<(R1R.x+R1R.w)) &&
      (R1R.y<(R2R.y+R2R.h)) && (R2R.y<(R1R.y+R1R.h)) ) {
     mes[lop].posX = R1R.x - 10;
       }
  if( (R1U.x<(R2U.x+R2U.w)) && (R2U.x<(R1U.x+R1U.w)) &&
      (R1U.y<(R2U.y+R2U.h)) && (R2U.y<(R1U.y+R1U.h)) ) {
     mes[lop].posY = R1U.y - 45;
     mes[lop].J_max = mes[lop].posY;
     mes[lop].Bjanp = 0;
     return 1;
       }
  if( (R1D.x<(R2D.x+R2D.w)) && (R2D.x<(R1D.x+R1D.w)) &&
      (R1D.y<(R2D.y+R2D.h)) && (R2D.y<(R1D.y+R1D.h)) ) {
     mes[lop].posY = R1D.y + 10;
     mes[lop].J_flag = 2;
     mes[lop].Bjanp = 0;
       }
      }
  else if(maps1[poY][poX] == 2|| maps1[poY][poX] == 16 || maps1[poY][poX] == 17 || maps1[poY][poX] == 18){//即死床ののとき
    SDL_Rect R1L,R1R,R1U,R1D,R2L,R2R,R2U,R2D;
  R1L.x=poX*REC;      R1L.y=poY*REC;      R1L.w=10;  R1L.h=REC;//左側の細胞の位置
  R1R.x=poX*REC + 38;      R1R.y=poY*REC;      R1R.w=10;  R1R.h=REC;//右側の細胞の位置
  R1U.x=poX*REC;      R1U.y=poY*REC;      R1U.w=48;  R1U.h=20;//上側の細胞の位置
  R1D.x=poX*REC + 2;      R1D.y=poY*REC + 45;      R1D.w=44;  R1D.h=4;//下側の細胞の位置
  R2L.x=mes[lop].posX+20;  R2L.y=mes[lop].posY+15;  R2L.w=10;  R2L.h=25;//自分の位置
  R2R.x=mes[lop].posX+20;  R2R.y=mes[lop].posY+15;  R2R.w=10;  R2R.h=25;//自分の位置
  R2U.x=mes[lop].posX+20;  R2U.y=mes[lop].posY+40;  R2U.w=10;  R2U.h=10;//自分の位置
  R2D.x=mes[lop].posX+20;  R2D.y=mes[lop].posY+5;  R2D.w=10;  R2D.h=10;//自分の位置
  if( (R1L.x<(R2L.x+R2L.w)) && (R2L.x<(R1L.x+R1L.w)) &&
      (R1L.y<(R2L.y+R2L.h)) && (R2L.y<(R1L.y+R1L.h)) ) {
     mes[lop].posX = R1L.x - 30;
     mes[lop].flag -= 1;
  	Mix_Chunk *chunk4;
	chunk4 = Mix_LoadWAV("chunk_gameover.wav");
if(Mix_Playing(4) == 0){
	Mix_PlayChannel(4, chunk4, 0);
    }
     SDL_Delay(300);
   }
  if( (R1R.x<(R2R.x+R2R.w)) && (R2R.x<(R1R.x+R1R.w)) &&
      (R1R.y<(R2R.y+R2R.h)) && (R2R.y<(R1R.y+R1R.h)) ) {
     mes[lop].posX = R1R.x - 20;
     mes[lop].flag -= 1;
	Mix_Chunk *chunk4;
	chunk4 = Mix_LoadWAV("chunk_gameover.wav");
if(Mix_Playing(4) == 0){
	Mix_PlayChannel(4, chunk4, 0);
  }
     SDL_Delay(300);
  }
  if( (R1U.x<(R2U.x+R2U.w)) && (R2U.x<(R1U.x+R1U.w)) &&
      (R1U.y<(R2U.y+R2U.h)) && (R2U.y<(R1U.y+R1U.h)) ) {
     mes[lop].posY = R1U.y - 45;
     mes[lop].flag -= 1;
     //死亡音
	Mix_Chunk *chunk4;
	chunk4 = Mix_LoadWAV("chunk_gameover.wav");
if(Mix_Playing(4) == 0){
	Mix_PlayChannel(4, chunk4, 0);
}
SDL_Delay(300);
       }
  if( (R1D.x<(R2D.x+R2D.w)) && (R2D.x<(R1D.x+R1D.w)) &&
      (R1D.y<(R2D.y+R2D.h)) && (R2D.y<(R1D.y+R1D.h)) ) {
     mes[lop].posY = R1D.y;
     mes[lop].flag -= 1;
	Mix_Chunk *chunk4;
	chunk4 = Mix_LoadWAV("chunk_gameover.wav");
if(Mix_Playing(4) == 0){
	Mix_PlayChannel(4, chunk4, 0);
    }
       SDL_Delay(300);
    }
    }

  else if(maps1[poY][poX] == 3){//スイッチのとき
    SDL_Rect R1L,R1R,R1U,R1D,R2L,R2R,R2U,R2D;
  R1L.x=poX*REC;      R1L.y=poY*REC;      R1L.w=10;  R1L.h=REC;//左側の細胞の位置
  R1R.x=poX*REC + 38;      R1R.y=poY*REC;      R1R.w=10;  R1R.h=REC;//右側の細胞の位置
  R1U.x=poX*REC;      R1U.y=poY*REC;      R1U.w=48;  R1U.h=20;//上側の細胞の位置
  R1D.x=poX*REC + 2;      R1D.y=poY*REC + 45;      R1D.w=44;  R1D.h=4;//下側の細胞の位置
  R2L.x=mes[lop].posX+20;  R2L.y=mes[lop].posY+15;  R2L.w=10;  R2L.h=25;//自分の位置
  R2R.x=mes[lop].posX+20;  R2R.y=mes[lop].posY+15;  R2R.w=10;  R2R.h=25;//自分の位置
  R2U.x=mes[lop].posX+20;  R2U.y=mes[lop].posY+40;  R2U.w=10;  R2U.h=10;//自分の位置
  R2D.x=mes[lop].posX+20;  R2D.y=mes[lop].posY+5;  R2D.w=10;  R2D.h=10;//自分の位置
  if( (R1L.x<(R2L.x+R2L.w)) && (R2L.x<(R1L.x+R1L.w)) &&
      (R1L.y<(R2L.y+R2L.h)) && (R2L.y<(R1L.y+R1L.h)) ) {
     mes[lop].posX = R1L.x - 30;
       }
  if( (R1R.x<(R2R.x+R2R.w)) && (R2R.x<(R1R.x+R1R.w)) &&
      (R1R.y<(R2R.y+R2R.h)) && (R2R.y<(R1R.y+R1R.h)) ) {
     mes[lop].posX = R1R.x - 20;
       }
  if( (R1U.x<(R2U.x+R2U.w)) && (R2U.x<(R1U.x+R1U.w)) &&
      (R1U.y<(R2U.y+R2U.h)) && (R2U.y<(R1U.y+R1U.h)) ) {
     mes[lop].posY = R1U.y - 45;
     maps1[poY][poX] = 4;
 
     //スイッチ押した音
    Mix_Chunk *chunk1;
	chunk1 = Mix_LoadWAV("chunk_switch.wav");
if(Mix_Playing(1) == 0)
	Mix_PlayChannel(1, chunk1, 0);

        for(poY=0;  poY<SIZE_Y;  poY++)
    for(poX=0;  poX<SIZE_X;  poX++)
      if(maps1[poY][poX] == 5){
          maps1[poY][poX] = 11;
          }
     else if(maps1[poY][poX] == 11){
          maps1[poY][poX] = 10;
          }
     else if(maps1[poY][poX] == 10){
          maps1[poY][poX] = 11;
          }
     else if(maps1[poY][poX] == 6){
          maps1[poY][poX] = 25;
          }
     else if(maps1[poY][poX] == 25){
          maps1[poY][poX] = 26;
          }
     else if(maps1[poY][poX] == 26){
          maps1[poY][poX] = 25;
          }
       }
  if( (R1D.x<(R2D.x+R2D.w)) && (R2D.x<(R1D.x+R1D.w)) &&
      (R1D.y<(R2D.y+R2D.h)) && (R2D.y<(R1D.y+R1D.h)) ) {
     mes[lop].posY = R1D.y;
    }
 }
else if(maps1[poY][poX] == 7){ //バネのとき
  SDL_Rect R1L,R1R,R1UB,R1UBs,R1D,R2L,R2R,R2U,R2D;
  R1L.x=poX*REC;      R1L.y=poY*REC;      R1L.w=10;  R1L.h=REC;//左側の細胞の位置
  R1R.x=poX*REC + 38;      R1R.y=poY*REC;      R1R.w=10;  R1R.h=REC;//右側の細胞の位置
  R1UB.x=poX*REC;      R1UB.y=poY*REC + 15;      R1UB.w=48;  R1UB.h=10;//上側の細胞の位置　バネ判定

  R1UBs.x=poX*REC;     R1UBs.y=poY*REC;     R1UBs.w=48; R1UBs.h=10;//上側の細胞の位置　音判定

  R1D.x=poX*REC + 2;      R1D.y=poY*REC + 45;      R1D.w=44;  R1D.h=4;//下側の細胞の位置
  R2L.x=mes[lop].posX+20;  R2L.y=mes[lop].posY+15;  R2L.w=10;  R2L.h=25;//自分の位置
  R2R.x=mes[lop].posX+20;  R2R.y=mes[lop].posY+15;  R2R.w=10;  R2R.h=25;//自分の位置
  R2U.x=mes[lop].posX+20;  R2U.y=mes[lop].posY+40;  R2U.w=10;  R2U.h=10;//自分の位置
  R2D.x=mes[lop].posX+20;  R2D.y=mes[lop].posY+5;  R2D.w=10;  R2D.h=10;//自分の位置
  if( (R1L.x<(R2L.x+R2L.w)) && (R2L.x<(R1L.x+R1L.w)) &&
      (R1L.y<(R2L.y+R2L.h)) && (R2L.y<(R1L.y+R1L.h)) ) {
     mes[lop].posX = R1L.x - 30;
       }
  if( (R1R.x<(R2R.x+R2R.w)) && (R2R.x<(R1R.x+R1R.w)) &&
      (R1R.y<(R2R.y+R2R.h)) && (R2R.y<(R1R.y+R1R.h)) ) {
     mes[lop].posX = R1R.x - 20;
       }
  if( (R1UB.x<(R2U.x+R2U.w)) && (R2U.x<(R1UB.x+R1UB.w)) &&
      (R1UB.y<(R2U.y+R2U.h)) && (R2U.y<(R1UB.y+R1UB.h)) ) {
      mes[lop].Bjanp = 1;
     mes[lop].J_flag = 0;
    return 9;
}
     
if( (R1UBs.x<(R2U.x+R2U.w)) && (R2U.x<(R1UBs.x+R1UBs.w)) &&
      (R1UBs.y<(R2U.y+R2U.h)) && (R2U.y<(R1UBs.y+R1UBs.h)) ) {
     //バネ踏んだ音
Mix_Chunk *chunk3;
	chunk3 = Mix_LoadWAV("chunk_spring.wav");
if(Mix_Playing(3) == 0)
	Mix_PlayChannel(3, chunk3, 0);
}
  if( (R1D.x<(R2D.x+R2D.w)) && (R2D.x<(R1D.x+R1D.w)) &&
      (R1D.y<(R2D.y+R2D.h)) && (R2D.y<(R1D.y+R1D.h)) ) {
     mes[lop].posY = R1D.y;
 }
 }
 else if(maps1[poY][poX] == 8){ //扉のとき
  SDL_Rect R1,R2;
  R1.x=poX*REC;      R1.y=poY*REC;      R1.w=REC;  R1.h=REC;//左側の細胞の位置
  R2.x=mes[lop].posX+20;  R2.y=mes[lop].posY+15;  R2.w=10;  R2.h=25;//自分の位置
  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
      (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
     mes[lop].S_move = 1;
       }
 }

else if(maps1[poY][poX] == 12 || maps1[poY][poX] == 19 || maps1[poY][poX] == 20 || maps1[poY][poX] == 21){//移動床のとき
   SDL_Rect R1L,R1R,R1U,R1D,R2L,R2R,R2U,R2D;
  R1L.x=poX*REC;      R1L.y=poY*REC;      R1L.w=10;  R1L.h=REC;//左側の細胞の位置
  R1R.x=poX*REC + 38;      R1R.y=poY*REC;      R1R.w=10;  R1R.h=REC;//右側の細胞の位置
  R1U.x=poX*REC;      R1U.y=poY*REC;      R1U.w=48;  R1U.h=10;//上側の細胞の位置
  R1D.x=poX*REC + 1;      R1D.y=poY*REC + 38;      R1D.w=46;  R1D.h=10;//下側の細胞の位置
  R2L.x=mes[lop].posX+20;  R2L.y=mes[lop].posY+15;  R2L.w=10;  R2L.h=25;//自分の位置
  R2R.x=mes[lop].posX+20;  R2R.y=mes[lop].posY+15;  R2R.w=10;  R2R.h=25;//自分の位置
  R2U.x=mes[lop].posX+20;  R2U.y=mes[lop].posY+40;  R2U.w=10;  R2U.h=10;//自分の位置
  R2D.x=mes[lop].posX+20;  R2D.y=mes[lop].posY+5;  R2D.w=10;  R2D.h=15;//自分の位置
  if( (R1L.x<(R2L.x+R2L.w)) && (R2L.x<(R1L.x+R1L.w)) &&
      (R1L.y<(R2L.y+R2L.h)) && (R2L.y<(R1L.y+R1L.h)) ) {
     mes[lop].posX = R1L.x - 30;
       }
  if( (R1R.x<(R2R.x+R2R.w)) && (R2R.x<(R1R.x+R1R.w)) &&
      (R1R.y<(R2R.y+R2R.h)) && (R2R.y<(R1R.y+R1R.h)) ) {
     mes[lop].posX = R1R.x - 10;
       }
  if( (R1U.x<(R2U.x+R2U.w)) && (R2U.x<(R1U.x+R1U.w)) &&
      (R1U.y<(R2U.y+R2U.h)) && (R2U.y<(R1U.y+R1U.h)) ) {
     mes[lop].posY = R1U.y - 45;
     mes[lop].J_max = mes[lop].posY;
     mes[lop].Bjanp = 0;
     return 5;
       }
  if( (R1D.x<(R2D.x+R2D.w)) && (R2D.x<(R1D.x+R1D.w)) &&
      (R1D.y<(R2D.y+R2D.h)) && (R2D.y<(R1D.y+R1D.h)) ) {
     mes[lop].posY = R1D.y + 10;
     mes[lop].J_flag = 2;
     mes[lop].Bjanp = 0;
       }
      }

 else if(maps1[poY][poX] == 14){ //青鍵のとき
  SDL_Rect R1,R2;
  R1.x=poX*REC;      R1.y=poY*REC;      R1.w=REC;  R1.h=REC;//左側の細胞の位置
  R2.x=mes[lop].posX+20;  R2.y=mes[lop].posY+15;  R2.w=10;  R2.h=25;//自分の位置
  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
      (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
    maps1[poY][poX] = 0;
	mes[lop].clear1 = 1;
	}
 }

 else if(maps1[poY][poX] == 15){ //ピンク鍵のとき
  SDL_Rect R1,R2;
  R1.x=poX*REC;      R1.y=poY*REC;      R1.w=REC;  R1.h=REC;//左側の細胞の位置
  R2.x=mes[lop].posX+20;  R2.y=mes[lop].posY+15;  R2.w=10;  R2.h=25;//自分の位置
  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
      (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
    maps1[poY][poX] = 0;
	mes[lop].clear2 = 1;
	}
 }
 }
if(games == 2){//ステージ２
  for(poY=0;  poY<SIZE_Y;  poY++)
    for(poX=0;  poX<SIZE_X;  poX++)
 if(maps2[poY][poX] == 1 || maps2[poY][poX] == 6 || maps2[poY][poX] == 11 || maps2[poY][poX] == 26){//床のとき
   SDL_Rect R1L,R1R,R1U,R1D,R2L,R2R,R2U,R2D;
  R1L.x=poX*REC;      R1L.y=poY*REC;      R1L.w=10;  R1L.h=REC;//左側の細胞の位置
  R1R.x=poX*REC + 38;      R1R.y=poY*REC;      R1R.w=10;  R1R.h=REC;//右側の細胞の位置
  R1U.x=poX*REC;      R1U.y=poY*REC;      R1U.w=48;  R1U.h=20;//上側の細胞の位置
  R1D.x=poX*REC + 1;      R1D.y=poY*REC + 38;      R1D.w=46;  R1D.h=10;//下側の細胞の位置
  R2L.x=mes[lop].posX+20;  R2L.y=mes[lop].posY+15;  R2L.w=10;  R2L.h=25;//自分の位置
  R2R.x=mes[lop].posX+20;  R2R.y=mes[lop].posY+15;  R2R.w=10;  R2R.h=25;//自分の位置
  R2U.x=mes[lop].posX+20;  R2U.y=mes[lop].posY+40;  R2U.w=10;  R2U.h=10;//自分の位置
  R2D.x=mes[lop].posX+20;  R2D.y=mes[lop].posY+5;  R2D.w=10;  R2D.h=10;//自分の位置
  if( (R1L.x<(R2L.x+R2L.w)) && (R2L.x<(R1L.x+R1L.w)) &&
      (R1L.y<(R2L.y+R2L.h)) && (R2L.y<(R1L.y+R1L.h)) ) {
     mes[lop].posX = R1L.x - 30;
       }
  if( (R1R.x<(R2R.x+R2R.w)) && (R2R.x<(R1R.x+R1R.w)) &&
      (R1R.y<(R2R.y+R2R.h)) && (R2R.y<(R1R.y+R1R.h)) ) {
     mes[lop].posX = R1R.x - 10;
       }
  if( (R1U.x<(R2U.x+R2U.w)) && (R2U.x<(R1U.x+R1U.w)) &&
      (R1U.y<(R2U.y+R2U.h)) && (R2U.y<(R1U.y+R1U.h)) ) {
     mes[lop].posY = R1U.y - 45;
     mes[lop].J_max = mes[lop].posY;
     mes[lop].Bjanp = 0;
     return 1;
       }
  if( (R1D.x<(R2D.x+R2D.w)) && (R2D.x<(R1D.x+R1D.w)) &&
      (R1D.y<(R2D.y+R2D.h)) && (R2D.y<(R1D.y+R1D.h)) ) {
     mes[lop].posY = R1D.y + 10;
     mes[lop].J_flag = 2;
     mes[lop].Bjanp = 0;
       }
      }
  else if(maps2[poY][poX] == 2|| maps2[poY][poX] == 16 || maps2[poY][poX] == 17 || maps2[poY][poX] == 18){//即死床ののとき
    SDL_Rect R1L,R1R,R1U,R1D,R2L,R2R,R2U,R2D;
  R1L.x=poX*REC;      R1L.y=poY*REC;      R1L.w=10;  R1L.h=REC;//左側の細胞の位置
  R1R.x=poX*REC + 38;      R1R.y=poY*REC;      R1R.w=10;  R1R.h=REC;//右側の細胞の位置
  R1U.x=poX*REC;      R1U.y=poY*REC;      R1U.w=48;  R1U.h=20;//上側の細胞の位置
  R1D.x=poX*REC + 2;      R1D.y=poY*REC + 45;      R1D.w=44;  R1D.h=4;//下側の細胞の位置
  R2L.x=mes[lop].posX+20;  R2L.y=mes[lop].posY+15;  R2L.w=10;  R2L.h=25;//自分の位置
  R2R.x=mes[lop].posX+20;  R2R.y=mes[lop].posY+15;  R2R.w=10;  R2R.h=25;//自分の位置
  R2U.x=mes[lop].posX+20;  R2U.y=mes[lop].posY+40;  R2U.w=10;  R2U.h=10;//自分の位置
  R2D.x=mes[lop].posX+20;  R2D.y=mes[lop].posY+5;  R2D.w=10;  R2D.h=10;//自分の位置
  if( (R1L.x<(R2L.x+R2L.w)) && (R2L.x<(R1L.x+R1L.w)) &&
      (R1L.y<(R2L.y+R2L.h)) && (R2L.y<(R1L.y+R1L.h)) ) {
     mes[lop].posX = R1L.x - 30;
     mes[lop].flag -= 1;
	Mix_Chunk *chunk4;
	chunk4 = Mix_LoadWAV("chunk_gameover.wav");
if(Mix_Playing(4) == 0){
	Mix_PlayChannel(4, chunk4, 0);
    }
       SDL_Delay(300);
       }
  if( (R1R.x<(R2R.x+R2R.w)) && (R2R.x<(R1R.x+R1R.w)) &&
      (R1R.y<(R2R.y+R2R.h)) && (R2R.y<(R1R.y+R1R.h)) ) {
     mes[lop].posX = R1R.x - 20;
     mes[lop].flag -= 1;
	Mix_Chunk *chunk4;
	chunk4 = Mix_LoadWAV("chunk_gameover.wav");
if(Mix_Playing(4) == 0){
	Mix_PlayChannel(4, chunk4, 0);
   }
      SDL_Delay(300);
       }
  if( (R1U.x<(R2U.x+R2U.w)) && (R2U.x<(R1U.x+R1U.w)) &&
      (R1U.y<(R2U.y+R2U.h)) && (R2U.y<(R1U.y+R1U.h)) ) {
     mes[lop].posY = R1U.y - 45;
     mes[lop].flag -= 1;
     //死亡音
	Mix_Chunk *chunk4;
	chunk4 = Mix_LoadWAV("chunk_gameover.wav");
if(Mix_Playing(4) == 0){
	Mix_PlayChannel(4, chunk4, 0);
}
      SDL_Delay(300);
       }
  if( (R1D.x<(R2D.x+R2D.w)) && (R2D.x<(R1D.x+R1D.w)) &&
      (R1D.y<(R2D.y+R2D.h)) && (R2D.y<(R1D.y+R1D.h)) ) {
     mes[lop].posY = R1D.y;
     mes[lop].flag -= 1;
	Mix_Chunk *chunk4;
	chunk4 = Mix_LoadWAV("chunk_gameover.wav");
if(Mix_Playing(4) == 0){
	Mix_PlayChannel(4, chunk4, 0);
   }
       SDL_Delay(300);
    }
    }

  else if(maps2[poY][poX] == 3){//スイッチのとき
    SDL_Rect R1L,R1R,R1U,R1D,R2L,R2R,R2U,R2D;
  R1L.x=poX*REC;      R1L.y=poY*REC;      R1L.w=10;  R1L.h=REC;//左側の細胞の位置
  R1R.x=poX*REC + 38;      R1R.y=poY*REC;      R1R.w=10;  R1R.h=REC;//右側の細胞の位置
  R1U.x=poX*REC;      R1U.y=poY*REC;      R1U.w=48;  R1U.h=20;//上側の細胞の位置
  R1D.x=poX*REC + 2;      R1D.y=poY*REC + 45;      R1D.w=44;  R1D.h=4;//下側の細胞の位置
  R2L.x=mes[lop].posX+20;  R2L.y=mes[lop].posY+15;  R2L.w=10;  R2L.h=25;//自分の位置
  R2R.x=mes[lop].posX+20;  R2R.y=mes[lop].posY+15;  R2R.w=10;  R2R.h=25;//自分の位置
  R2U.x=mes[lop].posX+20;  R2U.y=mes[lop].posY+40;  R2U.w=10;  R2U.h=10;//自分の位置
  R2D.x=mes[lop].posX+20;  R2D.y=mes[lop].posY+5;  R2D.w=10;  R2D.h=10;//自分の位置
  if( (R1L.x<(R2L.x+R2L.w)) && (R2L.x<(R1L.x+R1L.w)) &&
      (R1L.y<(R2L.y+R2L.h)) && (R2L.y<(R1L.y+R1L.h)) ) {
     mes[lop].posX = R1L.x - 30;
       }
  if( (R1R.x<(R2R.x+R2R.w)) && (R2R.x<(R1R.x+R1R.w)) &&
      (R1R.y<(R2R.y+R2R.h)) && (R2R.y<(R1R.y+R1R.h)) ) {
     mes[lop].posX = R1R.x - 20;
       }
  if( (R1U.x<(R2U.x+R2U.w)) && (R2U.x<(R1U.x+R1U.w)) &&
      (R1U.y<(R2U.y+R2U.h)) && (R2U.y<(R1U.y+R1U.h)) ) {
     mes[lop].posY = R1U.y - 45;
     maps2[poY][poX] = 4;
 
     //スイッチ押した音
    Mix_Chunk *chunk1;
	chunk1 = Mix_LoadWAV("chunk_switch.wav");
if(Mix_Playing(1) == 0)
	Mix_PlayChannel(1, chunk1, 0);
        for(poY=0;  poY<SIZE_Y;  poY++)
    for(poX=0;  poX<SIZE_X;  poX++)
      if(maps2[poY][poX] == 5){
          maps2[poY][poX] = 11;
          }
     else if(maps2[poY][poX] == 11){
          maps2[poY][poX] = 10;
          }
     else if(maps2[poY][poX] == 10){
          maps2[poY][poX] = 11;
          }
     else if(maps2[poY][poX] == 6){
          maps2[poY][poX] = 25;
          }
     else if(maps2[poY][poX] == 25){
          maps2[poY][poX] = 26;
          }
     else if(maps2[poY][poX] == 26){
          maps2[poY][poX] = 25;
          }
       }
  if( (R1D.x<(R2D.x+R2D.w)) && (R2D.x<(R1D.x+R1D.w)) &&
      (R1D.y<(R2D.y+R2D.h)) && (R2D.y<(R1D.y+R1D.h)) ) {
     mes[lop].posY = R1D.y;
    }
 }
else if(maps2[poY][poX] == 7){ //バネのとき
  SDL_Rect R1L,R1R,R1UB,R1UBs,R1D,R2L,R2R,R2U,R2D;
  R1L.x=poX*REC;      R1L.y=poY*REC;      R1L.w=10;  R1L.h=REC;//左側の細胞の位置
  R1R.x=poX*REC + 38;      R1R.y=poY*REC;      R1R.w=10;  R1R.h=REC;//右側の細胞の位置
  R1UB.x=poX*REC;      R1UB.y=poY*REC + 15;      R1UB.w=48;  R1UB.h=10;//上側の細胞の位置　バネ判定

  R1UBs.x=poX*REC;     R1UBs.y=poY*REC;     R1UBs.w=48; R1UBs.h=10;//上側の細胞の位置　音判定

  R1D.x=poX*REC + 2;      R1D.y=poY*REC + 45;      R1D.w=44;  R1D.h=4;//下側の細胞の位置
  R2L.x=mes[lop].posX+20;  R2L.y=mes[lop].posY+15;  R2L.w=10;  R2L.h=25;//自分の位置
  R2R.x=mes[lop].posX+20;  R2R.y=mes[lop].posY+15;  R2R.w=10;  R2R.h=25;//自分の位置
  R2U.x=mes[lop].posX+20;  R2U.y=mes[lop].posY+40;  R2U.w=10;  R2U.h=10;//自分の位置
  R2D.x=mes[lop].posX+20;  R2D.y=mes[lop].posY+5;  R2D.w=10;  R2D.h=10;//自分の位置
  if( (R1L.x<(R2L.x+R2L.w)) && (R2L.x<(R1L.x+R1L.w)) &&
      (R1L.y<(R2L.y+R2L.h)) && (R2L.y<(R1L.y+R1L.h)) ) {
     mes[lop].posX = R1L.x - 30;
       }
  if( (R1R.x<(R2R.x+R2R.w)) && (R2R.x<(R1R.x+R1R.w)) &&
      (R1R.y<(R2R.y+R2R.h)) && (R2R.y<(R1R.y+R1R.h)) ) {
     mes[lop].posX = R1R.x - 20;
       }
  if( (R1UB.x<(R2U.x+R2U.w)) && (R2U.x<(R1UB.x+R1UB.w)) &&
      (R1UB.y<(R2U.y+R2U.h)) && (R2U.y<(R1UB.y+R1UB.h)) ) {
      mes[lop].Bjanp = 1;
     mes[lop].J_flag = 0;
    return 9;
}
     
if( (R1UBs.x<(R2U.x+R2U.w)) && (R2U.x<(R1UBs.x+R1UBs.w)) &&
      (R1UBs.y<(R2U.y+R2U.h)) && (R2U.y<(R1UBs.y+R1UBs.h)) ) {
     //バネ踏んだ音
Mix_Chunk *chunk3;
	chunk3 = Mix_LoadWAV("chunk_spring.wav");
if(Mix_Playing(3) == 0)
	Mix_PlayChannel(3, chunk3, 0);
}
  if( (R1D.x<(R2D.x+R2D.w)) && (R2D.x<(R1D.x+R1D.w)) &&
      (R1D.y<(R2D.y+R2D.h)) && (R2D.y<(R1D.y+R1D.h)) ) {
     mes[lop].posY = R1D.y;
 }
 }
 else if(maps2[poY][poX] == 8){ //扉のとき
  SDL_Rect R1,R2;
  R1.x=poX*REC;      R1.y=poY*REC;      R1.w=REC;  R1.h=REC;//左側の細胞の位置
  R2.x=mes[lop].posX+20;  R2.y=mes[lop].posY+15;  R2.w=10;  R2.h=25;//自分の位置
  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
      (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
     mes[lop].S_move = 1;
       }
 }
else if(maps2[poY][poX] == 9){ //閉じた扉のとき
  SDL_Rect R1,R2,r2;
  R1.x=poX*REC;      R1.y=poY*REC;      R1.w=REC;  R1.h=REC;//左側の細胞の位置
  R2.x=mes[lop].posX+20;  R2.y=mes[lop].posY+15;  R2.w=10;  R2.h=25;//自分の位置

  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) && (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h))){
     if(mes[lop].clear1 == 1){
        clear1 = 1;
       }
     if(mes[lop].clear2 == 1){
        clear2 = 1;
       }
     }
 if(clear1 == 1 && clear2 == 1)
{
maps2[poY][poX] = 8;
}
}

else if(maps2[poY][poX] == 12 || maps2[poY][poX] == 19 || maps2[poY][poX] == 20 || maps2[poY][poX] == 21){//移動床のとき
   SDL_Rect R1L,R1R,R1U,R1D,R2L,R2R,R2U,R2D;
  R1L.x=poX*REC;      R1L.y=poY*REC;      R1L.w=10;  R1L.h=REC;//左側の細胞の位置
  R1R.x=poX*REC + 38;      R1R.y=poY*REC;      R1R.w=10;  R1R.h=REC;//右側の細胞の位置
  R1U.x=poX*REC;      R1U.y=poY*REC;      R1U.w=48;  R1U.h=10;//上側の細胞の位置
  R1D.x=poX*REC + 1;      R1D.y=poY*REC + 38;      R1D.w=46;  R1D.h=10;//下側の細胞の位置
  R2L.x=mes[lop].posX+20;  R2L.y=mes[lop].posY+15;  R2L.w=10;  R2L.h=25;//自分の位置
  R2R.x=mes[lop].posX+20;  R2R.y=mes[lop].posY+15;  R2R.w=10;  R2R.h=25;//自分の位置
  R2U.x=mes[lop].posX+20;  R2U.y=mes[lop].posY+40;  R2U.w=10;  R2U.h=10;//自分の位置
  R2D.x=mes[lop].posX+20;  R2D.y=mes[lop].posY+5;  R2D.w=10;  R2D.h=15;//自分の位置
  if( (R1L.x<(R2L.x+R2L.w)) && (R2L.x<(R1L.x+R1L.w)) &&
      (R1L.y<(R2L.y+R2L.h)) && (R2L.y<(R1L.y+R1L.h)) ) {
     mes[lop].posX = R1L.x - 30;
       }
  if( (R1R.x<(R2R.x+R2R.w)) && (R2R.x<(R1R.x+R1R.w)) &&
      (R1R.y<(R2R.y+R2R.h)) && (R2R.y<(R1R.y+R1R.h)) ) {
     mes[lop].posX = R1R.x - 10;
       }
  if( (R1U.x<(R2U.x+R2U.w)) && (R2U.x<(R1U.x+R1U.w)) &&
      (R1U.y<(R2U.y+R2U.h)) && (R2U.y<(R1U.y+R1U.h)) ) {
     mes[lop].posY = R1U.y - 45;
     mes[lop].J_max = mes[lop].posY;
     mes[lop].Bjanp = 0;
    return 5;
       }
  if( (R1D.x<(R2D.x+R2D.w)) && (R2D.x<(R1D.x+R1D.w)) &&
      (R1D.y<(R2D.y+R2D.h)) && (R2D.y<(R1D.y+R1D.h)) ) {
     mes[lop].posY = R1D.y + 10;
     mes[lop].J_flag = 2;
     mes[lop].Bjanp = 0;
       }
      }

 else if(maps2[poY][poX] == 14){ //青鍵のとき
  SDL_Rect R1,R2;
  R1.x=poX*REC;      R1.y=poY*REC;      R1.w=REC;  R1.h=REC;//左側の細胞の位置
  R2.x=mes[lop].posX+20;  R2.y=mes[lop].posY+15;  R2.w=10;  R2.h=25;//自分の位置
  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
      (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
    maps2[poY][poX] = 27;
	mes[lop].clear1 = 1;
	}
 }

 else if(maps2[poY][poX] == 15){ //ピンク鍵のとき
  SDL_Rect R1,R2;
  R1.x=poX*REC;      R1.y=poY*REC;      R1.w=REC;  R1.h=REC;//左側の細胞の位置
  R2.x=mes[lop].posX+20;  R2.y=mes[lop].posY+15;  R2.w=10;  R2.h=25;//自分の位置
  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
      (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
    maps2[poY][poX] = 28;
	mes[lop].clear2 = 1;
	}
 }
 }
return 0;
}


void me_mg(int lop)//重力
{
    if(hitChek_me_f(lop) == 0){
 mes[lop].posY += 1;
 }
   if(mes[lop].J_flag == 1){
  mes[lop].posY -= 2;
 }
}

void me_janp()//自機ジャンプ
{
 int lop;
 for(lop=0; lop<me_max; lop++){
 if(mes[lop].J_flag == 1){
     mes[lop].posY -= 3;
    }
  if(mes[lop].posY < mes[lop].J_max - 150){
     mes[lop].J_flag = 2;
     }
  }
}
   
void me_Bjanp()//自機バネジャンプ
{
 int lop;
 for(lop=0; lop<me_max; lop++){
 if(mes[lop].Bjanp == 1){
  mes[lop].BJ_max = mes[lop].posY;
  mes[lop].J_max = mes[lop].posY;
  mes[lop].Bjanp = 2;
 }
  if(mes[lop].Bjanp == 2){
  mes[lop].posY -= 6;
  }
  if(mes[lop].posY < mes[lop].BJ_max - 250){
  mes[lop].Bjanp = 0;
 }
 }
}
 

void me_revive()//死んだら最初の地点へ
{
 int lop;
   for(lop=0; lop<me_max; lop++){
 if(mes[lop].flag <= 0){
 mes[lop].posX = 0;
 mes[lop].posY = 810;
 map_reset();
 }
 }
}

void map_reset()//死んだとき,初期化のときにスイッチと床をリセット
{
 Sint16 poX,poY;
    for(poY=0;  poY<SIZE_Y;  poY++)
    for(poX=0;  poX<SIZE_X;  poX++)
      if(maps1[poY][poX] == 4){
          maps1[poY][poX] = 3;
       }
       else if(maps1[poY][poX] == 11){
          maps1[poY][poX] = 5;
       } 
       else if(maps1[poY][poX] == 10){
          maps1[poY][poX] = 5;
       } 
       else if(maps1[poY][poX] == 25){
          maps1[poY][poX] = 6;
       } 
       else if(maps1[poY][poX] == 26){
          maps1[poY][poX] = 6;
       } 
       else if(maps2[poY][poX] == 4){
          maps2[poY][poX] = 3;
          } 
        else if(maps2[poY][poX] == 11){
          maps2[poY][poX] = 5;
          } 
        else if(maps2[poY][poX] == 10){
          maps2[poY][poX] = 5;
          }   
       else if(maps2[poY][poX] == 25){
          maps2[poY][poX] = 6;
       } 
       else if(maps2[poY][poX] == 26){
          maps2[poY][poX] = 6;
       } 
       else if(maps2[poY][poX] == 27){
          maps2[poY][poX] = 14;
       } 
       else if(maps2[poY][poX] == 28){
          maps2[poY][poX] = 15;
       }
 }

void me_main()//自機の関数をまとめた
{
 int lop;
    for(lop=0; lop<clientnum; lop++){
  me_src(mes[lop].posX, mes[lop].posY, lop);
  hitChek_me_f(lop);
  } 
}

int hitChek_t_f(int lop)//マップチップと自機との判定色々
{
  Sint16 poX,poY;
 if(games == 2){
  for(poY=0;  poY<SIZE_Y;  poY++)
    for(poX=0;  poX<SIZE_X;  poX++)
 if(maps2[poY][poX] == 1 || maps2[poY][poX] == 6 || maps2[poY][poX] == 11){//床のとき
   SDL_Rect R1,R2;
  R1.x=poX*REC;      R1.y=poY*REC;      R1.w=REC;  R1.h=REC;//細胞の位置
  R2.x=traps[lop].posX;  R2.y=traps[lop].posY;  R2.w=48;  R2.h=48;//胃酸の位置
  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
      (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
     traps[lop].flg = 0;
     return 1;
      }
   }
  }
}

int hitChek_me_t()//自機と胃酸の当たり判定
{
  int trap;//表示中の罠を探す
  int me;
  for(trap=0; trap<t_max; trap++){
     for(me=0; me<me_max; me++){
    if(traps[trap].flg==1)
      {
	SDL_Rect R1,R2;
	//自機の座標と大きさ設定
	R1.x=mes[me].posX+20; R1.y=mes[me].posY+15; R1.w=10; R1.h=25;
	//罠の座標と大きさ設定
	R2.x=traps[trap].posX; R2.y=traps[trap].posY; R2.w=48; R2.h=48;
   
	//当り判定、当たってたらフラグ下げる
	if( (R1.x < (R2.x+R2.w)) &&
	    (R2.x < (R1.x+R1.w)) &&
	    (R1.y < (R2.y+R2.h)) &&
	    (R2.y < (R1.y+R1.h)) )
	  {
        mes[me].flag -= 1;
        SDL_Delay(100);
	    return 1;
	  }
      }
     }
    }
  return 0;
}


void trap_srcY(Sint16 posX, Sint16 posY)//胃酸サーフェイス
{
  SDL_Rect src_rect = {0, 0, 48, 48};
  SDL_Rect dst_rect = {posX, posY};
  SDL_BlitSurface(image[12], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}

void trap_init(Sint16 posX,Sint16 posY)//胃酸を表示
{
  int lop;
  for(lop=0; lop<t_max; lop++)
    if(traps[lop].flg==0)
      {
	traps[lop].flg=1;//フラグ立てる
	traps[lop].posX=posX; traps[lop].posY=posY;//座標代入
	traps[lop].spd=1+rand()%3;//スピード決める
	break;//ループ抜ける
      }
}

void trap_main_y()//胃酸まとめ
{
  int lop;
  for(lop=0; lop<t_max; lop++)
    if(traps[lop].flg==1)
      {
	//移動量計算
	traps[lop].posY+=traps[lop].spd;
	//弾を描画
	trap_srcY(traps[lop].posX,traps[lop].posY);
    //当たり判定
	if(hitChek_me_t() == 1){
       traps[lop].flg=0;
       }
	//床に当たれば消去
	if(hitChek_t_f(lop) == 1){
      traps[lop].flg=0;
      }
      }
}


void trap_Y(Sint16 posX, Sint16 posY)//胃酸すべてをまとめた関数
{
  trap_init(posX, posY);
  trap_main_y();
}

void enemys_mainY(double posX,double posY)//敵のまとめ
{
int lop;
for(lop=0; lop<me_max; lop++){
enemys_src(posX, posY,lop);
if (hitChek_me_e(mes[lop].posX, mes[lop].posY, posX,posY)==1){
mes[lop].flag-=1;
SDL_Delay(300);
 }
}
}

void enemys_src(double posX, double posY,int lop)//敵の関数
{
  SDL_Rect src_rect = {0, 0, 50, 50};
  SDL_Rect dst_rect = {posX, posY};

switch (lop){
  case 0: SDL_BlitSurface(image[13], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 1: SDL_BlitSurface(image[13], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 2: SDL_BlitSurface(image[13], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 3: SDL_BlitSurface(image[13], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 4: SDL_BlitSurface(image[13], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
    }
}

int hitChek_me_e(Sint16 posX, Sint16 posY, double poX, double poY)//敵と自機との当たり判定
{
        SDL_Rect R1,R2;
        //自機の座標と大きさ設定                                               
        R1.x=posX+12; R1.y=posY+15; R1.w=24; R1.h=30;
        //敵の座標と大きさ設定                                                 
        R2.x=poX+10; R2.y=poY+10; R2.w=28; R2.h=28;
        //当たり判定、当たってたらフラグ下げる                                   
        if( (R1.x < (R2.x+R2.w)) &&
            (R2.x < (R1.x+R1.w)) &&
            (R1.y < (R2.y+R2.h)) &&
            (R2.y < (R1.y+R1.h)) )
          {
	    return 1;
	  }
	return 0;
}


