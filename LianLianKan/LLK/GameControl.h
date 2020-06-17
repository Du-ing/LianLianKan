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
	int GetElement(int nRow, int nCol);//�����к��кŻ��Ԫ��ֵ
	void SetFirstPoint(int nRow, int nCol);//���õ�һ����
	void SetSecondPoint(int nRow, int nCol);//���õڶ�����
	bool Link(Vertex Path[16], int &nVertexNum);//�����ж�

private:
	CGraph m_graph;//��Ϸ��ͼ
	Vertex m_ptSelFirst;//��һ��ѡ���
	Vertex m_ptSelSecond;//�ڶ���ѡ���
public:
	bool IsWin(void);
};

