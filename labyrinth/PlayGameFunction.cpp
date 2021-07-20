#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "PlayGame.h"

Player::Player()//无参构造函数
{
	int i, j;
	this->mapLength = DefaultSize;//初始化地图的高度
	this->mapWidth = DefaultSize;//初始化地图的宽度
	this->pathCount = 0;

	for (i = 1; i <= this->mapLength; i++)//1~mapLength是需要的范围
	{
		for (j = 1; j <= this->mapWidth; j++)
		{
			this->Map[i][j].data = 1;//墙
		}
	}

	for (int i = 0; i < MaxSize; i++)
	{
		for (int j = 0; j < MaxSize; j++)
		{
			this->Map[i][j].visited = 0;//最大限度内，地图的所有点都默认未被访问过
		}
	}

	this->front = -1;
	this->rear = -1;
	this->top = -1;
}

Player::Player(int m, int n)//有参构造函数
{
	int i, j;
	this->mapLength = m;//初始化地图的高度
	this->mapWidth = n;//初始化地图的宽度
	this->pathCount = 0;

	for (i = 1; i <= this->mapLength + 1; i++)//1~mapLength是需要的范围
	{
		for (j = 1; j <= this->mapWidth + 1; j++)
		{
			if (i == 0 || i == this->mapLength + 1 || j == 0 || j == this->mapWidth + 1)
			{
				this->Map[i][j].data = 0;//通路
			}
			else
			{
				this->Map[i][j].data = 1;//墙
			}
		}
	}

	for (int i = 0; i < MaxSize; i++)
	{
		for (int j = 0; j < MaxSize; j++)
		{
			this->Map[i][j].visited = 0;//最大限度内，地图的所有点都默认未被访问过
		}
	}

	this->front = -1;
	this->rear = -1;
	this->top = -1;
}

void Player::Push()//入栈
{
	this->front = this->rear + 1;
	this->rear = 0;
	this->top = -1;

	this->mapStack[++this->top] = this->mapQueue[front - 1];//？？

	int direction[4][2] = { 1, 0, 0, 1, 0, -1, -1, 0 };//定义方向向量

	while (this->front != this->rear)//队列不为空时
	{
		this->front--;
		for (int i = 0; i < 4; i++)
		{
			//当栈顶的x坐标+方向向量第1列 == 队列队首的x坐标 且 栈顶的y坐标+方向向量第2列 == 队列队首的y坐标
			if (this->mapStack[top].positionX + direction[i][0] == this->mapQueue[this->front - 1].positionX && this->mapStack[top].positionY + direction[i][1] == this->mapQueue[this->front - 1].positionY)
			{
				this->mapStack[++top] = this->mapQueue[this->front - 1];//将队列的队首入栈
			}
		}
	}
}

void Player::Show()//展示最短路径
{
	system("cls");

	for (int i = 0; i <= this->top; i++)
	{
		if (this->Map[this->mapStack[i].positionX][this->mapStack[i].positionY].data != 2 && this->Map[this->mapStack[i].positionX][this->mapStack[i].positionY].data != 3)
		{
			this->Map[this->mapStack[i].positionX][this->mapStack[i].positionY].data = 4;
		}
	}
	this->SaveMap();

	system("pause");
}

