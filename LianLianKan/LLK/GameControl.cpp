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
	CGameLogic gameLogic;//创建一个CGameLogic对象
	gameLogic.InitMap(m_graph);//初始化地图
}

//获取对应行号列号元素的值
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

//判断两次选择的点是否连通
bool CGameControl::Link(Vertex Path[16], int &nVertexNum)
{
	//判断两个是否在同一位置
	if(m_ptSelFirst.row == m_ptSelSecond.row && m_ptSelFirst.col == m_ptSelSecond.col)
	{
		return false;
	}
	//判断两个图片元素是否相同
	int Index1 = m_graph.GetVertex(m_ptSelFirst.row * 4 + m_ptSelFirst.col);
	int Index2 = m_graph.GetVertex(m_ptSelSecond.row * 4 + m_ptSelSecond.col);
	if(Index1 != Index2 || Index1 == -1 || Index2 == -1)
	{
		return false;
	}
	//判断是否连通
	CGameLogic gameLogic;
	if(gameLogic.IsLink(m_graph, m_ptSelFirst, m_ptSelSecond))
	{
		//消子
		gameLogic.Clear(m_graph, m_ptSelFirst, m_ptSelSecond);
		//获取消除的路径并返回路径顶点数
		nVertexNum = gameLogic.GetVertexPath(Path);
		return true;
	}
	return false;
}

//判断胜负
bool CGameControl::IsWin(void)
{
	CGameLogic gameLogic;
	if(gameLogic.IsBlank(m_graph))
	{
		//胜利后游戏结束，清理图
		m_graph.ClearGraph();
		return true;
	}
	return false;
}
