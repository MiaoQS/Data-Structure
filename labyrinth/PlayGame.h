#pragma once
#ifndef PLAYGAME_H
#define PLAYGAME_H

using namespace std;

const int MaxSize = 100;
const int NumberOfCheckpoints = 5;//���ؿ���
const int DefaultSize = 11;//Ĭ�ϵ�ͼ�ߴ�

struct MapPoint
{
	int data;
	int positionX;
	int positionY;//·��������
	int visited;//�Ƿ񱻷��ʹ�
};

class Player
{
private:
	int top;
	int rear, front;
	int mapLength, mapWidth;//��ͼ�ĳߴ�

	MapPoint mapStack[MaxSize];//��ͼջ
	MapPoint mapQueue[MaxSize];//��ͼ����
public:
	Player();//�޲ι��캯��
	Player(int m, int n);//�вι��캯�����ֶ����õ�ͼ�ĳߴ�
	void Push();//��ջ
	void Show();//չʾ���·��
	bool Move();//�ƶ�
	void SaveMap();//����������ƶ�·��
	void ShowMap();//��ʾ��ͼ
	void PreShort(Player player);//���·����ǰ�÷���
	void EditorMap();//�༭��ͼ
	void ShortMap(MapPoint& Map);//�����·��
	void Generate(int x, int y);//���ɵ�ͼ
	void PrintMap();//��ӡ��ͼ
	bool MoveJudge(int x, int y);//�ƶ��ж�

	void ShowAllPath(int x, int y);//չʾ����·��
	int pathCount;//����·��������

	MapPoint Map[MaxSize][MaxSize];//��ͼ����
};

#endif
