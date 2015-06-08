//파일명 - tetris.cpp
//설명 - 테트리스 기능구현에 관한 함수들을 정의
//작성자 - 장은준
//작성일자 - 2015-04-17

#include "common.h"
#include "Screen.h"
#include "BlockModel.h"

int g_Board[BH+1][BW+2];

void BoardInit()
{
	int i,j;


		for(i=0;i<BH+1;i++)
		{
			for(j=0;j<BW+2;j++)
			{
				if(j==0||j==BW+1||i==BH)
				{
					g_Board[i][j]=WALL;
				}
				else
				{
					g_Board[i][j]=EMPTY;
				}
			}
		}
	

}


void DrawBoard()
{
	int i,j;

		for(i=0;i<BH+1;i++)
		{
			for(j=0;j<BW+2;j++)
			{
				if(j==0||j==BW+1||i==BH)
				{
					g_Board[i][j]=WALL;
				}
			}
	}
	

	for(i=0;i<BH+1;i++)
	{
		for(j=0;j<BW+2;j++)
		{
			ScreenPrint(j*2,i,(g_Board[i][j]==EMPTY) ? blockShape[EMPTY] : (g_Board[i][j]==BLOCK) ? blockShape[BLOCK] : blockShape[WALL] );
		}
	}
}

bool Collition(int nx, int ny,int shape)	//true = 움직일 수 없다, false = 움직일 수 있다.
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if((blockModel[shape][i][j]==BLOCK)&&(g_Board[ny+i][nx+j]==BLOCK||g_Board[ny+i][nx+j]==WALL))
				return true;
		}
	}

	return false;
}
void PrintBlock(int nx, int ny, int shape)
{
	int i,j;

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(blockModel[shape][i][j]==BLOCK)
				ScreenPrint((nx+j)*2,ny+i,blockShape[BLOCK]);
		}
	}

}

void RotBlock(int nx,int ny, int shape)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(blockModel[shape][i][j]==BLOCK)
			{
				g_Board[ny+i][nx+j]=BLOCK;
			}
		}
	}
}

void ExcapeLine(int & score, int & speed)
{
	int i,j,h;
	int cnt=0;
	for(i=BH;i>0;i--)
	{
		for(j=1;j<=BW;j++)
		{
			if(g_Board[i][j]==BLOCK)
				cnt++;
		}
		if(cnt==BW)
		{
			for(j=1;j<=BW;j++)			//그 줄을 비운다.
			{
				g_Board[i][j]=EMPTY;
			}
			for(h=i;h>0;h--)				//줄이 채워진 그 줄에서 부터 내림
			{
				for(j=1;j<=BW;j++)
				{
					g_Board[h][j]=g_Board[h-1][j];
				}
			}
			i++;
			score+=52;
			speed -= 10;
		}
		cnt=0;

	}
}



void CheckDownBlock(int nx,int ny,int shape)
{
	int y,i,j;
	for(y=ny;y<BH;y++)
	{
		if(Collition(nx,y,shape)==true)
		{
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
				{
					if(blockModel[shape][i][j]==BLOCK)
					{
						ScreenPrint((nx+j)*2,y+i-1,blockShape[CHECK]);
					}
				}
			}
			break;
		}
	}

}

