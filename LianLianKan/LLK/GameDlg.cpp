// GameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"


// CGameDlg �Ի���

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg::IDD, pParent)
{
	//��Ϸ������߿�ľ���
	m_ptGameTop.x = MAP_LEFT;
    m_ptGameTop.y = MAP_TOP;
	//Ԫ��ͼƬ��С
	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;
	//��ʼ����Ϸ��������
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_WID;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_WID;
	//��ʼ��ı�ʶ
	m_bFirstPoint = true;
	m_bPlaying = false;//��Ϸδ��ʼ
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


// CGameDlg ��Ϣ�������


void CGameDlg::InitBackground(void)
{
	//��õ�ǰ�Ի������Ƶ�ڴ�
	CClientDC dc(this);
	//����BMPͼƬ��Դ
	HANDLE bmp = ::LoadImage(NULL, _T("pic\\gameBG1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcBG.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ��DC
	m_dcBG.SelectObject(bmp);

	//��ʼ���ڴ�DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);
	//���Ʊ������ڴ�DC��
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	UpdateWindow();
}

void CGameDlg::UpdateWindow()
{
	//�������ڴ�С
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);//��ô��ڴ�С
	this->GetClientRect(rtClient);//��ÿͻ�����С
	//����������߿�Ĵ�С
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeight = rtWin.Height() - rtClient.Height();
	//���ô��ڴ�С
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);
	//���öԻ�����ʾ��������
	CenterWindow();
}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitBackground();
	InitElement();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);
}

//��ʼ��Ԫ��
void CGameDlg::InitElement()
{
	//��õ�ǰ�Ի������Ƶ�ڴ�
	CClientDC dc(this);
	//����BMPͼƬ��Դ
	HANDLE hBmpBG = ::LoadImage(NULL, _T("pic\\element1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcElement.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ��DC
	m_dcElement.SelectObject(hBmpBG);

	//����BMPͼƬ��Դ
	HANDLE hBmpMask = ::LoadImage(NULL, _T("pic\\element1_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcMask.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ��DC
	m_dcMask.SelectObject(hBmpMask);
}

//�����ʼ��Ϸ��ť����Ӧ
void CGameDlg::OnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ����Ϸ��ͼ
	m_gameControl.StartGame();	
	//��Ϸ��ʼ
	m_bPlaying = true;
	//��ֹ��ʼ��Ϸ��ť
	this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	//���µ�ͼ
	UpdateMap();
	//����
	InvalidateRect(m_rtGameRect, FALSE);
}

//���µ�ͼ
void CGameDlg::UpdateMap()
{
	//����Ԫ��
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top, m_rtGameRect.Width(), 
		m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	//���μ���ͼƬԪ��
	for(int i = 0;i < MAX_WID;i++)
	{
		for(int j = 0;j < MAX_WID;j++)
		{
			int nInfo = m_gameControl.GetElement(i, j);
			if(nInfo == BLANK)//Ԫ��Ϊ��������
			{
				continue;
			}
			//���������������
			m_dcMem.BitBlt(nLeft+j*nElemW, nTop+i*nElemH, nElemW, nElemH, &m_dcMask, 0, nInfo*nElemH, SRCPAINT);
			//�ٽ�Ԫ������
			m_dcMem.BitBlt(nLeft+j*nElemW, nTop+i*nElemH, nElemW, nElemH, &m_dcElement, 0, nInfo*nElemH, SRCAND);
		}
	}
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		//������ʾ��
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else
	{
		DrawTipFrame(nRow, nCol);
		m_gameControl.SetSecondPoint(nRow, nCol);

		//·��
		Vertex Path[MAX_VERTEX_NUM];
		int vexNum = 0;//������
		//�ж��Ƿ������
		if(m_gameControl.Link(Path, vexNum))
		{
			DrawTipLine(Path, vexNum);//����������
			UpdateMap();//���µ�ͼ
		}
		Sleep(200);//�ӳ�0.2S���õ��Ч����ʾ����
		InvalidateRect(m_rtGameRect, FALSE);

		//�ж�ʤ��
		if(m_gameControl.IsWin())
		{
			MessageBox(_T("\t��Ӯ����"));
			m_bPlaying = false;//��Ϸ����
			this->GetDlgItem(IDC_BUTTON_START)->EnableWindow(true); //��ʼ��Ϸ��ť�ָ�
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

//��������
void CGameDlg::DrawTipLine(Vertex Path[MAX_VERTEX_NUM], int vertexNum)
{
	//��ȡDC
	CClientDC dc(this);
	//���û���
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	//������ѡ��DC
	CPen* pOldPen = dc.SelectObject(&penLine);
	
	//��·������
	dc.MoveTo(m_ptGameTop.x + Path[0].col * m_sizeElem.cx + m_sizeElem.cx / 2, 
			m_ptGameTop.y + Path[0].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	for(int i = 0;i < vertexNum - 1;i++)
	{
		//����������
		dc.LineTo(m_ptGameTop.x + Path[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2, 
			m_ptGameTop.y + Path[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldPen);
}

//�����ʾ��ť
void CGameDlg::OnClickedButtonTishi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Vertex avPath[MAX_VERTEX_NUM];//�洢��ʾ·����
	int Vexnum;//����
	//��ʾ·��
	if(m_gameControl.Help(avPath, Vexnum))
	{
		//�����������������ƾ��ο�
		DrawTipFrame(avPath[0].row, avPath[0].col);
		DrawTipFrame(avPath[Vexnum - 1].row, avPath[Vexnum - 1].col);
		Sleep(200);//�ӳ�0.2S
		InvalidateRect(m_rtGameRect, FALSE);
	}
}

//������Ű�ť
void CGameDlg::OnClickedButtonReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����
	m_gameControl.Reset();
	//���½���
	UpdateMap();
	//�����ػ�
	InvalidateRect(m_rtGameRect, FALSE); 
}
