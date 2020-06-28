#pragma once
#include "GameControl.h"


// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
	enum { IDD = IDD_GAME_DIALOG };

protected:
	CDC m_dcMem;//内存DC
	CDC m_dcBG;
	CDC m_dcElement;//元素DC
	CDC m_dcMask;//元素背景DC
	CDC m_dcPause;//暂停图片
	CRect m_rtGameRect;//游戏更新区域
	int m_anMap[4][4];//游戏地图
	CPoint m_ptGameTop;//起始坐标
	CSize m_sizeElem;//元素图片的大小
	bool m_bFirstPoint;//第一次选中标识
	Vertex m_ptSelFirst;//第一次选择点
	Vertex m_ptSelSecond;//第二次选择点

	CGameControl m_gameControl;//游戏控制
	bool m_bPlaying;//游戏是否结束
	bool m_bPause;//游戏是否暂停

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
	//初始化窗口与大小
	void InitBackground(void);
	//设置窗口
	void UpdateWindow();
	//初始化元素
	void InitElement();
	//绘制游戏地图
	void UpdateMap();
	//给元素画框
	void DrawTipFrame(int nRow, int nCol);
	//元素连线
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
	afx_msg void OnBnClickedButtonHelping();
};
