#include <graphics.h>
#ifndef _PRINT_H_
#define _PRINT_H_
void button(int x, int y, int w, int h, TCHAR* text);
void exbutton(int x, int y, int w, int h, TCHAR* text);
void pieceprint(int x, int y,int i);
void emphasize(int x, int y, int w, int h, TCHAR* text, MOUSEMSG msg,int *a);
void chesspageprint();
void showchess(int add[10][2]);
void endpageprint(int flag, int add[10][2],FILE* data);
void startpageprint();
void modeselectprint();
FILE *filepageprint(int flag);
void showmouse(MOUSEMSG m);
extern int cou;
extern int ecy;
#endif // !_PRINT_H_
