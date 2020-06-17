#include "StdAfx.h"
#include "GameControl.h"


CGameControl::CGameControl(void)
{
}


CGameControl::~CGameControl(void)
{
}

void CGameControl::StartGame()
{
	CGameLogic gameLogic;//����һ��CGameLogic����
	gameLogic.InitMap(m_graph);//��ʼ����ͼ
}

//��ȡ��Ӧ�к��к�Ԫ�ص�ֵ
int CGameControl::GetElement(int nRow, int nCol)
{
	return m_graph.GetVertex(nRow * 4 + nCol);
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

void CGameControl::SetSecondPoint(int nRow, int nCol)
{
	m_ptSelSecond.row = nRow;
	m_ptSelSecond.col = nCol;
}

//�ж�����ѡ��ĵ��Ƿ���ͨ
bool CGameControl::Link(Vertex Path[16], int &nVertexNum)
{
	//�ж������Ƿ���ͬһλ��
	if(m_ptSelFirst.row == m_ptSelSecond.row && m_ptSelFirst.col == m_ptSelSecond.col)
	{
		return false;
	}
	//�ж�����ͼƬԪ���Ƿ���ͬ
	int Index1 = m_graph.GetVertex(m_ptSelFirst.row * 4 + m_ptSelFirst.col);
	int Index2 = m_graph.GetVertex(m_ptSelSecond.row * 4 + m_ptSelSecond.col);
	if(Index1 != Index2 || Index1 == -1 || Index2 == -1)
	{
		return false;
	}
	//�ж��Ƿ���ͨ
	CGameLogic gameLogic;
	if(gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSecond))
	{
		//����
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSecond);
		//��ȡ������·��������·��������
		nVertexNum = gameLogic.GetVertexPath(Path);
		return true;
	}
	return false;
}

//�ж�ʤ��
bool CGameControl::IsWin(void)
{
	CGameLogic gameLogic;
	if(gameLogic.IsBlank(m_graph))
	{
		//ʤ������Ϸ����������ͼ
		m_graph.ClearGraph();
		return true;
	}
	return false;
}
