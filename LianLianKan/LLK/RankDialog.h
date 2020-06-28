#pragma once


// CRankDialog 对话框

class CRankDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CRankDialog)

public:
	CRankDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRankDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_RANK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	BOOL OnInitDialog(void);
	void OnPaint(void);
	void UpdateHelp(int nPos);

protected:
	HICON m_hIcon;    //系统图片
	CDC m_dcMem;      //内存DC
	CDC m_dcHelp;     //帮助图片DC
	CRect m_rtHelp;   //帮助图片显示区域
};
