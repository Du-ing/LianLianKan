#pragma once

//����ṹ��
typedef struct tagVertex
{
	int row;//��
	int col;//��
	int info;//��Ϣ
}Vertex;

#define BLANK -1//Ԫ��Ϊ��
#define MAX_WID 12//��ͼÿ��ÿ�п�����Ԫ����
#define MAX_VERTEX_NUM 144//�������
#define MAX_PIC_NUM 12//ͼƬ��ɫ
#define REPEAT_NUM 12//ÿ�ֻ�ɫͼƬ�ظ�����
#define PIC_WIDTH 40//��ϷͼƬ���
#define PIC_HEIGHT 40//��ϷͼƬ�߶�
#define MAP_TOP 50//��ͼ���Ͻ�������
#define MAP_LEFT 80//��ͼ���ϽǺ�����
