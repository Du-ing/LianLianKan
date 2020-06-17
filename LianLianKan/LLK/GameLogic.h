#pragma once
#include "global.h"
#include "Graph.h"

class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);

	void InitMap(CGraph &graph);//初始化地图
	bool IsLink(CGraph &graph, Vertex v1, Vertex v2);//连接判断
	void Clear(CGraph &graph, Vertex v1, Vertex v2);//元素消除后置空
	int GetVertexPath(Vertex avPath[16]);//获取消除的路径

protected:
	int m_anPath[16];//保存路径的顶点索引
	int m_nVexNum;//路径中顶点个数
	int m_nCorner;//保存拐点数

public:
	void UpdateArc(CGraph& graph, int nRow, int Col);//更新边
	bool SearchPath(CGraph& graph, int nV0, int nV1);
	bool IsExist(int nVi);
	void PushVertex(int nV);
	void PopVertex(void);
	bool IsCorner(void);
	bool IsBlank(CGraph &graph);
};

