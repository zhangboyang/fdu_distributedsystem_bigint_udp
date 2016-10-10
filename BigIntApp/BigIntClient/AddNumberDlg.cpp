// AddNumberDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BigIntClient.h"
#include "AddNumberDlg.h"


// CAddNumberDlg �Ի���

IMPLEMENT_DYNAMIC(CAddNumberDlg, CDialog)

CAddNumberDlg::CAddNumberDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddNumberDlg::IDD, pParent)
	, m_Number1(_T(""))
	, m_Number2(_T(""))
{

}

CAddNumberDlg::~CAddNumberDlg()
{
}

void CAddNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Number1);
	DDX_Text(pDX, IDC_EDIT2, m_Number2);
}


BEGIN_MESSAGE_MAP(CAddNumberDlg, CDialog)
	ON_BN_CLICKED(IDC_RANDOM, &CAddNumberDlg::OnBnClickedRandom)
	ON_BN_CLICKED(IDOK, &CAddNumberDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddNumberDlg ��Ϣ�������

BOOL CAddNumberDlg::OnInitDialog()
{
	OnBnClickedRandom();
	return TRUE;
}

void CAddNumberDlg::OnBnClickedRandom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR numch[] = _T("0123456789");
	CString s[2];
	int len = 15;
	for (int sid = 0; sid < 2; sid++) {
		for (int i = 0; i < len; i++) {
			TCHAR ch = numch[rand() % 10];
			if (ch == numch[0] && s[sid].GetLength() == 0 && i != len - 1) {
				continue;
			}
			s[sid] += ch;
		}
	}
	m_Number1 = s[0];
	m_Number2 = s[1];
	UpdateData(FALSE);
}

void CAddNumberDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_Number1.GetLength() == 0 || m_Number2.GetLength() == 0) {
		MessageBox(_T("������������������֡�"), NULL, MB_ICONERROR);
		return;
	}
	OnOK();
}
