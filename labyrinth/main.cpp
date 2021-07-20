// 老鼠走迷宫.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include <conio.h>
#include "PlayGame.h"

void GameInterface();//开始界面
void ChooseLevel();//选择关卡
void StartGame(Player* player, bool* flag);//开始游戏
void EditorGame(Player* player, bool* flag);//编辑游戏
void ShortestPath(Player player[], bool* flag);//最短路径
void GameDescription();//游戏说明
void ExitGame();//退出游戏
void Hidden();//隐藏光标
void ShowAll(Player player[], bool* flag);//所有路径

int main()
{
	Player* player;
	for (int i = 0; i < NumberOfCheckpoints; i++)
	{
		player = new Player[NumberOfCheckpoints];
	}

	//Player player[NumberOfCheckpoints];

	char myChoice;
	char yes_no;

	bool flag[NumberOfCheckpoints];
	for (int i = 0; i < NumberOfCheckpoints; i++)
	{
		flag[i] = false;//默认每一关都闯关失败
	}

	Hidden();
	do
	{
		GameInterface();

		cin >> myChoice;
		system("cls");

		switch (myChoice)
		{
		case '1':
			StartGame(player, flag);//开始游戏
			break;
		case '2':
			EditorGame(player, flag);//编辑游戏
			break;
		case '3':
			ShortestPath(player, flag);//展示最短路径
			break;
		case '4':
			ShowAll(player, flag);//展示所有路径
			break;
		case '5':
			GameDescription();//游戏说明
			break;
		case '0':
			ExitGame();//退出游戏
			break;
		default:
			cout << "│────★输入非法！★────│" << endl;
			Sleep(1000);
			break;
		}

		if (myChoice == '0')
		{
			break;
		}

		do
		{
			system("cls");
			cout << "│────★是否回到主菜单？(Y/N)★────│" << endl;
			cin >> yes_no;
			if (yes_no != 'Y' && yes_no != 'y' && yes_no != 'N' && yes_no != 'n')
			{
				system("cls");
				cout << "│────★输入非法！请重新输入！★────│" << endl;
				Sleep(1000);
			}
		} while (yes_no != 'Y' && yes_no != 'y' && yes_no != 'N' && yes_no != 'n');

		if (yes_no == 'N' || yes_no == 'n')
		{
			ExitGame();
			break;
		}

	} while (yes_no == 'Y' || yes_no == 'y');

	delete[] player;
	return 0;
}

void GameInterface()//开始界面
{
	system("cls");
	system("@color 0a");//淡绿色前景色
	cout << "┌──────────────────────────────────────────────┐" << endl;
	cout << "│                                              │" << endl;
	cout << "│                ★1.开始游戏★                │" << endl;
	cout << "│                                              │" << endl;
	cout << "│                ★2.编辑游戏★                │" << endl;
	cout << "│                                              │" << endl;
	cout << "│              ★3.查看最短路径★              │" << endl;
	cout << "│                                              │" << endl;
	cout << "│              ★4.查看所有路径★              │" << endl;
	cout << "│                                              │" << endl;
	cout << "│         ★5.游戏说明（游戏前必读）★         │" << endl;
	cout << "│                                              │" << endl;
	cout << "│                ★0.退出游戏★                │" << endl;
	cout << "│                                              │" << endl;
	cout << "└──────────────────────────────────────────────┘" << endl;
}

void ChooseLevel()//选择关卡
{
	system("cls");
	system("@color 09");//淡蓝色前景色
	cout << "┌────★请选择关卡★────┐" << endl;
	for (int i = 0; i < NumberOfCheckpoints; i++)
	{
		cout << "│       " << i + 1 << "." << "第" << i + 1 << "关        │" << endl;
	}
	cout << "└──────────────────────┘" << endl;
}

