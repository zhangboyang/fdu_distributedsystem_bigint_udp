
// BigIntClientDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CBigIntClientDlg �Ի���




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


// CBigIntClientDlg ��Ϣ�������

BOOL CBigIntClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	srand(time(NULL));
	send_failrate = 0.1;
	send_waitrate = 0.1;

	pLogger = this;

	m_NumList.InsertColumn(0, _T("������"), 0, 150, -1);
	m_NumList.InsertColumn(1, _T("����"), 0, 150, -1);
	m_NumList.InsertColumn(2, _T("���"), 0, 200, -1);
	m_NumList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	m_SrvAddr = CString(_T("127.0.0.1:1234"));
	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBigIntClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBigIntClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBigIntClientDlg::OnBnClickedAddnumber()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAddNumberDlg dlg;
	dlg.DoModal();
	int nIndex = m_NumList.InsertItem(m_NumList.GetItemCount(), dlg.m_Number1);
	m_NumList.SetItemText(nIndex, 1, dlg.m_Number2);
	m_NumList.SetItemText(nIndex, 2, _T("�޽��"));
}

void CBigIntClientDlg::OnBnClickedDelnumber()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//m_NumList.DeleteItem();
	POSITION pos = m_NumList.GetFirstSelectedItemPosition();
	while (pos != NULL) {
		m_NumList.DeleteItem(m_NumList.GetNextSelectedItem(pos));
		pos = m_NumList.GetFirstSelectedItemPosition();
	}
}

void CBigIntClientDlg::OnBnClickedGetresult()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for (int i = 0; i < m_NumList.GetItemCount(); i++) {
		m_NumList.SetItemText(i, 2, _T("���ڻ�ȡ"));
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
		m_NumList.SetItemText(i, 2, (s2ws(c) + (ok ? _T(" (��ȷ)") : _T(" (����)"))).c_str());
		m_NumList.RedrawWindow();

		if (!ok) {
			::Log(_T("�������a+b=%hs c=%hs"), add(a, b).c_str(), c.c_str());
			break;
		}
	}
	::Log(_T("���"));
}

void CBigIntClientDlg::OnBnClickedClearresult()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for (int i = 0; i < m_NumList.GetItemCount(); i++) {
		m_NumList.SetItemText(i, 2, _T("�޽��"));
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

	// TODO: �ڴ˴������Ϣ����������
	pLogger = NULL;
}
