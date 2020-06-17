#include "StdAfx.h"
#include "Graph.h"


CGraph::CGraph(void)
{
	//ÿ������ζ�Ҫ��ʼ��ͼ
	InitGraph();
}


CGraph::~CGraph(void)
{
}

void CGraph::InitGraph()
{
	//��ʼ��Ϊ0
	m_nVertexnum = 0;
	m_nArcnum = 0;
	//��ʼ������
	for(int i = 0;i < MAX_VERTEX;i++)
	{
		m_Vertices[i] = -1;//��ʼ��Ϊ��
	}

	//��ʼ����
	for(int i = 0;i < MAX_VERTEX;i++)
	{
		for(int j = 0;j < MAX_VERTEX;j++)
		{
			m_AdjMatrix[i][j] = 0;//��ʼ��û�б�
		}
	}
}

//��Ӷ���
int CGraph::AddVertex(int nInfo)
{
	if(m_nVertexnum >= MAX_VERTEX)
		return m_nVertexnum;
	m_Vertices[m_nVertexnum] = nInfo;
	m_nVertexnum++;
	return m_nVertexnum;
}

//��ӱ�
void CGraph::AddArc(int nIndex1, int nIndex2)
{
	m_AdjMatrix[nIndex1][nIndex2] = 1;
	m_AdjMatrix[nIndex2][nIndex1] = 1;
}

//��ȡ����
int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

//��ȡ��
int CGraph::GetArc(int nIndex1, int nIndex2)
{
	return m_AdjMatrix[nIndex1][nIndex2];
}

//���¶���ֵ
void CGraph::UpdateVertex(int nIndex, int info)
{
	m_Vertices[nIndex] = info;
}

//��ȡ������
int CGraph::GetVertexNum(void)
{
	return m_nVertexnum;
}

//���ͼ
void CGraph::ClearGraph(void)
{
	InitGraph();
}
