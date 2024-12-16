#include<graphics.h>
#include<mmsystem.h>
#include<stdio.h>
#include<conio.h>
#include"print.h"
#include"mode.h"
#pragma comment(lib,"winmm.lib")
int qi[16][16];
int hs[3000], bs[3000], bu = 1;
//判断函数
int check(FILE *data) {
	int add[10][2]; 
	memset(add, 0, sizeof(add));
	if (bu == 224) {
		for (int i = 0; i <= 9; i++) { add[i][0] = -10; add[i][1] = -10; }
		endpageprint(3, add, data);
	}
	if (bu % 2 != 0) {//判断黑棋
		//横纵
		int judge = 1;
		add[0][0] = hs[bu]; add[0][1] = hs[bu + 1];
		for (int i = 1; i <= 4; i++) {
			if ((hs[bu] - i) < 0) break;
			if (qi[hs[bu] - i][hs[bu + 1]] == 2) {
				add[i][0] = hs[bu] - i; add[i][1] = hs[bu + 1];
				judge++;
			}
			else break;
		}
		for (int i = 1; i <= 4; i++) {
			if ((hs[bu] + i) > 14) break;
			if (qi[hs[bu] + i][hs[bu + 1]] == 2) {
				add[judge][0] = hs[bu] + i;
				add[judge][1] = hs[bu + 1];
				judge++;
			}
			else break;
		}
		if (judge >= 5) {
			endpageprint(2, add, data);
			return 2;
		}
		judge = 1;
		memset(add, 0, sizeof(add));
		add[0][0] = hs[bu]; add[0][1] = hs[bu + 1];
		for (int i = 1; i <= 4; i++) {
			if ((hs[bu + 1] + i) > 14) break;
			if (qi[hs[bu]][hs[bu + 1] + i] == 2) {
				add[i][0] = hs[bu]; add[i][1] = hs[bu + 1] + i;
				judge++;
			}
			else break;
		}
		for (int i = 1; i <= 4; i++) {
			if ((hs[bu + 1] - i) < 0) break;
			if (qi[hs[bu]][hs[bu + 1] - i] == 2) {
				add[judge][0] = hs[bu];
				add[judge][1] = hs[bu + 1] - i;
				judge++;
			}
			else break;
		}
		if (judge >= 5) {
			endpageprint(2, add,data);
			return 2;
		}
		//判断斜线
		judge = 1;//注意此处坐标轴y向下为正方向
		memset(add, 0, sizeof(add));
		add[0][0] = hs[bu]; add[0][1] = hs[bu + 1];
		for (int i = 1; i <= 4; i++) {//图片左下右上位置
			if (hs[bu] + i > 14 || hs[bu + 1] - i < 0) break;//防止越界
			if (qi[hs[bu] + i][hs[bu + 1] - i] == 2) {
				add[i][0] = hs[bu] + i; add[i][1] = hs[bu + 1] - i;
				judge++;
			}
			else break;
		}
		for (int i = 1; i <= 4; i++) {
			if (hs[bu] - i < 0 || hs[bu + 1] + i>14) break;
			if (qi[hs[bu] - i][hs[bu + 1] + i] == 2) {
				add[judge][0] = hs[bu] - i;
				add[judge][1] = hs[bu + 1] + i;
				judge++;
			}
			else break;
		}
		if (judge >= 5) {
			endpageprint(2, add, data);
			return 2;
		}
		judge = 1;
		memset(add, 0, sizeof(add));
		add[0][0] = hs[bu]; add[0][1] = hs[bu + 1];
		for (int i = 1; i <= 4; i++) {//图片左上右下位置
			if (hs[bu] - i < 0 || hs[bu + 1] - i < 0) break;
			if (qi[hs[bu] - i][hs[bu + 1] - i] == 2) {
				add[i][0] = hs[bu] - i; add[i][1] = hs[bu + 1] - i;
				judge++;
			}
			else break;
		}
		for (int i = 1; i <= 4; i++) {
			if (hs[bu] + i > 14 || hs[bu + 1] + i > 14) break;
			if (qi[hs[bu] + i][hs[bu + 1] + i] == 2) {
				add[judge][0] = hs[bu] + i;
				add[judge][1] = hs[bu + 1] + i;
				judge++;
			}
			else break;
		}
		if (judge >= 5) {
			endpageprint(2, add, data);
			return 2;
		}
	}
	else {//判断白棋横纵
		int judge = 1;
		memset(add, 0, sizeof(add));
		add[0][0] = bs[bu]; add[0][1] = bs[bu + 1];
		for (int i = 1; i <= 4; i++) {
			if ((bs[bu] - i) < 0) break;
			if (qi[bs[bu] - i][bs[bu + 1]] == 1) {
				add[i][0] = bs[bu] - i; add[i][1] = bs[bu + 1];
				judge++;
			}
			else break;
		}
		for (int i = 1; i <= 4; i++) {
			if ((bs[bu] + i) > 14) break;
			if (qi[bs[bu] + i][bs[bu + 1]] == 1) {
				add[judge][0] = bs[bu] + i;
				add[judge][1] = bs[bu + 1];
				judge++;
			}
			else break;
		}
		if (judge >= 5) {
			endpageprint(1, add,data);
			return 1;
		}
		memset(add, 0, sizeof(add));
		judge = 1;
		add[0][0] = bs[bu]; add[0][1] = bs[bu + 1];
		for (int i = 1; i <= 4; i++) {
			if ((bs[bu + 1] + i) > 14) break;
			if (qi[bs[bu]][bs[bu + 1] + i] == 1) {
				add[i][0] = bs[bu]; add[i][1] = bs[bu + 1] + i;
				judge++;
			}
			else break;
		}
		for (int i = 1; i <= 4; i++) {
			if ((bs[bu + 1] - i) < 0) break;
			if (qi[bs[bu]][bs[bu + 1] - i] == 1) {
				add[judge][0] = bs[bu];
				add[judge][1] = bs[bu + 1] - i;
				judge++;
			}
			else break;
		}
		if (judge >= 5) {
			endpageprint(1, add, data);
			return 1;
		}
		memset(add, 0, sizeof(add));
		judge = 1;//注意此处坐标轴y向下为正方向
		add[0][0] = bs[bu]; add[0][1] = bs[bu + 1];
		for (int i = 1; i <= 4; i++) {//图片左下右上位置
			if (bs[bu] + i > 14 || bs[bu + 1] - i < 0) break;//防止越界
			if (qi[bs[bu] + i][bs[bu + 1] - i] == 1) {
				add[i][0] = bs[bu] + i; add[i][1] = bs[bu + 1] - i;
				judge++;
			}
			else break;
		}
		for (int i = 1; i <= 4; i++) {
			if (bs[bu] - i < 0 || bs[bu + 1] + i>14) break;
			if (qi[bs[bu] - i][bs[bu + 1] + i] == 1) {
				add[judge][0] = bs[bu] - i;
				add[judge][1] = bs[bu + 1] + i;
				judge++;
			}
			else break;
		}
		if (judge >= 5) {
			endpageprint(1, add,data);
			return 1;
		}
		judge = 1;
		memset(add, 0, sizeof(add));
		add[0][0] = bs[bu]; add[0][1] = bs[bu + 1];
		for (int i = 1; i <= 4; i++) {//图片左上右下位置
			if (bs[bu] - i < 0 || bs[bu + 1] - i < 0) break;
			if (qi[bs[bu] - i][bs[bu + 1] - i] == 1) {
				add[i][0] = bs[bu] - i; add[i][1] = bs[bu + 1] - i;
				judge++;
			}
			else break;
		}
		for (int i = 1; i <= 4; i++) {
			if (bs[bu] + i > 14 || bs[bu + 1] + i > 14) break;
			if (qi[bs[bu] + i][bs[bu + 1] + i] == 1) {
				add[judge][0] = bs[bu] + i;
				add[judge][1] = bs[bu + 1] + i;
				judge++;
			}
			else break;
		}
		if (judge >= 5) {
			endpageprint(1, add, data);
			return 1;
		}
	}
	return 0;
}
//悔棋函数
void regret() {
	chesspageprint();
	for (int i = 1; i <= bu; i++) {
		if (i % 2 != 0) {
			setfillcolor(BLACK);
			solidcircle(hs[i] * 40 + 220, hs[i + 1] * 40 + 70, 15);
		}
		else {
			setfillcolor(WHITE);
			solidcircle(bs[i] * 40 + 220, bs[i + 1] * 40 + 70, 15);
		}
	}
}
//纯粹是为减少replay函数代码量
void replayprint(int add[10][2],FILE *data) {
	MOUSEMSG m; int a[2] = { 0 }; int b[2] = { 0 }; int c[2] = { 0 }; int d[2] = { 0 };
	TCHAR button1[15] = { "退出" };
	TCHAR button2[15] = { "继续" };
	TCHAR button5[15] = { "音乐暂停" };
	TCHAR button6[15] = { "音乐继续" };
	button(800, 500, 100, 35, button2);
	button(800, 550, 100, 35, button1);
	button(80, 500, 100, 35, button5);
	int j = 0;
	for (int i = 1; i <= bu; i++) {
		if (i % 2 != 0) {
			setfillcolor(BLACK);
			Sleep(500);
			solidcircle(hs[i] * 40 + 220, hs[i + 1] * 40 + 70, 15);
		}
		else {
			setfillcolor(WHITE);
			Sleep(500);
			solidcircle(bs[i] * 40 + 220, bs[i + 1] * 40 + 70, 15);
		}
		while (1) {
			m = GetMouseMsg();
			emphasize(800, 500, 100, 35, button2, m, a);
			emphasize(800, 550, 100, 35, button1, m, b);
			if (j == 0) emphasize(80, 500, 100, 35, button5, m, c);
			else  emphasize(80, 500, 100, 35, button6, m, d);
			if (m.mkLButton && m.x >= 800 && m.x <= 900 && m.y >= 500 && m.y <= 535) {
				break;
			}
			if (m.mkLButton && m.x >= 800 && m.x <= 900 && m.y >= 550 && m.y <= 585) {
				fclose(data);
				mciSendString("close ../replay.mp3", 0, 0, 0);
				modeselectprint();
			}
			if (m.x >= 80 && m.x <= 180 && m.y >= 500 && m.y <= 535&&m.mkLButton) {
				if (j == 0) {
					button(80, 500, 100, 35, button6); mciSendString("pause ../replay.mp3", 0, 0, 0); j = 1;
					continue;
				}
				if (j == 1) {
					button(80, 500, 100, 35, button5); mciSendString("resume ../replay.mp3", 0, 0, 0); j = 0;
				}
			}
		}
	}
}
//复盘函数
void replay(int add[10][2], FILE* data) {
	Sleep(3000);
	HWND hnd = GetHWnd();
	int click = MessageBox(hnd, "是否复盘", "棋局结束", MB_OKCANCEL);
	if (click == IDOK) {
		IMAGE chessboard;
		loadimage(&chessboard, "../print/chessboard.jpg", 960, 630, false);
		setbkcolor(RGB(253, 255, 218));
		cleardevice();
		putimage(20, 15, &chessboard);
		mciSendString("open ../replay.mp3", 0, 0, 0);
		mciSendString("play ../replay.mp3 repeat", 0, 0, 0);
		IMAGE wssbecy2;
		loadimage(&wssbecy2, "../print/endpage.jpg", 190, 190);
		if(ecy==1)putimage(25, 180, &wssbecy2);
		setbkmode(TRANSPARENT);
		settextstyle(17, 0, _T("方正舒体"));
		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 2);
		for (int i = 70; i <= 630; i += 40) {
			line(220, i, 780, i);
		}
		for (int i = 220; i <= 780; i += 40) {
			line(i, 70, i, 630);
		}
		HWND hnd2 = GetHWnd();
		int click2 = MessageBox(hnd2, "是否进行自动演示", "复盘", MB_OKCANCEL);
		if (click2 == IDCANCEL) {
			replayprint(add,data);
			mciSendString("close ../replay.mp3", 0, 0, 0);
			endpageprint(bu % 2 + 1, add, data);
		}
		else if (click2 == IDOK) {
			settextcolor(BLACK);
			if (ecy == 1)outtextxy((110 - textwidth(_T("要暂停自己打开控制台按空格！")) / 2), 380, _T("要暂停自己打开控制台按空格！"));
			for (int i = 1; i <= bu; i++) {
				if (i % 2 != 0) {
					setfillcolor(BLACK);
					Sleep(500);
					solidcircle(hs[i] * 40 + 220, hs[i + 1] * 40 + 70, 15);
				}
				else {
					setfillcolor(WHITE);
					Sleep(500);
					solidcircle(bs[i] * 40 + 220, bs[i + 1] * 40 + 70, 15);
				}
				if (_kbhit() != 0) {
					if (GetAsyncKeyState(VK_SPACE)) system("Pause");
				}
			}
			mciSendString("close ../replay.mp3", 0, 0, 0);
			if (bu == 224) endpageprint(3, add, data);
			else endpageprint(bu % 2 + 1, add, data);
		}
	}
		else if (click == IDCANCEL) {
			fclose(data);
			modeselectprint();
		}
	}
