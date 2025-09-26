#include "stdafx.h"
#include "MyEditScene.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "ButtonMgr.h"
#include "WallMgr.h"
#include "ObjMgr.h"

CMyEditScene::CMyEditScene() :
	m_pBtnMgr(nullptr)
{
}

CMyEditScene::~CMyEditScene()
{
    Release();
}

void CMyEditScene::Initialize()
{
	m_pBtnMgr = new CButtonMgr;
	m_pBtnMgr->Initialize();

	CScrollMgr::GetInstance()->SetTarget(nullptr);
}

SCENEID CMyEditScene::Update()
{
	if (KEY_DOWN('T'))
		return SCENEID::TITLE;

	m_pBtnMgr->Update();
	CObjMgr::GetInstance()->Update();

	return SCENEID::EDIT;
}

void CMyEditScene::LateUpdate()
{
	m_pBtnMgr->LateUpdate();
	CObjMgr::GetInstance()->LateUpdate();

	ControlScroll();
}

void CMyEditScene::Render(HDC hDC)
{
	m_pBtnMgr->Render(hDC);
	CObjMgr::GetInstance()->Render(hDC);
}

void CMyEditScene::Release()
{
	Safe_Delete<CButtonMgr*>(m_pBtnMgr);
	//CObjMgr::GetInstance()->DeleteObj(WALL);
	CObjMgr::GetInstance()->SetActive(WALL, false);
}

void CMyEditScene::ControlScroll()
{
	if (KEY_PRESS(VK_LEFT))
		CScrollMgr::GetInstance()->SetScrollX(5.f);

	if (KEY_PRESS(VK_RIGHT))
		CScrollMgr::GetInstance()->SetScrollX(-5.f);

	if (KEY_PRESS(VK_UP))
		CScrollMgr::GetInstance()->SetScrollY(5.f);

	if (KEY_PRESS(VK_DOWN))
		CScrollMgr::GetInstance()->SetScrollY(-5.f);
}

void CMyEditScene::AddRect(VEC2 _vLeftTop, VEC2 _vRightBottom)
{
}
