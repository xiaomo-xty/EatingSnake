#pragma once
#ifndef __GAMEDRAW__
#define __GAMWDRAW__

#include <graphics.h>


#define WIN_WIDTH 780  //���ڻ��Ƹ߶�
#define WIN_HEIGHT 480  //���ڻ��Ƹ߶�
#define SOLE_SIZE 10
#define INF_COLUMN 10  //��Ϣ����λ���

#define MINTIME 5000
#define MAXTIME 10000

#define MAX_SNAKE 100

//�����
class Point {
public:
	int x;
	int y;
	friend bool operator==(const Point& a, const Point& b) 
	{
		return (a.x == b.x && a.y == b.y);
	};
};

//����
typedef enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
}DIR;


//����
class GameWin {
public:
	//������ƴ��ڵĿ���
	GameWin(int WinWidth, int WinHeigth,COLORREF BackColor,int outline_color);
	void init();
	void GameOver(const wchar_t* tip);
	void OutLine_Draw();
	void Print_Sorce();

	int sorce = 0;
	int status;
private:
	int max_sorce;
	int WinWidth;  //���ڿ��
	int WinHeight;  //���ڸ߶�
	int GameWidth;
	int outline_color;  //�߿���ɫ
	int BackColor;  //������ɫ

};


//��
class Snake {
public:
	int move_dir;   //��ǰ��ͷ�ƶ�����
	Snake(int body_color, int outline_color,int head_color);  //���ý�������ƶ��������������ɫ����������ɫ
	void SnakeDraw(Point node); //��������
	void HeadDraw(Point node);
	void CreateSnake(int node_num, int move_dir);  //�ߵĳ�ʼ����
	bool move();  //����任
	void draw();  //ȫ�����
	void eatingFood(const Point& food,int& is_exit,int& sorce);  //��ʳ����

	bool is_live() {
		return node_num > 0;
	};
	bool is_SlefEating();  //��ʳ���

	int node_num;  //��ǰ����
private:
	int size = 10;  //����ڵ�ߴ磬������Ϊsize*size
	COLORREF body_color;  //��ǰ���������ɫ
	COLORREF head_color;  //��ǰ��ͷ�����ɫ
	COLORREF outline_color;  //���������߿���ɫ
	Point node[MAX_SNAKE];  //������������

	friend class Food_tlg;
};


//ʳ��
class Food_tlg {
public:
	Food_tlg(int color) {
		this->color = color;  //ʳ����ɫ
		this->size = SOLE_SIZE;   //ʳ�� �߳�/ֱ��
		is_exist = MAXTIME;  //����״̬
	};
	Point point;

	int is_exist;
	void draw();
	void create(const Snake& snake);
private:
	int size;
	int color;

	friend class Snake;
};

#endif