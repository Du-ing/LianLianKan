#pragma once
#include "global.h"
#include "GameLogic.h"
#include "Graph.h"

class CGameControl
{
public:
	CGameControl(void);
	~CGameControl(void);
	void StartGame();
	int GetElement(int nRow, int nCol);//根据行号列号获得元素值
	void SetFirstPoint(int nRow, int nCol);//设置第一个点
	void SetSecondPoint(int nRow, int nCol);//设置第二个点
	bool Link(Vertex Path[16], int &nVertexNum);//连接判断

private:
	CGraph m_graph;//游戏地图
	Vertex m_ptSelFirst;//第一次选择点
	Vertex m_ptSelSecond;//第二次选择点
public:
	bool IsWin(void);
};