void StartGame(Player* player, bool* flag)//开始游戏
{
	int i = 0;
	//bool flag = false;//每一关是否闯关成功
	char yes_no;

	system("@color 06");//黄色前景色
	cout << "┌──────────────────────★游戏说明★───────────────────────┐" << endl;
	cout << "│  使用键盘方向键移动老鼠(※)，在规定的时间内走到粮仓(★) │" << endl;
	cout << "└─────────────────────────────────────────────────────────┘" << endl;
	Sleep(1500);



	do
	{
		system("cls");
		cout << "│────★第" << i + 1 << "关★────│" << endl;
		Sleep(1000);
		system("cls");

		player[i].ShowMap();
		flag[i] = player[i].Move();

		if (flag[i] == true)//若当前关卡闯关成功
		{
			system("cls");
			player[i].SaveMap();//保存并展示老鼠的路径
			system("pause");
			if (i == NumberOfCheckpoints - 1)
			{
				cout << "│────★您已通关所有关卡！祝贺您！★────│" << endl;
				system("pause");
				break;
			}

			do
			{
				cout << "┌────★路径生成完毕，请进行你的选择★────┐" << endl;
				cout << "│             ★Y.继续游戏★             │" << endl;
				cout << "│             ★N.结束游戏★             │" << endl;
				cout << "└────────────────────────────────────────┘" << endl;

				cin >> yes_no;
				if (yes_no != 'Y' && yes_no != 'y' && yes_no != 'N' && yes_no != 'n')
				{
					cout << "│────★输入非法！请重新输入！★────│" << endl;
					Sleep(1000);
				}
			} while (yes_no != 'Y' && yes_no != 'y' && yes_no != 'N' && yes_no != 'n');

			if (yes_no == 'Y' || yes_no == 'y')
			{
				i++;//地图下标+1，下一关
			}
			else
			{
				break;
			}

		}

	} while (flag[i - 1] == true && i - 1 < NumberOfCheckpoints);//成功通关且在关卡最大数量限制内


}

void EditorGame(Player* player, bool* flag)//编辑游戏
{
	int myChoice;

	do
	{
		ChooseLevel();

		cin >> myChoice;

		if (myChoice < 1 || myChoice > NumberOfCheckpoints)
		{
			cout << "│────★输入非法！请重新输入！★────│" << endl;
			Sleep(1000);
		}
	} while (myChoice < 1 || myChoice > NumberOfCheckpoints);

	system("@color 0d");//淡紫色前景色
	player[myChoice - 1].EditorMap();//编辑相应的地图
	flag[myChoice - 1] = false;
	system("cls");

	Sleep(500);
}

void ShortestPath(Player player[], bool* flag)//最短路径
{
	int myChoice;

	do
	{
		ChooseLevel();

		cin >> myChoice;

		if (myChoice < 1 || myChoice > NumberOfCheckpoints)
		{
			cout << "│────★输入非法！请重新输入！★────│" << endl;
		}
	} while (myChoice < 1 || myChoice > NumberOfCheckpoints);

	if (flag[myChoice - 1] == true)
	{
		player[myChoice - 1].PreShort(player[myChoice - 1]);//调用该对象的前置最短路径方法
		system("cls");
	}
	else
	{
		cout << "│────★请先通关本关卡再看最短路径！★────│" << endl;
		Sleep(1000);
	}


}

void GameDescription()//游戏说明
{
	system("cls");
	cout << "│────★游戏说明★────│" << endl;
	cout << "│────★1.本游戏提供了随机生成迷宫、编辑迷宫、查看最短路径、查看所有路径等功能★────│" << endl;
	cout << "│────★2.玩家需先通过关卡才能够查看最短路径和所有路径，编辑地图后也需要先通关再查看最短路径和所有路径★────│" << endl;
	cout << "│────★3.通过键盘的方向键进行老鼠（※）的移动，到达粮仓（★）即为闯关成功且进入下一关，关卡耗时越少分数越高；规定时间内未能到达粮仓则闯关失败★────│" << endl;
	cout << "│────★4.编辑地图时通过WASD键控制老鼠的上下左右方向是否生产墙或通路★────│" << endl;
	cout << "│────★5.编辑地图时应保证至少有一条通路，编辑地图时可以编辑多条通路，若为死路则无法通关★────│" << endl;
	system("pause");
}

void ExitGame()//退出游戏
{
	system("@color 0c");//淡红色前景色
	cout << "│────★游戏结束，感谢体验★────│" << endl;
	system("pause");
}

void Hidden()//隐藏光标
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(hOut, &cci);
}

void ShowAll(Player player[], bool* flag)//展示所有路径
{
	system("cls");

	int myChoice;

	do
	{
		ChooseLevel();

		cin >> myChoice;

		if (myChoice < 1 || myChoice > NumberOfCheckpoints)
		{
			cout << "│────★输入非法！请重新输入！★────│" << endl;
		}

	} while (myChoice < 1 || myChoice > NumberOfCheckpoints);

	if (flag[myChoice - 1] == true)
	{
		for (int i = 1; i <= DefaultSize; i++)
		{
			for (int j = 1; j <= DefaultSize; j++)
			{
				if (player[myChoice - 1].Map[i][j].data == 4)
				{
					player[myChoice - 1].Map[i][j].data = 0;
				}
			}
		}

		player[myChoice - 1].pathCount = 0;
		player[myChoice - 1].ShowAllPath(DefaultSize / 2 + 1, DefaultSize / 2 + 1);//调用该对象的所有短路径方法
		system("pause");
	}
	else
	{
		cout << "│────★请先通关本关卡再看所有路径！★────│" << endl;
		Sleep(1000);
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

