#include "headers.h"
int games;
int wii;
int atack;
int change;
int bullet;
int finish=0;
SDL_Surface *mWIN;
SDL_Surface *image[img_max];
SDL_Surface *drwTxt[txt_max];
TTF_Font *font;
//Mix_Chunk *se[M_max];
timers timer;
ziki mes;
trap traps[];
enemy enemys;
bos boss;
zou zous;
object obj;

Sint16 maps1[SIZE_Y][SIZE_X]=
{
 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
 {1, 0, 1, 1, 2, 1, 1, 1, 1, 1},
 {1, 0, 1, 2, 2, 2, 1, 1, 1, 1},
 {1, 1, 1, 1, 2, 1, 1, 1, 3, 3},
 {0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
 {0, 1, 1, 1, 1, 1, 1, 3, 1, 1},
 {0, 0, 1, 1, 0, 0, 1, 1, 0, 1},
 {1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
 {1, 0, 1, 0, 0, 1, 1, 1, 0, 1},
 {1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
 {0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
 {0, 0, 0, 0, 1, 1, 0, 1, 0, 0},
 {0, 1, 1, 0, 1, 1, 0, 1, 0, 1},
 {0, 1, 1, 1, 1, 1, 0, 1, 1, 1},
 {1, 1, 1, 1, 2, 1, 2, 1, 1, 1},
};

Sint16 maps2[SIZE_Y][SIZE_X]=
{
 {1, 1, 1, 1, 1, 2, 1, 1, 1, 1},
 {0, 0, 0, 1, 2, 2, 2, 1, 1, 1},
 {0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
 {0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
 {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
 {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
 {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
 {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
 {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
 {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
};

Sint16 maps3[SIZE_Y][SIZE_X]=
{
 {1, 1, 3, 3, 1, 2, 1, 3, 3, 1},
 {1, 1, 1, 1, 2, 2, 2, 1, 1, 1},
 {1, 1, 1, 1, 1, 2, 1, 1, 1, 1},
 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
 {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
 {0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
 {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
 {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
 {0, 0, 0, 0, 0, 1, 3, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
 {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
 {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
 {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
};


Sint16 maps4[SIZE_Y][SIZE_X]=
{
 {0, 0, 3, 3, 2, 3, 3, 1, 0, 0},
 {0, 1, 1, 2, 2, 2, 1, 1, 1, 0},
 {0, 1, 1, 1, 2, 1, 1, 1, 1, 0},
 {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
 {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
 {3, 1, 1, 1, 1, 1, 1, 1, 1, 3},
 {3, 1, 1, 1, 1, 1, 1, 1, 1, 3},
 {3, 1, 1, 1, 1, 1, 1, 1, 1, 3},
 {3, 1, 1, 1, 1, 1, 1, 1, 1, 3},
 {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
 {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
 {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
 {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
 {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
 {0, 0, 0, 2, 2, 2, 2, 0, 0, 0},
};

Sint16 maps5[SIZE_Y][SIZE_X]=
{
  {1, 1, 1, 2, 4, 2, 1, 1, 1, 1},
  {1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 2, 2, 2, 2, 1, 1, 1},
};

void startUp()
{
if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO) < 0)
SDL_Quit();

mWIN=SDL_SetVideoMode(480,720,32,SDL_SWSURFACE);
SDL_WM_SetCaption("actiongame",NULL);
games=0;
imageLoad();
//LoadSound();
}

void frames()
{
timer.now=SDL_GetTicks();//現在時間を取得
timer.wit=timer.now-timer.lev;//待ち時間を計算

if(timer.wit<16)
   SDL_Delay(16-timer.wit);//16以下ならCPUを休ませる

timer.lev=SDL_GetTicks();//経過時間を更新
SDL_UpdateRect(mWIN,0,0,0,0);//画面を更新
}


int thread(void* args)
{
   // Wiiリモコンがオープン（接続状態）であればループ
	while (wiimote_is_open(&wiimote)) {
		// Wiiリモコンの状態を取得・更新する
		if (wiimote_update(&wiimote) < 0) {
			wiimote_disconnect(&wiimote);
          break;
		}
	  // ***** Wiiのキー（ボタン）ごとに処理 *****              
	  // HOMEボタンが押された時                                          
   	  if (wiimote.keys.home) {//終了処理
	    finish = 1;
	    wiimote_disconnect(&wiimote);// Wiiリモコンとの接続を解除     
	    quits();
	  } 
	  if (wiimote.keys.plus){
	    wii = 1;
	  }

	  if(wiimote.keys.right){
	    wii = 2;
	  mes.posY -= 1;
	  }
      if(wiimote.keys.right && wiimote.keys.one){
        mes.posY -= 2;
      }

      if(wiimote.keys.left){
	    wii = 3;
	  mes.posY += 1;
	  }
      if(wiimote.keys.left && wiimote.keys.one){
      mes.posY += 2;
      }

      if(wiimote.keys.up){
	    wii = 4;
	  mes.posX -= 1;
	  }
      if(wiimote.keys.up && wiimote.keys.one){
      mes.posX -= 2;
      }

      if(wiimote.keys.down){
	    wii = 5;
	 mes.posX += 1;
	  }
      if(wiimote.keys.down && wiimote.keys.one){
     mes.posX += 2;
}
      if(wiimote.keys.minus){
	 wii = 6;
     }
     /* if(wiimote.axis.x <= 50 || wiimote.axis.x >=150){
     atack = 1;
      }*/
      /*else if(wiimote.axis.y <= 50 || wiimote.axis.y >=150){
      atack = 1;
     }*/
      if(wiimote.axis.z <= 70 || wiimote.axis.z >=180){
      atack = 1;
     }
     else{
     atack = 0;
     }
 }
return 0;
}

void imageLoad()
{
image[0] = IMG_Load("bg.png");
if(!image[0])	SDL_Quit();
image[1] = IMG_Load("bg2.png");
if(!image[1])	SDL_Quit();
image[2] = IMG_Load("map.png");
if(!image[2])   SDL_Quit();
image[3] = IMG_Load("c_north.png");
if(!image[3])   SDL_Quit();
image[4] = IMG_Load("c_south.png");
if(!image[4])   SDL_Quit();
image[5] = IMG_Load("c_west.png");
if(!image[5])   SDL_Quit();
image[6] = IMG_Load("c_east.png");
if(!image[6])   SDL_Quit();
image[7] = IMG_Load("e_east.png");
if(!image[7])   SDL_Quit();
image[8] = IMG_Load("e_north.png");
if(!image[8])   SDL_Quit();
image[9] = IMG_Load("e_west.png");
if(!image[9])   SDL_Quit();
image[10] = IMG_Load("e_south.png");
if(!image[10])   SDL_Quit();
image[11] = IMG_Load("w_south.png");
if(!image[11])   SDL_Quit();
image[12] = IMG_Load("w_west.png");
if(!image[12])   SDL_Quit();
image[13] = IMG_Load("obj.png");
if(!image[13])   SDL_Quit();
image[14] = IMG_Load("i_north.png");
if(!image[14])   SDL_Quit();
image[15] = IMG_Load("i_south.png");
if(!image[15])   SDL_Quit();
image[16] = IMG_Load("i_west.png");
if(!image[16])   SDL_Quit();
image[17] = IMG_Load("i_east.png");
if(!image[17])   SDL_Quit();
image[18] = IMG_Load("b_east.png");
if(!image[18])   SDL_Quit();
image[19] = IMG_Load("b_north.png");
if(!image[19])   SDL_Quit();
image[20] = IMG_Load("b_west.png");
if(!image[20])   SDL_Quit();
image[21] = IMG_Load("b_south.png");
if(!image[21])   SDL_Quit();
image[22] = IMG_Load("clear.png");
if(!image[22])   SDL_Quit();
image[23] = IMG_Load("gameover.png");
if(!image[23])   SDL_Quit();
image[24] = IMG_Load("bullet.png");
if(!image[24])   SDL_Quit();
image[25] = IMG_Load("obj2.png");
if(!image[25])   SDL_Quit();
}

/*void LoadSound()
{
if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,1024)==-1)SDL_Quit();
se[0]=Mix_LoadWAV("sword-slash4.mp3");
}

void playSE(int num)
{
Mix_PlayChannel(-1, se[num], 0);
}*/

void backGraund()
{
SDL_Rect src_rect = {0, 0, 480, 720};
SDL_Rect dst_rect = {0, 0};
SDL_BlitSurface(image[0], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}

void backGraund2()
{
SDL_Rect src_rect = {0, 0, 480, 720};
SDL_Rect dst_rect = {0, 0};
SDL_BlitSurface(image[1], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}

void backGraund3()
{
  SDL_Rect src_rect = {0, 0, 480, 720};
  SDL_Rect dst_rect = {0, 0};
  SDL_BlitSurface(image[22], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}

void backGraund4()
{
  SDL_Rect src_rect = {0, 0, 480, 720};
  SDL_Rect dst_rect = {0, 0};
  SDL_BlitSurface(image[23], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}


void mapSrc(Sint16 num,Sint16 poX,Sint16 poY)
{
  SDL_Rect src,drw;
  src.x=num*REC;  src.y=0;      
  src.w=REC; src.h=REC;
  drw.x=poX;      drw.y=poY;
  SDL_BlitSurface(image[2],&src,SDL_GetVideoSurface(),&drw);
}

void mapDrw()
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
  if(games == 3){
    for(poY=0;  poY<SIZE_Y;  poY++)
      for(poX=0;  poX<SIZE_X;  poX++)
        mapSrc(maps3[poY][poX], poX*REC, poY*REC);
  }
  if(games == 4){
    for(poY=0;  poY<SIZE_Y;  poY++)
      for(poX=0;  poX<SIZE_X;  poX++)
        mapSrc(maps4[poY][poX], poX*REC, poY*REC);
  }
  if(games == 5){
    for(poY=0;  poY<SIZE_Y;  poY++)
      for(poX=0;  poX<SIZE_X;  poX++)
        mapSrc(maps5[poY][poX], poX*REC, poY*REC);
  }

}

int quits()
{
  if(finish == 0){
    return 0;//ゲーム中
  }
  return 1;//終了
}

void resets()
{
  int trap, lop;
  mes.posX=240; mes.posY=680;//自機の初期座標
  zous.hp=10;
  for(trap=0; trap<t_max; trap++){
    traps[trap].flg=0;
  }
  for(lop=0; lop<bltMax; lop++){//弾フラグ下げる
    mes.flgB[lop]=0;
  }
  enemys.flg=0;
  change = 0;
  boss.hp = 0;
  obj.flg = 1;
}

void startGame()
{
  if(wii == 1){
    games = 1;
    me_src(mes.posX, mes.posY);
   backGraund2();
  }
  resets();
}

void continue_game()
{
  SDL_FillRect(mWIN,NULL,SDL_MapRGB(mWIN->format,0,0,0));
  //メッセージ
  resets();
  SDL_Delay(2000);
  games += 1;
}
    
   
void me_src(Sint16 posX, Sint16 posY)
{
  SDL_Rect src_rect = {10, 10, 28, 38};
  SDL_Rect dst_rect = {posX, posY};
  switch (wii){
  case 1: SDL_BlitSurface(image[3], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 2: SDL_BlitSurface(image[3], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 3: SDL_BlitSurface(image[4], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 4: SDL_BlitSurface(image[5], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 5: SDL_BlitSurface(image[6], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  default:break;
  }
 
}

void me_move()
{
  if(mes.posX<=0)
    mes.posX=0;//画面からはみ出さないようにする
  else if(mes.posX>=460)
    mes.posX=460;
  if(mes.posY<=0)
    mes.posY=0;//画面からはみ出さないようにする                               
  else if(mes.posY>=700)
    mes.posY=700;
}

void me_main()
{
  me_move();
  me_src(mes.posX, mes.posY);
  hitChek_me_f();
  me_bullet_main();
}

void trap_srcY(Sint16 posX, Sint16 posY)
{
  SDL_Rect src_rect = {20, 24, 8, 20};
  SDL_Rect dst_rect = {posX, posY};
  SDL_BlitSurface(image[11], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}

void trap_srcX(Sint16 posX, Sint16 posY)
{
  SDL_Rect src_rect = {17, 28, 20, 8};
  SDL_Rect dst_rect = {posX, posY};
  SDL_BlitSurface(image[12], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}


void trap_init(Sint16 posX,Sint16 posY)
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

void trap_main_y()
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
	hitChek_me_t(lop);
	//画面から出たら消去
	if(traps[lop].posY>720)traps[lop].flg=0;
      }
}

void trap_main_x()
{
  int lop;
  for(lop=0; lop<t_max; lop++)
    if(traps[lop].flg==1)
      {
        //移動量計算                                                          
	    traps[lop].posX-=traps[lop].spd;
	//弾を描画                                                             
        trap_srcX(traps[lop].posX,traps[lop].posY);
	    	//当たり判定
	    hitChek_me_t(lop);
        //画面から出たら消去                                                   
        if(traps[lop].posX<0)traps[lop].flg=0;
      }
}

void hitChek_me_t(int a)
{
  int trap;//表示中の罠を探す
  for(trap=0; trap<t_max; trap++)
    if(traps[trap].flg==1)
      {
	SDL_Rect R1,R2;
	//自機の座標と大きさ設定
	R1.x=mes.posX+13; R1.y=mes.posY+23; R1.w=25; R1.h=30;
	//罠の座標と大きさ設定
	R2.x=traps[a].posX+17; R2.y=traps[a].posY+23; R2.w=18; R2.h=8;
   
	//当り判定、当たってたらフラグ下げる
	if( (R1.x < (R2.x+R2.w)) &&
	    (R2.x < (R1.x+R1.w)) &&
	    (R1.y < (R2.y+R2.h)) &&
	    (R2.y < (R1.y+R1.h)) )
	  {
	    games = 6;
	    break;//ループ抜ける
	  }
      }
}

int hitChek_me_e(Sint16 posX, Sint16 posY, double poX, double poY)
{
        SDL_Rect R1,R2;
        //自機の座標と大きさ設定                                               
        R1.x=posX+12; R1.y=posY+15; R1.w=24; R1.h=30;
        //敵の座標と大きさ設定                                                 
        R2.x=poX+10; R2.y=poY+10; R2.w=28; R2.h=28;
        //当り判定、当たってたらフラグ下げる                                   
        if( (R1.x < (R2.x+R2.w)) &&
            (R2.x < (R1.x+R1.w)) &&
            (R1.y < (R2.y+R2.h)) &&
            (R2.y < (R1.y+R1.h)) )
          {
	    return 1;
	  }
	return 0;
}

int hitChek_me_b(Sint16 posX, Sint16 posY, double poX, double poY)
{
  SDL_Rect R1,R2;
  //自機の座標と大きさ設定                                               
  R1.x=posX+12; R1.y=posY+15; R1.w=24; R1.h=30;
  //敵の座標と大きさ設定                                                 
  R2.x=poX+10; R2.y=poY+10; R2.w=36; R2.h=42;
  //当り判定、当たってたらフラグ下げる                                   
  if( (R1.x < (R2.x+R2.w)) &&
      (R2.x < (R1.x+R1.w)) &&
      (R1.y < (R2.y+R2.h)) &&
      (R2.y < (R1.y+R1.h)) )
    {
      return 1;
    }
  return 0;
}

int hitChek_me_obj(Sint16 posX, Sint16 posY, Sint16 poX, Sint16 poY)
{
  SDL_Rect R1,R2;
  //自機の座標と大きさ設定                                               
  R1.x=posX+12; R1.y=posY+15; R1.w=24; R1.h=30;
  //オーブの座標と大きさ設定                                                 
  R2.x=poX+13; R2.y=poY; R2.w=26; R2.h=28;
  //当り判定、当たってたらフラグ下げる                                   
  if( (R1.x < (R2.x+R2.w)) &&
      (R2.x < (R1.x+R1.w)) &&
      (R1.y < (R2.y+R2.h)) &&
      (R2.y < (R1.y+R1.h)) )
    {
      return 1;
    }
  return 0;
}

int hitChek_meb_b(Sint16 posX, Sint16 posY, double poX, double poY)
{
  SDL_Rect R1,R2;
  //自機の座標と大きさ設定                                               
  R1.x=posX+10; R1.y=posY+18; R1.w=38; R1.h=38;
  //敵の座標と大きさ設定                                                 
  R2.x=poX+10; R2.y=poY+10; R2.w=36; R2.h=42;
  //当り判定、当たってたらフラグ下げる                                   
  if( (R1.x < (R2.x+R2.w)) &&
      (R2.x < (R1.x+R1.w)) &&
      (R1.y < (R2.y+R2.h)) &&
      (R2.y < (R1.y+R1.h)) )
    {
      return 1;
    }
  return 0;
}

int hitChek_mew_e(Sint16 posX, Sint16 posY, double poX, double poY)
{
 if (change == 0){
 if (atack == 1){
    if (wii == 2){
        SDL_Rect R1,R2;
	
        //自機の座標と大きさ設定                                               
        R1.x=posX; R1.y=posY-20; R1.w=30; R1.h=30;
        //敵の座標と大きさ設定                                                 
        R2.x=poX+10; R2.y=poY+10; R2.w=28; R2.h=28;
        //当り判定、当たってたらフラグ下げる                                   
        if( (R1.x < (R2.x+R2.w)) &&
            (R2.x < (R1.x+R1.w)) &&
            (R1.y < (R2.y+R2.h)) &&
            (R2.y < (R1.y+R1.h)) )
          {
	    return 1;
	  }
    }
    if (wii == 3){
        SDL_Rect R1,R2;
        //自機の座標と大きさ設定                                               
        R1.x=posX; R1.y=posY+38; R1.w=30; R1.h=30;
        //敵の座標と大きさ設定                                                 
        R2.x=poX+10; R2.y=poY+10; R2.w=28; R2.h=28;
        //当り判定、当たってたらフラグ下げる                                   
        if( (R1.x < (R2.x+R2.w)) &&
            (R2.x < (R1.x+R1.w)) &&
            (R1.y < (R2.y+R2.h)) &&
            (R2.y < (R1.y+R1.h)) )
          {
	    return 1;
	  }
    }

    if (wii == 4){
        SDL_Rect R1,R2;
        //自機の座標と大きさ設定                                               
        R1.x=posX-20; R1.y=posY; R1.w=30; R1.h=30;
        //敵の座標と大きさ設定                                                 
        R2.x=poX+10; R2.y=poY+10; R2.w=28; R2.h=28;
        //当り判定、当たってたらフラグ下げる                                   
        if( (R1.x < (R2.x+R2.w)) &&
            (R2.x < (R1.x+R1.w)) &&
            (R1.y < (R2.y+R2.h)) &&
            (R2.y < (R1.y+R1.h)) )
          {
	    return 1;
	  }
    }

    if (wii == 5){
        SDL_Rect R1,R2;
        //自機の座標と大きさ設定                                               
        R1.x=posX+28; R1.y=posY; R1.w=30; R1.h=30;
        //敵の座標と大きさ設定                                                 
        R2.x=poX+10; R2.y=poY+10; R2.w=28; R2.h=28;
        //当り判定、当たってたらフラグ下げる                                   
        if( (R1.x < (R2.x+R2.w)) &&
            (R2.x < (R1.x+R1.w)) &&
            (R1.y < (R2.y+R2.h)) &&
            (R2.y < (R1.y+R1.h)) )
          {
	    return 1;
	  }
   }
  }
 }
	return 0;
}

void hitChek_mew_b(Sint16 posX, Sint16 posY, double poX, double poY)
{
  if (change == 0){
  if (atack == 1){
    if (wii == 2){
      SDL_Rect R1,R2;

      //自機の座標と大きさ設定                                               
      R1.x=posX; R1.y=posY-20; R1.w=40; R1.h=40;
      //敵の座標と大きさ設定                                                 
      R2.x=poX+10; R2.y=poY+10; R2.w=36; R2.h=42;
      weapon_src(R1.x, R1.y);
      //当り判定、当たってたらフラグ下げる                                   
      if( (R1.x < (R2.x+R2.w)) &&
	  (R2.x < (R1.x+R1.w)) &&
	  (R1.y < (R2.y+R2.h)) &&
	  (R2.y < (R1.y+R1.h)) )
	{
	  boss.poY -= 50;
	}
    }
    if (wii == 3){
      SDL_Rect R1,R2;
      //自機の座標と大きさ設定                                               
      R1.x=posX; R1.y=posY+38; R1.w=40; R1.h=40;
      //敵の座標と大きさ設定                                                 
      R2.x=poX+10; R2.y=poY+10; R2.w=36; R2.h=42;
      weapon_src(R1.x, R1.y);
      //当り判定、当たってたらフラグ下げる                                   
      if( (R1.x < (R2.x+R2.w)) &&
	  (R2.x < (R1.x+R1.w)) &&
	  (R1.y < (R2.y+R2.h)) &&
	  (R2.y < (R1.y+R1.h)) )
	{
	  boss.poY += 50;
	}
    }
    if (wii == 4){
      SDL_Rect R1,R2;
      //自機の座標と大きさ設定                                               
      R1.x=posX-20; R1.y=posY; R1.w=40; R1.h=40;
      //敵の座標と大きさ設定                                                 
      R2.x=poX+10; R2.y=poY+10; R2.w=36; R2.h=42;
      //当り判定、当たってたらフラグ下げる  
      weapon_src(R1.x, R1.y);                                 
      if( (R1.x < (R2.x+R2.w)) &&
	  (R2.x < (R1.x+R1.w)) &&
	  (R1.y < (R2.y+R2.h)) &&
	  (R2.y < (R1.y+R1.h)) )
	{
	  boss.poX -= 50;
	}
    }

    if (wii == 5){
      SDL_Rect R1,R2;
      //自機の座標と大きさ設定                                               
      R1.x=posX+28; R1.y=posY; R1.w=40; R1.h=40;
      //敵の座標と大きさ設定                                                 
      R2.x=poX+10; R2.y=poY+10; R2.w=36; R2.h=42;
      //当り判定、当たってたらフラグ下げる      
      weapon_src(R1.x, R1.y);                             
      if( (R1.x < (R2.x+R2.w)) &&
	  (R2.x < (R1.x+R1.w)) &&
	  (R1.y < (R2.y+R2.h)) &&
	  (R2.y < (R1.y+R1.h)) )
	{
	  boss.poX += 50;
	}
    }
  }
}
}




int hitChek_mew_o(Sint16 posX, Sint16 posY, Sint16 poX, Sint16 poY)
{
 if (change == 0){
 if (atack == 1){
    if (wii == 2){
        SDL_Rect R1,R2;
        //自機の座標と大きさ設定                                               
        R1.x=posX; R1.y=posY-20; R1.w=40; R1.h=40;
        //像の座標と大きさ設定                                                 
        R2.x=poX+17; R2.y=poY; R2.w=15; R2.h=48;
        //当り判定、当たってたらフラグ下げる
	weapon_src(R1.x, R1.y);
        if( (R1.x < (R2.x+R2.w)) &&
            (R2.x < (R1.x+R1.w)) &&
            (R1.y < (R2.y+R2.h)) &&
            (R2.y < (R1.y+R1.h)) )
          {
	    return 1;
	  }
    }
    if (wii == 3){
        SDL_Rect R1,R2;
        //自機の座標と大きさ設定                                               
        R1.x=posX; R1.y=posY+38; R1.w=40; R1.h=40;
        //像の座標と大きさ設定                                                 
        R2.x=poX+17; R2.y=poY; R2.w=15; R2.h=48;
        //当り判定、当たってたらフラグ下げる 
	weapon_src(R1.x, R1.y);
        if( (R1.x < (R2.x+R2.w)) &&
            (R2.x < (R1.x+R1.w)) &&
            (R1.y < (R2.y+R2.h)) &&
            (R2.y < (R1.y+R1.h)) )
          {
	    return 1;
	  }
    }

    if (wii == 4){
        SDL_Rect R1,R2;
        //自機の座標と大きさ設定                                               
        R1.x=posX-20; R1.y=posY; R1.w=40; R1.h=40;
        //像の座標と大きさ設定                                                 
        R2.x=poX+17; R2.y=poY; R2.w=15; R2.h=48;
        //当り判定、当たってたらフラグ下げる 
	weapon_src(R1.x, R1.y);
        if( (R1.x < (R2.x+R2.w)) &&
            (R2.x < (R1.x+R1.w)) &&
            (R1.y < (R2.y+R2.h)) &&
            (R2.y < (R1.y+R1.h)) )
          {
	    return 1;
	  }
    }

    if (wii == 5){
        SDL_Rect R1,R2;
        //自機の座標と大きさ設定                                               
        R1.x=posX+28; R1.y=posY; R1.w=40; R1.h=40;
        //像の座標と大きさ設定                                                 
        R2.x=poX+17; R2.y=poY; R2.w=15; R2.h=48;
        //当り判定、当たってたらフラグ下げる
	weapon_src(R1.x, R1.y);
        if( (R1.x < (R2.x+R2.w)) &&
            (R2.x < (R1.x+R1.w)) &&
            (R1.y < (R2.y+R2.h)) &&
            (R2.y < (R1.y+R1.h)) )
          {
	    return 1;
	  }
   }
  }
 }
	return 0;
}


void hitChek_me_f()
{
  Sint16 poX,poY;
 if(games == 1){
  for(poY=0;  poY<SIZE_Y;  poY++)
    for(poX=0;  poX<SIZE_X;  poX++)
 if(maps1[poY][poX] == 0){
  SDL_Rect R1,R2;
  R1.x=poX*REC;      R1.y=poY*REC;      R1.w=REC;  R1.h=REC;//穴の位置
  R2.x=mes.posX+15;  R2.y=mes.posY+15;  R2.w=10;  R2.h=10;//自分の位置
  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
      (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
     games = 6;
       }
      }
    }
   if(games == 2){
  for(poY=0;  poY<SIZE_Y;  poY++)
    for(poX=0;  poX<SIZE_X;  poX++)
 if(maps2[poY][poX] == 0){
  SDL_Rect R1,R2;
  R1.x=poX*REC;      R1.y=poY*REC;      R1.w=REC;  R1.h=REC;//穴の位置
  R2.x=mes.posX+15;  R2.y=mes.posY+15;  R2.w=10;  R2.h=10;//自分の位置
  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
      (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
     games = 6;
       }
      }
   }
   if(games == 3){
     for(poY=0;  poY<SIZE_Y;  poY++)
       for(poX=0;  poX<SIZE_X;  poX++)
	 if(maps3[poY][poX] == 0){
	   SDL_Rect R1,R2;
	   R1.x=poX*REC;      R1.y=poY*REC;      R1.w=REC;  R1.h=REC;//穴の位置
	   R2.x=mes.posX+15;  R2.y=mes.posY+15;  R2.w=10;  R2.h=10;//自分の位置
	   if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
	       (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
	     games = 6;
	   }
	 }
   }
   if(games == 4){
     for(poY=0;  poY<SIZE_Y;  poY++)
       for(poX=0;  poX<SIZE_X;  poX++)
	 if(maps4[poY][poX] == 0){
	   SDL_Rect R1,R2;
	   R1.x=poX*REC;      R1.y=poY*REC;      R1.w=REC;  R1.h=REC;//穴の位置
	   R2.x=mes.posX+15;  R2.y=mes.posY+15;  R2.w=10;  R2.h=10;//自分の位置
	   if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
	       (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
	     games = 6;
	   }
	 }
   }
}

int hitChek_enemy_f()
{
  Sint16 posX,posY;
 if(games == 1){
  for(posY=0;  posY<SIZE_Y;  posY++)
    for(posX=0;  posX<SIZE_X;  posX++)
 if(maps1[posY][posX] == 0){
  SDL_Rect R1,R2;
  R1.x=posX*REC;      R1.y=posY*REC;      R1.w=REC;  R1.h=REC;//穴の位置
  R2.x=enemys.poX+15;  R2.y=enemys.poY+15;  R2.w=10;  R2.h=10;//敵の位置
  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
      (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
     return 1;
       }
      }
    }
   if(games == 2){
  for(posY=0;  posY<SIZE_Y;  posY++)
    for(posX=0;  posX<SIZE_X;  posX++)
 if(maps2[posY][posX] == 0){
  SDL_Rect R1,R2;
  R1.x=posX*REC;      R1.y=posY*REC;      R1.w=REC;  R1.h=REC;//穴の位置
  R2.x=enemys.poX+15;  R2.y=enemys.poY+15;  R2.w=10;  R2.h=10;//敵の位置
  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
      (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
     return 1;
       }
      }
    }
   if(games == 3){
  for(posY=0;  posY<SIZE_Y;  posY++)
    for(posX=0;  posX<SIZE_X;  posX++)
 if(maps3[posY][posX] == 0){
  SDL_Rect R1,R2;
  R1.x=posX*REC;      R1.y=posY*REC;      R1.w=REC;  R1.h=REC;//穴の位置
  R2.x=enemys.poX+15;  R2.y=enemys.poY+15;  R2.w=10;  R2.h=10;//敵の位置
  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
      (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
     return 1;
       }
      }
    }
   if(games == 4){
  for(posY=0;  posY<SIZE_Y;  posY++)
    for(posX=0;  posX<SIZE_X;  posX++)
 if(maps4[posY][posX] == 0){
  SDL_Rect R1,R2;
  R1.x=posX*REC;      R1.y=posY*REC;      R1.w=REC;  R1.h=REC;//穴の位置
  R2.x=enemys.poX+15;  R2.y=enemys.poY+15;  R2.w=10;  R2.h=10;//敵の位置
  if( (R1.x<(R2.x+R2.w)) && (R2.x<(R1.x+R1.w)) &&
      (R1.y<(R2.y+R2.h)) && (R2.y<(R1.y+R1.h)) ) {
     return 1;
       }
      }
    }
  
return 0;
}


void trap_X(Sint16 posX, Sint16 posY)
{
  trap_init(posX, posY);
  trap_main_x();
}

void trap_Y(Sint16 posX, Sint16 posY)
{
  trap_init(posX, posY);
  trap_main_y();
}

void textInit()
{
   TTF_Init();
   font=TTF_OpenFont("../../../../../usr/share/fonts/kochi-gothic-subst.ttf", 24);
   SDL_Color clr={255,255,255};
   drwTxt[0]=TTF_RenderUTF8_Solid(font,"探検家は力尽きた...",clr);
   drwTxt[1]=TTF_RenderUTF8_Solid(font,"マイナスボタンでタイトルへ。ホームで終了。",clr);
   drwTxt[2]=TTF_RenderUTF8_Solid(font,"プラスボタンで潜入",clr);
   drwTxt[3]=TTF_RenderUTF8_Solid(font,"１階層目",clr);
   drwTxt[4]=TTF_RenderUTF8_Solid(font,"２階層目",clr);
   drwTxt[5]=TTF_RenderUTF8_Solid(font,"奥層",clr);
   drwTxt[6]=TTF_RenderUTF8_Solid(font,"おめでとう！！",clr);
   TTF_CloseFont(font); 
}

void textDrw(Sint16 num, Sint16 poX, Sint16 poY)
{
SDL_Rect dst; dst.x=poX; dst.y=poY;
SDL_BlitSurface(drwTxt[num], NULL, mWIN, &dst);
}

void gameover()
{
backGraund4();
}

void clear()
{
backGraund3();
}

void backtitle()
{
  if(wii == 6)
    games = 0;
}

void enemy_homing(Sint16 posx, Sint16 posy)
{
  if(enemys.flg==0)//初期化
    {
      enemys.flg=1;        enemys.spd=rand()%3+0.5 ;//スピード
      enemys.poX=posx;  enemys.poY=posy;//自弾の座標初期値
  
      //目的地まの距離検出
      double taX=(mes.posX+REC*0.5)-enemys.poX;
      double taY=(mes.posY+REC*0.5)-enemys.poY;
  
      //弾の発射角度取得し移動量設定
      if( taX==0 && taY==0 ){
      taX+=0.00001; //atan2エラー防止
      taY+=0.00001; //atan2エラー防止
      enemys.tar=atan2( taY, taX );
  }
      //移動量格納
      enemys.moX=cos(enemys.tar)*enemys.spd;
      enemys.moY=sin(enemys.tar)*enemys.spd;
    }
  //メイン処理
  else if( hitChek_me_e(mes.posX,mes.posY,enemys.poX,enemys.poY)==1 )//当たり判定
    {
      enemys.flg=0;  //それぞれフラグ下げる
      games = 6;
    }

  else if(hitChek_enemy_f() == 1)//床と敵の判定
     {
       enemys.flg=0; 
     }

  else if(hitChek_mew_e(mes.posX,mes.posY,enemys.poX,enemys.poY) == 1)
    {
      enemys.flg=0; 
    }

  else
    {
      if( (enemys.cnt+=1)>10)//このカウント毎にターゲットの位置を確認する
	{
	  //ターゲット地点再取得
	  double taX=(mes.posX+REC*0.5)-enemys.poX;
	  double taY=(mes.posY+REC*0.5)-enemys.poY;
	  if(taX==0 && taY==0) {
      taX+=0.00001;
      taY+=0.00001;
}
	  enemys.tar=atan2( taY, taX )*(180/PAI);
	  if(enemys.tar<=0) enemys.tar+=360;  //360に直す

	  enemys.cnt=0;//カウントリセット
	}
      else//ホーミングの計算
	{
	  //角度±5でターゲットの方向に向かせる-自弾の角度修正
	  if     (enemys.tar-enemys.rot>=   0 && enemys.tar-enemys.rot< 180) enemys.rot+=5;
	  else if(enemys.tar-enemys.rot>= 180 && enemys.tar-enemys.rot< 360) enemys.rot-=5;
	  else if(enemys.tar-enemys.rot<    0 && enemys.tar-enemys.rot>-180) enemys.rot-=5;
	  else if(enemys.tar-enemys.rot<=-180 && enemys.tar-enemys.rot>-360) enemys.rot+=5;
	  //360度に直す
	  if     (enemys.rot<=0 ) enemys.rot+=360;
	  else if(enemys.rot>360) enemys.rot-=360;
	  //移動量計算
	  enemys.moX=cos( enemys.rot*(PAI/180) )*enemys.spd;
	  enemys.moY=sin( enemys.rot*(PAI/180) )*enemys.spd;
	}
     /* //画面の上下左右をループ
      if     (enemys.poX<0)     enemys.poX=WIW-1;
      else if(enemys.poX>WIW-1) enemys.poX=0;
      else if(enemys.poY<0)     enemys.poY=WIH-1;
      else if(enemys.poY>WIH-1) enemys.poY=0;
	*/
      //移動量を計算し目的地まで飛ばす
      enemys.poX+=enemys.moX;enemys.poY+=enemys.moY;
      enemys_src(enemys.poX,enemys.poY); //描画
    }
}

void enemys_src(Sint16 posX, Sint16 posY)
{
  SDL_Rect src_rect = {10, 10, 28, 48};
  SDL_Rect dst_rect = {posX, posY};
  if(enemys.tar <= 45 || enemys.tar >= 315)
    SDL_BlitSurface(image[7], &src_rect, SDL_GetVideoSurface(), &dst_rect);
  if(enemys.tar > 45 && enemys.tar <= 135)
    SDL_BlitSurface(image[10], &src_rect, SDL_GetVideoSurface(), &dst_rect);
  if(enemys.tar > 135 && enemys.tar <= 225)
    SDL_BlitSurface(image[9], &src_rect, SDL_GetVideoSurface(), &dst_rect);
  if(enemys.tar > 225 && enemys.tar < 315)
    SDL_BlitSurface(image[8], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}

void weapon_src(Sint16 posX, Sint16 posY)
{
  SDL_Rect src_rect = {15, 15, 20, 38};
  SDL_Rect src_rect1 = {8, 22, 32, 20};
  SDL_Rect dst_rect = {posX, posY};
  switch(wii){
  case 2: SDL_BlitSurface(image[14], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 3: SDL_BlitSurface(image[15], &src_rect, SDL_GetVideoSurface(), &dst_rect);break;
  case 4: SDL_BlitSurface(image[16], &src_rect1, SDL_GetVideoSurface(), &dst_rect);break;
  case 5: SDL_BlitSurface(image[17], &src_rect1, SDL_GetVideoSurface(), &dst_rect);break;
  default:break;
  }
}

void boss_main(Sint16 posX, Sint16 posY)
{
  boss_homing(posX, posY);
  hitChek_mew_b(mes.posX, mes.posY, boss.poX, boss.poY);
}
  

void boss_src(Sint16 posX, Sint16 posY)
{
  SDL_Rect src_rect = {5, 5, 47, 55};
  SDL_Rect dst_rect = {posX, posY};
  if(boss.tar <= 45 || boss.tar >= 315)
    SDL_BlitSurface(image[18], &src_rect, SDL_GetVideoSurface(), &dst_rect);
  if(boss.tar > 45 && boss.tar <= 135)
    SDL_BlitSurface(image[21], &src_rect, SDL_GetVideoSurface(), &dst_rect);
  if(boss.tar > 135 && boss.tar <= 225)
    SDL_BlitSurface(image[20], &src_rect, SDL_GetVideoSurface(), &dst_rect);
  if(boss.tar > 225 && boss.tar < 315)
    SDL_BlitSurface(image[19], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}

void boss_homing(Sint16 posx, Sint16 posy)
{
      if(boss.hp == 0){
      boss.hp = 11;
      boss.spd=2;//スピード                    
      boss.poX=posx;  boss.poY=posy;//自弾の座標初期値                     
      //目的地まの距離検出                                                     
      double taX=(mes.posX+REC*0.5)-boss.poX;
      double taY=(mes.posY+REC*0.5)-boss.poY;
      //弾の発射角度取得し移動量設定                                          
      if( taX==0 && taY==0 ){
	taX+=0.00001; //atan2エラー防止                                        
	taY+=0.00001; //atan2エラー防止                                        
	boss.tar=atan2( taY, taX );
      }
      //移動量格納                                                             
      boss.moX=cos(boss.tar)*boss.spd;
      boss.moY=sin(boss.tar)*boss.spd;
	}
  else if( hitChek_me_b(mes.posX,mes.posY,boss.poX,boss.poY)==1 )//当たり判定 
    {
      boss.hp=0;  //それぞれフラグ下げる                                    
      games = 6;
    }
  else if(hitChek_meb_b(mes.bltX[0], mes.bltY[0], boss.poX, boss.poY) == 1){
      boss.hp -= 1;
      mes.flgB[0] = 0;
      mes.bltX[0] = 0;
      mes.bltY[0] = 0;
    }
  else if(boss.hp == 1){
      games = 7;
     }
  else
    {
      if( (boss.cnt+=1)>10)//このカウント毎にターゲットの位置を確認する      
        {
          //ターゲット地点再取得                                               
          double taX=(mes.posX+REC*0.5)-boss.poX;
          double taY=(mes.posY+REC*0.5)-boss.poY;
          if(taX==0 && taY==0) {
	    taX+=0.00001;
	    taY+=0.00001;
	  }
          boss.tar=atan2( taY, taX )*(180/PAI);
          if(boss.tar<=0) boss.tar+=360;  //360に直す                      
          boss.cnt=0;//カウントリセット                                      
        }
      else//ホーミングの計算                                                   
        {
          //角度±5でターゲットの方向に向かせる-自弾の角度修正                  
          if     (boss.tar-boss.rot>=   0 && boss.tar-boss.rot< 180) boss.rot+=5;
          else if(boss.tar-boss.rot>= 180 && boss.tar-boss.rot< 360) boss.rot-=5;
          else if(boss.tar-boss.rot<    0 && boss.tar-boss.rot>-180) boss.rot-=5;
          else if(boss.tar-boss.rot<=-180 && boss.tar-boss.rot>-360) boss.rot+=5;
          //360度に直す                                                        
          if     (boss.rot<=0 ) boss.rot+=360;
          else if(boss.rot>360) boss.rot-=360;
          //移動量計算                                                         
          boss.moX=cos( boss.rot*(PAI/180) )*boss.spd;
          boss.moY=sin( boss.rot*(PAI/180) )*boss.spd;
        }
      boss.poX+=boss.moX;boss.poY+=boss.moY;
      boss_src(boss.poX,boss.poY); //描画                                
    }
}



void obj_src(Sint16 posX, Sint16 posY)
{
  SDL_Rect src_rect = {17, 0, 15, 48};
  SDL_Rect dst_rect = {posX, posY};
  SDL_BlitSurface(image[13], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}

void obj2_src(Sint16 posX, Sint16 posY)
{
  SDL_Rect src_rect = {11, 0, 26, 28};
  SDL_Rect dst_rect = {posX, posY};
  SDL_BlitSurface(image[25], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}

void obj2_main(Sint16 poX, Sint16 poY)
{
  obj.posX = poX; obj.posY = poY;
  if(obj.flg == 1){
	obj2_src(obj.posX, obj.posY);
    }
    if(hitChek_me_obj(mes.posX, mes.posY, obj.posX, obj.posY)== 1){
	   obj.flg = 0;
       change = 1;
     }
}

void obj_main(Sint16 poX, Sint16 poY)
{
  zous.posX = poX; zous.posY = poY;
  if(zous.hp >= 1){
    obj_src(zous.posX, zous.posY);
    if(hitChek_mew_o(mes.posX, mes.posY, zous.posX, zous.posY) == 1){
      zous.hp -= 1;
      //playSE(0);
    }
  }
  if(zous.hp < 1){
    continue_game();
  }
}

void me_bullet_main()
{ 
  if(change == 1){
  switch(wii){
    case 2: me_bullet_north();break;
    case 3: me_bullet_south();break;
    case 4: me_bullet_west();break;
    case 5: me_bullet_east();break;
    default:break;
   }
  switch(bullet){
    case 1: me_bullet_north_move();break;
    case 2: me_bullet_south_move();break;
    case 3: me_bullet_west_move();break;
    case 4: me_bullet_east_move();break;
    default:break;
   }
 }
}

void me_srcB(Sint16 posX, Sint16 posY)
{
  SDL_Rect src_rect = {10, 18, 38, 38};
  SDL_Rect dst_rect = {posX, posY};
  SDL_BlitSurface(image[24], &src_rect, SDL_GetVideoSurface(), &dst_rect);
}

void me_bullet_north()
{
int lop;
//発射されてない弾を探し初期化
if(change==1){
 if(atack==1){
for(lop=0; lop<bltMax; lop++) 
if(mes.flgB[lop]==0)
   {
   mes.flgB[lop]=1;
   mes.bltX[lop]=mes.posX+24;
   mes.bltY[lop]=mes.posY-10;
   bullet = 1;
   break;//一発だけ発射して抜ける
   }
  } 
 } 
}

void me_bullet_north_move()
{
int lop;
//発射されてる弾を探し移動計算
for(lop=0; lop<bltMax; lop++)
if(mes.flgB[lop]==1)
   {
   mes.bltY[lop]-=5;
   if(mes.bltY[lop]<0)mes.flgB[lop]=0;//フラグ下げる
   me_srcB(mes.bltX[lop],mes.bltY[lop]);//弾描画
   }
}


void me_bullet_south()
{
int lop;
//発射されてない弾を探し初期化
if(change==1){
 if(atack==1){
for(lop=0; lop<bltMax; lop++) 
if(mes.flgB[lop]==0)
   {
   mes.flgB[lop]=1;
   mes.bltX[lop]=mes.posX+24;
   mes.bltY[lop]=mes.posY-30;
   bullet = 2;
   break;//一発だけ発射して抜ける
   }
  } 
 } 
}

void me_bullet_south_move()
{
int lop;
//発射されてる弾を探し移動計算
for(lop=0; lop<bltMax; lop++)
if(mes.flgB[lop]==1)
   {
   mes.bltY[lop]+=5;
   if(mes.bltY[lop]>720)mes.flgB[lop]=0;//フラグ下げる
   me_srcB(mes.bltX[lop],mes.bltY[lop]);//弾描画
   }
}

void me_bullet_east()
{
int lop;
//発射されてない弾を探し初期化
if(change==1){
 if(atack==1){
for(lop=0; lop<bltMax; lop++) 
if(mes.flgB[lop]==0)
   {
   mes.flgB[lop]=1;
   mes.bltX[lop]=mes.posX+34;
   mes.bltY[lop]=mes.posY+24;
   bullet = 4;
   break;//一発だけ発射して抜ける
  }
  } 
 } 
}

void me_bullet_east_move()
{
int lop;
//発射されてる弾を探し移動計算
for(lop=0; lop<bltMax; lop++)
if(mes.flgB[lop]==1)
   {
   mes.bltX[lop]+=5;
   if(mes.bltX[lop]>480)mes.flgB[lop]=0;//フラグ下げる
   me_srcB(mes.bltX[lop],mes.bltY[lop]);//弾描画
   }
}
   

void me_bullet_west()
{
int lop;
//発射されてない弾を探し初期化
if(change==1){
 if(atack==1){
for(lop=0; lop<bltMax; lop++) 
if(mes.flgB[lop]==0)
   {
   mes.flgB[lop]=1;
   mes.bltX[lop]=mes.posX+10;
   mes.bltY[lop]=mes.posY+24;
   bullet = 3;
   break;//一発だけ発射して抜ける
   }
  } 
 }
}

void me_bullet_west_move()
{
int lop;
//発射されてる弾を探し移動計算
for(lop=0; lop<bltMax; lop++)
if(mes.flgB[lop]==1)
   {
   mes.bltX[lop]-=5;
   if(mes.bltX[lop]<0)mes.flgB[lop]=0;//フラグ下げる
   me_srcB(mes.bltX[lop],mes.bltY[lop]);//弾描画
   }
 }
  

