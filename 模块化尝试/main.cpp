/*******************
* phd create in sduqd
********************/
#include<stdio.h>
#include<graphics.h>
#include"print.h"
/* print,function�ȵ�����װΪͷ�ļ�*/
int ecy = 0;
int main() {
	MOUSEMSG msg1; IMAGE picture[200];
	char name[50];
	int a[2] = { 0 }; 
	int mercury=0; 
	//��ʼ����ʼ����
	TCHAR button1[100] = { "��ʼ��Ϸ" };
	startpageprint();
	while (1) {//��׽�����Ϣ
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
//���ǣ�Ϊʲô��д��ô��һ�Ա�׼������30��
//ahhhhhhhhhhhh
//�Ѿ�����д�������ˣ�ÿ���߰˸�Сʱ������Ĳ��������
//����������̫�ߣ����װ���ġ�����
//�ӿ�ȷʵ̫����
//��Ȼ����Ԫ����yyds
//�����,�˻���ս
//�����,���Լ�д��ai��ܻ���һ�ֺ����������
//�Ժ���ʱ�����Ż���
//���˼�¼����ɵĵ�һ��С��Ϸ 2023.12.14
***********************************/
