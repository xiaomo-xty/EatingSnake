/*
��Ϸ����̰����
�������ڣ� 2021/11/13 ����
����������visual studio 2019
����ƽ̨��windows
����������easyx��c++С��Ϸ
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

	//���ڿ��ߣ�����ɫ���߿�ɫ
	GameWin gw(WIN_WIDTH, WIN_HEIGHT, RGB(255, 222, 173), RGB(139, 69, 19));
	Food_tlg fd(RGB(255, 0, 0));
	//�����߱ߣ���ͷ
	Snake snake(RGB(255, 140, 0), RGB(0,0,256), RGB(255, 69, 0));
	DWORD t1, t2;
	int delay;

	while (gw.status != 2)  //0������1�ؿ���2�˳�
	{
		gw.status = 0;
		gw.sorce = 0;
		fd.is_exist = -1;
		delay = Init_Delay;
		//��ʼ����ͼ
		//GameWin gw(WIN_WIDTH, WIN_HEIGHT, RGB(105, 160, 141),RED);
		gw.init();

		//��ʼ����
		snake.CreateSnake(3, RIGHT);

		//Food_tlg fd(randRgb(256));
		fd.create(snake);
		t1 = t2 = GetTickCount();
		BeginBatchDraw();  //������ͼ����
		while (1)
		{

			//�����¼�����
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

			//��ʱ
			if (t2 - t1 > delay)
			{
				if (!snake.move())
					gw.GameOver(L"ͷ��ײ���ˣ�");
				t1 = t2;

				fd.is_exist -= (Init_Delay - delay);
				printf("%u\n", fd.is_exist);
			}

			if (gw.status)
				break;

			t2 = GetTickCount();

			if (!snake.is_SlefEating())  //û�гԵ��Լ�
			{
				snake.eatingFood(fd.point, fd.is_exist, gw.sorce);
				snake.draw();  //����
				fd.create(snake);
				gw.OutLine_Draw();


				FlushBatchDraw();
			}
			else
			{
				//C:\Users\little suns\Desktop\a.mp3
				mciSendString(L"open �鷳��.mp3 alias ht", 0, 0, 0);
				mciSendString(L"play ht", 0, 0, 0);
				gw.GameOver(L"ҧ���Լ��ˣ�");
			}

			delay = Init_Delay - snake.node_num * 3;
		}
	}
	return 0;
}