#pragma once


// CAddNumberDlg 对话框

class CAddNumberDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddNumberDlg)

public:
	CAddNumberDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddNumberDlg();

// 对话框数据
	enum { IDD = IDD_ADDNUMBER };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Number1;
	CString m_Number2;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRandom();
	afx_msg void OnBnClickedOk();
};