bool Player::Move()//老鼠的移动
{
	bool flag = true;

	time_t startTime, endTime;

	int score = 100;//关卡初始分数
	char enter;
	int countDownTime = 20;//倒计时
	int timeDifference;//时间差
	int b = 0;
	int c = this->mapLength / 2 + 1;//地图高度的中点
	int d = this->mapWidth / 2 + 1;//地图宽度的中点
	int i, j;

	startTime = time(NULL);//获取系统当前时间并且startTime不变

	for (int i = 1; i <= this->mapLength; i++)
	{
		for (int j = 1; j <= this->mapWidth; j++)
		{
			if (this->Map[i][j].data == 4)
			{
				this->Map[i][j].data = 0;
			}
		}
	}

	while (countDownTime >= 0)
	{
		endTime = time(NULL);//同样的，获取系统当前时间
		timeDifference = endTime - startTime;//时间差（递增）

		if (_kbhit() == 0)//键盘输入事件未发生时
		{
			if (b != timeDifference)
			{
				system("cls");

				this->PrintMap();

				cout << endl << "│────★倒计时：" << countDownTime-- << "秒★────│" << endl;
				b = timeDifference;

				if (countDownTime == -1)
				{
					system("cls");
					cout << "│────★闯关失败！★────│" << endl;
					system("pause");
					flag = false;
					break;
				}
			}
		}

		if (_kbhit() != 0)//键盘输入事件发生时
		{
			enter = _getch();
			system("cls");
			if (enter == -32)//当键盘事件为方向键或功能键时，必须调用两次_getch()函数，第一次调用返回0或0xe0(转换为-32)，第二次返回实际的键代码
			{
				enter = _getch();//实际键盘代码
				if (enter == 75)//左方向键
				{
					if (this->Map[c][d - 1].data != 1 && this->MoveJudge(c, d - 1) == true)//左边不是墙
					{
						this->Map[c][d - 1].data = 2;//即将走的路标记为老鼠
						this->Map[c][d].data = 4;//之前的路标记为路径
						d -= 1;//移动成功，列标-1
					}
				}
				else if (enter == 77)//右方向键
				{
					if (this->Map[c][d + 1].data != 1 && this->MoveJudge(c, d + 1) == true)//右边不是墙
					{
						this->Map[c][d + 1].data = 2;
						this->Map[c][d].data = 4;
						d += 1;
					}
				}
				else if (enter == 72)//上方向键
				{
					if (this->Map[c - 1][d].data != 1 && this->MoveJudge(c - 1, d) == true)//上边不是墙
					{
						this->Map[c - 1][d].data = 2;
						this->Map[c][d].data = 4;
						c -= 1;
					}
				}
				else if (enter == 80)//下方向键
				{
					if (Map[c + 1][d].data != 1 && this->MoveJudge(c + 1, d) == true)//下边不是墙
					{
						this->Map[c + 1][d].data = 2;
						this->Map[c][d].data = 4;
						c += 1;
					}
				}
			}

			this->PrintMap();

			if (this->Map[this->mapLength - 1][this->mapLength - 1].data != 3)//当原本粮仓的位置变成老鼠
			{
				system("cls");
				cout << "│────★恭喜闯关成功！★────│" << endl;
				score -= timeDifference;
				cout << "│────★本关卡耗时：" << timeDifference << "秒" << endl;
				cout << "│────★本关卡得分：" << score << endl;
				flag = true;
				Sleep(1000);
				cout << "│────★正在生成路径.";
				Sleep(500);
				cout << ".";
				Sleep(500);
				cout << ".";
				Sleep(500);
				break;
			}
		}
	}

	return flag;
}

void Player::SaveMap()//保存老鼠的移动路径
{
	for (int i = 1; i <= this->mapLength; i++)
	{
		for (int j = 1; j <= this->mapWidth; j++)
		{
			switch (this->Map[i][j].data)
			{
			case 1:
				cout << "■";
				break;
			case 2:
				cout << "※";
				break;
			case 3:
				cout << "★";
				break;
			case 4:
				cout << "×";//经过的路径标记为×
				break;
			case 0:
				cout << "  ";
				break;
			default:
				break;
			}
		}
		cout << endl;
	}
}

void Player::ShowMap()//展示初始地图
{
	//srand((unsigned)time(NULL));//使用随机数种子，确保每次程序启动生成的随机数(rand)都是不一样的

	this->Generate(2 * (rand() % (this->mapLength / 2 + 1)), 2 * (rand() % (this->mapWidth / 2 + 1)));//调用生成地图函数，参数为一个随机的点
	this->Map[this->mapLength / 2 + 1][this->mapWidth / 2 + 1].data = 2;//老鼠的初始位置
	this->Map[this->mapLength - 1][this->mapWidth - 1].data = 3;//粮仓的初始位置

	this->PrintMap();
}

