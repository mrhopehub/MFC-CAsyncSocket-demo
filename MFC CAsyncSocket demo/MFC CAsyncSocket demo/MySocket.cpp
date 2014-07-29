// MySocket.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC CAsyncSocket demo.h"
#include "MySocket.h"
#include "MFC CAsyncSocket demoDlg.h"

// MySocket

MySocket::MySocket()
{
}

MySocket::~MySocket()
{
}


// MySocket 成员函数


void MySocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnAccept(nErrorCode);
}


void MySocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(nErrorCode==0)
	{
		((CMFCCAsyncSocketdemoDlg*)m_dialog)->OnClose(); 
	}	
	CAsyncSocket::OnClose(nErrorCode);
}


void MySocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(nErrorCode==0)
	{
		((CMFCCAsyncSocketdemoDlg*)m_dialog)->OnConnect(); 
	}
	CAsyncSocket::OnConnect(nErrorCode);
}


void MySocket::OnOutOfBandData(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnOutOfBandData(nErrorCode);
}


void MySocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(nErrorCode==0)
	{
		((CMFCCAsyncSocketdemoDlg*)m_dialog)->OnReceive(); 
	}
	CAsyncSocket::OnReceive(nErrorCode);
}


void MySocket::OnSend(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnSend(nErrorCode);
}
void MySocket::set_dialog(CDialogEx *dialog)
{
	this->m_dialog = dialog;
}