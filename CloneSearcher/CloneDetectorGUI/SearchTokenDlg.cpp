// SearchTokenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CloneDetectorGUI.h"
#include "SearchTokenDlg.h"
#include "afxdialogex.h"


extern CString g_dbName;
extern CString g_dbUser;
extern CString g_dbPwd;


// SearchTokenDlg dialog

IMPLEMENT_DYNAMIC(SearchTokenDlg, CDialogEx)

SearchTokenDlg::SearchTokenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(SearchTokenDlg::IDD, pParent)
	  , m_searchStr(_T(""))
	  , m_ok(false)
	  , m_dbName(g_dbName)
	  , m_dbUser(g_dbUser)
	  , m_dbPwd(g_dbPwd)
	  , m_string(FALSE)
	  , m_constant(FALSE)
	  , m_import(FALSE)
{

}

SearchTokenDlg::~SearchTokenDlg()
{
}

void SearchTokenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEARCH_TOKEN_COMBO, m_comboBox);
	DDX_Text(pDX, IDC_DB_NAME_TOK, m_dbName);
	DDX_Text(pDX, IDC_DB_USER_TOK, m_dbUser);
	DDX_Text(pDX, IDC_DB_PWD_TOK, m_dbPwd);
	DDX_Check(pDX, IDC_CHECK_STRING, m_string);
	DDX_Check(pDX, IDC_CHECK_CONST, m_constant);
	DDX_Check(pDX, IDC_CHECK_IMPORT, m_import);
}


BEGIN_MESSAGE_MAP(SearchTokenDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &SearchTokenDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// SearchTokenDlg message handlers


void SearchTokenDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

    CString strText;
	DWORD pos = m_comboBox.GetEditSel();
	if( pos != 0)
	{
		// user hit "ENTER"
		m_comboBox.GetWindowText(strText);
		if( strText.GetLength() > 0)
			m_strVec.push_back(strText);
	}
	else
	{
		// user clicked "OK"
		int idx = m_comboBox.GetCurSel();
		if( idx >= 0)
		{
			// select the existing string from the pull down list
			m_comboBox.GetLBText(idx,strText);
		}
		else
		{
			// user typed in the new string
			m_comboBox.GetWindowText(strText);
			if( strText.GetLength() > 0)
				m_strVec.push_back(strText);
		}
	}

	if(!m_string &&	!m_constant && !m_import)
	{
		AfxMessageBox(_T("Please select at least one search token type."));
		return;
	}

	if( strText.GetLength() > 0) 
	{
		m_searchStr = strText;
        g_dbName = m_dbName;
        g_dbUser = m_dbUser;
        g_dbPwd = m_dbPwd;

		m_ok = true;
	}

	CDialogEx::OnOK();
}


BOOL SearchTokenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_searchStr = _T("");
	m_ok = false;

	//load the previous strings
	std::vector<CString>::iterator itr = m_strVec.begin();
	for( ; itr != m_strVec.end(); ++itr)
	{
		m_comboBox.AddString(*itr);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}