#pragma once
#ifndef PLAYGAME_H
#define PLAYGAME_H

using namespace std;

const int MaxSize = 100;
const int NumberOfCheckpoints = 5;//最大关卡数
const int DefaultSize = 11;//默认地图尺寸

struct MapPoint
{
	int data;
	int positionX;
	int positionY;//路径的坐标
	int visited;//是否被访问过
};

class Player
{
private:
	int top;
	int rear, front;
	int mapLength, mapWidth;//地图的尺寸

	MapPoint mapStack[MaxSize];//地图栈
	MapPoint mapQueue[MaxSize];//地图队列
public:
	Player();//无参构造函数
	Player(int m, int n);//有参构造函数，手动设置地图的尺寸
	void Push();//入栈
	void Show();//展示最短路径
	bool Move();//移动
	void SaveMap();//保存老鼠的移动路径
	void ShowMap();//显示地图
	void PreShort(Player player);//最短路径的前置方法
	void EditorMap();//编辑地图
	void ShortMap(MapPoint& Map);//求最短路径
	void Generate(int x, int y);//生成地图
	void PrintMap();//打印地图
	bool MoveJudge(int x, int y);//移动判断

	void ShowAllPath(int x, int y);//展示所有路径
	int pathCount;//所有路径的数量

	MapPoint Map[MaxSize][MaxSize];//地图数组
};

#endif
