#include<stdio.h>
#include<Windows.h>
#include<graphics.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<conio.h>
int num = 2;                             //1表示白子下，2是黑子下
int piece[14][14] = { 0 };               //表示还没开始下
int comx = 0, comy = 0;
void chus()                              //初始化
{            
	num = 2;
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			piece[i][j] = { 0 };
		}
	}
	initgraph(680, 680);                    //
	IMAGE msg1;
	loadimage(&msg1, "界面.png");            
	putimage(0, 0, &msg1);
}
int Full(int game[14][14]) {               //平局判断                                                                                                    //判断棋盘是否已满
	int h = 1;
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 14; j++) {
			if (game[i][j] == 0) {        //遍历数组，当有一个位置为空，则棋盘不满
				h = 0;
				break;
			}
		}
	}
	return h;                              //若为1则说明棋盘已满
}
int Win(int game[14][14])                                                                                                                               //判断胜负
{
	if (Full(piece) == 1)
	{
		return 2;
	}
	int i = 0; int j = 0;
	for (i = 0; i < 14; i++)//行
	{
		for (j = 0; j < 10; j++)
		{
			if (game[i][j] == game[i][j + 1] && game[i][j + 1] == game[i][j + 2] && game[i][j + 2] == game[i][j + 3] && game[i][j + 3] == game[i][j + 4] && game[i][j] != 0)
				return 1;
		}
	}
	for (i = 0; i < 10; i++)//列
	{
		for (j = 0; j < 14; j++)
		{
			if (game[i][j] == game[i + 1][j] && game[i + 1][j] == game[i + 2][j] && game[i + 2][j] == game[i + 3][j] && game[i + 3][j] == game[i + 4][j] && game[i][j] != 0)
				return 1;
		}
	}
	for (i = 0; i < 10; i++)//左斜
	{
		for (j = 0; j < 10; j++)
		{
			if (game[i][j] == game[i + 1][j + 1] && game[i + 1][j + 1] == game[i + 2][j + 2] && game[i + 2][j + 2] == game[i + 3][j + 3] && game[i + 3][j + 3] == game[i + 4][j + 4] && game[i][j] != 0)
				return 1;
		}
	}
	for (i = 4; i < 14; i++)//右斜
	{
		for (j = 0; j < 10; j++)
		{
			if (game[i][j] == game[i - 1][j + 1] && game[i - 1][j + 1] == game[i - 2][j + 2] && game[i - 2][j + 2] == game[i - 3][j + 3] && game[i - 3][j + 3] == game[i - 4][j + 4] && game[i][j] != 0)
				return 1;
		}
	}
	return 0;
}
void Select(int gamea[14][14])                                                                                                    // 计分（完全遍历)
{
	int Score[14][14] = { 0 };
	for (int row = 0; row < 14; row++)
	{
		for (int col = 0; col < 14; col++)
		{
			// 计算空位置
			if (gamea[row][col] == 0)
			{
				// 周围方向
				for (int y = -1; y <= 1; y++)
				{
					for (int x = -1; x <= 1; x++)
					{
						int white = 0;              //白
						int black = 0;              //黑
						int empty = 0;              //空
						//白棋分数
						if (!(y == 0 && x == 0)) 
						{
							for (int i = 1; i <= 4; i++)//延伸四个棋子 
							{
								if (row + i * y > 0 && row + i * y < 14 && col + i * x > 0 && col + i * x < 14 && gamea[row + i * y][col + i * x] == 1) // 白子下
									white++;
								if (row + i * y > 0 && row + i * y < 14 && col + i * x > 0 && col + i * x < 14 && gamea[row + i * y][col + i * x] == 0) // 空白位
								{
									empty++;
									break;
								}
								else
									break;
							}
							for (int i = 1; i <= 4; i++)
							{
								if (row - i * y > 0 && row - i * y < 14 && col - i * x > 0 && col - i * x < 14 && gamea[row - i * y][col - i * x] == 1) // 白子
								{
									white++;
								}
								else if (row - i * y > 0 && row - i * y < 14 && col - i * x > 0 && col - i * x < 14 && gamea[row - i * y][col - i * x] == 0) // 空白位下
								{
									empty++;
									break;
								}
								else
									break;  
							}
						}
						if (black == 0)                      
							Score[row][col] += 1;
						else if (white == 1)                      
							Score[row][col] += 2;
						else if (white == 2)                 
						{
							if (empty == 1)
								Score[row][col] += 5;
							else if (empty == 2)
								Score[row][col] += 8;
						}
						else if (white == 3)                 
						{
							if (empty == 1)
								Score[row][col] += 15;
							else if (empty == 2)
								Score[row][col] += 20;
						}
						else if (white == 4)                 
							Score[row][col] += 100;
						empty = 0;

						// 黑棋分数
						for (int i = 1; i <= 4; i++)
						{
							if (row + i * y > 0 && row + i * y < 14 && col + i * x > 0 && col + i * x < 14 && gamea[row + i * y][col + i * x] == 2) // 黑子
							{
								black++;
							}
							else if (row + i * y > 0 && row + i * y < 14 && col + i * x > 0 && col + i * x < 14 && gamea[row + i * y][col + i * x] == 0) // 空白位
							{
								empty++;
								break;
							}
							else            
								break;
						}
						for (int i = 1; i <= 4; i++)
						{
							if (row - i * y > 0 && row - i * y < 14 && col - i * x > 0 && col - i * x < 14 && gamea[row - i * y][col - i * x] == 2) // 黑子
							{
								black++;
							}
							else if (row - i * y > 0 && row - i * y < 14 && col - i * x > 0 && col - i * x < 14 && gamea[row - i * y][col - i * x] == 0) // 空白位
							{
								empty++;
								break;
							}
							else            
								break;
						}

						if (black == 0)                
							Score[row][col] += 1;
						else if (black == 1)       
							Score[row][col] += 2;
						else if (black == 2)      
						{
							if (empty == 1)
								Score[row][col] += 5;
							else if (empty == 2)
								Score[row][col] += 8;
						}
						else if (black == 3)    
						{
							if (empty == 1)
								Score[row][col] += 15;
							else if (empty == 2)
								Score[row][col] += 20;
						}
						else if (black >= 4)             
							Score[row][col] += 100;
					}
				}
			}
		}
	}	                           
	int Max = 0;                                    // 找出最大分数的位置
	comx = 0; comy = 0;
	for (int row = 0; row < 14; row++)
	{
		for (int col = 0; col < 14; col++)
		{		                                      
			if (gamea[row][col] == 0)                // 若该位置没有棋子
			{
				if (Score[row][col] >= Max)          //最大分数
				{
					Max = Score[row][col];
					comx = row;
					comy = col;
				}
			}
		}
	}
}
int DrawPiece(int x, int y)
{
	int m, n;
	m = (x + 25) / 50;
	n = (y + 25) / 50;
	settextstyle(40, 0, _T("华文楷体"));                               
	if (m > 0 && n > 0 && m < 14 && n < 14 && piece[m][n]==0)
	{
		if (num == 1)
		{
			setfillcolor(WHITE);                                      //1为白棋
			piece[m][n] = 1;
			outtextxy(200, 660, "       请黑棋落子         ");
		}
		else
		{
			setfillcolor(BLACK);                                      //2为黑棋
			piece[m][n] = 2;
			outtextxy(200, 660, "       请白棋落子         ");
		}
		fillcircle(m * 50, n * 50, 15);                               //画棋子
		num = 3 - num;
		return 1;
	}
	else if(m <= 0||n <= 0||n >= 14||m >= 14)                         //出界
	{
		outtextxy(200, 660, "请在正确的位置下棋");
	}
	else if (piece[m][n] == 1)                                       //重复下棋
	{
		outtextxy(200, 660, "请在正确的位置下棋");
	}
}
int PVP()
{
		initgraph(700, 700);
		IMAGE msg2;
		loadimage(&msg2, "棋盘.jpg");
		putimage(0, 0, &msg2);                                      
		MOUSEMSG m;                                           
		settextstyle(40, 0, _T("华文楷体"));
		outtextxy(0, 660, "退出");
		outtextxy(200, 660, "       请黑棋落子         ");
		while (1)
		{
			m = GetMouseMsg();                                 //获取鼠标坐标，点击信息
			if (m.uMsg == WM_LBUTTONDOWN)                           //如果鼠标左键按下
			{
				if (m.x > 0 && m.x < 70 && m.y > 660 && m.y < 700)  //退出
				{
					closegraph;
					chus();
					return 0;
				}
				DrawPiece(m.x, m.y);
				if (Win(piece) == 1) 
				{                                                    //如果胜利
					if (num == 2)
					{
						outtextxy(200, 660, "        白棋胜利       ");
					}
					if (num == 1)
					{
						outtextxy(200, 660, "        黑棋胜利       ");
					}
					if (Win(piece) == 2)                             //如果平局
					{
						outtextxy(220, 660, "        平局           ");
					}
				}
			}
		}
		return 0;
}
int PVE()
{
	initgraph(700, 700);
	loadimage(NULL, "棋盘.jpg");
	MOUSEMSG m;
	settextstyle(40, 0, _T("华文楷体"));
	outtextxy(0, 660, "退出");
	outtextxy(200, 660, "       请黑棋落子         ");
	while (1) {
		if (num == 1)
		{
			Select(piece);
			setfillcolor(WHITE);
			fillcircle(comx * 50, comy * 50, 15);                 //画棋子
			outtextxy(200, 660, "       请黑棋落子         ");
			piece[comx][comy] = 1;
			num = 3 - num;                                    //切换黑白子
			if (Win(piece) == 1)                              //如果胜利
			{
				if (num == 2)
				{
					outtextxy(200, 660, "        白棋胜利       ");
					return 2;
				}
				if (num == 1)
				{
					outtextxy(200, 660, "        黑棋胜利       ");
					return 2;
				}
				if (Win(piece) == 2)                          //如果平局
				{
					outtextxy(220, 660, "        平局           ");
					return 2;
				}
			}
		}
		if (num == 2) {
			int h = 0;
			while (1) {
				m = GetMouseMsg();
				if (m.uMsg == WM_LBUTTONDOWN)             
				{
					if (m.x > 0 && m.x < 70 && m.y > 660 && m.y < 700)   //退出
					{
						closegraph;
						chus();
						return 0;
					}
					h = DrawPiece(m.x, m.y);                           //电脑下棋
					if (Win(piece) == 1)                               //如果胜利
					{
						if (num == 2)
						{
							outtextxy(200, 660, "        白棋胜利       ");
							return 2;
						}
						if (num == 1)
						{
							outtextxy(200, 660, "        黑棋胜利       ");
							return 2;
						}
						if (Win(piece) == 2)                            //如果平局
						{
							outtextxy(220, 660, "        平局           ");
							return 2;
						}
					}
				}
				if (h == 1)  break;
			}
		}
	}
}
int main()
{
	chus();
	MOUSEMSG n;                                                      
	while (1)
	{
		n = GetMouseMsg();                                     //获取鼠标坐标，点击信息
		switch (n.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (n.x < 630 && n.x>470 && n.y < 300 && n.y>140)
			{
				closegraph;
				PVP();
			}
			if (n.x < 620 && n.x >460 && n.y < 630 && n.y > 470)
			{
				closegraph;
				PVE();
			}
		}
	}
}