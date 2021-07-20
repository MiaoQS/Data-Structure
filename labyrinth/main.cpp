// �������Թ�.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <windows.h>
#include <conio.h>
#include "PlayGame.h"

void GameInterface();//��ʼ����
void ChooseLevel();//ѡ��ؿ�
void StartGame(Player* player, bool* flag);//��ʼ��Ϸ
void EditorGame(Player* player, bool* flag);//�༭��Ϸ
void ShortestPath(Player player[], bool* flag);//���·��
void GameDescription();//��Ϸ˵��
void ExitGame();//�˳���Ϸ
void Hidden();//���ع��
void ShowAll(Player player[], bool* flag);//����·��

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
		flag[i] = false;//Ĭ��ÿһ�ض�����ʧ��
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
			StartGame(player, flag);//��ʼ��Ϸ
			break;
		case '2':
			EditorGame(player, flag);//�༭��Ϸ
			break;
		case '3':
			ShortestPath(player, flag);//չʾ���·��
			break;
		case '4':
			ShowAll(player, flag);//չʾ����·��
			break;
		case '5':
			GameDescription();//��Ϸ˵��
			break;
		case '0':
			ExitGame();//�˳���Ϸ
			break;
		default:
			cout << "����������������Ƿ����賓��������" << endl;
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
			cout << "�������������Ƿ�ص����˵���(Y/N)�賓��������" << endl;
			cin >> yes_no;
			if (yes_no != 'Y' && yes_no != 'y' && yes_no != 'N' && yes_no != 'n')
			{
				system("cls");
				cout << "����������������Ƿ������������룡�賓��������" << endl;
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

void GameInterface()//��ʼ����
{
	system("cls");
	system("@color 0a");//����ɫǰ��ɫ
	cout << "������������������������������������������������������������������������������������������������" << endl;
	cout << "��                                              ��" << endl;
	cout << "��                ��1.��ʼ��Ϸ��                ��" << endl;
	cout << "��                                              ��" << endl;
	cout << "��                ��2.�༭��Ϸ��                ��" << endl;
	cout << "��                                              ��" << endl;
	cout << "��              ��3.�鿴���·����              ��" << endl;
	cout << "��                                              ��" << endl;
	cout << "��              ��4.�鿴����·����              ��" << endl;
	cout << "��                                              ��" << endl;
	cout << "��         ��5.��Ϸ˵������Ϸǰ�ض�����         ��" << endl;
	cout << "��                                              ��" << endl;
	cout << "��                ��0.�˳���Ϸ��                ��" << endl;
	cout << "��                                              ��" << endl;
	cout << "������������������������������������������������������������������������������������������������" << endl;
}

void ChooseLevel()//ѡ��ؿ�
{
	system("cls");
	system("@color 09");//����ɫǰ��ɫ
	cout << "��������������ѡ��ؿ��賓��������" << endl;
	for (int i = 0; i < NumberOfCheckpoints; i++)
	{
		cout << "��       " << i + 1 << "." << "��" << i + 1 << "��        ��" << endl;
	}
	cout << "������������������������������������������������" << endl;
}

void StartGame(Player* player, bool* flag)//��ʼ��Ϸ
{
	int i = 0;
	//bool flag = false;//ÿһ���Ƿ񴳹سɹ�
	char yes_no;

	system("@color 06");//��ɫǰ��ɫ
	cout << "��������������������������������������������������Ϸ˵���賓����������������������������������������������" << endl;
	cout << "��  ʹ�ü��̷�����ƶ�����(��)���ڹ涨��ʱ�����ߵ�����(��) ��" << endl;
	cout << "����������������������������������������������������������������������������������������������������������������������" << endl;
	Sleep(1500);



	do
	{
		system("cls");
		cout << "�������������" << i + 1 << "�ء賓��������" << endl;
		Sleep(1000);
		system("cls");

		player[i].ShowMap();
		flag[i] = player[i].Move();

		if (flag[i] == true)//����ǰ�ؿ����سɹ�
		{
			system("cls");
			player[i].SaveMap();//���沢չʾ�����·��
			system("pause");
			if (i == NumberOfCheckpoints - 1)
			{
				cout << "����������������ͨ�����йؿ���ף�������賓��������" << endl;
				system("pause");
				break;
			}

			do
			{
				cout << "������������·��������ϣ���������ѡ��賓��������" << endl;
				cout << "��             ��Y.������Ϸ��             ��" << endl;
				cout << "��             ��N.������Ϸ��             ��" << endl;
				cout << "������������������������������������������������������������������������������������" << endl;

				cin >> yes_no;
				if (yes_no != 'Y' && yes_no != 'y' && yes_no != 'N' && yes_no != 'n')
				{
					cout << "����������������Ƿ������������룡�賓��������" << endl;
					Sleep(1000);
				}
			} while (yes_no != 'Y' && yes_no != 'y' && yes_no != 'N' && yes_no != 'n');

			if (yes_no == 'Y' || yes_no == 'y')
			{
				i++;//��ͼ�±�+1����һ��
			}
			else
			{
				break;
			}

		}

	} while (flag[i - 1] == true && i - 1 < NumberOfCheckpoints);//�ɹ�ͨ�����ڹؿ��������������


}

void EditorGame(Player* player, bool* flag)//�༭��Ϸ
{
	int myChoice;

	do
	{
		ChooseLevel();

		cin >> myChoice;

		if (myChoice < 1 || myChoice > NumberOfCheckpoints)
		{
			cout << "����������������Ƿ������������룡�賓��������" << endl;
			Sleep(1000);
		}
	} while (myChoice < 1 || myChoice > NumberOfCheckpoints);

	system("@color 0d");//����ɫǰ��ɫ
	player[myChoice - 1].EditorMap();//�༭��Ӧ�ĵ�ͼ
	flag[myChoice - 1] = false;
	system("cls");

	Sleep(500);
}

void ShortestPath(Player player[], bool* flag)//���·��
{
	int myChoice;

	do
	{
		ChooseLevel();

		cin >> myChoice;

		if (myChoice < 1 || myChoice > NumberOfCheckpoints)
		{
			cout << "����������������Ƿ������������룡�賓��������" << endl;
		}
	} while (myChoice < 1 || myChoice > NumberOfCheckpoints);

	if (flag[myChoice - 1] == true)
	{
		player[myChoice - 1].PreShort(player[myChoice - 1]);//���øö����ǰ�����·������
		system("cls");
	}
	else
	{
		cout << "����������������ͨ�ر��ؿ��ٿ����·�����賓��������" << endl;
		Sleep(1000);
	}


}

void GameDescription()//��Ϸ˵��
{
	system("cls");
	cout << "��������������Ϸ˵���賓��������" << endl;
	cout << "������������1.����Ϸ�ṩ����������Թ����༭�Թ����鿴���·�����鿴����·���ȹ��ܡ賓��������" << endl;
	cout << "������������2.�������ͨ���ؿ����ܹ��鿴���·��������·�����༭��ͼ��Ҳ��Ҫ��ͨ���ٲ鿴���·��������·���賓��������" << endl;
	cout << "������������3.ͨ�����̵ķ�����������󣨡������ƶ����������֣����Ϊ���سɹ��ҽ�����һ�أ��ؿ���ʱԽ�ٷ���Խ�ߣ��涨ʱ����δ�ܵ��������򴳹�ʧ�ܡ賓��������" << endl;
	cout << "������������4.�༭��ͼʱͨ��WASD������������������ҷ����Ƿ�����ǽ��ͨ·�賓��������" << endl;
	cout << "������������5.�༭��ͼʱӦ��֤������һ��ͨ·���༭��ͼʱ���Ա༭����ͨ·����Ϊ��·���޷�ͨ�ء賓��������" << endl;
	system("pause");
}

void ExitGame()//�˳���Ϸ
{
	system("@color 0c");//����ɫǰ��ɫ
	cout << "��������������Ϸ��������л����賓��������" << endl;
	system("pause");
}

void Hidden()//���ع��
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(hOut, &cci);
}

void ShowAll(Player player[], bool* flag)//չʾ����·��
{
	system("cls");

	int myChoice;

	do
	{
		ChooseLevel();

		cin >> myChoice;

		if (myChoice < 1 || myChoice > NumberOfCheckpoints)
		{
			cout << "����������������Ƿ������������룡�賓��������" << endl;
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
		player[myChoice - 1].ShowAllPath(DefaultSize / 2 + 1, DefaultSize / 2 + 1);//���øö�������ж�·������
		system("pause");
	}
	else
	{
		cout << "����������������ͨ�ر��ؿ��ٿ�����·�����賓��������" << endl;
		Sleep(1000);
	}
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�

