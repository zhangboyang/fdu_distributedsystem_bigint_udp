
// BigIntClientDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "RobustUDPClient.h"
#include "MsgLogger.h"

// CBigIntClientDlg 对话框
class CBigIntClientDlg : public CDialog, public MsgLogger
{
// 构造
public:
	CBigIntClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BIGINTCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	RobustUDPClient client;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddnumber();
	CListCtrl m_NumList;
	afx_msg void OnBnClickedDelnumber();
	afx_msg void OnBnClickedGetresult();
	afx_msg void OnBnClickedClearresult();
	CString m_SrvAddr;

	void OnLogMessage(LPCTSTR msg);
	CListBox m_LogList;

	virtual void Log(LPCTSTR msg);
	afx_msg void OnDestroy();
};
