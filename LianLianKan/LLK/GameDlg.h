#pragma once
#include "GameControl.h"


// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();

// �Ի�������
	enum { IDD = IDD_GAME_DIALOG };

protected:
	CDC m_dcMem;//�ڴ�DC
	CDC m_dcBG;
	CDC m_dcElement;//Ԫ��DC
	CDC m_dcMask;//Ԫ�ر���DC
	CDC m_dcPause;//��ͣͼƬ
	CRect m_rtGameRect;//��Ϸ��������
	int m_anMap[4][4];//��Ϸ��ͼ
	CPoint m_ptGameTop;//��ʼ����
	CSize m_sizeElem;//Ԫ��ͼƬ�Ĵ�С
	bool m_bFirstPoint;//��һ��ѡ�б�ʶ
	Vertex m_ptSelFirst;//��һ��ѡ���
	Vertex m_ptSelSecond;//�ڶ���ѡ���

	CGameControl m_gameControl;//��Ϸ����
	bool m_bPlaying;//��Ϸ�Ƿ����
	bool m_bPause;//��Ϸ�Ƿ���ͣ

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
	//��ʼ���������С
	void InitBackground(void);
	//���ô���
	void UpdateWindow();
	//��ʼ��Ԫ��
	void InitElement();
	//������Ϸ��ͼ
	void UpdateMap();
	//��Ԫ�ػ���
	void DrawTipFrame(int nRow, int nCol);
	//Ԫ������
	void DrawTipLine(Vertex Path[MAX_VERTEX_NUM], int vertexNum);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedButtonStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonTishi();
	afx_msg void OnClickedButtonReset();
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void JudgeWin(void);
	afx_msg void OnClickedButtonPause();
};
