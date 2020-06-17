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
	//自定义初始化地图
	//初始化顶点
	int anTemp[4][4] = {2,0,1,3,2,2,1,0,0,1,3,0,3};
	for(int i = 0;i < 4;i++)
	{
		for(int j = 0;j<4;j++)
		{
			graph.AddVertex(anTemp[i][j]);
			//初始化边
			UpdateArc(graph, i, j);
		}
	}
}

bool CGameLogic::IsLink(CGraph &graph, Vertex v1, Vertex v2)
{
	//获取在顶点数组中的索引号
	int Index1 = v1.row * 4 + v1.col;
	int Index2 = v2.row * 4 + v2.col;
	//压入第一个1
	PushVertex(Index1);
	//相连
	if(SearchPath(graph, Index1, Index2))
	{
		return true;
	}
	//取出压入的顶点
	PopVertex();

	return false;
}

//清除顶点
void CGameLogic::Clear(CGraph &graph, Vertex v1, Vertex v2)
{
	//获取顶点索引号
	int Index1 = v1.row * 4 + v1.col;
	int Index2 = v2.row * 4 + v2.col;
	//更新顶点
	graph.UpdateVertex(Index1, -1);
	graph.UpdateVertex(Index2, -1);
	//更新边
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

//更新边
void CGameLogic::UpdateArc(CGraph& graph, int nRow, int nCol)
{
	int nIndex1 = nRow * 4 + nCol;
	if(nCol > 0)//左边相邻
	{
		int nIndex2 = nIndex1 - 1;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == -1 || nInfo2 == -1)
		{
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if(nCol < 3)//右边相邻 
	{
		int nIndex2 = nIndex1 + 1;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == -1 || nInfo2 == -1)
		{
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if(nRow > 0)//上边相邻
	{
		int nIndex2 = nIndex1 - 4;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == -1 || nInfo2 == -1)
		{
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if(nRow < 3)//下边相邻
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
	//得到顶点数
	int nVexnum = graph.GetVertexNum();
	//遍历图中nV0行
	for(int nVi = 0;nVi < nVexnum;nVi++)
	{
		if(graph.GetArc(nV0, nVi) && !IsExist(nVi))
		{
			//压入栈
			PushVertex(nVi);
			//拐点数大于2
			if(m_nCorner > 2)
			{
				PopVertex();//跳出此路径
				continue;
			}

			if(nVi != nV1)
			{
				//当中间顶点不为空时，表示该条路径不通
				if(graph.GetVertex(nVi) != -1)
				{
					PopVertex();
					continue;
				}
				if(SearchPath(graph, nVi, nV1))
				{
					//已经找到了一条连通路径
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

//判断元素是否加入到栈中
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

//顶点压入栈
void CGameLogic::PushVertex(int nV)
{
	m_anPath[m_nVexNum] = nV;
	m_nVexNum++;
	if(IsCorner())
	{
		m_nCorner++;
	}
}

//抛出栈顶元素
void CGameLogic::PopVertex(void)
{
	if(IsCorner())
	{
		m_nCorner--;
	}
	m_nVexNum--;
}

//判断是否形成拐点
bool CGameLogic::IsCorner(void)
{
	//大于三个顶点时才能形成拐点
	if(m_nVexNum >= 3)
	{
		if((m_anPath[m_nVexNum-1] + m_anPath[m_nVexNum-3])/2 != m_anPath[m_nVexNum-2])
		{
			return true;
		}
	}
	return false;
}

//判断顶点是否全部消除
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
