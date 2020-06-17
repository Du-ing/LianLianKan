// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg::IDD, pParent)
{
	//游戏区距离边框的距离
	m_ptGameTop.x = MAP_LEFT;
    m_ptGameTop.y = MAP_TOP;
	//元素图片大小
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;
	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_WID;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_WID;
	//初始点的标识
	m_bFirstPoint = true;
	m_bPlaying = false;//游戏未开始
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CGameDlg::OnClickedButtonStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_TISHI, &CGameDlg::OnClickedButtonTishi)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CGameDlg::OnClickedButtonReset)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::InitBackground(void)
{
	//获得当前对话框的视频内存
	CClientDC dc(this);
	//加载BMP图片资源
	HANDLE bmp = ::LoadImage(NULL, _T("pic\\gameBG1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建于视频内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcBG.SelectObject(bmp);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);
	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	UpdateWindow();
}

void CGameDlg::UpdateWindow()
{
	//调整窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);//获得窗口大小
	this->GetClientRect(rtClient);//获得客户区大小
	//标题栏和外边框的大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	//设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	//设置对话框显示在正中央
	CenterWindow();
}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitBackground();
	InitElement();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

//初始化元素
void CGameDlg::InitElement()
{
	//获得当前对话框的视频内存
	CClientDC dc(this);
	//加载BMP图片资源
	HANDLE hBmpBG = ::LoadImage(NULL, _T("pic\\element1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建于视频内存兼容的内存DC
	m_dcElement.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcElement.SelectObject(hBmpBG);

	//加载BMP图片资源
	HANDLE hBmpMask = ::LoadImage(NULL, _T("pic\\element1_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建于视频内存兼容的内存DC
	m_dcMask.CreateCompatibleDC(&dc);
	//将位图资源选入DC
	m_dcMask.SelectObject(hBmpMask);
}

//点击开始游戏按钮的响应
void CGameDlg::OnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	//初始化游戏地图
	m_gameControl.StartGame();	
	//游戏开始
	m_bPlaying = true;
	//禁止开始游戏按钮
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	//更新地图
	UpdateMap();
	//覆盖
	InvalidateRect(m_rtGameRect, FALSE);
}

//更新地图
void CGameDlg::UpdateMap()
{
	//加载元素
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), 
		m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	//依次加载图片元素
	for(int i = 0;i < MAX_WID;i++)
	{
		for(int j = 0;j < MAX_WID;j++)
		{
			int nInfo = m_gameControl.GetElement(i, j);
			if(nInfo == BLANK)//元素为空则跳过
			{
				continue;
			}
			//将背景与掩码相或
			m_dcMem.BitBlt(nLeft+j*nElemW, nTop+i*nElemH, nElemW, nElemH, &m_dcMask, 0, nInfo*nElemH, SRCPAINT);
			//再将元素相与
			m_dcMem.BitBlt(nLeft+j*nElemW, nTop+i*nElemH, nElemW, nElemH, &m_dcElement, 0, nInfo*nElemH, SRCAND);
		}
	}
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(point.x < m_ptGameTop.x || point.y < m_ptGameTop.y)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	int nRow = (point.y - m_ptGameTop.y)/m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x)/m_sizeElem.cx;

	if(nRow > MAX_WID-1 || nCol > MAX_WID-1)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	if(m_bFirstPoint)
	{
		//绘制提示框
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else
	{
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecondPoint(nRow, nCol);

		//路径
		Vertex Path[MAX_VERTEX_NUM];
		int vexNum = 0;//顶点数
		//判断是否可消除
		if(m_gameControl.Link(Path, vexNum))
		{
			DrawTipLine(Path, vexNum);//绘制连接线
			UpdateMap();//更新地图
		}
		Sleep(200);//延迟0.2S，让点击效果显示出来
		InvalidateRect(m_rtGameRect, FALSE);

		//判断胜负
		if(m_gameControl.IsWin())
		{
			MessageBox(_T("\t你赢啦！"));
			m_bPlaying = false;//游戏结束
			this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(true); //开始游戏按钮恢复
			return;
		}
	}
	m_bFirstPoint = !m_bFirstPoint;
}

void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}

//绘制连线
void CGameDlg::DrawTipLine(Vertex Path[MAX_VERTEX_NUM], int vertexNum)
{
	//获取DC
	CClientDC dc(this);
	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);
	
	//按路径连线
	dc.MoveTo(m_ptGameTop.x + Path[0].col * m_sizeElem.cx + m_sizeElem.cx / 2, 
			m_ptGameTop.y + Path[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	for(int i = 0;i < vertexNum - 1;i++)
	{
		//绘制连接线
		dc.LineTo(m_ptGameTop.x + Path[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2, 
			m_ptGameTop.y + Path[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}

//点击提示按钮
void CGameDlg::OnClickedButtonTishi()
{
	// TODO: 在此添加控件通知处理程序代码
	Vertex avPath[MAX_VERTEX_NUM];//存储提示路径点
	int Vexnum;//个数
	//提示路径
	if(m_gameControl.Help(avPath, Vexnum))
	{
		//给点击的两个顶点绘制矩形框
		DrawTipFrame(avPath[0].row, avPath[0].col);
		DrawTipFrame(avPath[Vexnum - 1].row, avPath[Vexnum - 1].col);
		Sleep(200);//延迟0.2S
		InvalidateRect(m_rtGameRect, FALSE);
	}
}

//点击重排按钮
void CGameDlg::OnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	//重排
	m_gameControl.Reset();
	//更新界面
	UpdateMap();
	//界面重绘
	InvalidateRect(m_rtGameRect, FALSE); 
}
