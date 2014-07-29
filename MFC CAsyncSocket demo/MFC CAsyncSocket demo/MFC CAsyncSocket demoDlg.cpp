
// MFC CAsyncSocket demoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC CAsyncSocket demo.h"
#include "MFC CAsyncSocket demoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCCAsyncSocketdemoDlg �Ի���




CMFCCAsyncSocketdemoDlg::CMFCCAsyncSocketdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCCAsyncSocketdemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCAsyncSocketdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipcontrol);
	DDX_Control(pDX, IDC_EDIT1, m_portcontrol);
	DDX_Control(pDX, IDC_BUTTON1, m_btn_con);
	DDX_Control(pDX, IDC_BUTTON2, m_btn_discon);
	DDX_Control(pDX, IDC_EDIT2, m_messagecontrol);
}

BEGIN_MESSAGE_MAP(CMFCCAsyncSocketdemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCCAsyncSocketdemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCCAsyncSocketdemoDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCCAsyncSocketdemoDlg ��Ϣ�������

BOOL CMFCCAsyncSocketdemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	this->m_socket.set_dialog(this);
	//��ť�������
	this->m_btn_con.EnableWindow(true);
	this->m_btn_discon.EnableWindow(false);
	//ip��ַ��˿��������
	this->m_address = _T("192.168.1.150");
	this->m_ipcontrol.SetAddress(192,168,1,150);
	this->m_port = 2000;
	this->m_portcontrol.SetWindowText(_T("2000"));
	//���������������
	this->m_recieveddata = _T("");
	this->m_messagecontrol.SetWindowText(_T(""));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCCAsyncSocketdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCCAsyncSocketdemoDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCCAsyncSocketdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CMFCCAsyncSocketdemoDlg::OnReceive()
{
	char *pBuf = new char [1025];
	CString strData;
	int iLen;
	iLen=this->m_socket.Receive(pBuf,1024);
	if(iLen==SOCKET_ERROR)
	{
		::MessageBox(GetSafeHwnd(), _T("�޷���������!"), _T("������ʾ��"), MB_OK);
	}
	else
	{
		pBuf[iLen] = NULL;
		strData = pBuf;
		this->m_recieveddata.Insert(this->m_recieveddata.GetLength(),strData + _T("\r\n"));   //display in server
		this->m_messagecontrol.SetWindowText(this->m_recieveddata);
		delete pBuf;
	}
}
void CMFCCAsyncSocketdemoDlg::OnConnect()
{
	this->m_recieveddata.Insert(this->m_recieveddata.GetLength(),_T("���ӷ������ɹ�!\r\n"));
	this->m_messagecontrol.SetWindowText(this->m_recieveddata);
	this->m_btn_con.EnableWindow(false);
	this->m_btn_discon.EnableWindow(true);
}
void CMFCCAsyncSocketdemoDlg::OnClose()
{
	this->m_socket.Close();
	this->m_recieveddata.Insert(this->m_recieveddata.GetLength(),_T("�����������Ͽ�����!\r\n"));
	this->m_messagecontrol.SetWindowText(this->m_recieveddata);
	this->m_btn_con.EnableWindow(true);
	this->m_btn_discon.EnableWindow(false);
}

void CMFCCAsyncSocketdemoDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwAddress;
	this->m_ipcontrol.GetAddress(dwAddress);
	this->m_address.Format(_T("%d.%d.%d.%d"),(0xFF000000&dwAddress)>>24,(0xFF0000&dwAddress)>>16,(0xFF00&dwAddress)>>8,0xFF&dwAddress);
	CString csport;
	this->m_portcontrol.GetWindowText(csport);
	this->m_port = _ttoi(csport);
	//��Ҫ�ĵط�:Create()
	this->m_socket.Create();
	this->m_socket.Connect(m_address,m_port);
	this->m_btn_con.EnableWindow(false);
	this->m_recieveddata = _T("");
	this->m_recieveddata.Insert(this->m_recieveddata.GetLength(),_T("���ڽ�������!!������IP:") + this->m_address + _T("\r\n"));
	this->m_messagecontrol.SetWindowText(this->m_recieveddata);
}


void CMFCCAsyncSocketdemoDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->m_socket.Close();
	this->m_recieveddata.Insert(this->m_recieveddata.GetLength(),_T("���ͻ��������Ͽ�����!\r\n"));
	this->m_messagecontrol.SetWindowText(this->m_recieveddata);
	this->m_btn_con.EnableWindow(true);
	this->m_btn_discon.EnableWindow(false);
}
