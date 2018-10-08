#include "stdafx.h"
#include "2018_Semicolon.h"
#include "sndenum.h"



FMOD_SYSTEM *g_System; //FMOD system ��������
FMOD_SOUND *g_Sound[10];
FMOD_CHANNEL *channel = nullptr;
FMOD_BOOL IsPlaying;

float volume = 1; //���� 0~1 


void SoundInit(void) {
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, 10, FMOD_INIT_NORMAL, nullptr); //�ִ� 10���� �Ҹ�������� 

															   /*���� ����*/
	FMOD_System_CreateSound(g_System, "..\\res\\bgm.wav", FMOD_LOOP_NORMAL, nullptr, &g_Sound[S_BGM]);
	FMOD_System_CreateSound(g_System, "..\\res\\bullet.wav", FMOD_DEFAULT, nullptr, &g_Sound[S_PL_BULLET]);
	FMOD_System_CreateSound(g_System, "..\\res\\enemyhit1.wav", FMOD_DEFAULT, nullptr, &g_Sound[S_ENEMYDIE1]);
	FMOD_System_CreateSound(g_System, "..\\res\\enemyhit2.wav", FMOD_DEFAULT, nullptr, &g_Sound[S_ENEMYDIE2]);
	FMOD_System_CreateSound(g_System, "..\\res\\enemyhit3.wav", FMOD_DEFAULT, nullptr, &g_Sound[S_ENEMYHIT3]);
	FMOD_System_CreateSound(g_System, "..\\res\\enemy3die.wav", FMOD_DEFAULT, nullptr, &g_Sound[S_ENEMYDIE3]);

	//FMOD_System_CreateSound(g_System, "..\\sound\\NewPlayerInit.wav", FMOD_DEFAULT, 0, &g_Sound[S_START]);
	//FMOD_System_CreateSound(g_System, ".\\sound\\enemybullet.wav", FMOD_DEFAULT, 0, &g_Sound[S_EN_BULLET]);
}


void StopSound(void) {
	FMOD_Channel_Stop(channel); //ä���� �Ҹ� ������� 
}


void VolumeSetSound(void) {
	FMOD_Channel_SetVolume(channel, volume); //���� �������� �Ҹ�ũ�� ���� 
}


void SoundUpdate(void) {
	if (IsPlaying == 1)
		FMOD_System_Update(g_System);
}

/*
void VolumeCtrl(void) {
	//char n;
	system("cls");
	prn_xy("��: ���� ���� �� MAX 10 ��", 27, 8, CR_LGREEN, CR_BLACK, false);

	prn_xy("��: ���� ���� �� MIN 0  ��", 27, 10, CR_RED, CR_BLACK, false);

	prn_xy("[ESC] : ���� ������", 30, 12, CR_WHITE, CR_BLACK, false);

	prn_xy("�Ҹ� ����: ", 32, 16, CR_WHITE, CR_BLACK, false);
	while (true) {
		gotoxy(44, 16);
		printf("%02d", (int)(volume * 10));


		if (GetAsyncKeyState(VK_UP) < 0 && volume < 1.0f) {
			// ȭ��ǥ ���� Ű�� ������ �� 
			volume += 0.1f;
			FMOD_Channel_SetVolume(channel, volume);
		}


		if (GetAsyncKeyState(VK_DOWN) < 0 && volume > 0.0f) {
			// ȭ��ǥ �Ʒ��� Ű�� ������ �� 
			volume -= 0.1f;
			FMOD_Channel_SetVolume(channel, volume);
		}

		if (GetAsyncKeyState(VK_ESCAPE) < 0) break;
		Sleep(50);
	}
	title();

}
*/

/*-----�ش� ���� ���-----*/
void Sound_Play(int n) {
	FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[n], 0, &channel);
}