void Player::PreShort(Player player)//最短路径的前置函数
{
	player.front = -1;
	player.rear = -1;

	for (int i = 1; i <= player.mapLength; i++)//将走过的路径置为0，否则最短路径将会显示为走过的路径
	{
		for (int j = 1; j <= player.mapWidth; j++)
		{
			if (player.Map[i][j].data == 4)
			{
				player.Map[i][j].data = 0;
			}
		}
	}

	player.ShowMap();//展示初始地图

	system("cls");

	int m = player.mapLength - 1, n = player.mapWidth - 1;

	MapPoint p;//定义一个点的结构（终点）
	p.positionX = m;
	p.positionY = n;
	p.visited = 1;
	p.data = 3;
	player.ShortMap(p);//将终点传入最短路径函数
	player.Show();
}

void Player::EditorMap()//编辑地图
{
	int c = this->mapLength / 2 + 1;
	int d = this->mapWidth / 2 + 1;
	this->ShowMap();//展示初始地图
	system("cls");
	char enter;
	while (true)
	{
		this->Map[this->mapLength - 1][this->mapWidth - 1].data = 3;//避免走到终点时覆盖终点
		this->PrintMap();
		cout << "│────★按下回车键保存修改★────│" << endl;

		enter = _getch();
		system("cls");
		if (enter == -32)//当键盘事件为方向键或功能键时，必须调用两次_getch()函数，第一次调用返回0或0xe0(转换为 - 32)，第二次返回实际的键代码
		{
			enter = _getch();//实际键盘代码
			if (enter == 75)//左方向键
			{
				if (this->Map[c][d - 1].data != 1)
				{
					this->Map[c][d - 1].data = 2;
					this->Map[c][d].data = 0;
					d -= 1;
				}
			}
			else if (enter == 77)//右方向键
			{
				if (this->Map[c][d + 1].data != 1)
				{
					this->Map[c][d + 1].data = 2;
					this->Map[c][d].data = 0;
					d += 1;
				}
			}
			else if (enter == 72)//上方向键
			{
				if (this->Map[c - 1][d].data != 1)
				{
					this->Map[c - 1][d].data = 2;
					this->Map[c][d].data = 0;
					c -= 1;
				}
			}
			else if (enter == 80)//下方向键
			{
				if (this->Map[c + 1][d].data != 1)
				{
					this->Map[c + 1][d].data = 2;
					this->Map[c][d].data = 0;
					c += 1;
				}
			}
		}

		if (enter == 97)//A键
		{
			if (this->Map[c][d - 1].data == 1)//墙变路
			{
				this->Map[c][d - 1].data = 0;
			}
			else if (this->Map[c][d - 1].data == 0 || this->Map[c][d - 1].data == 4)//路变墙（包括走过的路）
			{
				this->Map[c][d - 1].data = 1;
			}
		}
		else if (enter == 119)//W键
		{
			if (this->Map[c - 1][d].data == 1)//墙变路
			{
				this->Map[c - 1][d].data = 0;
			}
			else if (this->Map[c - 1][d].data == 0 || this->Map[c - 1][d].data == 4)//路变墙（包括走过的路）
			{
				this->Map[c - 1][d].data = 1;
			}
		}
		else if (enter == 100)//D键
		{
			if (this->Map[c][d + 1].data == 1)//墙变路
			{
				this->Map[c][d + 1].data = 0;
			}
			else if (this->Map[c][d + 1].data == 0 || this->Map[c][d + 1].data == 4)//路变墙（包括走过的路）
			{
				this->Map[c][d + 1].data = 1;
			}
		}
		else if (enter == 115)//S键
		{
			if (this->Map[c + 1][d].data == 1)//墙变路
			{
				this->Map[c + 1][d].data = 0;
			}
			else if (this->Map[c + 1][d].data == 0 || this->Map[c + 1][d].data == 4)//路变墙（包括走过的路）
			{
				this->Map[c + 1][d].data = 1;
			}
		}
		else if (enter == 0x0D)//按下回车键
		{
			this->Map[c][d].data = 0;//老鼠所在位置变成路
			break;
		}
	}
}

