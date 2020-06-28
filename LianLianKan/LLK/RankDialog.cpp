// RankDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "RankDialog.h"
#include "afxdialogex.h"


// CRankDialog �Ի���

IMPLEMENT_DYNAMIC(CRankDialog, CDialogEx)

CRankDialog::CRankDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRankDialog::IDD, pParent)
{

}

CRankDialog::~CRankDialog()
{
}

void CRankDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRankDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CRankDialog ��Ϣ�������
BOOL CRankDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	CClientDC dc(this);

	//����HelpͼƬ��Դ
	//����BMPͼƬ��Դ
	HANDLE hBmpHelp = ::LoadImage(NULL, _T("pic\\rank.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//��������Ƶ���ݼ��ݵ��ڴ�DC
	m_dcHelp.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ��DC
	m_dcHelp.SelectObject(hBmpHelp);


	//�����ڴ�DC��С
	CRect rtClient;
	this->GetWindowRect(&rtClient);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, rtClient.Width(), rtClient.Height());
	m_dcMem.SelectObject(&bmpMem);

	//���ư�ɫ����
	m_dcMem.BitBlt(0, 0, rtClient.Width(), rtClient.Height(), NULL, 0, 0, WHITENESS);

	//���ư�����Ϣ��ʾ����
	this->GetDlgItem(IDC_STATIC_RANK)->GetWindowRect(&m_rtHelp);
	this->ScreenToClient(&m_rtHelp);
	//���ư�����
	UpdateHelp(0);

	return TRUE;// �쳣: OCX ����ҳӦ���� FALSE
}


void CRankDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect   rect;
	GetClientRect(rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));   //����Ϊ��ɫ����

												  //hu���Ʊ������ڴ�DC��
	m_dcMem.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, 0, SRCCOPY);

	//���Ʊ���ͼƬ
	dc.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcMem, 0, 0, SRCCOPY);
	CDialogEx::OnPaint();
}

void CRankDialog::UpdateHelp(int nPos)
{
	//���ػ��������Ƴɰ�ɫ
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(),
		m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	//���Ƶ�ǰ��İ�����Ϣ
	m_dcMem.BitBlt(m_rtHelp.left, m_rtHelp.top, m_rtHelp.Width(),
		m_rtHelp.Height(), &m_dcHelp, 0, nPos, SRCCOPY);
}