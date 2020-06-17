#pragma once
#include "global.h"
#include "Graph.h"

class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);

	void InitMap(CGraph &graph);//��ʼ����ͼ
	bool IsLink(CGraph &graph, Vertex v1, Vertex v2);//�����ж�
	void Clear(CGraph &graph, Vertex v1, Vertex v2);//Ԫ���������ÿ�
	int GetVertexPath(Vertex avPath[MAX_VERTEX_NUM]);//��ȡ������·��

protected:
	int m_anPath[MAX_VERTEX_NUM];//����·���Ķ�������
	int m_nVexNum;//·���ж������
	int m_nCorner;//����յ���

public:
	void UpdateArc(CGraph& graph, int nRow, int Col);//���±�
	bool SearchPath(CGraph& graph, int nV0, int nV1);
	bool IsExist(int nVi);
	void PushVertex(int nV);
	void PopVertex(void);
	bool IsCorner(void);
	bool IsBlank(CGraph &graph);
	bool SearchValidPath(CGraph &graph);
	void ResetGraph(CGraph& graph);
};

