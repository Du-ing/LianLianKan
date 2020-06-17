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

//初始化地图
void CGameLogic::InitMap(CGraph &graph)
{
	
	int anTemp[MAX_VERTEX_NUM];//存储随机的地图

	//花色
	for(int i = 0;i < MAX_PIC_NUM;i++)
	{
		//重复次数
		for(int j = 0;j < REPEAT_NUM;j++)
		{
			anTemp[i * REPEAT_NUM + j] = i;
		}
	}

	//随机数
	srand((int)time(NULL));

	//随机交换两个数字
	for(int i = 0;i < MAX_VERTEX_NUM;i++)
	{
		//随机得到两个坐标
		int Index1 = rand() % MAX_VERTEX_NUM;
		int Index2 = rand() % MAX_VERTEX_NUM;
		//交换元素
		int t = anTemp[Index1];
		anTemp[Index1] = anTemp[Index2];
		anTemp[Index2] = t;
	}

	//保存到地图数组
	//初始化顶点
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		graph.AddVertex(anTemp[i]);
	}
	for(int i = 0;i < MAX_PIC_NUM;i++)
	{
		for(int j = 0;j < REPEAT_NUM;j++)
		{
			//更新边
			UpdateArc(graph, i, j);
		}
	}
}

//判断连通
bool CGameLogic::IsLink(CGraph &graph, Vertex v1, Vertex v2)
{
	//获取在顶点数组中的索引号
	int Index1 = v1.row * MAX_WID + v1.col;
	int Index2 = v2.row * MAX_WID + v2.col;
	//压入第一个1
	PushVertex(Index1);
	//相连
	if(SearchPath(graph, Index1, Index2))
	{
		return true;
	}
	//取出压入的顶点
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

//清除顶点
void CGameLogic::Clear(CGraph &graph, Vertex v1, Vertex v2)
{
	//获取顶点索引号
	int Index1 = v1.row * MAX_WID + v1.col;
	int Index2 = v2.row * MAX_WID + v2.col;
	//更新顶点
	graph.UpdateVertex(Index1, BLANK);
	graph.UpdateVertex(Index2, BLANK);
	//更新边
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

//更新边
void CGameLogic::UpdateArc(CGraph& graph, int nRow, int nCol)
{
	int nIndex1 = nRow * MAX_WID + nCol;
	if(nCol > 0)//左边相邻
	{
		int nIndex2 = nIndex1 - 1;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
		{
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if(nCol < MAX_WID-1)//右边相邻 
	{
		int nIndex2 = nIndex1 + 1;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
		{
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if(nRow > 0)//上边相邻
	{
		int nIndex2 = nIndex1 - MAX_WID;
		int nInfo1 = graph.GetVertex(nIndex1);
		int nInfo2 = graph.GetVertex(nIndex2);
		if(nInfo1 == nInfo2 || nInfo1 == BLANK || nInfo2 == BLANK)
		{
			graph.AddArc(nIndex1, nIndex2);
		}
	}
	if(nRow < MAX_WID-1)//下边相邻
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
				if(graph.GetVertex(nVi) != BLANK)
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
		if(graph.GetVertex(i) != BLANK)
		{
			return false;
		}
	}
	return true;
}

//提示功能
bool CGameLogic::SearchValidPath(CGraph &graph)
{
	int Vexnum = graph.GetVertexNum();//顶点数
	for(int i = 0;i < Vexnum;i++)
	{
		//第一个非空顶点
		if(graph.GetVertex(i) == BLANK)
		{
			continue;
		}
		for(int j = 0;j < Vexnum;j++)
		{
			if(i != j)//两个点不重合
			{
				if(graph.GetVertex(i) == graph.GetVertex(j))//如果两个同色
				{
					//第一个顶点进栈
					PushVertex(i);
					//如果两点连通
					if(SearchPath(graph, i, j))
					{
						return true;
					}
					//出栈
					PopVertex();
				}
			}
		}
	}
	return false;
}

//随机交换顶点,实现重排
void CGameLogic::ResetGraph(CGraph& graph)
{
	//随机交换两个顶点
	for(int i = 0;i < MAX_VERTEX_NUM;i++)
	{
		//随机得到两个坐标
		int Index1 = rand() % MAX_VERTEX_NUM;
		int Index2 = rand() % MAX_VERTEX_NUM;
		//交换元素
		int Info1 = graph.GetVertex(Index1);
		int Info2 = graph.GetVertex(Index2);
		graph.UpdateVertex(Index1, Info2);
		graph.UpdateVertex(Index2, Info1);
	}
	//更新边信息
	for(int i = 0;i < MAX_WID;i++)
	{
		for(int j = 0;j < MAX_WID;j++)
		{
			UpdateArc(graph, i, j);
		}
	}
}
