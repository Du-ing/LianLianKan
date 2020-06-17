#pragma once
//ͼ���ݽṹ��
class CGraph
{
public:
	CGraph(void);
	~CGraph(void);

	void InitGraph();//��ʼ��ͼ

	#define MAX_VERTEX 16//�������
	typedef int Vertices[MAX_VERTEX];//����
	typedef bool AdjMatrix[MAX_VERTEX][MAX_VERTEX];//��

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

