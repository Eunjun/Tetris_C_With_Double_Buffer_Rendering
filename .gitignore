//파일명 - main.cpp
//설명 - 프레임워크 안에서 테트리스를 구현함.
//작성자 - 장은준
//작성일자 - 2015-04-17

#include "Screen.h"

#include "tetris.h"

#include "common.h"

#include <fmod.h>

FMOD_SYSTEM * g_System;
FMOD_SOUND * g_Sound[4];	//1.explore 2.pickup 3.select
FMOD_CHANNEL * channel[2];
FMOD_BOOL IsPlaying;

#define START_X			5
#define START_Y			0

//enum {EMPTY,BLOCK,WALL,CHECK};

clock_t movetime=clock();

int shape;
int nextshape;
int keepshape=-1;
int score=0;
int speed=1000;

int BlockX=START_X;
int BlockY=START_Y;

void ProcessKey()
{
	int nkey;
	if(_kbhit())
	{
		if(nkey = _getch())
		{
			switch(nkey)
			{
			case UP:
				if(shape%4==3)				//블록 회전구현
				{
					if(Collition(BlockX,BlockY,shape-3)==false)
					{
					    shape -=3; 
					}
					else
					{
						if(Collition(BlockX+1,BlockY,shape-3)==false)
						{
							BlockX++;
							shape-=3;
						}
						else if(Collition(BlockX-1,BlockY,shape-3)==false)
						{
							BlockX--;
							shape-=3;
						}
					}
				}
				else
				{
					if(Collition(BlockX,BlockY,shape+1)==false)
					{
					    shape++;
					}
					else
					{
						if(Collition(BlockX+1,BlockY,shape+1)==false)
						{
							BlockX++;
							shape++;
						}
						else if(Collition(BlockX-1,BlockY,shape+1)==false)
						{
							BlockX--;
							shape++;
						}
					}
				}
				FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[2],0,&channel[1]);
				break;

			case DOWN:
				if(Collition(BlockX,BlockY+1,shape)==false)
				    BlockY++;
				FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[2],0,&channel[1]);
				break;

			case LEFT:
				if(Collition(BlockX-1,BlockY,shape)==false)
				    BlockX--;
				FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[2],0,&channel[1]);
				break;

			case RIGHT:
				if(Collition(BlockX+1,BlockY,shape)==false)
				    BlockX++;
				FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[2],0,&channel[1]);
				break;

			case SPACE:
				int i;
				for(i=BlockY;i<BH;i++)
				{
					if(Collition(BlockX,i,shape)==true)
					{
						i -= 1;
						RotBlock(BlockX,i,shape);
						BlockX = START_X;
						BlockY = START_Y;
						ExcapeLine(score,speed);
						shape = nextshape;
						nextshape = rand()%7*4;
						break;
					}
				}
				FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[3],0,&channel[1]);
				break;

			case ENTER:
				int temp;

				BlockX=START_X;
				BlockY=START_Y;

				if(keepshape == -1)
				{
					keepshape = shape;
				    shape = nextshape;
					nextshape = rand()%7*4;
				}
			    
				else
				{
					temp = shape;
					shape = keepshape;
					keepshape = temp;
				}
                
				FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[3],0,&channel[1]);
				break;
			default:
				;

			}
		}
		
	}
}

void Init()
{
	srand((unsigned int)time(NULL));
	shape = rand()%7*4;
	nextshape = rand()%7*4;

	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System,32,FMOD_INIT_NORMAL,NULL);
	FMOD_System_CreateSound(g_System,"Tetris_Theme.mp3",FMOD_DEFAULT,0,&g_Sound[0]);
	FMOD_System_CreateSound(g_System,"explore.wav",FMOD_DEFAULT,0,&g_Sound[1]);
	FMOD_System_CreateSound(g_System,"pickup.wav",FMOD_DEFAULT,0,&g_Sound[2]);
	FMOD_System_CreateSound(g_System,"select.wav",FMOD_DEFAULT,0,&g_Sound[3]);

	FMOD_Channel_SetVolume(channel[1],0.3f);


	ScreenInit();
	BoardInit();
}

void Update()
{
	ProcessKey();
	clock_t CurTime;
	

	CurTime = clock();

	if(CurTime - movetime > speed) 
	{
		movetime = CurTime;
		if(Collition(BlockX,BlockY+1,shape)==false)
		{
		    BlockY++;
		}
		else
		{
			RotBlock(BlockX,BlockY,shape);
			BlockX = START_X;
			BlockY = START_Y;
			ExcapeLine(score,speed);
			shape = nextshape;
			nextshape = rand()%7*4;
		}

	}
}

void Render()
{
	char watermark[3][50] = { { 0 }, { 0 } };
	char howtoplay[5][100] = { { 0 }, { 0 } };
	char info[3][100] = { { 0 }, { 0 } };
	char string[100] = {0};

	ScreenClear();
	DrawBoard();
	CheckDownBlock(BlockX,BlockY,shape);
	PrintBlock(BlockX,BlockY,shape);

	sprintf(watermark[0],"테트리스(tetris) ver 1.3");
	sprintf(watermark[1],"제작자 : 칼맞은노치");
	sprintf(howtoplay[0],"←→ : 좌우이동");
	sprintf(howtoplay[1]," ↑  : 블록 회전");
	sprintf(howtoplay[2]," ↓  : 블록 아래로 한칸 내림");
	sprintf(howtoplay[3],"space: 블록 아래로 전부 내림");
	sprintf(howtoplay[4],"enter: 블록 저장");

	sprintf(info[0],"score : %d",score);
	sprintf(info[1],"다음블록");
	sprintf(info[2],"저장된 블록");

	

	ScreenPrint(26,1,watermark[0]);
	ScreenPrint(26,2,watermark[1]);
	for(int i = 0;i<5;i++)
	{
		ScreenPrint(26,3+i,howtoplay[i]);
	}
	ScreenPrint(26,8,info[0]);
	ScreenPrint(26,10,info[1]);
	PrintBlock(14,11,nextshape);



	if(keepshape!=-1)
	{
	    ScreenPrint(26,15,info[2]);
		PrintBlock(14,16,keepshape);
	}
	ScreenFlipping();
}

void Release()
{
	for(int i = 0; i<4; i++)
		FMOD_Sound_Release(g_Sound[i]);
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}

int main()
{
	channel[0] = NULL;
	channel[1] = NULL;
	
	clock_t CurTime, OldTime;
	char string[100] = {0};

	
	Init();
    FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[0],0,&channel[0]);
	OldTime = clock();
	while(1)
	{
		
		Update();
		Render();
        if(Collition(START_X,START_Y,shape))
			break;
		while(1)
		{
			CurTime = clock();

			if(CurTime - OldTime > 33) 
			{
				OldTime = CurTime;
				break;
			}

		}
		FMOD_Channel_IsPlaying(channel[0],&IsPlaying);
		if (IsPlaying == 0)
			FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[0],0,&channel[0]);
		FMOD_System_Update(g_System);
	}
    
	
	Release();
	ScreenRelease();

	system("cls");
	printf("G A M E  O V E R ! !\n");
	system("pause");
	
	return 0;
}



