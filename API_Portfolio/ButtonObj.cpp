#include "stdafx.h"
#include "ButtonObj.h"
#include "RectCollider.h"

#include "BmpMgr.h"

CButtonObj::CButtonObj() :
    m_bPushed(false)
{
}

CButtonObj::~CButtonObj()
{
    Release();
}

void CButtonObj::Initialize()
{
    m_eObjType = MAPOBJ;
    m_eRenderID = RENDER_BACKGROUND;

    m_eState = OFF;
    m_bActive = true;

    m_vSize = { 48, 48 };

    m_pCollider = new CRectCollider(this, m_vSize);

    InitializeImage();
}

int CButtonObj::Update()
{
    return SCENE_NOEVENT;
}

void CButtonObj::LateUpdate()
{
}

void CButtonObj::Render(HDC hDC)
{
    m_pCollider->Render(hDC);

    CStaticObj::Render(hDC);
}

void CButtonObj::Release()
{
}

void CButtonObj::OnCollision(CObj* _pOther)
{
    // 충돌하지 않는 상태를 어떻게 확인하지
}

void CButtonObj::InitializeImage()
{
    m_hMemDC = CBmpMgr::GetInstance()->FindBmp(L"BUTTON");

    m_vecFrame.resize(ST_END);

    m_vecFrame[OFF] = new FRAME(OFF, 0, 0, false);
    m_vecFrame[ON] = new FRAME(0, 1, 1, false);
}
