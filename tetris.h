//파일명 - tetris.h
//설명 - 다른 파일에서 테트리스 함수를 사용하기 위해 정의함
//작성자 - 장은준
//작성일자 - 2015-04-17

#ifndef __TETRIS_H_
#define __TETRIS_H_

void BoardInit();
void DrawBoard();


bool Collition(int nx, int ny,int shape);

void PrintBlock(int nx, int ny, int shape);
void RotBlock(int nx,int ny, int shape);
void ExcapeLine(int & score, int & speed);

void CheckDownBlock(int nx,int ny,int shape);



#endif
