#include "StdAfx.h"
#include "GameLogic.h"
#include "global.h"


CGameLogic::CGameLogic(void)
{
	m_nVexNum = 0;
	m_nCorner = 0;
}


CGameLogic::~CGameLogic(void)
{
}

void CGameLogic::InitMap(CGraph &graph)
{
	//�Զ����ʼ����ͼ
	//��ʼ������
	int anTemp[4][4] = {2,0,1,3,2,2,1,0,0,1,3,0,3};
	for(int i = 0;i < 4;i++)
	{
		for(int j = 0;j<4;j++)
		{
			graph.AddVertex(anTemp[i][j]);
			//��ʼ����
			UpdateArc(graph, i, j);
		}
	}
}

bool CGameLogic::IsLink(CGraph &graph, Vertex v1, Vertex v2)
{
	//��ȡ�ڶ��������е�������
	int Index1 = v1.row * 4 + v1.col;
	int Index2 = v2.row * 4 + v2.col;
	//ѹ���һ��1
	PushVertex(Index1);
	//����
	if(SearchPath(graph, Index1, Index2))
	{
		return true;
	}
	//ȡ��ѹ��Ķ���
	PopVertex();

	return false;
}

//�������
void CGameLogic::Clear(CGraph &graph, Vertex v1, Vertex v2)
{
	//��ȡ����������
	int Index1 = v1.row * 4 + v1.col;
	int Index2 = v2.row * 4 + v2.col;
	//���¶���
	graph.UpdateVertex(Index1, -1);
	graph.UpdateVertex(Index2, -1);
	//���±�
	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);
}

int CGameLogic::GetVertexPath(Vertex avPath[16])
{
	Vertex point;
	for (int i = 0; i < m_nVexNum; i++)
		for (point.col = 0; point.col < 4; point.col++)
		{
			for (point.row = 0; point.row < 4; point.row++)
			{
				if (point.row * 4 + point.col == m_anPath[i])
				{
					avPath[i] = point;
				}
			}
		}
	return m_nVexNum;
}

//���±�
void CGameLogic::UpdateArc(CGraph& graph, int nRow, int nCol)
{
	int nIndex1 = nRow * 4 + nCol;
	if(nCol > 0)//�������
	{
		int nIndex2 = nIndex1 - 1;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == -1 || nInfo2 == -1)
		{
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if(nCol < 3)//�ұ����� 
	{
		int nIndex2 = nIndex1 + 1;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == -1 || nInfo2 == -1)
		{
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if(nRow > 0)//�ϱ�����
	{
		int nIndex2 = nIndex1 - 4;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == -1 || nInfo2 == -1)
		{
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if(nRow < 3)//�±�����
	{
		int nIndex2 = nIndex1 + 4;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == -1 || nInfo2 == -1)
		{
			graph.AddArc(nIndex1, nIndex2);
		}
	}
}


bool CGameLogic::SearchPath(CGraph& graph, int nV0, int nV1)
{
	//�õ�������
	int nVexnum = graph.GetVertexNum();
	//����ͼ��nV0��
	for(int nVi = 0;nVi < nVexnum;nVi++)
	{
		if(graph.GetArc(nV0, nVi) && !IsExist(nVi))
		{
			//ѹ��ջ
			PushVertex(nVi);
			//�յ�������2
			if(m_nCorner > 2)
			{
				PopVertex();//������·��
				continue;
			}

			if(nVi != nV1)
			{
				//���м䶥�㲻Ϊ��ʱ����ʾ����·����ͨ
				if(graph.GetVertex(nVi) != -1)
				{
					PopVertex();
					continue;
				}
				if(SearchPath(graph, nVi, nV1))
				{
					//�Ѿ��ҵ���һ����ͨ·��
					return true;
				}
			}
			else
			{
				return true;
			}
			PopVertex();
		}
	}
	return false;
}

//�ж�Ԫ���Ƿ���뵽ջ��
bool CGameLogic::IsExist(int nVi)
{
	for(int i = 0;i < m_nVexNum;i++)
	{
		if(nVi == m_anPath[i])
		{
			return true;
		}
	}
	return false;
}

//����ѹ��ջ
void CGameLogic::PushVertex(int nV)
{
	m_anPath[m_nVexNum] = nV;
	m_nVexNum++;
	if(IsCorner())
	{
		m_nCorner++;
	}
}

//�׳�ջ��Ԫ��
void CGameLogic::PopVertex(void)
{
	if(IsCorner())
	{
		m_nCorner--;
	}
	m_nVexNum--;
}

//�ж��Ƿ��γɹյ�
bool CGameLogic::IsCorner(void)
{
	//������������ʱ�����γɹյ�
	if(m_nVexNum >= 3)
	{
		if((m_anPath[m_nVexNum-1] + m_anPath[m_nVexNum-3])/2 != m_anPath[m_nVexNum-2])
		{
			return true;
		}
	}
	return false;
}

//�ж϶����Ƿ�ȫ������
bool CGameLogic::IsBlank(CGraph &graph)
{
	for(int i = 0;i < graph.GetVertexNum();i++)
	{
		if(graph.GetVertex(i) != -1)
		{
			return false;
		}
	}
	return true;
}
