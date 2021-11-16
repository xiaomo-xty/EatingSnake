/*
游戏名：贪吃蛇
开发日期： 2021/11/13 ——
开发环境：visual studio 2019
运行平台：windows
描述：基于easyx的c++小游戏
*/

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "GameDraw.h"

#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define randRgb(x) RGB(rand()%x,rand()%x,rand()%x)

//static int sorce;
static int Init_Delay = 150; //ms


int main(void)
{
	mciSendString(L"open a.mp3 alias b", 0, 0, 0);
	//C:\Users\little suns\Desktop\a.mp3

	mciSendString(L"play b repeat", 0, 0, 0);
	srand(time(NULL));

	//窗口宽，高，背景色，边框色
	GameWin gw(WIN_WIDTH, WIN_HEIGHT, RGB(255, 222, 173), RGB(139, 69, 19));
	Food_tlg fd(RGB(255, 0, 0));
	//蛇身，蛇边，蛇头
	Snake snake(RGB(255, 140, 0), RGB(0,0,256), RGB(255, 69, 0));
	DWORD t1, t2;
	int delay;

	while (gw.status != 2)  //0正常，1重开，2退出
	{
		gw.status = 0;
		gw.sorce = 0;
		fd.is_exist = -1;
		delay = Init_Delay;
		//初始化地图
		//GameWin gw(WIN_WIDTH, WIN_HEIGHT, RGB(105, 160, 141),RED);
		gw.init();

		//初始化蛇
		snake.CreateSnake(3, RIGHT);

		//Food_tlg fd(randRgb(256));
		fd.create(snake);
		t1 = t2 = GetTickCount();
		BeginBatchDraw();  //批量绘图声明
		while (1)
		{

			//键盘事件监听
			if (GetAsyncKeyState(VK_UP) && snake.move_dir != DOWN)
				snake.move_dir = UP;
			else if (GetAsyncKeyState(VK_DOWN) && snake.move_dir != UP)
				snake.move_dir = DOWN;
			else if (GetAsyncKeyState(VK_LEFT) && snake.move_dir != RIGHT)
				snake.move_dir = LEFT;
			else if (GetAsyncKeyState(VK_RIGHT) && snake.move_dir != LEFT)
				snake.move_dir = RIGHT;
			else if (GetAsyncKeyState(VK_SPACE))
				system("pause");

			//延时
			if (t2 - t1 > delay)
			{
				if (!snake.move())
					gw.GameOver(L"头都撞破了！");
				t1 = t2;

				fd.is_exist -= (Init_Delay - delay);
				printf("%u\n", fd.is_exist);
			}

			if (gw.status)
				break;

			t2 = GetTickCount();

			if (!snake.is_SlefEating())  //没有吃到自己
			{
				snake.eatingFood(fd.point, fd.is_exist, gw.sorce);
				snake.draw();  //画蛇
				fd.create(snake);
				gw.OutLine_Draw();


				FlushBatchDraw();
			}
			else
			{
				//C:\Users\little suns\Desktop\a.mp3
				mciSendString(L"open 麻烦了.mp3 alias ht", 0, 0, 0);
				mciSendString(L"play ht", 0, 0, 0);
				gw.GameOver(L"咬到自己了！");
			}

			delay = Init_Delay - snake.node_num * 3;
		}
	}
	return 0;
}