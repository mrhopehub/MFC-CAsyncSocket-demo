// MySocket.cpp : ʵ���ļ�
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


// MySocket ��Ա����


void MySocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnAccept(nErrorCode);
}


void MySocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(nErrorCode==0)
	{
		((CMFCCAsyncSocketdemoDlg*)m_dialog)->OnClose(); 
	}	
	CAsyncSocket::OnClose(nErrorCode);
}


void MySocket::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(nErrorCode==0)
	{
		((CMFCCAsyncSocketdemoDlg*)m_dialog)->OnConnect(); 
	}
	CAsyncSocket::OnConnect(nErrorCode);
}


void MySocket::OnOutOfBandData(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnOutOfBandData(nErrorCode);
}


void MySocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(nErrorCode==0)
	{
		((CMFCCAsyncSocketdemoDlg*)m_dialog)->OnReceive(); 
	}
	CAsyncSocket::OnReceive(nErrorCode);
}


void MySocket::OnSend(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnSend(nErrorCode);
}
void MySocket::set_dialog(CDialogEx *dialog)
{
	this->m_dialog = dialog;
}