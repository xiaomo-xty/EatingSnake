#include "GameDraw.h"
#include <graphics.h>
#include <cstdio>
#include <cstdlib>

GameWin::GameWin(int WinWidth, int WinHeight, COLORREF BackColor,int outline_color)
{
	initgraph(WinWidth, WinHeight, SHOWCONSOLE);  //���ڳ�ʼ��,���������д��ڼ������
	this->WinWidth = WinWidth;
	this->WinHeight = WinHeight;
	this->GameWidth = WinWidth - (INF_COLUMN+4)*SOLE_SIZE;
	this->BackColor = BackColor;
	this->outline_color = outline_color;
	this->sorce = 0;
	this->max_sorce = 0;
	this->status = 0;
}
void GameWin::init()
{
	setbkcolor(BackColor);  //������ɫ����
	OutLine_Draw();
	cleardevice();
	Print_Sorce();
}



//��Ϸ�������
void GameWin::OutLine_Draw()
{
	setfillcolor(outline_color);  //�߽�����ɫ���
	setlinecolor(outline_color);  //

	//�߿����
	fillrectangle(0, SOLE_SIZE,SOLE_SIZE, WIN_HEIGHT- SOLE_SIZE);  //�������
	fillrectangle(GameWidth, SOLE_SIZE, GameWidth + SOLE_SIZE, WIN_HEIGHT- SOLE_SIZE);  //��Ϸ����ʾ��������
	fillrectangle(WIN_WIDTH - SOLE_SIZE, SOLE_SIZE, WIN_WIDTH, WIN_HEIGHT- SOLE_SIZE);  //����߱߿�
	fillrectangle(0, 0, WIN_WIDTH, SOLE_SIZE);  //�����߿�
	fillrectangle(0, WIN_HEIGHT - SOLE_SIZE, WIN_WIDTH, WIN_HEIGHT);  //�ײ��ײ��߿�

	Print_Sorce();
}

void GameWin::Print_Sorce()
{
	TCHAR tip[20] = TEXT(""),max_sorces[20] = TEXT("");
	wsprintf(tip,L"%d",sorce);
	wsprintf(max_sorces, L"%d", max_sorce);
	setbkmode(TRANSPARENT);
	setcolor(BLACK);
	outtextxy(GameWidth+2*SOLE_SIZE,2*SOLE_SIZE,L"��ǰ������");
	outtextxy(GameWidth + 2 * SOLE_SIZE, 4 * SOLE_SIZE, tip);
	outtextxy(GameWidth + 2 * SOLE_SIZE, 8 * SOLE_SIZE, L"��ʷ��߷֣�");
	outtextxy(GameWidth + 2 * SOLE_SIZE, 10 * SOLE_SIZE, max_sorces);
	setcolor(WHITE);
	//outtextxy(20, 20, tip);
}

void GameWin::GameOver(const wchar_t*  tip)
{
	//ˢ����߷�
	if (sorce > max_sorce)
		max_sorce = sorce;

	setbkmode(TRANSPARENT);
	//outtextxy(20, 20, tip);
	setcolor(RED);
	outtextxy(GameWidth/2,WinHeight/2 - SOLE_SIZE, tip);
	outtextxy(GameWidth / 2, WinHeight / 2+SOLE_SIZE*2, TEXT("���س�������esc�˳�"));
	setcolor(WHITE);
	FlushBatchDraw();

	while (1)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			status = 2;
			break;
		}
		else if (GetAsyncKeyState(VK_RETURN))  //�س�
		{
			status = 1;
			break;
		}
	}

}

void Food_tlg::create(const Snake& snake)
{

	if (is_exist <= 0 || is_exist == MAXTIME)
	{
		//����ʳ�����ɵ�������
		for (int i = 0; i < snake.node_num; i++)
		{
			if (i == 0)
			{
				point.x = rand() % ((WIN_WIDTH - SOLE_SIZE * (4 + INF_COLUMN)) / SOLE_SIZE) * SOLE_SIZE + SOLE_SIZE;
				point.y = rand() % ((WIN_HEIGHT - SOLE_SIZE * 2) / SOLE_SIZE) * 10 + SOLE_SIZE;
			}

			if (point == snake.node[i])
				i == 0;
		}
		is_exist = rand() % (MAXTIME - MINTIME) + MINTIME;
	}

	setlinecolor(color);
	setfillcolor(color);
	fillellipse(point.x,point.y,point.x + size,point.y + size);
}

void Food_tlg::draw()
{
	
	setfillcolor(color);
	fillcircle(point.x+size/2, point.y+size/2, size/2);
}

//=========================snake====================

Snake::Snake(int body_color,int outline_color,int head_color)
{
	this->body_color = body_color;
	this->head_color = head_color;
	this->outline_color = outline_color;
	this->size = SOLE_SIZE;
}

//������ͷ
void Snake::HeadDraw(Point node)
{
	setfillcolor(head_color);  //��ͷ��ɫ���
	setlinecolor(outline_color);
	fillrectangle(node.x, node.y, node.x + size, node.y + size);

	printf("x=%d,y=%d\n", node.x, node.y);
}

void Snake::SnakeDraw(Point node)
{
	setfillcolor(body_color);  //������ɫ���
	setlinecolor(outline_color);
	//fillrectangle(node.x + SOLE_SIZE, node.y + SOLE_SIZE, node.x + SOLE_SIZE + size, node.y + SOLE_SIZE + size);
	fillrectangle(node.x, node.y, node.x + size, node.y  + size);

	printf("x=%d,y=%d\n",node.x,node.y);
}

void Snake::CreateSnake(int node_num, int move_dir)
{
	this->node_num = node_num;
	this->move_dir = move_dir;
	//��ʼ�������
	for (int i = 0; i < node_num; i++)
	{
		node[node_num - i - 1].x = (i + 1) * size;
		node[i].y = SOLE_SIZE;
	}

	for (int i = 0; i < node_num; i++)
	{
		SnakeDraw(node[i]);
	}

}




bool Snake::move()
{
	/*
	if (!is_live())
		getchar();
		*/
	for (int i = node_num - 1; i > 0; i--)
	{
		node[i].x = node[i - 1].x;
		node[i].y = node[i - 1].y;
	}
	
	if (move_dir == UP) //����
	{
		if (node[0].y > size + 0)
			node[0].y -= 10;
		else   //���߲���
			return FALSE;

	}
	else if (move_dir == DOWN)  //����
		if (node[0].y < WIN_HEIGHT - size * 2)
			node[0].y += 10;
		else   //���߲���
			return FALSE;

	else if (move_dir == LEFT)  //����
		if (node[0].x > 0 + size)
			node[0].x -= 10;
		else   //���߲���
			return FALSE;

	else  //����
		if (node[0].x < WIN_WIDTH - size * 15)
			node[0].x += 10;
		else   //���߲���
			return FALSE;
	return TRUE;
}

void Snake::draw()
{
	cleardevice();  //����
	for (int i = 1; i < node_num; i++)
	{
		SnakeDraw(node[i]);
	}
	HeadDraw(node[0]);
}

void Snake::eatingFood(const Point& food,int& is_exist,int& sorce) 
{
	if (node[0] == food && is_exist)
	{
		//printf("node=(%d,%d)\n",node[0].x,node[0].y);
		node_num++;
		sorce += is_exist/10;
		is_exist = MAXTIME;
	}
	else if (is_exist < 0)
	{
		node_num--;
	}
}

bool Snake::is_SlefEating()
{
	for (int i = 1; i < node_num; i++)
	{
		if (node[0] == node[i])
			return 1;
	}
	return 0;
}

//==============================snake----snake-----snake===============================
