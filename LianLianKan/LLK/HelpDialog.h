#pragma once


// CHelpDialog �Ի���

class CHelpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDialog)

public:
	CHelpDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHelpDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_HELP };

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