//以二维数组为参量勾画棋盘
void reprint(){
	for (int row = 0; row < 15; row++) {
		for (int col = 0; col < 15; col++) {
			if (qi[row][col] == 1) {
				setfillcolor(WHITE);
				solidcircle(row*40+220,col*40+70,15);
			}
			else if(qi[row][col]==2){
				setfillcolor(BLACK);
				solidcircle(row*40+220,col*40+70, 15);
			}
		}
	}
}
//由原先记录的文档读入
int datainput(FILE *data) {
	int i = 1;
	int flag; int a, b, c, d;
	fscanf_s(data,"%d%d%d%d",&a,&b,&c,&d);
	while (1) {
		if (i % 2 != 0) {
			if (fscanf_s(data, "%d%d%d", &hs[i], &hs[i + 1], &flag)== EOF) break;
			if (flag == 0) {
				qi[hs[i]][hs[i + 1]] = 2;
				i++;
			}
			else {//悔棋棋子位置判断
				qi[hs[i]][hs[i + 1]] = 0;
				for (int j = 1; j < i; j++) {
					if (hs[j] == hs[i] && hs[j + 1] == hs[i + 1]) {
						hs[j] = -10; hs[j + 1] = -10;
					}
				}
			}
		}
		else {//白棋情况
			if (fscanf_s(data, "%d%d%d\n", &bs[i], &bs[i + 1],&flag) == EOF) break;
			if (flag == 0) {
				qi[bs[i]][bs[i + 1]] = 1;
				i++;
			}
			else {
				qi[bs[i]][bs[i + 1]] = 0;
				for (int j = 2; j <i; j++) {
					if (bs[j] == bs[i] && bs[j + 1] == bs[i + 1]) {
						bs[j] = -10; bs[j + 1] = -10;
					}
				}
			}
		}
	}
	reprint();
	return i;
}