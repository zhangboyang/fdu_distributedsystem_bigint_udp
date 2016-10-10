
// BigIntClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BigIntClient.h"
#include "BigIntClientDlg.h"
#include "AddNumberDlg.h"
#include "SimpleUDP.h"
#include "BigInt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBigIntClientDlg 对话框




CBigIntClientDlg::CBigIntClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBigIntClientDlg::IDD, pParent)
	, m_SrvAddr(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBigIntClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NUMLIST, m_NumList);
	DDX_Text(pDX, IDC_SERVER, m_SrvAddr);
	DDX_Control(pDX, IDC_LOGLIST, m_LogList);
}

BEGIN_MESSAGE_MAP(CBigIntClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ADDNUMBER, &CBigIntClientDlg::OnBnClickedAddnumber)
	ON_BN_CLICKED(IDC_DELNUMBER, &CBigIntClientDlg::OnBnClickedDelnumber)
	ON_BN_CLICKED(IDC_GETRESULT, &CBigIntClientDlg::OnBnClickedGetresult)
	ON_BN_CLICKED(IDC_CLEARRESULT, &CBigIntClientDlg::OnBnClickedClearresult)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CBigIntClientDlg 消息处理程序

BOOL CBigIntClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	srand(time(NULL));
	send_failrate = 0.1;
	send_waitrate = 0.1;

	pLogger = this;

	m_NumList.InsertColumn(0, _T("被加数"), 0, 150, -1);
	m_NumList.InsertColumn(1, _T("加数"), 0, 150, -1);
	m_NumList.InsertColumn(2, _T("结果"), 0, 200, -1);
	m_NumList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	m_SrvAddr = CString(_T("127.0.0.1:1234"));
	UpdateData(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBigIntClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBigIntClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBigIntClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBigIntClientDlg::OnBnClickedAddnumber()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddNumberDlg dlg;
	dlg.DoModal();
	int nIndex = m_NumList.InsertItem(m_NumList.GetItemCount(), dlg.m_Number1);
	m_NumList.SetItemText(nIndex, 1, dlg.m_Number2);
	m_NumList.SetItemText(nIndex, 2, _T("无结果"));
}

void CBigIntClientDlg::OnBnClickedDelnumber()
{
	// TODO: 在此添加控件通知处理程序代码
	//m_NumList.DeleteItem();
	POSITION pos = m_NumList.GetFirstSelectedItemPosition();
	while (pos != NULL) {
		m_NumList.DeleteItem(m_NumList.GetNextSelectedItem(pos));
		pos = m_NumList.GetFirstSelectedItemPosition();
	}
}

void CBigIntClientDlg::OnBnClickedGetresult()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_NumList.GetItemCount(); i++) {
		m_NumList.SetItemText(i, 2, _T("正在获取"));
	}

	m_NumList.RedrawWindow();

	UpdateData(TRUE);

	client.SetServer(UDPSocket::SocketAddr(ws2s(std::wstring(m_SrvAddr))));

	for (int i = 0; i < m_NumList.GetItemCount(); i++) {
		std::string a = ws2s(std::wstring(m_NumList.GetItemText(i, 0)));
		std::string b = ws2s(std::wstring(m_NumList.GetItemText(i, 1)));
		std::string s = a + "+" + b;
		std::vector<char> request(s.c_str(), s.c_str() + s.length());
		std::vector<char> response = client.DoRequest(request);
		std::string c;
		for (std::vector<char>::iterator it = response.begin(); it != response.end(); it++) {
			c += *it;
		}

		bool ok = c == add(a, b);
		m_NumList.SetItemText(i, 2, (s2ws(c) + (ok ? _T(" (正确)") : _T(" (错误)"))).c_str());
		m_NumList.RedrawWindow();

		if (!ok) {
			::Log(_T("结果错误！a+b=%hs c=%hs"), add(a, b).c_str(), c.c_str());
			break;
		}
	}
	::Log(_T("完成"));
}

void CBigIntClientDlg::OnBnClickedClearresult()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < m_NumList.GetItemCount(); i++) {
		m_NumList.SetItemText(i, 2, _T("无结果"));
	}
}


void CBigIntClientDlg::Log(LPCTSTR msg)
{
	int nIndex = m_LogList.InsertString(m_LogList.GetCount(), msg);
	m_LogList.SetCurSel(nIndex);
}

void CBigIntClientDlg::OnDestroy()
{
	__super::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	pLogger = NULL;
}
