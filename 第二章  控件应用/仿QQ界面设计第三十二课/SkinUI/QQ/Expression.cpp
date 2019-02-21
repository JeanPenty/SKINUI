#include "StdAfx.h"
#include "Resource.h"
#include "Expression.h"

//////////////////////////////////////////////////////////////////////////////////
//�궨��

//λ�ö���
#define ITEM_SPACE					6									//�����϶
#define BORAD_SPACE					2									//�߿��϶
#define EXPRESSION_WIDTH			25									//������
#define EXPRESSION_HEIGHT			25									//����߶�

//��ɫ����
#define COLOR_BORAD					RGB(0,75,151)						//�߿���ɫ
#define COLOR_FRAME					RGB(0,75,151)						//�߿���ɫ
#define COLOR_BACK_GROUND			RGB(250,250,250)					//������ɫ

//��������
#define MAX_ROW_COUNT				10									//������Ŀ
#define MAX_LINE_COUNT				8									//������Ŀ

//////////////////////////////////////////////////////////////////////////////////
//��̬����

CExpressionManager * CExpressionManager::m_pExpressionManager=NULL;		//����ָ��

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CExpressionControl, CDialog)
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CExpression::CExpression()
{
	//���ñ���
	m_wIndex=INVALID_WORD;
	ZeroMemory(&m_ExpressionInfo,sizeof(m_ExpressionInfo));

	return;
}

//��������
CExpression::~CExpression()
{
}

//��ȡ·��
bool CExpression::GetExpressionPath(LPTSTR pszImagePath, WORD wMaxCount)
{
	//����Ŀ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	RenderEngine->GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//�����ַ
	_sntprintf(pszImagePath,wMaxCount,TEXT("%s\\QQ\\Face\\%03d.GIF"),szDirectory,m_wIndex);

	return true;
}

