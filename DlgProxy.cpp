﻿
// DlgProxy.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC-malware.h"
#include "DlgProxy.h"
#include "MFC-malwareDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCmalwareDlgAutoProxy

IMPLEMENT_DYNCREATE(CMFCmalwareDlgAutoProxy, CCmdTarget)

CMFCmalwareDlgAutoProxy::CMFCmalwareDlgAutoProxy()
{
	EnableAutomation();

	// 为使应用程序在自动化对象处于活动状态时一直保持
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。  设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMFCmalwareDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMFCmalwareDlg)))
		{
			m_pDialog = reinterpret_cast<CMFCmalwareDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMFCmalwareDlgAutoProxy::~CMFCmalwareDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	//	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != nullptr)
		m_pDialog->m_pAutoProxy = nullptr;
	AfxOleUnlockApp();
}

void CMFCmalwareDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMFCmalwareDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMFCmalwareDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IMFCmalware 的支持来支持类型安全绑定
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {68f6c186-957a-4212-8c6c-bee46ce081a3}
static const IID IID_IMFCmalware =
{0x68f6c186,0x957a,0x4212,{0x8c,0x6c,0xbe,0xe4,0x6c,0xe0,0x81,0xa3}};

BEGIN_INTERFACE_MAP(CMFCmalwareDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMFCmalwareDlgAutoProxy, IID_IMFCmalware, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏是在此项目的 pch.h 中定义的
// {07785ad7-7971-414b-8c0c-aad348ff51fb}
IMPLEMENT_OLECREATE2(CMFCmalwareDlgAutoProxy, "MFCmalware.Application", 0x07785ad7,0x7971,0x414b,0x8c,0x0c,0xaa,0xd3,0x48,0xff,0x51,0xfb)


// CMFCmalwareDlgAutoProxy 消息处理程序
