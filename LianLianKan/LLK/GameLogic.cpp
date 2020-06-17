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

//��ʼ����ͼ
void CGameLogic::InitMap(CGraph &graph)
{
	
	int anTemp[MAX_VERTEX_NUM];//�洢����ĵ�ͼ

	//��ɫ
	for(int i = 0;i < MAX_PIC_NUM;i++)
	{
		//�ظ�����
		for(int j = 0;j < REPEAT_NUM;j++)
		{
			anTemp[i * REPEAT_NUM + j] = i;
		}
	}

	//�����
	srand((int)time(NULL));

	//���������������
	for(int i = 0;i < MAX_VERTEX_NUM;i++)
	{
		//����õ���������
		int Index1 = rand() % MAX_VERTEX_NUM;
		int Index2 = rand() % MAX_VERTEX_NUM;
		//����Ԫ��
		int t = anTemp[Index1];
		anTemp[Index1] = anTemp[Index2];
		anTemp[Index2] = t;
	}

	//���浽��ͼ����
	//��ʼ������
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		graph.AddVertex(anTemp[i]);
	}
	for(int i = 0;i < MAX_PIC_NUM;i++)
	{
		for(int j = 0;j < REPEAT_NUM;j++)
		{
			//���±�
			UpdateArc(graph, i, j);
		}
	}
}

//�ж���ͨ
bool CGameLogic::IsLink(CGraph &graph, Vertex v1, Vertex v2)
{
	//��ȡ�ڶ��������е�������
	int Index1 = v1.row * MAX_WID + v1.col;
	int Index2 = v2.row * MAX_WID + v2.col;
	//ѹ���һ��1
	PushVertex(Index1);
	//����
	if(SearchPath(graph, Index1, Index2))
	{
		return true;
	}
	//ȡ��ѹ��Ķ���
	PopVertex();

	if (v1.row == v2.row) {
		if (v1.row == 0 || v1.row == MAX_WID - 1) {
			return true;
		}
	}

	if (v1.col == v2.col) {
		if (v1.col == 0 || v1.col == MAX_WID - 1) {
			return true;
		}
	}

	return false;
}

//�������
void CGameLogic::Clear(CGraph &graph, Vertex v1, Vertex v2)
{
	//��ȡ����������
	int Index1 = v1.row * MAX_WID + v1.col;
	int Index2 = v2.row * MAX_WID + v2.col;
	//���¶���
	graph.UpdateVertex(Index1, BLANK);
	graph.UpdateVertex(Index2, BLANK);
	//���±�
	UpdateArc(graph, v1.row, v1.col);
	UpdateArc(graph, v2.row, v2.col);
}

int CGameLogic::GetVertexPath(Vertex avPath[MAX_VERTEX_NUM])
{
	Vertex point;
	for (int i = 0; i < m_nVexNum; i++)
		for (point.col = 0; point.col < MAX_WID; point.col++)
		{
			for (point.row = 0; point.row < MAX_WID; point.row++)
			{
				if (point.row * MAX_WID + point.col == m_anPath[i])
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
	int nIndex1 = nRow * MAX_WID + nCol;
	if(nCol > 0)//�������
	{
		int nIndex2 = nIndex1 - 1;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
		{
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if(nCol < MAX_WID-1)//�ұ����� 
	{
		int nIndex2 = nIndex1 + 1;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
		{
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if(nRow > 0)//�ϱ�����
	{
		int nIndex2 = nIndex1 - MAX_WID;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
		{
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if(nRow < MAX_WID-1)//�±�����
	{
		int nIndex2 = nIndex1 + MAX_WID;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
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
				if(graph.GetVertex(nVi) != BLANK)
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
		if(graph.GetVertex(i) != BLANK)
		{
			return false;
		}
	}
	return true;
}

//��ʾ����
bool CGameLogic::SearchValidPath(CGraph &graph)
{
	int Vexnum = graph.GetVertexNum();//������
	for(int i = 0;i < Vexnum;i++)
	{
		//��һ���ǿն���
		if(graph.GetVertex(i) == BLANK)
		{
			continue;
		}
		for(int j = 0;j < Vexnum;j++)
		{
			if(i != j)//�����㲻�غ�
			{
				if(graph.GetVertex(i) == graph.GetVertex(j))//�������ͬɫ
				{
					//��һ�������ջ
					PushVertex(i);
					//���������ͨ
					if(SearchPath(graph, i, j))
					{
						return true;
					}
					//��ջ
					PopVertex();
				}
			}
		}
	}
	return false;
}

//�����������,ʵ������
void CGameLogic::ResetGraph(CGraph& graph)
{
	//���������������
	for(int i = 0;i < MAX_VERTEX_NUM;i++)
	{
		//����õ���������
		int Index1 = rand() % MAX_VERTEX_NUM;
		int Index2 = rand() % MAX_VERTEX_NUM;
		//����Ԫ��
		int Info1 = graph.GetVertex(Index1);
		int Info2 = graph.GetVertex(Index2);
		graph.UpdateVertex(Index1, Info2);
		graph.UpdateVertex(Index2, Info1);
	}
	//���±���Ϣ
	for(int i = 0;i < MAX_WID;i++)
	{
		for(int j = 0;j < MAX_WID;j++)
		{
			UpdateArc(graph, i, j);
		}
	}
}
