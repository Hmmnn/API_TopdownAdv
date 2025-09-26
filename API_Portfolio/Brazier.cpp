#include "stdafx.h"
#include "Brazier.h"
#include "RectCollider.h"

#include "BmpMgr.h"

CBrazier::CBrazier()
{
}

CBrazier::~CBrazier()
{
    Release();
}

void CBrazier::Initialize()
{
    m_eObjType = MAPOBJ;

    m_eState = OFF;
    m_bActive = true;

    m_vSize = { 48, 48 };

    m_pCollider = new CRectCollider(this, { 48, 48 });

    InitializeImage();
}

int CBrazier::Update()
{

    return SCENE_NOEVENT;
}

void CBrazier::LateUpdate()
{
    RunAnimation();
}

void CBrazier::Render(HDC hDC)
{
    m_pCollider->Render(hDC);

    CStaticObj::Render(hDC);
}

void CBrazier::Release()
{
}

void CBrazier::OnCollision(CObj* _pOther)
{
}

void CBrazier::InitializeImage()
{
    m_hMemDC = CBmpMgr::GetInstance()->FindBmp(L"BRAZIER");

    m_vecFrame.resize(ST_END);

    m_vecFrame[OFF] = new FRAME(OFF, 0, 0, false);
    m_vecFrame[ON] = new FRAME(ON, 0, 3, true);
}