void Player::ShortMap(MapPoint& Map)//最短路径，参数为终点结构的引用
{
	/*
		核心思想：图的广度优先算法寻找最短路径
		1.首先将终点Map入队
		2.从终点出发，所有与终点邻接的非墙的点与队首一起入队
		3.将其标记为1
	*/
	bool flag = false;

	Map.visited = 1;//终点标记为1

	this->PrintMap();//首先打印地图

	this->front = -1;
	this->rear = -1;

	this->mapQueue[++this->rear] = Map;

	int direction[4][2] = { 1, 0, 0, 1, 0, -1, -1, 0 };//定义方向向量
	while (this->rear != this->front)//当队列不为空时
	{
		this->front++;

		for (int j = 0; j < 4; j++)
		{
			bool flag1 = false, flag2 = false, flag3 = false, flag4 = false, flag5 = false, flag6 = false;
			if (this->Map[this->mapQueue[this->front].positionX + direction[j][0]][this->mapQueue[this->front].positionY + direction[j][1]].data == 0)
			{
				flag1 = true;
			}
			if (this->Map[this->mapQueue[this->front].positionX + direction[j][0]][this->mapQueue[this->front].positionY + direction[j][1]].data == 2)
			{
				flag2 = true;
			}
			if (this->Map[this->mapQueue[this->front].positionX + direction[j][0]][this->mapQueue[this->front].positionY + direction[j][1]].data == 4)
			{
				flag3 = true;
			}
			if (this->Map[this->mapQueue[this->front].positionX + direction[j][0]][this->mapQueue[this->front].positionY + direction[j][1]].visited == 0)
			{
				flag4 = true;
			}
			if (this->mapQueue[this->front].positionX < this->mapWidth && this->mapQueue[this->front].positionX >= 1)
			{
				flag5 = true;
			}
			if (this->mapQueue[this->front].positionY < this->mapLength && this->mapQueue[this->front].positionY >= 1)
			{
				flag6 = true;
			}
			if ((flag1 == true || flag2 == true || flag3 == true) && flag4 == true && flag5 == true && flag6 == true)
			{
				this->rear++;

				this->mapQueue[this->rear].positionX = this->mapQueue[this->front].positionX + direction[j][0];
				this->mapQueue[this->rear].positionY = this->mapQueue[this->front].positionY + direction[j][1];

				this->Map[this->mapQueue[this->front].positionX + direction[j][0]][this->mapQueue[this->front].positionY + direction[j][1]].visited = 1;

				if (this->mapQueue[this->rear].positionX == (this->mapLength / 2 + 1) && this->mapQueue[this->rear].positionY == (this->mapWidth / 2 + 1))//当地图队列队尾的坐标等于老鼠的坐标时
				{
					flag = true;
					break;
				}
			}
		}

		if (flag == true)
		{
			break;
		}
	}
	this->Push();
}

