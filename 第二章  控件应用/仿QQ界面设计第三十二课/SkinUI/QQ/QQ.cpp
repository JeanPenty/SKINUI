// QQ.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "QQ.h"
#include "QQDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQQApp

BEGIN_MESSAGE_MAP(CQQApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CQQApp ����

CQQApp::CQQApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CQQApp ����

CQQApp theApp;


// CQQApp ��ʼ��

BOOL CQQApp::InitInstance()
{
	//_CrtSetBreakAlloc(1096);
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	AfxInitRichEdit();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	RenderEngine->GetWorkDirectory(GlobalUnits->m_szDefaultSkin,MAX_PATH);
	StrCat(GlobalUnits->m_szDefaultSkin,TEXT("\\QQ\\Skin\\main1.jpg"));
	CFileFind find;
	if ( find.FindFile(GlobalUnits->m_szDefaultSkin) == FALSE )
	{
		AfxMessageBox(TEXT("��Դ����ʧ��"));
		return FALSE;
	}

	m_ExpressionManager.LoadExpression();

	CQQDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
