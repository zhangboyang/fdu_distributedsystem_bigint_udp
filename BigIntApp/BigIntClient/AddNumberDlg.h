#pragma once


// CAddNumberDlg �Ի���

class CAddNumberDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddNumberDlg)

public:
	CAddNumberDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddNumberDlg();

// �Ի�������
	enum { IDD = IDD_ADDNUMBER };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Number1;
	CString m_Number2;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRandom();
	afx_msg void OnBnClickedOk();
};
