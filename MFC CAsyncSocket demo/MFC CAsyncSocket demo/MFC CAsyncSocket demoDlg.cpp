
// MFC CAsyncSocket demoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC CAsyncSocket demo.h"
#include "MFC CAsyncSocket demoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCCAsyncSocketdemoDlg 对话框




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


// CMFCCAsyncSocketdemoDlg 消息处理程序

BOOL CMFCCAsyncSocketdemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	this->m_socket.set_dialog(this);
	//按钮相关设置
	this->m_btn_con.EnableWindow(true);
	this->m_btn_discon.EnableWindow(false);
	//ip地址与端口相关设置
	this->m_address = _T("192.168.1.150");
	this->m_ipcontrol.SetAddress(192,168,1,150);
	this->m_port = 2000;
	this->m_portcontrol.SetWindowText(_T("2000"));
	//接收数据相关设置
	this->m_recieveddata = _T("");
	this->m_messagecontrol.SetWindowText(_T(""));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCCAsyncSocketdemoDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
		::MessageBox(GetSafeHwnd(), _T("无法接受数据!"), _T("错误提示！"), MB_OK);
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
	this->m_recieveddata.Insert(this->m_recieveddata.GetLength(),_T("连接服务器成功!\r\n"));
	this->m_messagecontrol.SetWindowText(this->m_recieveddata);
	this->m_btn_con.EnableWindow(false);
	this->m_btn_discon.EnableWindow(true);
}
void CMFCCAsyncSocketdemoDlg::OnClose()
{
	this->m_socket.Close();
	this->m_recieveddata.Insert(this->m_recieveddata.GetLength(),_T("服务器主动断开连接!\r\n"));
	this->m_messagecontrol.SetWindowText(this->m_recieveddata);
	this->m_btn_con.EnableWindow(true);
	this->m_btn_discon.EnableWindow(false);
}

void CMFCCAsyncSocketdemoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwAddress;
	this->m_ipcontrol.GetAddress(dwAddress);
	this->m_address.Format(_T("%d.%d.%d.%d"),(0xFF000000&dwAddress)>>24,(0xFF0000&dwAddress)>>16,(0xFF00&dwAddress)>>8,0xFF&dwAddress);
	CString csport;
	this->m_portcontrol.GetWindowText(csport);
	this->m_port = _ttoi(csport);
	//重要的地方:Create()
	this->m_socket.Create();
	this->m_socket.Connect(m_address,m_port);
	this->m_btn_con.EnableWindow(false);
	this->m_recieveddata = _T("");
	this->m_recieveddata.Insert(this->m_recieveddata.GetLength(),_T("正在建立连接!!服务器IP:") + this->m_address + _T("\r\n"));
	this->m_messagecontrol.SetWindowText(this->m_recieveddata);
}


void CMFCCAsyncSocketdemoDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	this->m_socket.Close();
	this->m_recieveddata.Insert(this->m_recieveddata.GetLength(),_T("本客户端主动断开连接!\r\n"));
	this->m_messagecontrol.SetWindowText(this->m_recieveddata);
	this->m_btn_con.EnableWindow(true);
	this->m_btn_discon.EnableWindow(false);
}
