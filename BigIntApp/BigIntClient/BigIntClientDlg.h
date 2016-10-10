
// BigIntClientDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "RobustUDPClient.h"
#include "MsgLogger.h"

// CBigIntClientDlg �Ի���
class CBigIntClientDlg : public CDialog, public MsgLogger
{
// ����
public:
	CBigIntClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BIGINTCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	RobustUDPClient client;

	// ���ɵ���Ϣӳ�亯��
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
