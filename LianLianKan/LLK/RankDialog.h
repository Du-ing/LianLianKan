#pragma once


// CRankDialog �Ի���

class CRankDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDialog)

public:
	CRankDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRankDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_RANK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	BOOL OnInitDialog(void);
	void OnPaint(void);
	void UpdateHelp(int nPos);

protected:
	HICON m_hIcon;    //ϵͳͼƬ
	CDC m_dcMem;      //�ڴ�DC
	CDC m_dcHelp;     //����ͼƬDC
	CRect m_rtHelp;   //����ͼƬ��ʾ����
};
