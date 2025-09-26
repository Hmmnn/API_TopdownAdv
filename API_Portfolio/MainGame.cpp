#include "stdafx.h"
#include "MainGame.h"

#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "SkillMgr.h"
#include "StateMgr.h"
#include "SoundMgr.h"
#include "WallMgr.h"
#include "ItemMgr.h"
#include "Inventory.h"
#include "UIMgr.h"
#include "EffectMgr.h"

CMainGame::CMainGame() : hBackBuffer(NULL), m_DC(NULL)
{
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	srand(unsigned int(time(NULL)));

	m_DC = GetDC(g_hWnd);

	CKeyMgr::GetInstance();
	CTimeMgr::GetInstance();
	CScrollMgr::GetInstance();
	CBmpMgr::GetInstance();
	CSoundMgr::Get_Instance()->Initialize();
	CObjMgr::GetInstance();
	CSkillMgr::GetInstance();
	CStateMgr::GetInstance()->Initialize();
	CWallMgr::GetInstance();
	CSceneMgr::GetInstance()->Initialize();
	CItemMgr::GetInstance()->Initialize();
	CUIMgr::GetInstance();
	CInventory::GetInstance()->Initialize();
	CEffectMgr::GetInstance()->Initialize();

	HDC		hDC = GetDC(g_hWnd);

	hBackBuffer = CreateCompatibleDC(hDC);
	HBITMAP	hBitmap = CreateCompatibleBitmap(hDC, WINCX, WINCY);

	ReleaseDC(g_hWnd, hDC);

	SelectObject(hBackBuffer, hBitmap);

#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif // _DEBUG
	
}

void CMainGame::Update()
{
	if (KEY_DOWN('0'))
		g_bDebugMode = !g_bDebugMode;

	static bool bInvenActive = false;

	if (KEY_DOWN('I'))
	{
		bInvenActive = !bInvenActive;

		if (bInvenActive)
			CInventory::GetInstance()->EnterInventory();
		else
			CInventory::GetInstance()->ExitInventory();
	}

	CTimeMgr::GetInstance()->Update();

	CSceneMgr::GetInstance()->Update();
}

void CMainGame::LateUpdate()
{
	CInventory::GetInstance()->ControlCursor();
	
	CSceneMgr::GetInstance()->LateUpdate();

	CScrollMgr::GetInstance()->UpdateScroll();
	CScrollMgr::GetInstance()->ScrollLock();

}

void CMainGame::Render()
{
	TCHAR m_szFPS[32] = L"";
	swprintf_s(m_szFPS, L"FPS : %d", CTimeMgr::GetInstance()->GetFPS());
	
	SetWindowText(g_hWnd, m_szFPS);

	PatBlt(hBackBuffer, 0, 0, WINCX, WINCY, RGB(255, 255, 255));
	
	CSceneMgr::GetInstance()->Render(hBackBuffer);

	CInventory::GetInstance()->RenderItems(hBackBuffer);

	BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);
}

void CMainGame::Release()
{
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG
	
	CSceneMgr::DestroyInstance();
	CKeyMgr::DestroyInstance();
	CTimeMgr::DestroyInstance();
	CScrollMgr::DestroyInstance();
	CBmpMgr::DestroyInstance();
	CSoundMgr::Destroy_Instance();
	CSkillMgr::DestroyInstance();
	CStateMgr::DestroyInstance();
	CWallMgr::DestroyInstance();
	CItemMgr::DestroyInstance();
	CInventory::DestroyInstance();
	CUIMgr::DestroyInstance();
	CObjMgr::DestroyInstance();
	CEffectMgr::DestroyInstance();

	DeleteObject(hBackBuffer);
	ReleaseDC(g_hWnd, m_DC);
}
