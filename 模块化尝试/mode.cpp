#include<graphics.h>
#include<mmsystem.h>
#include<time.h>
#include<stdio.h>
#include"function.h"
#include"print.h"
#include"mode.h"
#pragma comment(lib,"winmm.lib")
constexpr auto MAXN = 99999999999999;
constexpr auto MINN = -99999999999999;
int add[2] = { -10 };
void pvp(int flag) {
	MEMSET(qi,hs,bs);bu = 1;
	int a[2] = { 0 }; int b[2] = { 0 };
	MOUSEMSG m;
	FILE* data = NULL;
	TCHAR button1[10] = { "悔棋" };
	TCHAR button2[10] = { "返回" };
	TCHAR button3[15] = { "黑棋回合" };
	TCHAR button4[15] = {"白棋回合"};
	TCHAR button5[15] = { "音乐暂停" };
	TCHAR button6[15] = { "音乐继续" };
	if (flag == 0) {
		data = filepageprint(0);
		chesspageprint();
	}
	//新建文档
	if (flag == 1) {
		data = filepageprint(1);
		chesspageprint();
		bu = datainput(data)-1;
		Sleep(500);
		check(data);
		bu++;
	}//读取现有文档
	if(bu%2==0)button(45, 100, 150, 50, button4);//提示当前所在回合
	else button(45, 100, 150, 50, button3);
	button(80, 500, 100,35, button5);
	mciSendString("open ../bgm.mp3", 0, 0, 0);
	mciSendString("play ../bgm.mp3 repeat", 0, 0, 0);
	int j = 0; int c[2] = { 0 }; int d[2] = { 0 };
	while (1) {
		m = GetMouseMsg();
		//if (m.uMsg) {  reprint(); showmouse(m); }
		if(j==0) emphasize(80,500,100, 35, button5, m, c);
		else  emphasize(80, 500, 100, 35, button6, m, d);
		emphasize(800, 550, 100, 35, button1, m, a);
		emphasize(800, 590, 100, 35, button2, m, b);
		//记录棋局
		if (m.mkLButton) {//棋子位置判断
			if (m.x >= 205 && m.x <= 795 && m.y >= 55 && m.y <= 645) {
				int wei1 = abs(m.x - 220);int x = wei1 / 40;int panx = wei1 % 40;
				if (panx >= 20) x++;
				int wei2 = abs(m.y - 70);int y = wei2 / 40;int pany = wei2 % 40;
				if (pany >= 20) y++;
				if (qi[x][y] == 0) {
					qi[x][y] = (bu % 2) + 1;
					if (bu % 2 != 0) {
						hs[bu] = x;hs[bu + 1] = y;
						button(45, 100, 150, 50, button4);
					}
					else {
						bs[bu] = x; bs[bu + 1] = y;
						button(45, 100, 150, 50, button3);
					}
					fprintf(data, "%d %d %d\n", x, y,0);//导出棋盘数据
					x = x * 40 + 220; y = y * 40 + 70;
					pieceprint(x, y,bu);
					if (check(data) != 0)  break;
					bu++;
				}
			}
			if (m.x >= 800 && m.x <= 900 && m.y >= 550 && m.y <= 585) {
				if (bu - 1 > 0) {
					if ((bu - 1) % 2 != 0) {
						bu--;
						qi[hs[bu]][hs[bu + 1]] = 0;
						fprintf(data, "%d %d %d\n", hs[bu], hs[bu + 1], 1);
						hs[bu] = -10;
						hs[bu + 1] = -10;
					}
					else {
						bu--;
						qi[bs[bu]][bs[bu + 1]] = 0;
						fprintf(data, "%d %d %d\n", bs[bu], bs[bu + 1], 1);
						bs[bu] = -10;
						bs[bu + 1] = -10;
					}
					regret();
				}
			}
			if (m.x >= 800 && m.x <= 900 && m.y >= 590 && m.y <= 625) break;
			if (m.x >= 80 && m.x <= 180 && m.y >= 500 && m.y <= 535) {
				if (j == 0) {
					button(80, 500, 100, 35, button6); mciSendString("pause ../bgm.mp3", 0, 0, 0); j = 1;
					continue;
				}
				if (j == 1) {
					button(80, 500, 100, 35, button5); mciSendString("resume ../bgm.mp3", 0, 0, 0); j = 0;
				}
			}
		}
		if (bu >= 225) break;
	}
	mciSendString("close ../bgm.mp3", 0, 0, 0);
	fclose(data);
	modeselectprint();
}
//分数表
long long scoretable(int chess, int kong,int flag) {
	if (flag == 1) {
		if (chess == 1 && kong == 4) return 600;
		if (chess == 2 && kong == 3) return 1200;
		if (chess == 3 && kong == 2) return 160000;
		if (chess == 4 && kong == 1) return 20000005;
		if (chess == 5) return 70000000000;
		if (chess == 3 && kong == 1) return 120000;
		if (chess == 3 && kong == 0) return 160000;
	}
	else if(flag==2){
		if (chess == 1 && kong == 4) return 700;
		if (chess == 2 && kong == 3) return 1500;
		if (chess == 3 && kong == 2) return 20000000;
		if (chess == 4 && kong == 1) return 60000000000;
	}
}
//估分函数
long long judge(int flag) {
	long long score = 0; int kong = 0; int chess=0;
	for (int i = 0; i <= 14; i++) {
		for (int j = 0; j <= 14; j++) {
			if (qi[i][j] == flag) {
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i][j + h] == flag % 2 + 1 || j + h > 14) break;
					if (qi[i][j + h] == 0) kong++;
					if (qi[i][j + h] == flag) chess++;
				}
				score += scoretable(chess, kong,1);
				if (chess == 4 && kong == 0) score += 150000;
				if (qi[i][j + 1] == flag && qi[i][j + 2] == flag && qi[i][j + 3] == flag && qi[i][j + 4] == 0) score += 50000000;
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i][j - h] == flag % 2 + 1 || j - h < 0) break;
					if (qi[i][j - h] == 0) kong++;
					if (qi[i][j - h] == flag) chess++;
				}
				 score += scoretable(chess, kong, 1);
				if (chess == 4 && kong == 0) score += 150000;
				if (qi[i][j - 1] == flag && qi[i][j - 2] == flag && qi[i][j - 3] == flag && qi[i][j - 4] == 0) score += 50000000;
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i + h][j] == flag % 2 + 1 || i + h > 14) break;
					if (qi[i + h][j] == 0) kong++;
					if (qi[i + h][j] == flag) chess++;
				}
				score += scoretable(chess, kong, 1);
				if (chess == 4 && kong == 0) score += 150000;
				if (qi[i + 1][j] == flag && qi[i + 2][j] == flag && qi[i + 3][j] == flag && qi[i + 4][j] == 0) score += 50000000;
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i - h][j] == flag % 2 + 1 || i - h < 0) break;
					if (qi[i - h][j] == 0) kong++;
					if (qi[i - h][j] == flag) chess++;
				}
				score += scoretable(chess, kong, 1);
				if (chess == 4 && kong == 0) score += 150000;
				if (qi[i - 1][j] == flag && qi[i - 2][j] == flag && qi[i - 3][j] == flag && qi[i - 4][j] == 0) score += 50000000;
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i - h][j - h] == flag % 2 + 1 || i - h < 0 || j - h < 0) break;
					if (qi[i - h][j - h] == 0) kong++;
					if (qi[i - h][j - h] == flag) chess++;
				}
				score += scoretable(chess, kong, 1);
				if (chess == 4 && kong == 0) score += 150000;
				if (qi[i - 1][j - 1] == flag && qi[i - 2][j - 2] == flag && qi[i - 3][j - 3] == flag && qi[i - 4][j - 4] == 0) score += 50000000;
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i + h][j + h] == flag % 2 + 1 || i + h > 14 || j + h > 14) break;
					if (qi[i + h][j + h] == 0) kong++;
					if (qi[i + h][j + h] == flag) chess++;
				}
				 score += scoretable(chess, kong,1);
				if (chess == 4 && kong == 0) score += 150000;
				if (qi[i + 1][j + 1] == flag && qi[i + 2][j + 2] == flag && qi[i + 3][j + 3] == flag && qi[i + 4][j + 4] == 0) score += 50000000;
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i + h][j - h] == flag % 2 + 1 || i + h > 14 || j - h < 0) break;
					if (qi[i + h][j - h] == 0) kong++;
					if (qi[i + h][j - h] == flag) chess++;
				}
				 score += scoretable(chess, kong,1);
				if (chess == 4 && kong == 0) score += 150000;
				if (qi[i + 1][j - 1] == flag && qi[i + 2][j - 2] == flag && qi[i + 3][j - 3] == flag && qi[i + 4][j - 4] == 0) score += 50000000;
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i - h][j + h] == flag % 2 + 1 || i - h < 0 || j + h > 14) break;
					if (qi[i - h][j + h] == 0) kong++;
					if (qi[i - h][j + h] == flag) chess++;
				}
				score += scoretable(chess, kong,1);
				if (chess == 4 && kong == 0) score += 150000;
				if (qi[i - 1][j + 1] == flag && qi[i - 2][j + 2] == flag && qi[i - 3][j + 3] == flag && qi[i - 4][j + 4] == 0) score += 50000000;
			}
			if (i - 4 < 0 || i + 4 > 14 || j + 4 > 14 || j - 4 < 0) score -= 5000;
		}
	}
	for (int i = 4; i <= 10; i++) {
		for (int j = 4; j <= 10; j++) {
			if (qi[i][j] == 0) {
				if (qi[i + 1][j] == flag && qi[i + 2][j] == flag && qi[i + 3][j] == flag && qi[i + 4][j] == 0)
					score += 2000000;
				if (qi[i - 1][j] == flag && qi[i - 2][j] == flag && qi[i - 3][j] == flag && qi[i - 4][j] == 0)
					score += 2000000;
				if (qi[i][j + 1] == flag && qi[i][j + 2] == flag && qi[i][j + 3] == flag && qi[i][j + 4] == 0)
					score += 2000000;
				if (qi[i][j - 1] == flag && qi[i][j - 2] == flag && qi[i][j - 3] == flag && qi[i][j - 4] == 0)
					score += 2000000;
				if (qi[i + 1][j - 1] == flag && qi[i + 2][j - 2] == flag && qi[i + 3][j - 3] == flag && qi[i + 4][j - 4] == 0)
					score += 2000000;
				if (qi[i - 1][j - 1] == flag && qi[i - 2][j - 2] == flag && qi[i - 3][j - 3] == flag && qi[i - 4][j - 4] == 0)
					score += 2000000;
				if (qi[i + 1][j + 1] == flag && qi[i + 2][j + 2] == flag && qi[i + 3][j + 3] == flag && qi[i + 4][j + 4] == 0)
					score += 2000000;
				if (qi[i - 1][j + 1] == flag && qi[i - 2][j + 2] == flag && qi[i - 3][j + 3] == flag && qi[i - 4][j + 4] == 0)
					score += 2000000;
			}
		}
	}
			for (int i = 0; i <= 14; i++) {
				for (int j = 0; j <= 14; j++) {
			if (qi[i][j] == flag%2+1) {
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i][j + h] == flag || j + h > 14) break;
					if (qi[i][j + h] == 0) kong++;
					if (qi[i][j + h] == flag % 2 + 1) chess++;
				}
				score -= scoretable(chess, kong,2);
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i][j - h] == flag || j - h < 0) break;
					if (qi[i][j - h] == 0) kong++;
					if (qi[i][j - h] == flag % 2 + 1) chess++;
				}
				score -= scoretable(chess, kong,2);
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i + h][j] == flag  || i + h > 14) break;
					if (qi[i + h][j] == 0) kong++;
					if (qi[i + h][j] == flag % 2 + 1) chess++;
				}
				score -= scoretable(chess, kong,2);
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i - h][j] == flag  || i - h < 0) break;
					if (qi[i - h][j] == 0) kong++;
					if (qi[i - h][j] == flag % 2 + 1) chess++;
				}
				score -= scoretable(chess, kong,2);
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i - h][j - h] == flag  || i - h < 0 || j - h < 0) break;
					if (qi[i - h][j - h] == 0) kong++;
					if (qi[i - h][j - h] == flag % 2 + 1) chess++;
				}
				 score -= scoretable(chess, kong,2);
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i + h][j + h] == flag  || i + h > 14 || j + h > 14) break;
					if (qi[i + h][j + h] == 0) kong++;
					if (qi[i + h][j + h] == flag % 2 + 1) chess++;
				}
				 score -= scoretable(chess, kong,2);
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i + h][j - h] == flag|| i + h > 14 || j - h < 0) break;
					if (qi[i + h][j - h] == 0) kong++;
					if (qi[i + h][j - h] == flag % 2 + 1) chess++;
				}
				 score -= scoretable(chess, kong,2);
				kong = 0; chess = 1;
				for (int h = 1; h <= 4; h++) {
					if (qi[i - h][j + h] == flag || i - h < 0 || j + h > 14) break;
					if (qi[i - h][j + h] == 0) kong++;
					if (qi[i - h][j + h] == flag % 2 + 1) chess++;
				}
				 score -= scoretable(chess, kong,2);
			}
		}
	}
			for (int i = 4; i <= 10; i++) {
				for (int j = 4; j <= 10; j++) {
					if (qi[i][j] == 0) {
						if (qi[i + 1][j] == flag % 2 + 1 && qi[i + 2][j] == flag % 2 + 1 && qi[i + 3][j] == flag % 2 + 1 && qi[i + 4][j] == 0)
							score -= 10000000;
						if (qi[i -1][j] == flag % 2 + 1 && qi[i - 2][j] == flag % 2 + 1 && qi[i - 3][j] == flag % 2 + 1 && qi[i - 4][j] == 0)
							score -= 10000000;
						if (qi[i ][j+1] == flag % 2 + 1 && qi[i ][j+2] == flag % 2 + 1 && qi[i ][j+3] == flag % 2 + 1 && qi[i ][j+4] == 0)
							score -= 10000000;
						if (qi[i][j -1] == flag % 2 + 1 && qi[i][j - 2] == flag % 2 + 1 && qi[i][j - 3] == flag % 2 + 1 && qi[i][j -4] == 0)
							score -= 10000000;
						if (qi[i+1][j - 1] == flag % 2 + 1 && qi[i+2][j - 2] == flag % 2 + 1 && qi[i+3][j - 3] == flag % 2 + 1 && qi[i+4][j - 4] == 0)
							score -= 10000000;
						if (qi[i - 1][j-1] == flag % 2 + 1 && qi[i - 2][j-2] == flag % 2 + 1 && qi[i - 3][j-3] == flag % 2 + 1 && qi[i - 4][j-4] == 0)
							score -= 10000000;
						if (qi[i+1][j + 1] == flag % 2 + 1 && qi[i+2][j + 2] == flag % 2 + 1 && qi[i+3][j + 3] == flag % 2 + 1 && qi[i+4][j + 4] == 0)
							score -= 10000000;
						if (qi[i - 1][j + 1] == flag % 2 + 1 && qi[i - 2][j + 2] == flag % 2 + 1 && qi[i -3][j + 3] == flag % 2 + 1 && qi[i -4][j + 4] == 0)
							score -= 10000000;
					}
				}
			}
	return score;
}
//深度搜索博弈树和α-β剪枝
int dfs(int depth, int flag, int node,int alpha,int beta) {
	long long minmax = 0;
	if (depth == 2) return judge(bu%2+1);
	if (node == 1) {
		for (int i = 0; i <= 14; i++) {
			for (int j = 0; j <= 14; j++) {
				if (qi[i][j] == 0) {
					qi[i][j] = flag;
					 minmax= dfs(depth - 1, flag % 2 + 1, 2, alpha, beta);
					qi[i][j] = 0;
					if (minmax >= alpha) {
						alpha = minmax;
						if (alpha >= beta) return beta;
					}
				}
			}
		}
		return alpha;
	}
	if (node == 2) {
	for (int i = 0; i <= 14; i++) {
		for (int j = 0; j <= 14; j++) {
			if (qi[i][j] == 0) {
				qi[i][j] = flag;
					minmax = dfs(depth - 1, flag % 2 + 1, 1,alpha,beta);
					qi[i][j] = 0;
					if ( minmax<= beta) {
						beta = minmax;
						if (alpha >= beta) return alpha;
					}
				}
			}
		}
	}
	return beta;
}
//记录位置
void mark(int flag,int depth) {
	long long alpha =MINN, beta = MAXN;
	long long mark1[16][16],max=MINN,min=MAXN;
	add[0] = 0; add[1] = 0;
	MEMSET(mark1);
	for (int j = 0; j <= 14; j++) {
		for (int i = 0; i <= 7; i++) {
			mark1[i][j] += i;
		}
		for (int i = 7; i >= 0; i--) {
			mark1[i][j] += i;
		}
	}
	for (int j = 0; j <= 14; j++) {
		for (int i = 0; i <= 7; i++) {
			mark1[j][i] += i;
		}
		for (int i = 7; i >= 0; i--) {
			mark1[j][i] += i;
		}
	}
	for (int i = 0; i <= 14; i++) {
		for (int j = 0; j <= 14; j++) {
			if (qi[i][j] == 0) {
				qi[i][j] = flag;
				if (depth == 1) mark1[i][j] += judge(bu % 2 + 1);
				else if (depth > 1) {
					if (bu <= 4) mark1[i][j] += judge(bu % 2 + 1);
					else mark1[i][j] += dfs(depth, flag % 2 + 1, 2, alpha, beta) + judge(bu % 2 + 1)/2;
				}
					if (mark1[i][j] > max) {
						max = mark1[i][j];
						add[0] = i; add[1] = j;
					}
					qi[i][j] = 0;
			}
		}
	}
}
//人机对战
void pve(int flag,int depth) {
	MEMSET(qi, hs, bs); bu = 1;
	int flag1 = 2,flag2 = 0;
	int a[2] = { 0 }; int b[2] = { 0 };
	MOUSEMSG m;
	FILE* data = NULL;
	TCHAR button1[10] = { "悔棋" };
	TCHAR button2[10] = { "返回" };
	TCHAR button3[15] = { "黑棋回合" };
	TCHAR button4[15] = { "白棋回合" };
	TCHAR button5[15] = { "音乐暂停" };
	TCHAR button6[15] = { "音乐继续" };
	if (flag == 0) {
		data = filepageprint(0);
		chesspageprint();
		HWND hnd = GetHWnd();
		int click = MessageBox(hnd, "你是否选择先手", "顺序选择", MB_OKCANCEL | MB_ICONINFORMATION);
		if (click == IDOK) {
			flag1 = 1;
			flag2 = 0;
		}
	}
	//新建文档
	if (flag == 1) {
		data = filepageprint(1);
		chesspageprint();
		bu = datainput(data) - 1;
		Sleep(500);
		check(data);
		bu++;
		flag2 = 1;
	}//读取现有文档
	if (bu % 2 == 0)button(45, 100, 150, 50, button4);//提示当前所在回合
	else button(45, 100, 150, 50, button3);
	button(80, 500, 100, 35, button5);
	mciSendString("open ../bgm.mp3", 0, 0, 0);
	mciSendString("play ../bgm.mp3 repeat", 0, 0, 0);
	int j = 0; int c[2] = { 0 }; int d[2] = { 0 };
	int x; int y;
	if ((bu%2!=0&&flag2==1)||(flag1==2)) {
		mark(2,depth);
		qi[add[0]][add[1]] = 2;
		hs[bu] = add[0]; hs[bu + 1] = add[1];
		button(45, 100, 150, 50, button3);
		fprintf(data, "%d %d %d\n", hs[bu], hs[bu + 1], 0);
		x = hs[bu] * 40 + 220;
		y = hs[bu + 1] * 40 + 70;
		pieceprint(x, y, bu);
		bu++;
	}
	while (1) {
		m = GetMouseMsg();
		if (j == 0) emphasize(80, 500, 100, 35, button5, m, c);
		else  emphasize(80, 500, 100, 35, button6, m, d);
		emphasize(800, 550, 100, 35, button1, m, a);
		emphasize(800, 590, 100, 35, button2, m, b);
		//记录棋局
		if (m.mkLButton) {//棋子位置判断
			if (m.x >= 205 && m.x <= 795 && m.y >= 55 && m.y <= 645) {
				int wei1 = abs(m.x - 220); x = wei1 / 40; int panx = wei1 % 40;
				if (panx >= 20) x++;
				int wei2 = abs(m.y - 70); y = wei2 / 40; int pany = wei2 % 40;
				if (pany >= 20) y++;
				if (qi[x][y] == 0) {
					qi[x][y] = (bu % 2) + 1;
					if (bu % 2 != 0) {
						hs[bu] = x; hs[bu + 1] = y;
						button(45, 100, 150, 50, button4);
					}
					else {
						bs[bu] = x; bs[bu + 1] = y;
						button(45, 100, 150, 50, button3);
					}
					fprintf(data, "%d %d %d\n", x, y, 0);//导出棋盘数据
					x = x * 40 + 220; y = y * 40 + 70;
					pieceprint(x, y, bu);
					if (check(data) != 0)  break;
					bu++;
					mark(bu%2+1,depth);
					qi[add[0]][add[1]] = bu%2+1;
					if (bu % 2 != 0) {
						hs[bu] = add[0]; hs[bu + 1] = add[1];
						button(45, 100, 150, 50, button4);
						x = hs[bu] * 40 + 220;
						y = hs[bu + 1] * 40 + 70;
					}
					else {
						bs[bu] = add[0]; bs[bu + 1] = add[1];
						button(45, 100, 150, 50, button3);
						x = bs[bu] * 40 + 220;
						y = bs[bu + 1] * 40 + 70;
					}
					fprintf(data, "%d %d %d\n", add[0], add[1], 0);
					Sleep(100);
					pieceprint(x,y,bu);
					if (check(data) != 0)  break;
					bu++;
				}
			}
			if (m.x >= 800 && m.x <= 900 && m.y >= 550 && m.y <= 585) {
				if (bu - 1 > 0) {
					if ((bu - 1) % 2 != 0) {
						bu--;
						qi[hs[bu]][hs[bu + 1]] = 0;
						fprintf(data, "%d %d %d\n", hs[bu], hs[bu + 1], 1);
						hs[bu] = -10;
						hs[bu + 1] = -10;
					}
					else {
						bu--;
						qi[bs[bu]][bs[bu + 1]] = 0;
						fprintf(data, "%d %d %d\n", bs[bu], bs[bu + 1], 1);
						bs[bu] = -10;
						bs[bu + 1] = -10;
					}
					regret();
				}
			}
			if (m.x >= 800 && m.x <= 900 && m.y >= 590 && m.y <= 625) break;
			if (m.x >= 80 && m.x <= 180 && m.y >= 500 && m.y <= 535) {
				if (j == 0) {
					button(80, 500, 100, 35, button6); mciSendString("pause ../bgm.mp3", 0, 0, 0); j = 1;
					continue;
				}
				if (j == 1) {
					button(80, 500, 100, 35, button5); mciSendString("resume ../bgm.mp3", 0, 0, 0); j = 0;
				}
			}
		}
		if (bu >= 225) break;
	}
	mciSendString("close ../bgm.mp3", 0, 0, 0);
	fclose(data);
	modeselectprint();
}
//电脑互殴
void eve(int flag) {
	srand((unsigned int)time(NULL));
	MEMSET(qi, hs, bs); bu = 1;
	int a[2] = { 0 }; int b[2] = { 0 };
	int y1 = 1;
	MOUSEMSG m;
	FILE* data = NULL;
	TCHAR button1[10] = { "悔棋" };
	TCHAR button2[10] = { "返回" };
	TCHAR button3[15] = { "黑棋回合" };
	TCHAR button4[15] = { "白棋回合" };
	TCHAR button5[15] = { "音乐暂停" };
	TCHAR button6[15] = { "音乐继续" };
	char button7[15] = { "暂停棋局" };
	if (flag == 0) {
		data = filepageprint(0);
		chesspageprint();
	}
	//新建文档
	if (flag == 1) {
		data = filepageprint(1);
		chesspageprint();
		bu = datainput(data) - 1;
		Sleep(500);
		check(data);
		bu++;
	}//读取现有文档
	if (bu % 2 == 0)button(45, 100, 150, 50, button4);//提示当前所在回合
	else button(45, 100, 150, 50, button3);
	button(80, 500, 100, 35, button5);
	button(80, 550, 100, 35, button7);
	mciSendString("open ../bgm.mp3", 0, 0, 0);
	mciSendString("play ../bgm.mp3 repeat", 0, 0, 0);
	int j = 0; int c[2] = { 0 }; int d[2] = { 0 }; int e[2] = { 0 };
	int x; int y;
	while (1) {
		m = GetMouseMsg();
		if (j == 0) emphasize(80, 500, 100, 35, button5, m, c);
		else  emphasize(80, 500, 100, 35, button6, m, d);
		emphasize(800, 550, 100, 35, button1, m, a);
		emphasize(800, 590, 100, 35, button2, m, b);
		emphasize(80, 550, 100, 35, button7, m, e);
		//记录棋局
		if (y1 == 1) {
			mark(bu % 2 + 1,2);
			y1 = y1 % 2 + 1;
		}
		else {
			mark(bu % 2 + 1, 3);
			y1 = y1 % 2 + 1;
		}
		qi[add[0]][add[1]] = bu % 2 + 1;
		if (bu % 2 != 0) {
			hs[bu] = add[0]; hs[bu + 1] = add[1];
			button(45, 100, 150, 50, button4);
			x = hs[bu] * 40 + 220;
			y = hs[bu + 1] * 40 + 70;
		}
		else {
			bs[bu] = add[0]; bs[bu + 1] = add[1];
			button(45, 100, 150, 50, button3);
			x = bs[bu] * 40 + 220;
			y = bs[bu + 1] * 40 + 70;
		}
		fprintf(data, "%d %d %d\n", add[0], add[1], 0);
		Sleep(200);
		pieceprint(x, y, bu);
		if (check(data) != 0)  break;
		bu++;
		if (m.mkLButton) {
			if (m.x >= 800 && m.x <= 900 && m.y >= 550 && m.y <= 585) {
				if (bu - 1 > 0) {
					if ((bu - 1) % 2 != 0) {
						bu--;
						qi[hs[bu]][hs[bu + 1]] = 0;
						fprintf(data, "%d %d %d\n", hs[bu], hs[bu + 1], 1);
						hs[bu] = -10;
						hs[bu + 1] = -10;
					}
					else {
						bu--;
						qi[bs[bu]][bs[bu + 1]] = 0;
						fprintf(data, "%d %d %d\n", bs[bu], bs[bu + 1], 1);
						bs[bu] = -10;
						bs[bu + 1] = -10;
					}
					regret();
				}
			}
			if (m.x >= 800 && m.x <= 900 && m.y >= 590 && m.y <= 625) break;
			if (m.x >= 80 && m.x <= 180 && m.y >= 500 && m.y <= 535) {
				if (j == 0) {
					button(80, 500, 100, 35, button6); mciSendString("pause ../bgm.mp3", 0, 0, 0); j = 1;
					continue;
				}
				if (j == 1) {
					button(80, 500, 100, 35, button5); mciSendString("resume ../bgm.mp3", 0, 0, 0); j = 0;
				}
			}
			if (m.x >= 80 && m.x <= 180 && m.y >= 550 && m.y <= 585) 
				while (1) {
				m = GetMouseMsg();
				if (m.x >= 80 && m.x <= 180 && m.y >= 550 && m.y <= 585&&m.mkLButton) break;
			}
		}
		if (bu >= 225) break;
	}
	mciSendString("close ../bgm.mp3", 0, 0, 0);
	fclose(data);
	modeselectprint();
}