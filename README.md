# EatingSnake

#### 介绍
项目名    ：贪吃蛇

项目语言：c/c++

开发工具：visual studio 2019 

开发时间：2021/11/13 - 2021/11/14

描        述：基于easyx库开发的c++图形界面小游戏，玩法基本与传统贪吃蛇相同





#### 软件架构
分为三部分：

[main.cpp](#####main.cpp)

[GameWin.cpp](#####GameWin.cpp)

[GameWin.h](#####GameWin.h)

##### main.cpp

​	是整个项目的主程序，在此进行了以下操作：

1. 对游戏进行数据初始化以及画面绘制
2. 键盘监控，响应相应操作
3. 游戏主体循环

##### GameWin.h

​	1. 对游戏要操作的对象以及窗口进行抽象以及类封装，声明相对应的方法，搭建基本框架

​	2. 利用宏定义以及运算符重载等简化代码

##### GameWin.cpp

1. 对[GameWin.h](#####GameWin.h)中声明的各种方法进行具体实现

#### 使用说明

##### 游戏操作

1.  移动：<kbd>↑</kbd>向上移动  <kbd>↓</kbd>向下移动  <kbd>←</kbd>>向左移动  <kbd>→</kbd>向右移动
2.  当由于碰壁或者自食死亡后，按<kbd>esc</kbd>退出，按<kbd>enter</kbd>重开
3.  注意: 随着蛇身长度增加，蛇移动速度会越来越快。食物消失速度也会加快，食物消失之前没有吃到食物蛇会退化的（变短）

##### 代码文档

1. [GameWin](######GameWin)

2. [Snake](######Snake)

3. [Food_tlg](######Food_tlg)



###### GameWin

```c++
GameWin(int WinWidth, int WinHeigth,COLORREF BackColor,int outline_color)
```

`WinWidth`: 窗口宽度 px

`WinHeight`: 窗口高度 px

`BackColor`: 背景颜色

`ouline——color`：界面边框颜色



```c++
init()
```

开始绘制界面



```c++
OutLine_Draw()
```

绘制界面外边框，init()的过程方法



```c++
Print_Sorce()
```

绘制分数



```c++
GameOver(const wchar_t*  tip)
```

`tip`： 在游戏结束时想输出到屏幕上的文本



###### Snake

```c++
Snake(int body_color, int outline_color,int head_color)
```

`body_color`: 蛇身颜色

`outline_color`: 蛇身外轮廓颜色

`int head_color`：头部颜色



```c++
HeadDraw(Point node)
```

画头

`node`：坐标

```c++
CreateSnake(int node_num, int move_dir)
```

用于创建一条新蛇

`node_num`: 蛇的身体长度

`move_dir`: 默认移动方向



```c++
eatingFood(const Point& food,int& is_exist,int& sorce)
```

吃食物时候的判断，判断是否已经吃到食物，或者食物已经消失

`food`： 食物的坐标

`is_exist`: 食物的存在标志

`sorce`: 一般是GameWin对象的sorce属性



###### Food_tlg

```c++
create(const Snake& snake)
```

`snake`：蛇的对象，用于创建食物时对食物位置的判定





#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request



#### [博客(gitee)](xiaomo-xty.gitee.io) [博客(github)](http://tangyuanya.top)

[gitee](https://gitee.com/xiaomo-xty)

