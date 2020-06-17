#pragma once
#include "global.h"
//ͼ���ݽṹ��
class CGraph
{
public:
	CGraph(void);
	~CGraph(void);

	void InitGraph();//��ʼ��ͼ

	typedef int Vertices[MAX_VERTEX_NUM];//����
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//��

protected:
	Vertices m_Vertices;//���涥��
	int m_nVertexnum;//������
	AdjMatrix m_AdjMatrix;//�����
	int m_nArcnum;//����

public:
	int AddVertex(int nInfo);//��Ӷ���
	void AddArc(int nIndex1, int nIndex2);//��ӱ�
	int GetVertex(int nIndex);//���������Ż�ȡ����Ԫ��
	int GetArc(int nIndex1, int nIndex2);//��ȡ��
	void UpdateVertex(int nIndex, int info);//���¶���
	int GetVertexNum(void);
	void ClearGraph(void);
};

