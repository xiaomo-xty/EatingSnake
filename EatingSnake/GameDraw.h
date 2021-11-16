#pragma once
#ifndef __GAMEDRAW__
#define __GAMWDRAW__

#include <graphics.h>


#define WIN_WIDTH 780  //窗口绘制高度
#define WIN_HEIGHT 480  //窗口绘制高度
#define SOLE_SIZE 10
#define INF_COLUMN 10  //信息栏单位宽度

#define MINTIME 5000
#define MAXTIME 10000

#define MAX_SNAKE 100

//坐标点
class Point {
public:
	int x;
	int y;
	friend bool operator==(const Point& a, const Point& b) 
	{
		return (a.x == b.x && a.y == b.y);
	};
};

//方向
typedef enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
}DIR;


//窗口
class GameWin {
public:
	//传入绘制窗口的宽，高
	GameWin(int WinWidth, int WinHeigth,COLORREF BackColor,int outline_color);
	void init();
	void GameOver(const wchar_t* tip);
	void OutLine_Draw();
	void Print_Sorce();

	int sorce = 0;
	int status;
private:
	int max_sorce;
	int WinWidth;  //窗口宽度
	int WinHeight;  //窗口高度
	int GameWidth;
	int outline_color;  //边框颜色
	int BackColor;  //背景颜色

};


//蛇
class Snake {
public:
	int move_dir;   //当前蛇头移动方向
	Snake(int body_color, int outline_color,int head_color);  //设置结点数，移动方向，身体填充颜色，外轮廓颜色
	void SnakeDraw(Point node); //绘制坐标
	void HeadDraw(Point node);
	void CreateSnake(int node_num, int move_dir);  //蛇的初始绘制
	bool move();  //坐标变换
	void draw();  //全身绘制
	void eatingFood(const Point& food,int& is_exit,int& sorce);  //吃食物检测

	bool is_live() {
		return node_num > 0;
	};
	bool is_SlefEating();  //自食检测

	int node_num;  //当前蛇身长
private:
	int size = 10;  //蛇身节点尺寸，正方体为size*size
	COLORREF body_color;  //当前蛇身填充颜色
	COLORREF head_color;  //当前蛇头填充颜色
	COLORREF outline_color;  //蛇身轮廓边框颜色
	Point node[MAX_SNAKE];  //蛇身坐标数组

	friend class Food_tlg;
};


//食物
class Food_tlg {
public:
	Food_tlg(int color) {
		this->color = color;  //食物颜色
		this->size = SOLE_SIZE;   //食物 边长/直径
		is_exist = MAXTIME;  //存在状态
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