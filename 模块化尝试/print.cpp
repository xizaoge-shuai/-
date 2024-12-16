#include<graphics.h>
#include<mmsystem.h>
#include<pthread.h>
#include"function.h"
#include"mode.h"
#include"print.h"
#pragma comment(lib,"winmm.lib")
int cou = 0;
//普通按钮
void button(int x, int y, int w, int h, TCHAR* text) {//封装按钮绘制
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(207, 255, 249));
	fillroundrect(x, y, x + w, y + h, 10, 10);
	settextstyle(25, 0, _T("方正舒体"));
	settextcolor(BLACK);
	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;
	outtextxy(tx, ty, (text));
}
//强调按钮
void exbutton(int x, int y, int w, int h, TCHAR* text) {//封装强调按钮绘制
	setbkmode(TRANSPARENT);
	setfillcolor(RED);
	fillroundrect(x, y, x + w, y + h, 10, 10);
	settextstyle(30, 0, _T("方正舒体"));
	settextcolor(WHITE);
	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;
	outtextxy(tx, ty, (text));
}
//棋子绘制
void pieceprint(int x, int y,int i) {
	mciSendString("open ../chess.mp3", 0, 0, 0);
	mciSendString("play ../chess.mp3", 0, 0, 0);
	if (i > 1) {
		if ((i - 1) % 2 != 0) {
			setfillcolor(BLACK);
			solidcircle(hs[i - 1] * 40 + 220, hs[i] * 40 + 70, 15);
		}
		else {
			setfillcolor(WHITE);
			solidcircle(bs[i - 1] * 40 + 220, bs[i] * 40 + 70, 15);
		}
	}
	if (i % 2 != 0) {
		setfillcolor(BLACK);
		solidcircle(x, y, 15);
	}
	else {
		setfillcolor(WHITE);
		solidcircle(x, y, 15);
	}
	setfillcolor(RED);
	solidcircle(x, y, 4);
	Sleep(200);
	mciSendString("close ../chess.mp3", 0, 0, 0);
}
//强调鼠标停留位置
void emphasize(int x, int y, int w, int h, TCHAR* text, MOUSEMSG msg,int *a) {
	if (msg.x>=x&&msg.x<=x+w&&msg.y>=y&&msg.y<=y+h) {
		if (a[1] == 0) {
			exbutton(x, y, w, h, text);
			a[0] = 0;
			a[1] = 1;
		}
	}
	else {
		if (a[0] == 0) {
			button(x, y, w, h, text);
			a[0] = 1;
			a[1] = 0;
		}
	}
}
//棋盘打印
void chesspageprint() {
	IMAGE chessboard;
	loadimage(&chessboard, "../print/chessboard.jpg", 960, 630, false);
	setbkcolor(RGB(253, 255, 218));
	cleardevice();
	putimage(20,15, &chessboard);
	TCHAR button1[40] = { "悔棋" };
	TCHAR button2[100] = { "返回" };
	TCHAR button5[15] = { "音乐暂停" };
	TCHAR button6[15] = { "音乐继续" };
	button(800,550, 100, 35, button1);
	button(800, 590, 100, 35, button2);
	button(80, 500, 100, 35, button5);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	for (int i = 70; i <= 630; i += 40) {
		line(220, i, 780, i);
	}
	for (int i = 220; i <= 780; i += 40) {
		line(i, 70, i, 630);
	}
}
//结束显示五子连珠位置
void showchess(int add[10][2]) {
	setfillcolor(RED);
	for (int i = 0; i < 5; i++) {
		solidcircle(add[i][0] * 40 + 220, add[i][1] * 40 + 70, 15);
	}
}
//开始界面展示
void startpageprint() {
	initgraph(1000,667);
	setbkcolor(RGB(253, 255, 218));
	cleardevice();
	IMAGE startimage;
	loadimage(&startimage,"../print/startimage.jpg");
	putimage(0, 0, &startimage);
	setbkmode(TRANSPARENT);
	settextstyle(70, 0, _T("方正舒体"));
	settextcolor(BLACK);
	outtextxy((500 - textwidth(_T("五子棋")) / 2), 70, _T("五子棋"));
	settextstyle(20, 0, _T("宋体"));
	outtextxy((900 - textwidth(_T("by 彭浩东")) / 2), 620, _T("by 彭浩东"));
	outtextxy((850 - textwidth(_T("2023 计算机科学与技术 3班")) / 2), 640, _T("2023 计算机科学与技术 3班"));
	TCHAR button1[100] = { "开始游戏" };
	button(400, 525, 200, 55, button1);
}
//文档选择界面
void filechoose() {
	int a[2] = { 0 };
	int b[2] = { 0 };
	int c[2] = { 0 };
	int d[2] = { 0 };
	int e[2] = { 0 };
	MOUSEMSG msg;
	int select = 0;
	setbkcolor(RGB(253, 255, 218));
	cleardevice();
	IMAGE startimage;
	IMAGE wssbecy;
	loadimage(&startimage, "../print/startimage.jpg");
	putimage(0, 0, &startimage);
	loadimage(&wssbecy, "../print/wssbecy.jpg", 378, 600);
	if (ecy == 1)putimage(20, 50, &wssbecy);
	setbkmode(TRANSPARENT);
	settextstyle(60, 0, _T("方正舒体"));
	settextcolor(BLACK);
	outtextxy((500 - textwidth(_T("以何种模式打开")) / 2), 70, _T("以何种模式打开"));
	TCHAR button1[100] = { "人人对战" };
	TCHAR button2[100] = { "人机对战(简单)" };
	TCHAR button3[100] = { "人机对战(困难)" };
	TCHAR button4[100] = { "返回" };
	char button6[50] = { "机机对战" };
	button(400, 200, 200, 55, button1);
	button(400, 300, 200, 55, button2);
	button(400, 400, 200, 55, button3);
	button(800, 550, 110, 35, button4);
	button(400, 500, 200, 55, button6);
	while (1) {
		msg = GetMouseMsg();//获取鼠标信息
		emphasize(400, 200, 200, 55, button1, msg, a);
		emphasize(400, 300, 200, 55, button2, msg, b);
		emphasize(400, 400, 200, 55, button3, msg, c);
		emphasize(800, 550, 110, 35, button4, msg, d);
		emphasize(400, 500, 200, 55, button6, msg, e);
		if (msg.mkLButton) {
			if (msg.x >= 400 && msg.x <= 600 && msg.y <= 255 && msg.y >= 200) {
				pvp(1);
				break;
			}
			if (msg.x >= 800 && msg.y <= 900 && msg.y >= 550 && msg.y <= 585) {
				modeselectprint();
			}
			if (msg.x >= 400 && msg.y <= 600 && msg.y >= 300 && msg.y <= 355) pve(1,1);
			if (msg.x >= 400 && msg.y <= 600 && msg.y >= 500 && msg.y <= 555) eve(1);
		}
	}
}
//模式选择界面打印
void modeselectprint() {
	int a[2] = { 0 };int b[2] = { 0 };int c[2] = { 0 };
	int d[2] = { 0 };int e[2] = { 0 };int f[2] = { 0 };
	MOUSEMSG msg;
	int select = 0;
	setbkcolor(RGB(253, 255, 218));
	cleardevice();
	IMAGE startimage;
	IMAGE wssbecy;
	loadimage(&startimage, "../print/startimage.jpg");
	putimage(0, 0, &startimage);
	loadimage(&wssbecy, "../print/wssbecy.jpg",378,600);
	//putimage(20, 50, &wssbecy);
	setbkmode(TRANSPARENT);
	settextstyle(70, 0, _T("方正舒体"));
	settextcolor(BLACK);
	outtextxy((500 - textwidth(_T("模式选择")) / 2), 70, _T("模式选择"));
	TCHAR button1[100] = { "人人对战" };
	TCHAR button2[100] = { "人机对战(简单)" };
	TCHAR button3[100] = { "人机对战(困难)" };
	TCHAR button4[100] = { "退出" };
	TCHAR button5[50] = { "读取存档" };
	char button6[50] = { "机机对战" };
	button(400, 200, 200, 55, button1);
	button(400, 300, 200, 55, button2);
	button(400, 400, 200, 55, button3);
	button(800, 550, 110, 35, button4);
	button(800, 590, 110, 35, button5);
	button(800, 510, 110, 35, button6);

	while (1) {
		msg = GetMouseMsg();//获取鼠标信息
		emphasize(400, 200, 200, 55, button1, msg, a);
		emphasize(400, 300, 200, 55, button2, msg, b);
		emphasize(400, 400, 200, 55, button3, msg, c);
		emphasize(800, 510, 110, 35, button6, msg, f);
		emphasize(800, 550, 110, 35, button4, msg, d);
		emphasize(800, 590, 110, 35, button5, msg, e);
		if (msg.mkLButton) {
			if (msg.x >= 400 && msg.x <= 600 && msg.y <= 255 && msg.y >= 200) {
				select = 1;
				break;
			}
			if (msg.x >= 800 && msg.x <= 910 && msg.y >= 550 && msg.y <= 585) {
				HWND hnd = GetHWnd();
				int click = MessageBox(hnd, "确认退出吗", "退出", MB_OKCANCEL | MB_ICONINFORMATION);
				if (click == IDOK) {
					if (ecy == 1) {
						IMAGE picture[800];
						char name[50];
						setbkcolor(BLACK);
						cleardevice();
						setbkmode(TRANSPARENT);
						settextstyle(70, 0, _T("Blackadder ITC"));
						settextcolor(WHITE);
						outtextxy((500 - textwidth(_T("Thanks")) / 2), 40, _T("Thanks"));
						for (int i = 0; i <= 719; i++) {
							sprintf_s(name, "../video/exit2/exit20%d.jpg", 1000 + i);
							loadimage(&picture[i], name, 720, 480);
						}
						mciSendString("open ../video/exitaudio2.mp3", 0, 0, 0);
						mciSendString("play ../video/exitaudio2.mp3", 0, 0, 0);
						for (int i = 0; i <= 719; i++) {
							putimage(140, 110, &picture[i]);
							Sleep(40);
						}
						cleardevice();
						outtextxy((500 - textwidth(_T("Exit")) / 2), 40, _T("Exit"));
						Sleep(1000);
					}
					exit(0);
				}
			}
			if (msg.x >= 800 && msg.x <= 910 && msg.y >= 590 && msg.y <= 625)filechoose();
			if (msg.x >= 400 && msg.x <= 600 && msg.y >= 300 && msg.y <= 355) pve(0,1);
			if (msg.x >= 800 && msg.x <= 910 && msg.y >= 510 && msg.y <= 545) eve(0);
			if (msg.x >= 400 && msg.x <= 600 && msg.y >= 400 && msg.y <= 455) pve(0,3);
		}
	}
	if (select == 1) {
		chesspageprint();
		pvp(0);
	}
}
//动画展示
void videoshow() {
	char picname[50];
	IMAGE video[150];
	for (int i = 10; i <= 143; i++) {
		sprintf_s(picname, "../video/endpage/picture%d.jpg", 1000 + i);
		loadimage(&video[i], picname, 190, 108);
	}
	for (int i = 10; i <= 143; i++) {
		putimage(30, 220, &video[i]);
		Sleep(20);
	}
}
//结束界面展示
void endpageprint(int flag, int add[10][2], FILE* data) {
	IMAGE wssbecy2;
	showchess(add);
	mciSendString("close ../bgm.mp3", 0, 0, 0);
	setbkmode(TRANSPARENT);
	settextstyle(45, 0, _T("方正舒体"));
	settextcolor(BLACK);
	if (ecy == 1) {
		videoshow();
		outtextxy((110 - textwidth(_T("拿捏~")) / 2), 330, _T("拿捏~"));
		loadimage(&wssbecy2, "../print/endpage2.jpg", 190, 123);
		putimage(780, 220, &wssbecy2);
	}
	settextstyle(70, 0, _T("方正舒体"));
	Sleep(300);
	if (flag == 2) {
		settextcolor(BLACK);
		outtextxy((860 - textwidth(_T("黑棋胜")) / 2), 150, _T("黑棋胜"));
		settextstyle(38, 0, _T("方正舒体"));
		settextcolor(RGB(255, 0, 198));
		Sleep(300);
		if (ecy == 1)outtextxy((880 - textwidth(_T("我可没输~")) / 2), 345, _T("我可没输~"));
	}
	else if (flag == 1) {
		settextcolor(WHITE);
		outtextxy((860 - textwidth(_T("白棋胜")) / 2), 150, _T("白棋胜"));
		settextstyle(38, 0, _T("方正舒体"));
		settextcolor(RGB(255, 0, 198));
		Sleep(300);
		if (ecy == 1)outtextxy((880 - textwidth(_T("算你运气好~")) / 2), 345, _T("算你运气好~"));
	}
	else {
		settextcolor(RED);
		outtextxy((860 - textwidth(_T("和棋")) / 2), 150, _T("和棋"));
		settextstyle(38, 0, _T("方正舒体"));
		settextcolor(RGB(255, 0, 198));
		Sleep(300);
		if (ecy == 1)outtextxy((880 - textwidth(_T("再来一把~")) / 2), 345, _T("再来一把~"));
	}
	replay( add, data);
}
//文件输出界面
FILE *filepageprint(int flag) {//文件操作页面
	int f=1; int sel = 0;
	FILE* name = NULL;
	FILE *c = NULL;
	while (1) {//计算当前有多少文件
		c = NULL;
		char prefix1[30] = {"../chessdata/chessdata"};
		char suffix1 = f + '0';
		char str1[5] = { ".csv" };
		char str12[10]; str12[0] = suffix1; str12[1] = '\0';
		strcat_s(str12, str1);
		strcat_s(prefix1, str12);
		if (fopen_s(&c,prefix1,"r")) { cou = f - 1; break; }
		fclose(c);
		f++;
	}
	 int count;
	if (flag == 0) {//新建文件的情况 
		if (cou >=9) cou = 0;
		cou++;
		count = cou;
		char prefix[30] = {"../chessdata/chessdata"};
		char suffix = count + '0';
		char str[5] = { ".csv" };
		char str2[10]; str2[0] = suffix; str2[1] = '\0';
		strcat_s(str2, str);
		strcat_s(prefix, str2);
		fopen_s(&name,prefix, "w+");
		time_t ctime;
		time(&ctime);
		struct tm p;
		localtime_s(&p,&ctime);
		fprintf(name, "%d %d %d %d\n", p.tm_year + 1900, p.tm_mon + 1, p.tm_mday, p.tm_hour);
	}
	if(flag==1){//读取之前的文件
		int a[2] = { 0 }; int judge = 0;
		MOUSEMSG m;
 		setbkcolor(RGB(253, 255, 218));
		cleardevice();
		IMAGE startimage;
		IMAGE wssbecy;
		loadimage(&startimage, "../print/startimage.jpg");
		putimage(0, 0, &startimage);
		loadimage(&wssbecy, "../print/wssbecy.jpg", 378, 600);
		if (ecy == 1)putimage(20, 50, &wssbecy);
		TCHAR button1[10] = { "data" };
		TCHAR button2[15] = { "新开对局" };
		if (cou == 0) {//无存档提醒
			setbkmode(TRANSPARENT);
			settextstyle(70, 0, _T("方正舒体"));
			settextcolor(BLACK);
			outtextxy((500 - textwidth(_T("无存档")) / 2), 300, _T("无存档"));
		}
		for (int i = 1; i <= cou; i++) {
			int y = i*60;
			int a, b, c, d;
			char prefix3[35] = { "../chessdata/chessdata" };
			char suffix3 = i + '0';
			char str[5] = { ".csv" };
			char str2[10]; str2[0] = suffix3; str2[1] = '\0';
			strcat_s(str2, str);
			strcat_s(prefix3, str2);
			fopen_s(&name, prefix3, "r");
			fscanf_s(name, "%d%d%d%d", &a, &b, &c, &d);
			char title[15] = { '\0'};
			a -= 2000;
			title[0] = a / 10 + '0'; title[1] = a % 10 + '0'; title[2] = '.';
			title[3] = b / 10 + '0'; title[4] = b % 10 + '0'; title[5] = '.';
			title[6] = c / 10 + '0'; title[7] = c % 10 + '0';
			button(450, y, 100, 35, title);
			fclose(name);
			name = NULL;
		}
		button(800, 550, 100, 35, button2);
		while (1) {
			m = GetMouseMsg();
			emphasize(800, 550, 100, 35,button2,m,a);
			//读取文件
				for (int i = 1; i <= cou; i++) {
				if (m.x >= 450 && m.x <= 550 && m.y >= i * 60 && m.y <= i * 60 + 35&&m.mkLButton) {
					HWND hnd = GetHWnd();
					int click = MessageBox(hnd, "确认读取吗？", "读取存档喵", MB_OKCANCEL | MB_ICONINFORMATION);
					if (click == IDOK) {
						sel = 1;
						count = i;
						break;
					}
				}
				//删除文件
				if (m.x >= 450 && m.x <= 550 && m.y >= i * 60 && m.y <= i * 60 + 35 && m.mkMButton) {
					HWND hnd = GetHWnd();
					int click = MessageBox(hnd, "确认删除吗？", "删除存档喵", MB_OKCANCEL | MB_ICONINFORMATION);
					if (click == IDOK) {
						char prefix3[35] = { "../chessdata/chessdata" };
						char suffix3 = i + '0';
						char str[5] = { ".csv" };
						char str2[10]; str2[0] = suffix3; str2[1] = '\0';
						strcat_s(str2, str);
						strcat_s(prefix3, str2);
						remove(prefix3);
						for (int j = i + 1; j <= cou; j++) {
							char prefix5[40] = { "../chessdata/chessdata" };
							char suffix5 = j + '0';
							str2[0] = suffix5; str2[1] = '\0';
							strcat_s(str2, str);
							strcat_s(prefix5, str2);
							char prefix4[40] = { "../chessdata/chessdata" };
							char suffix4 = j - 1 + '0';
							str2[0] = suffix4; str2[1] = '\0';
							strcat_s(str2, str);
							strcat_s(prefix4, str2);
							rename(prefix5, prefix4);
						}
						judge = 1;
						break;
					}
				}
			}
				if (m.x >= 800 && m.x <= 900 && m.y >= 550 && m.y <= 585&&m.mkLButton) {
					modeselectprint();
					break;
				}
				if (judge == 1) break;
			if (sel == 1) break;
		}
		if (judge == 1) filepageprint(1);
		if (sel == 1) {
			char prefix2[35] = { "../chessdata/chessdata" };
			char suffix2 = count + '0';
			char str[5] = { ".csv" };
			char str2[10]; str2[0] = suffix2; str2[1] = '\0';
			strcat_s(str2, str);
			strcat_s(prefix2, str2);
			fopen_s(&name, prefix2, "a+");
		}
	}
	return name;
}
//显示鼠标位置
void showmouse(MOUSEMSG m) {
	if (m.x >= 210 && m.x <= 790 && m.y >= 60 && m.y <= 645) {
		int wei1 = abs(m.x - 220);
		int x = wei1 / 40;
		int panx = wei1 % 40;
		if (panx >= 20) x++;
		int wei2 = abs(m.y - 70);
		int y = wei2 / 40;
		int pany = wei2 % 40;
		if (pany >= 20) y++;
		line(x * 40 + 210, y * 40 + 60, x * 40 + 230, y * 40 + 60);
		line(x * 40 + 210, y * 40 + 80, x * 40 + 230, y * 40 + 80);
		line(x * 40 + 210, y * 40 + 60, x * 40 + 210, y * 40 + 80);
		line(x * 40 + 230, y * 40 + 60, x * 40 + 230, y * 40 + 80);
	}
}