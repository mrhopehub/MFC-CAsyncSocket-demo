
// MFC CAsyncSocket demoDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "MySocket.h"


// CMFCCAsyncSocketdemoDlg 对话框
class CMFCCAsyncSocketdemoDlg : public CDialogEx
{
// 构造
public:
	CMFCCAsyncSocketdemoDlg(CWnd* pParent = NULL);	// 标准构造函数
	void OnReceive();
	void OnClose();
	void OnConnect();

// 对话框数据
	enum { IDD = IDD_MFCCASYNCSOCKETDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CIPAddressCtrl m_ipcontrol;
	CEdit m_portcontrol;
	CButton m_btn_con;
	CButton m_btn_discon;
	CEdit m_messagecontrol;

	MySocket m_socket;
	CString	m_recieveddata;
	CString m_address;
	int m_port;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
