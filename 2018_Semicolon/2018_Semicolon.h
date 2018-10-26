#pragma once

#include "resource.h"
#define MAX_LOADSTRING 100

#define TM_CTRL 5
#define TM_NEWFRM 1	//invalidateRect
#define TM_FIRECTRL 2	//PlayerFiring --> Player의 불릿의 가용성을 정의합니다
#define TM_PLSPEEDCTRL 4
#define TM_ENEMYCTRL 6
#define TM_ENMFIRE 7
#define CTRLPERSEC 100
#define FRAMEPERSEC 30
#define BULLETSPEED 18
#define MAXBULLET 10
#define MAX_ENEMY 100
#define BULLETDELAY 400
#define MEMCHKCYCLE 1000 * 5

#define BTN_PAUSE 1003
#define BTN_RESUME 1004

#define PlayerSpeed 0.3
#define SPEEDCTRLDELAY 20
#define SPEEDBREAK 0.4
#define WIN_X_SIZE 1280

#define ENMFIREPERSEC 1

#define WIN_Y_SIZE 720

#define RET_SUCCESS 0
#define RET_ERROR 1

#define ENEMYSPEED 5
#define MAX_PLAYER_SPEED 6

#define PERCOFENEMYFIRE 17
#define MAXEBULLET 20
#define EBULLETFUCKINGLOVERSTHATSMESPEED 15


#define ENEMYCTRLTMRDELAY 500
typedef struct _Jet {
	double x;
	int y;
	int Live;
	int level;
} Jet;

typedef struct _Bullet {
	int x;
	int y;
	int isUsed;
} Bullet;

extern time_t lastmovedtime;
extern Jet Player;
extern Jet Enemy[MAX_ENEMY];
extern HINSTANCE hInst;                                // 현재 인스턴스입니다.
extern WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
extern WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
extern HWND g_hWnd;
extern unsigned long long int score;

extern Bullet PBullet[MAXBULLET];
extern bool canFire;
extern Bullet EBullet[MAXEBULLET];

extern double speed;
void DrawScreen(void);
void CtrlEnemy(void);
void Control(void);
void MoveLeft(void);
void MoveRight(void);
void MoveUp(void);
void MoveDown(void);
void PlayerFired(void);
void CtrlPBullet(void);
void chkEnemy(int indexOfBullet);




//fmod 관련
void SoundInit(void);

void StopSound(void);
void VolumeSetSound(void);
void SoundUpdate(void);


void VolumeCtrl(void);
void Sound_Play(int n);

int spawnEnemy(int x, int y, int level);
void chkEnemyHit(void);
bool chkLevelClear(void);
void chkEnemyFuckedThePlayer(void);
void EnemyFire(int index);
bool Percentage(void);
void CtrlEBullet(void);
void chkPlayerHit(int i);
void chkBulletHit(void);