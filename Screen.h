//파일명 - Screen.h
//설명 - Screen에 관한 함수를 다른 파일에서 사용하기 위해 정의
//작성자 - 장은준
//작성일자 - 2015-04-17

#ifndef __SCREEN_H_
#define __SCRREN_H_

void ScreenInit();
void ScreenFlipping();
void ScreenClear();
void ScreenRelease();
void ScreenPrint(int x, int y, char * string);
void SetColor(unsigned short color);

#endif