void Player::ShowAllPath(int x, int y)//展示所有路径
{
	int i, j;

	this->Map[x][y].data = 4;

	if (x == DefaultSize - 1 && y == DefaultSize - 1)
	{
		cout << "发现第" << ++this->pathCount << "条路径" << endl;
		this->Map[this->mapLength / 2 + 1][this->mapWidth / 2 + 1].data = 2;
		this->Map[x][y].data = 3;
		for (i = 1; i <= this->mapLength; i++)
		{
			for (j = 1; j <= this->mapWidth; j++)
			{
				switch (this->Map[i][j].data)
				{
				case 1:
					cout << "■";
					break;
				case 2:
					cout << "※";
					break;
				case 3:
					cout << "★";
					break;
				case 4:
					cout << "×";
					break;
				case 0:
					cout << "  ";
					break;
				default:
					break;
				}
			}
			cout << endl;
		}

	}

	this->Map[this->mapLength / 2 + 1][this->mapWidth / 2 + 1].data = 4;
	this->Map[x][y].data = 4;

	if (this->Map[x][y + 1].data == 0 || this->Map[x][y + 1].data == 2)//右
	{
		this->ShowAllPath(x, y + 1);
	}
	if (this->Map[x + 1][y].data == 0 || this->Map[x + 1][y].data == 2)//下
	{
		this->ShowAllPath(x + 1, y);
	}
	if (this->Map[x][y - 1].data == 0 || this->Map[x][y - 1].data == 2)//左
	{
		this->ShowAllPath(x, y - 1);
	}
	if (this->Map[x - 1][y].data == 0 || this->Map[x - 1][y].data == 2)//上
	{
		this->ShowAllPath(x - 1, y);
	}
	this->Map[x][y].data = 0;
}

void Player::Generate(int m, int n)//地图的初始化过程，参数为一个随机的点
{
	int direction[4][2] = { 1, 0, 0, 1, 0, -1, -1, 0 };//定义方向向量
	int i, j, temp;
	for (i = 0; i < 4; i++)//打乱方向向量
	{
		j = rand() % 4;//随机生成方向向量
		temp = direction[i][0];
		direction[i][0] = direction[j][0];
		direction[j][0] = temp;

		temp = direction[i][1];
		direction[i][1] = direction[j][1];
		direction[j][1] = temp;
	}

	this->Map[m][n].data = 0;//传入的点设为通路

	for (i = 0; i < 4; i++)//任何两个空的地方都会有路可走
	{
		if (this->Map[m + 2 * direction[i][0]][n + 2 * direction[i][1]].data == 1)//当传入的点+随机方向向量为墙时
		{
			this->Map[m + direction[i][0]][n + direction[i][1]].data = 0;//打通墙，使墙变通路
			this->Generate(m + 2 * direction[i][0], n + 2 * direction[i][1]);//递归调用
		}
	}
}

void Player::PrintMap()//打印地图
{
	for (int i = 1; i <= this->mapWidth + 1; i++)//确保迷宫的上面都是墙，没有缺口
	{
		if (this->Map[1][i].data != 1)
		{
			this->Map[1][i].data = 1;
		}
	}
	for (int i = 1; i <= this->mapWidth + 1; i++)//确保迷宫的下面都是墙，没有缺口
	{
		if (this->Map[this->mapLength][i].data != 1)
		{
			this->Map[this->mapLength][i].data = 1;
		}
	}
	for (int i = 1; i <= this->mapLength + 1; i++)//确保迷宫的左面都是墙，没有缺口
	{
		if (this->Map[i][1].data != 1)
		{
			this->Map[i][1].data = 1;
		}
	}
	for (int i = 1; i <= this->mapLength + 1; i++)//确保迷宫的右面都是墙，没有缺口
	{
		if (this->Map[i][this->mapWidth].data != 1)
		{
			this->Map[i][this->mapWidth].data = 1;
		}
	}

	for (int i = 1; i <= this->mapLength; i++)
	{
		for (int j = 1; j <= this->mapLength; j++)
		{
			switch (this->Map[i][j].data)
			{
			case 1:
				cout << "■";
				break;
			case 2:
				cout << "※";
				break;
			case 3:
				cout << "★";
				break;
			case 4:
				cout << "  ";
				break;
			case 0:
				cout << "  ";
				break;
			default:
				break;
			}
		}
		cout << endl;
	}
}

bool Player::MoveJudge(int x, int y)//移动判断，是否走出边界
{
	bool flag = true;
	if ((x < 1 || x > DefaultSize) || (y < 1 || y > DefaultSize))
	{
		flag = false;
	}
	return flag;
}
