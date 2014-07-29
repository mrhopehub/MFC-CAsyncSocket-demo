
// MFC CAsyncSocket demoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "MySocket.h"


// CMFCCAsyncSocketdemoDlg �Ի���
class CMFCCAsyncSocketdemoDlg : public CDialogEx
{
// ����
public:
	CMFCCAsyncSocketdemoDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void OnReceive();
	void OnClose();
	void OnConnect();

// �Ի�������
	enum { IDD = IDD_MFCCASYNCSOCKETDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
