/*******************
* phd create in sduqd
********************/
#include<stdio.h>
#include<graphics.h>
#include"print.h"
/* print,function等单独封装为头文件*/
int ecy = 0;
int main() {
	MOUSEMSG msg1; IMAGE picture[200];
	char name[50];
	int a[2] = { 0 }; 
	int mercury=0; 
	//初始化开始界面
	TCHAR button1[100] = { "开始游戏" };
	startpageprint();
	while (1) {//捕捉鼠标消息
		msg1 = GetMouseMsg();
		emphasize(400, 525, 200, 55, button1,msg1,a);
		if (msg1.x >= 400 && msg1.x <= 600 && msg1.y <= 580 && msg1.y >= 525) {
			if (msg1.mkLButton) {
				mercury = 1;
				break;
			}
			if (msg1.mkRButton) {
				mercury = 2;
				break;
			}
		}
	}
	if (mercury == 1) modeselectprint();
	if (mercury == 2) {
		ecy = 1;
		modeselectprint();
	}
	system("pause");
	return 0;
}
/*******************************
//不是，为什么我写这么久一对标准就拿了30分
//ahhhhhhhhhhhh
//已经连续写了三天了，每天七八个小时，这真的不会猝死吗
//程序依赖度太高，这封装做的。。。
//接口确实太多了
//果然二次元才是yyds
//完成了,人机对战
//讲真的,被自己写的ai打败还是一种很特殊的体验
//以后有时间再优化吧
//谨此记录我完成的第一个小游戏 2023.12.14
***********************************/