//���ñ���
bool CExpression::SetExpressionInfo(WORD wIndex, tagExpressionInfo&ExpressionInfo)
{
	//Ч��״̬
	ASSERT(m_ExpressionItem.IsNull()==true);
	if (m_ExpressionItem.IsNull()==false) return false;

	//���ñ���
	m_wIndex=wIndex;
	m_ExpressionInfo=ExpressionInfo;

	//��ȡ·��
	TCHAR szImagePath[MAX_PATH]=TEXT("");
	GetExpressionPath(szImagePath,CountArray(szImagePath));

	//����ͼƬ
	if (m_ExpressionItem.LoadFromFile(szImagePath)==false)
	{
		ASSERT(FALSE);
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CExpressionManager::CExpressionManager()
{
	//���ö���
	ASSERT(m_pExpressionManager==NULL);
	if (m_pExpressionManager==NULL) m_pExpressionManager=this;

	return;
}

//��������
CExpressionManager::~CExpressionManager()
{
	//ɾ������
	for (INT_PTR i=0;i<m_ExpressionArray.GetCount();i++)
	{
		SafeDelete(m_ExpressionArray[i]);
	}

	//ɾ������
	m_ExpressionArray.RemoveAll();

	//�ͷŶ���
	ASSERT(m_pExpressionManager==this);
	if (m_pExpressionManager==this) m_pExpressionManager=NULL;

	return;
}

//��ʼ����
bool CExpressionManager::LoadExpression()
{
	//����Ŀ¼
	TCHAR szDirectory[MAX_PATH]=TEXT("");
	RenderEngine->GetWorkDirectory(szDirectory,CountArray(szDirectory));

	//����·��
	TCHAR szInfoFile[MAX_PATH]=TEXT("");
	_sntprintf(szInfoFile,CountArray(szInfoFile),TEXT("%s\\QQ\\Face\\Face.INI"),szDirectory);

	//��������
	WORD wIndex=0L;
	LPCTSTR pszItemKey[]={TEXT("CN"),TEXT("EN"),TEXT("PY")};

	//��ȡ����
	do
	{
		//��������
		bool bSuccess=false;
		TCHAR szItemName[16]=TEXT("");

		//��������
		tagExpressionInfo ExpressionInfo;
		ZeroMemory(&ExpressionInfo,sizeof(ExpressionInfo));

		//��ȡ����
		for (INT i=0;i<CountArray(ExpressionInfo.szExpression);i++)
		{
			//��ȡ��Ϣ
			_sntprintf(szItemName,CountArray(szItemName),TEXT("%s%03d"),pszItemKey[i],wIndex);
			GetPrivateProfileString(TEXT("Face"),szItemName,TEXT(""),ExpressionInfo.szExpression[i],CountArray(ExpressionInfo.szExpression[i]),szInfoFile);

			//����ж�
			if (ExpressionInfo.szExpression[i][0]!=0)
			{
				bSuccess=true;
				ExpressionInfo.nLength[i]=lstrlen(ExpressionInfo.szExpression[i]);
			}
			else ExpressionInfo.nLength[i]=0;
		}

		//�������
		if (bSuccess==true)
		{
			//�������
			CExpression * pExpression=NULL;
			try
			{
				pExpression=new CExpression;
				pExpression->SetExpressionInfo(wIndex++,ExpressionInfo);
			}
			catch (...)
			{
				ASSERT(FALSE);
				SafeDelete(pExpression);
			}

			//��������
			m_ExpressionArray.Add(pExpression);
		}

		//����ж�
		if (bSuccess==false)
		{
			break;
		}

	} while (true);

	return true;
}

//���ͱ���
bool CExpressionManager::TranslateString(LPCTSTR pszString, tagTranslateResult&TranslateResult)
{
	//Ч�����
	ASSERT((pszString!=NULL)&&(pszString[0]!=0));
	if ((pszString==NULL)||(pszString[0]==0)) return false;

	//��������
	INT nHandleLength=0;
	INT nStringLength=lstrlen(pszString);

	//���Ͳ���
	for (INT i=0;i<nStringLength-1;i++)
	{
		//�����ж�
		if (pszString[i]!=TEXT('/')) continue;

		//��������
		for (INT_PTR j=0;j<m_ExpressionArray.GetCount();j++)
		{
			//��ȡ����
			CExpression * pExpression=m_ExpressionArray[j];
			tagExpressionInfo * pExpressionInfo=&pExpression->m_ExpressionInfo;

			//�����Ա�
			for (INT k=0;k<CountArray(pExpressionInfo->szExpression);k++)
			{
				//�����ж�
				INT nInfoLength=pExpressionInfo->nLength[k];
				if ((nInfoLength<=0)||((nStringLength-1-i)<nInfoLength)) continue;

				//�ַ��Ա�
				if (memcmp(pExpressionInfo->szExpression[k],&pszString[i+1],sizeof(TCHAR)*nInfoLength)==0)
				{
					//���ý��
					TranslateResult.nStartPos=i;
					TranslateResult.nDescribeLen=nInfoLength+1;
					TranslateResult.pExpressionItem=pExpression;

					return true;
				}
			}
		}
	}

	//���ý��
	ZeroMemory(&TranslateResult,sizeof(TranslateResult));

	return false;
}

//������Ŀ
WORD CExpressionManager::GetExpressionCount()
{
	return (WORD)m_ExpressionArray.GetCount();
}

//ö�ٱ���
CExpression * CExpressionManager::GetExpressionItem(WORD wIndex)
{
	//Ч�����
	ASSERT(wIndex<m_ExpressionArray.GetCount());
	if (wIndex>=m_ExpressionArray.GetCount()) return NULL;

	//��ȡ����
	return m_ExpressionArray[wIndex];
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CExpressionControl::CExpressionControl()
{
	//���ñ���
	m_wItemCount=0;
	m_wSelectIndex=0xFFFF;

	return;
}

//��������
CExpressionControl::~CExpressionControl()
{
}

//��ʾ�ؼ�
VOID CExpressionControl::ShowExpression(CWnd * pParentWnd, INT nXPos, INT nYPos, IExpressionSink * pIExpressionSink)
{
	//Ч��״̬
	ASSERT((m_hWnd==NULL)&&(pIExpressionSink!=NULL));
	if ((m_hWnd!=NULL)||(pIExpressionSink==NULL)) return;

	//���ñ���
	m_pParentWnd=pParentWnd;
	m_pIExpressionSink=pIExpressionSink;

	//��ȡ����
	ASSERT(CExpressionManager::GetInstance()!=NULL);
	CExpressionManager * pExpressionManager=CExpressionManager::GetInstance();

	//��ȡ��Ϣ
	m_wSelectIndex=INVALID_WORD;
	m_wItemCount=pExpressionManager->GetExpressionCount();
	m_wItemCount=__min(MAX_ROW_COUNT*MAX_LINE_COUNT,m_wItemCount);

	//��������
	AfxSetResourceHandle(AfxGetInstanceHandle());
	Create(IDD_EXPRESSION,pParentWnd);
	AfxSetResourceHandle(GetModuleHandle(NULL));

	//��ȡλ��
	INT nXScreen=GetSystemMetrics(SM_CXSCREEN);
	INT nYScreen=GetSystemMetrics(SM_CYSCREEN);

	//����λ��
	INT nLineCount=(m_wItemCount+MAX_ROW_COUNT-1)/MAX_ROW_COUNT;
	INT nControlHeight=2*BORAD_SPACE+nLineCount*(EXPRESSION_HEIGHT+ITEM_SPACE)+ITEM_SPACE;
	INT nControlWidth=(EXPRESSION_WIDTH+ITEM_SPACE)*MAX_ROW_COUNT+ITEM_SPACE+2*BORAD_SPACE;

	//����λ��
	if ((nXPos+nControlWidth)>=nXScreen) nXPos=nXScreen-nControlWidth;
	SetWindowPos(&CWnd::wndTopMost,nXPos,nYPos-nControlHeight,nControlWidth,nControlHeight,SWP_NOZORDER|SWP_SHOWWINDOW);

	return;
}

//�滭ͷ��
VOID CExpressionControl::DrawExpression(CDC * pDC, WORD wItemIndex, bool bSelected)
{
	//��ȡ����
	CExpressionManager * pExpressionManager=CExpressionManager::GetInstance();
	CExpression * pExpression=pExpressionManager->GetExpressionItem(wItemIndex);

	//λ�ü���
	INT nFrameWidth=EXPRESSION_WIDTH+ITEM_SPACE;
	INT nFrameHeight=EXPRESSION_HEIGHT+ITEM_SPACE;

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(nFrameWidth,nFrameHeight,32);

	//�滭���
	CImageDC ImageDC(ImageBuffer);
	CDC * pBufferDC=CDC::FromHandle(ImageDC);

	//�滭����
	pBufferDC->FillSolidRect(0,0,nFrameWidth,nFrameHeight,COLOR_BACK_GROUND);
	pExpression->m_ExpressionItem.DrawImageFrame(pBufferDC,ITEM_SPACE/2,ITEM_SPACE/2,0L);

	//�滭�߿�
	COLORREF rcColor=(bSelected==true)?COLOR_FRAME:COLOR_BACK_GROUND;
	pBufferDC->Draw3dRect(0,0,nFrameWidth,nFrameHeight,rcColor,rcColor);

	//�滭����
	INT nXIndex=(wItemIndex%MAX_ROW_COUNT);
	INT nYIndex=(wItemIndex/MAX_ROW_COUNT);
	pDC->BitBlt(nXIndex*nFrameWidth+BORAD_SPACE+ITEM_SPACE/2,nYIndex*nFrameHeight+BORAD_SPACE+ITEM_SPACE/2,nFrameWidth,nFrameHeight,pBufferDC,0,0,SRCCOPY);

	return;
}

//�ػ���Ϣ
VOID CExpressionControl::OnPaint()
{
	CPaintDC dc(this);

	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//�滭׼��
	CDC * pDC=CDC::FromHandle(ImageBuffer.GetDC());

	//�滭����
	pDC->FillSolidRect(&rcClient,COLOR_BACK_GROUND);
	pDC->Draw3dRect(&rcClient,COLOR_BORAD,COLOR_BORAD);

	//�滭����
	for (WORD i=0;i<m_wItemCount;i++)
	{
		DrawExpression(pDC,i,m_wSelectIndex==i);
	}

	//�滭����
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),pDC,0,0,SRCCOPY);

	//������Դ
	ImageBuffer.ReleaseDC();

	return;
}

//�滭����
BOOL CExpressionControl::OnEraseBkgnd(CDC * pDC)
{
	//���´���
	Invalidate(FALSE);
	UpdateWindow();

	return TRUE;
}

//������Ϣ
VOID CExpressionControl::OnKillFocus(CWnd * pNewWnd)
{
	__super::OnKillFocus(pNewWnd);

	//ע������
	DestroyWindow();

	return;
}

//�����Ϣ
VOID CExpressionControl::OnLButtonDown(UINT nFlags, CPoint Point)
{
	__super::OnLButtonDown(nFlags,Point);

	//������Ϣ
	if (m_wSelectIndex!=INVALID_WORD)
	{
		//��ȡ����
		CExpressionManager * pExpressionManager=CExpressionManager::GetInstance();
		CExpression * pExpression=pExpressionManager->GetExpressionItem(m_wSelectIndex);

		//�¼�֪ͨ
		ASSERT(m_pIExpressionSink!=NULL);
		m_pIExpressionSink->OnExpressionSelect(pExpression,&pExpression->m_ExpressionInfo);

		//�رմ���
		DestroyWindow();
	}

	return;
}

//�����Ϣ
BOOL CExpressionControl::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage)
{
	//��ȡ���
	CPoint MousePoint;
	GetCursorPos(&MousePoint);
	ScreenToClient(&MousePoint);

	//����λ��
	WORD wCurrentItem=INVALID_WORD;
	INT nXPos=MousePoint.x-BORAD_SPACE-ITEM_SPACE;
	INT nYPos=MousePoint.y-BORAD_SPACE-ITEM_SPACE;

	//ѡ���ж�
	if ((nXPos>=0)&&(nYPos>=0)&&(nXPos<MAX_ROW_COUNT*(EXPRESSION_HEIGHT+ITEM_SPACE)))
	{
		wCurrentItem=nYPos/(EXPRESSION_HEIGHT+ITEM_SPACE)*MAX_ROW_COUNT+nXPos/(EXPRESSION_WIDTH+ITEM_SPACE);
		if (wCurrentItem>=m_wItemCount) wCurrentItem=INVALID_WORD;
	}

	//ѡ���ж�
	if (wCurrentItem!=m_wSelectIndex)
	{
		//��������
		CClientDC ClientDC(this);

		//��ǰѡ��
		if (wCurrentItem!=INVALID_WORD)
		{
			DrawExpression(&ClientDC,wCurrentItem,true);
		}

		//��ʷѡ��
		if (m_wSelectIndex!=INVALID_WORD)
		{
			DrawExpression(&ClientDC,m_wSelectIndex,false);
		}

		//���ñ���
		m_wSelectIndex=wCurrentItem;
	}

	//���ù��
	if (m_wSelectIndex!=INVALID_WORD)
	{
		SetCursor(LoadCursor(GetModuleHandle(SKINUI_DLL_NAME),MAKEINTRESOURCE(8000)));
		return TRUE;
	}

	return __super::OnSetCursor(pWnd,nHitTest,uMessage);
}

//////////////////////////////////////////////////////////////////////////////////
