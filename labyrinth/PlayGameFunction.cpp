#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "PlayGame.h"

Player::Player()//�޲ι��캯��
{
	int i, j;
	this->mapLength = DefaultSize;//��ʼ����ͼ�ĸ߶�
	this->mapWidth = DefaultSize;//��ʼ����ͼ�Ŀ��
	this->pathCount = 0;

	for (i = 1; i <= this->mapLength; i++)//1~mapLength����Ҫ�ķ�Χ
	{
		for (j = 1; j <= this->mapWidth; j++)
		{
			this->Map[i][j].data = 1;//ǽ
		}
	}

	for (int i = 0; i < MaxSize; i++)
	{
		for (int j = 0; j < MaxSize; j++)
		{
			this->Map[i][j].visited = 0;//����޶��ڣ���ͼ�����е㶼Ĭ��δ�����ʹ�
		}
	}

	this->front = -1;
	this->rear = -1;
	this->top = -1;
}

Player::Player(int m, int n)//�вι��캯��
{
	int i, j;
	this->mapLength = m;//��ʼ����ͼ�ĸ߶�
	this->mapWidth = n;//��ʼ����ͼ�Ŀ��
	this->pathCount = 0;

	for (i = 1; i <= this->mapLength + 1; i++)//1~mapLength����Ҫ�ķ�Χ
	{
		for (j = 1; j <= this->mapWidth + 1; j++)
		{
			if (i == 0 || i == this->mapLength + 1 || j == 0 || j == this->mapWidth + 1)
			{
				this->Map[i][j].data = 0;//ͨ·
			}
			else
			{
				this->Map[i][j].data = 1;//ǽ
			}
		}
	}

	for (int i = 0; i < MaxSize; i++)
	{
		for (int j = 0; j < MaxSize; j++)
		{
			this->Map[i][j].visited = 0;//����޶��ڣ���ͼ�����е㶼Ĭ��δ�����ʹ�
		}
	}

	this->front = -1;
	this->rear = -1;
	this->top = -1;
}

void Player::Push()//��ջ
{
	this->front = this->rear + 1;
	this->rear = 0;
	this->top = -1;

	this->mapStack[++this->top] = this->mapQueue[front - 1];//����

	int direction[4][2] = { 1, 0, 0, 1, 0, -1, -1, 0 };//���巽������

	while (this->front != this->rear)//���в�Ϊ��ʱ
	{
		this->front--;
		for (int i = 0; i < 4; i++)
		{
			//��ջ����x����+����������1�� == ���ж��׵�x���� �� ջ����y����+����������2�� == ���ж��׵�y����
			if (this->mapStack[top].positionX + direction[i][0] == this->mapQueue[this->front - 1].positionX && this->mapStack[top].positionY + direction[i][1] == this->mapQueue[this->front - 1].positionY)
			{
				this->mapStack[++top] = this->mapQueue[this->front - 1];//�����еĶ�����ջ
			}
		}
	}
}

void Player::Show()//չʾ���·��
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

