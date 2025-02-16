#pragma once

// ReSharper disable once CppUnusedIncludeDirective
#include "resource.h"
#define MAX_LOADSTRING 100

#define TM_CTRL 5
#define TM_NEWFRM 1	//invalidateRect
#define TM_FIRECTRL 2	//PlayerFiring --> Player의 불릿의 가용성을 정의합니다
#define TM_ENEMYCTRL 6
#define TM_ENMFIRE 7
#define TM_DRAWBGSTAR 10
#define CTRLPERSEC 100
#define FRAMEPERSEC 30
#define BULLETSPEED 18
#define MAXBULLET 10
#define MAX_ENEMY 100
#define BULLETDELAY 444
#define MEMCHKCYCLE 1000 * 5

#define BTN_PAUSE 1003
#define BTN_RESUME 1004

#define PlayerSpeed 0.6
#define SPEEDBREAK 0.3
#define WIN_X_SIZE 1280

#define ENMFIREPERSEC 1

#define WIN_Y_SIZE 720

#define RET_SUCCESS 0
#define RET_ERROR 1

#define ENEMYSPEED 20
#define MAX_PLAYER_SPEED 6

#define PERCOFENEMYDIVE 10

#define PERCOFENEMYFIRE 25
#define MAXEBULLET 20
#define EBULLETFUCKINGLOVERSTHATSMESPEED 15

#define ENEMYCTRLTMRDELAY 500

//	[필독]
#define BGDOTTYPE 2
// BGDOTTYPE: BGThread에서 점을 그릴때 사용.
// type 1: 굵은 색점
// type 2: 굵은 흰점
// type 3: 가는 색점
// type 4: 가는 흰점

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

extern HANDLE hThread_BG;

extern bool enemysprite;

extern bool levelclearhack;

extern double speed;
void DrawScreen(HWND hWnd);
void CtrlEnemy(void);
void CALLBACK Control(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
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
bool Percentage(int percent);
void CtrlEBullet(void);
void chkPlayerHit(int i);
void chkBulletHit(void);



extern FMOD_SYSTEM *g_System; //FMOD system 변수선언
extern FMOD_SOUND *g_Sound[32];
extern FMOD_CHANNEL *channel;
extern FMOD_BOOL IsPlaying;

extern float volume; //볼륨 0~1

DWORD WINAPI DIVEMOVEThread(LPVOID prc);
DWORD WINAPI DIVEControlThread(LPVOID prc);