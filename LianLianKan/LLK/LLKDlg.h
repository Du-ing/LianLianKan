// LLKDlg.h : ͷ�ļ�
//

#pragma once


// CLLKDlg �Ի���
class CLLKDlg : public CDialogEx
{
// ����
public:
	CLLKDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LLK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CDC m_dcMem;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void InitBackground();
public:
	afx_msg void OnClickedButtonBasic();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonXiuxian();
	afx_msg void OnBnClickedButtonGuanka();
	afx_msg void OnBnClickedButtonRank();
};
