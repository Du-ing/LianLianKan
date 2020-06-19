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
	return m_graph.GetVertex(nRow * MAX_WID + nCol);
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
bool CGameControl::Link(Vertex Path[MAX_VERTEX_NUM], int &nVertexNum)
{
	//�ж������Ƿ���ͬһλ��
	if(m_ptSelFirst.row == m_ptSelSecond.row && m_ptSelFirst.col == m_ptSelSecond.col)
	{
		return false;
	}
	//�ж�����ͼƬԪ���Ƿ���ͬ
	int Index1 = m_graph.GetVertex(m_ptSelFirst.row * MAX_WID + m_ptSelFirst.col);
	int Index2 = m_graph.GetVertex(m_ptSelSecond.row * MAX_WID + m_ptSelSecond.col);
	if(Index1 != Index2 || Index1 == BLANK || Index2 == BLANK)
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
int CGameControl::IsWin(int nTime)
{
	CGameLogic gameLogic;
	//���ʱ�䵽������Ϸʧ��
	if(nTime <= 0)
	{
		//���ͼ
		m_graph.ClearGraph();
		return GAME_LOSE;
	}
	//ȫ������
	if(gameLogic.IsBlank(m_graph))
	{
		//ʤ������Ϸ����������ͼ
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

//��ʾ����
bool CGameControl::Help(Vertex avPath[MAX_VERTEX_NUM], int& Vexnum)
{
	CGameLogic gameLogic;
	//�ж��Ƿ�Ϊ��
	if(gameLogic.IsBlank(m_graph))
	{
		return false;
	}
	//������ʾ·��
	if(gameLogic.SearchValidPath(m_graph))
	{
		//������ʾ��·������
		Vexnum = gameLogic.GetVertexPath(avPath);
		return true;
	}
	return false;
}

//����
void CGameControl::Reset(void)
{
	CGameLogic gameLogic;
	gameLogic.ResetGraph(m_graph);
}
