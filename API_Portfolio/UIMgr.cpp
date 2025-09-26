#include "stdafx.h"
#include "UIMgr.h"
#include "HeartHpBar.h"
#include "KeyGuide.h"
#include "Budget.h"

#include "ObjMgr.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr() :
	m_pPlayerHpBar(nullptr), m_pKeyGuide(nullptr), m_pBudget(nullptr)
{
}

CUIMgr::~CUIMgr()
{
}

void CUIMgr::InitializePlayerHp(int* _pHp)
{
	m_pPlayerHpBar = new CHeartHpBar(20);
	m_pPlayerHpBar->Initialize();
	m_pPlayerHpBar->SetHp(_pHp);
	CObjMgr::GetInstance()->AddObj(MISC, m_pPlayerHpBar);

}

void CUIMgr::InitializeKeyGuide()
{
	m_pKeyGuide = new CKeyGuide();
	m_pKeyGuide->Initialize();
	CObjMgr::GetInstance()->AddObj(MISC, m_pKeyGuide);
}

void CUIMgr::InitializeBudget()
{
	m_pBudget = new CBudget();
	m_pBudget->Initialize();
	CObjMgr::GetInstance()->AddObj(MISC, m_pBudget);
}

void CUIMgr::SetActionKeyGuide(int _iIndex, HDC _hImage)
{
	m_pKeyGuide->SetImage(_iIndex, _hImage);
}

void CUIMgr::RenderActionKey(HDC hDC)
{
	m_pKeyGuide->Render(hDC);
}

void CUIMgr::SetBudget(const int* _pBudget)
{
	m_pBudget->SetBudget(_pBudget);
}