bool Player::Move()//������ƶ�
{
	bool flag = true;

	time_t startTime, endTime;

	int score = 100;//�ؿ���ʼ����
	char enter;
	int countDownTime = 20;//����ʱ
	int timeDifference;//ʱ���
	int b = 0;
	int c = this->mapLength / 2 + 1;//��ͼ�߶ȵ��е�
	int d = this->mapWidth / 2 + 1;//��ͼ��ȵ��е�
	int i, j;

	startTime = time(NULL);//��ȡϵͳ��ǰʱ�䲢��startTime����

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
		endTime = time(NULL);//ͬ���ģ���ȡϵͳ��ǰʱ��
		timeDifference = endTime - startTime;//ʱ��������

		if (_kbhit() == 0)//���������¼�δ����ʱ
		{
			if (b != timeDifference)
			{
				system("cls");

				this->PrintMap();

				cout << endl << "�����������ﵹ��ʱ��" << countDownTime-- << "��賓��������" << endl;
				b = timeDifference;

				if (countDownTime == -1)
				{
					system("cls");
					cout << "�����������ﴳ��ʧ�ܣ��賓��������" << endl;
					system("pause");
					flag = false;
					break;
				}
			}
		}

		if (_kbhit() != 0)//���������¼�����ʱ
		{
			enter = _getch();
			system("cls");
			if (enter == -32)//�������¼�Ϊ��������ܼ�ʱ�������������_getch()��������һ�ε��÷���0��0xe0(ת��Ϊ-32)���ڶ��η���ʵ�ʵļ�����
			{
				enter = _getch();//ʵ�ʼ��̴���
				if (enter == 75)//�����
				{
					if (this->Map[c][d - 1].data != 1 && this->MoveJudge(c, d - 1) == true)//��߲���ǽ
					{
						this->Map[c][d - 1].data = 2;//�����ߵ�·���Ϊ����
						this->Map[c][d].data = 4;//֮ǰ��·���Ϊ·��
						d -= 1;//�ƶ��ɹ����б�-1
					}
				}
				else if (enter == 77)//�ҷ����
				{
					if (this->Map[c][d + 1].data != 1 && this->MoveJudge(c, d + 1) == true)//�ұ߲���ǽ
					{
						this->Map[c][d + 1].data = 2;
						this->Map[c][d].data = 4;
						d += 1;
					}
				}
				else if (enter == 72)//�Ϸ����
				{
					if (this->Map[c - 1][d].data != 1 && this->MoveJudge(c - 1, d) == true)//�ϱ߲���ǽ
					{
						this->Map[c - 1][d].data = 2;
						this->Map[c][d].data = 4;
						c -= 1;
					}
				}
				else if (enter == 80)//�·����
				{
					if (Map[c + 1][d].data != 1 && this->MoveJudge(c + 1, d) == true)//�±߲���ǽ
					{
						this->Map[c + 1][d].data = 2;
						this->Map[c][d].data = 4;
						c += 1;
					}
				}
			}

			this->PrintMap();

			if (this->Map[this->mapLength - 1][this->mapLength - 1].data != 3)//��ԭ�����ֵ�λ�ñ������
			{
				system("cls");
				cout << "�����������﹧ϲ���سɹ����賓��������" << endl;
				score -= timeDifference;
				cout << "�����������ﱾ�ؿ���ʱ��" << timeDifference << "��" << endl;
				cout << "�����������ﱾ�ؿ��÷֣�" << score << endl;
				flag = true;
				Sleep(1000);
				cout << "��������������������·��.";
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

void Player::SaveMap()//����������ƶ�·��
{
	for (int i = 1; i <= this->mapLength; i++)
	{
		for (int j = 1; j <= this->mapWidth; j++)
		{
			switch (this->Map[i][j].data)
			{
			case 1:
				cout << "��";
				break;
			case 2:
				cout << "��";
				break;
			case 3:
				cout << "��";
				break;
			case 4:
				cout << "��";//������·�����Ϊ��
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

void Player::ShowMap()//չʾ��ʼ��ͼ
{
	//srand((unsigned)time(NULL));//ʹ����������ӣ�ȷ��ÿ�γ����������ɵ������(rand)���ǲ�һ����

	this->Generate(2 * (rand() % (this->mapLength / 2 + 1)), 2 * (rand() % (this->mapWidth / 2 + 1)));//�������ɵ�ͼ����������Ϊһ������ĵ�
	this->Map[this->mapLength / 2 + 1][this->mapWidth / 2 + 1].data = 2;//����ĳ�ʼλ��
	this->Map[this->mapLength - 1][this->mapWidth - 1].data = 3;//���ֵĳ�ʼλ��

	this->PrintMap();
}

void Player::PreShort(Player player)//���·����ǰ�ú���
{
	player.front = -1;
	player.rear = -1;

	for (int i = 1; i <= player.mapLength; i++)//���߹���·����Ϊ0���������·��������ʾΪ�߹���·��
	{
		for (int j = 1; j <= player.mapWidth; j++)
		{
			if (player.Map[i][j].data == 4)
			{
				player.Map[i][j].data = 0;
			}
		}
	}

	player.ShowMap();//չʾ��ʼ��ͼ

	system("cls");

	int m = player.mapLength - 1, n = player.mapWidth - 1;

	MapPoint p;//����һ����Ľṹ���յ㣩
	p.positionX = m;
	p.positionY = n;
	p.visited = 1;
	p.data = 3;
	player.ShortMap(p);//���յ㴫�����·������
	player.Show();
}

void Player::EditorMap()//�༭��ͼ
{
	int c = this->mapLength / 2 + 1;
	int d = this->mapWidth / 2 + 1;
	this->ShowMap();//չʾ��ʼ��ͼ
	system("cls");
	char enter;
	while (true)
	{
		this->Map[this->mapLength - 1][this->mapWidth - 1].data = 3;//�����ߵ��յ�ʱ�����յ�
		this->PrintMap();
		cout << "�����������ﰴ�»س��������޸ġ賓��������" << endl;

		enter = _getch();
		system("cls");
		if (enter == -32)//�������¼�Ϊ��������ܼ�ʱ�������������_getch()��������һ�ε��÷���0��0xe0(ת��Ϊ - 32)���ڶ��η���ʵ�ʵļ�����
		{
			enter = _getch();//ʵ�ʼ��̴���
			if (enter == 75)//�����
			{
				if (this->Map[c][d - 1].data != 1)
				{
					this->Map[c][d - 1].data = 2;
					this->Map[c][d].data = 0;
					d -= 1;
				}
			}
			else if (enter == 77)//�ҷ����
			{
				if (this->Map[c][d + 1].data != 1)
				{
					this->Map[c][d + 1].data = 2;
					this->Map[c][d].data = 0;
					d += 1;
				}
			}
			else if (enter == 72)//�Ϸ����
			{
				if (this->Map[c - 1][d].data != 1)
				{
					this->Map[c - 1][d].data = 2;
					this->Map[c][d].data = 0;
					c -= 1;
				}
			}
			else if (enter == 80)//�·����
			{
				if (this->Map[c + 1][d].data != 1)
				{
					this->Map[c + 1][d].data = 2;
					this->Map[c][d].data = 0;
					c += 1;
				}
			}
		}

		if (enter == 97)//A��
		{
			if (this->Map[c][d - 1].data == 1)//ǽ��·
			{
				this->Map[c][d - 1].data = 0;
			}
			else if (this->Map[c][d - 1].data == 0 || this->Map[c][d - 1].data == 4)//·��ǽ�������߹���·��
			{
				this->Map[c][d - 1].data = 1;
			}
		}
		else if (enter == 119)//W��
		{
			if (this->Map[c - 1][d].data == 1)//ǽ��·
			{
				this->Map[c - 1][d].data = 0;
			}
			else if (this->Map[c - 1][d].data == 0 || this->Map[c - 1][d].data == 4)//·��ǽ�������߹���·��
			{
				this->Map[c - 1][d].data = 1;
			}
		}
		else if (enter == 100)//D��
		{
			if (this->Map[c][d + 1].data == 1)//ǽ��·
			{
				this->Map[c][d + 1].data = 0;
			}
			else if (this->Map[c][d + 1].data == 0 || this->Map[c][d + 1].data == 4)//·��ǽ�������߹���·��
			{
				this->Map[c][d + 1].data = 1;
			}
		}
		else if (enter == 115)//S��
		{
			if (this->Map[c + 1][d].data == 1)//ǽ��·
			{
				this->Map[c + 1][d].data = 0;
			}
			else if (this->Map[c + 1][d].data == 0 || this->Map[c + 1][d].data == 4)//·��ǽ�������߹���·��
			{
				this->Map[c + 1][d].data = 1;
			}
		}
		else if (enter == 0x0D)//���»س���
		{
			this->Map[c][d].data = 0;//��������λ�ñ��·
			break;
		}
	}
}

void Player::ShortMap(MapPoint& Map)//���·��������Ϊ�յ�ṹ������
{
	/*
		����˼�룺ͼ�Ĺ�������㷨Ѱ�����·��
		1.���Ƚ��յ�Map���
		2.���յ�������������յ��ڽӵķ�ǽ�ĵ������һ�����
		3.������Ϊ1
	*/
	bool flag = false;

	Map.visited = 1;//�յ���Ϊ1

	this->PrintMap();//���ȴ�ӡ��ͼ

	this->front = -1;
	this->rear = -1;

	this->mapQueue[++this->rear] = Map;

	int direction[4][2] = { 1, 0, 0, 1, 0, -1, -1, 0 };//���巽������
	while (this->rear != this->front)//�����в�Ϊ��ʱ
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

				if (this->mapQueue[this->rear].positionX == (this->mapLength / 2 + 1) && this->mapQueue[this->rear].positionY == (this->mapWidth / 2 + 1))//����ͼ���ж�β������������������ʱ
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

void Player::ShowAllPath(int x, int y)//չʾ����·��
{
	int i, j;

	this->Map[x][y].data = 4;

	if (x == DefaultSize - 1 && y == DefaultSize - 1)
	{
		cout << "���ֵ�" << ++this->pathCount << "��·��" << endl;
		this->Map[this->mapLength / 2 + 1][this->mapWidth / 2 + 1].data = 2;
		this->Map[x][y].data = 3;
		for (i = 1; i <= this->mapLength; i++)
		{
			for (j = 1; j <= this->mapWidth; j++)
			{
				switch (this->Map[i][j].data)
				{
				case 1:
					cout << "��";
					break;
				case 2:
					cout << "��";
					break;
				case 3:
					cout << "��";
					break;
				case 4:
					cout << "��";
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

	if (this->Map[x][y + 1].data == 0 || this->Map[x][y + 1].data == 2)//��
	{
		this->ShowAllPath(x, y + 1);
	}
	if (this->Map[x + 1][y].data == 0 || this->Map[x + 1][y].data == 2)//��
	{
		this->ShowAllPath(x + 1, y);
	}
	if (this->Map[x][y - 1].data == 0 || this->Map[x][y - 1].data == 2)//��
	{
		this->ShowAllPath(x, y - 1);
	}
	if (this->Map[x - 1][y].data == 0 || this->Map[x - 1][y].data == 2)//��
	{
		this->ShowAllPath(x - 1, y);
	}
	this->Map[x][y].data = 0;
}

void Player::Generate(int m, int n)//��ͼ�ĳ�ʼ�����̣�����Ϊһ������ĵ�
{
	int direction[4][2] = { 1, 0, 0, 1, 0, -1, -1, 0 };//���巽������
	int i, j, temp;
	for (i = 0; i < 4; i++)//���ҷ�������
	{
		j = rand() % 4;//������ɷ�������
		temp = direction[i][0];
		direction[i][0] = direction[j][0];
		direction[j][0] = temp;

		temp = direction[i][1];
		direction[i][1] = direction[j][1];
		direction[j][1] = temp;
	}

	this->Map[m][n].data = 0;//����ĵ���Ϊͨ·

	for (i = 0; i < 4; i++)//�κ������յĵط�������·����
	{
		if (this->Map[m + 2 * direction[i][0]][n + 2 * direction[i][1]].data == 1)//������ĵ�+�����������Ϊǽʱ
		{
			this->Map[m + direction[i][0]][n + direction[i][1]].data = 0;//��ͨǽ��ʹǽ��ͨ·
			this->Generate(m + 2 * direction[i][0], n + 2 * direction[i][1]);//�ݹ����
		}
	}
}

void Player::PrintMap()//��ӡ��ͼ
{
	for (int i = 1; i <= this->mapWidth + 1; i++)//ȷ���Թ������涼��ǽ��û��ȱ��
	{
		if (this->Map[1][i].data != 1)
		{
			this->Map[1][i].data = 1;
		}
	}
	for (int i = 1; i <= this->mapWidth + 1; i++)//ȷ���Թ������涼��ǽ��û��ȱ��
	{
		if (this->Map[this->mapLength][i].data != 1)
		{
			this->Map[this->mapLength][i].data = 1;
		}
	}
	for (int i = 1; i <= this->mapLength + 1; i++)//ȷ���Թ������涼��ǽ��û��ȱ��
	{
		if (this->Map[i][1].data != 1)
		{
			this->Map[i][1].data = 1;
		}
	}
	for (int i = 1; i <= this->mapLength + 1; i++)//ȷ���Թ������涼��ǽ��û��ȱ��
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
				cout << "��";
				break;
			case 2:
				cout << "��";
				break;
			case 3:
				cout << "��";
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

bool Player::MoveJudge(int x, int y)//�ƶ��жϣ��Ƿ��߳��߽�
{
	bool flag = true;
	if ((x < 1 || x > DefaultSize) || (y < 1 || y > DefaultSize))
	{
		flag = false;
	}
	return flag;
}
