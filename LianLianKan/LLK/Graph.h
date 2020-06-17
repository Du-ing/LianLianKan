#pragma once
#include "global.h"
//图数据结构类
class CGraph
{
public:
	CGraph(void);
	~CGraph(void);

	void InitGraph();//初始化图

	typedef int Vertices[MAX_VERTEX_NUM];//顶点
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//边

protected:
	Vertices m_Vertices;//保存顶点
	int m_nVertexnum;//顶点数
	AdjMatrix m_AdjMatrix;//保存边
	int m_nArcnum;//边数

public:
	int AddVertex(int nInfo);//添加顶点
	void AddArc(int nIndex1, int nIndex2);//添加边
	int GetVertex(int nIndex);//根据索引号获取顶点元素
	int GetArc(int nIndex1, int nIndex2);//获取边
	void UpdateVertex(int nIndex, int info);//更新顶点
	int GetVertexNum(void);
	void ClearGraph(void);
};

