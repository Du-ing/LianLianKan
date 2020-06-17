#include "StdAfx.h"
#include "Graph.h"

CGraph::CGraph(void)
{
	//每点击两次都要初始化图
	InitGraph();
}


CGraph::~CGraph(void)
{
}

void CGraph::InitGraph()
{
	//初始化为0
	m_nVertexnum = 0;
	m_nArcnum = 0;
	//初始化顶点
	for(int i = 0;i < MAX_VERTEX_NUM;i++)
	{
		m_Vertices[i] = BLANK;//初始化为空
	}

	//初始化边
	for(int i = 0;i < MAX_VERTEX_NUM;i++)
	{
		for(int j = 0;j < MAX_VERTEX_NUM;j++)
		{
			m_AdjMatrix[i][j] = 0;//初始化没有边
		}
	}
}

//添加顶点
int CGraph::AddVertex(int nInfo)
{
	if(m_nVertexnum >= MAX_VERTEX_NUM)
		return m_nVertexnum;
	m_Vertices[m_nVertexnum] = nInfo;
	m_nVertexnum++;
	return m_nVertexnum;
}

//添加边
void CGraph::AddArc(int nIndex1, int nIndex2)
{
	m_AdjMatrix[nIndex1][nIndex2] = 1;
	m_AdjMatrix[nIndex2][nIndex1] = 1;
}

//获取顶点
int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

//获取边
int CGraph::GetArc(int nIndex1, int nIndex2)
{
	return m_AdjMatrix[nIndex1][nIndex2];
}

//更新顶点值
void CGraph::UpdateVertex(int nIndex, int info)
{
	m_Vertices[nIndex] = info;
}

//获取顶点数
int CGraph::GetVertexNum(void)
{
	return m_nVertexnum;
}

//清空图
void CGraph::ClearGraph(void)
{
	InitGraph();
}
