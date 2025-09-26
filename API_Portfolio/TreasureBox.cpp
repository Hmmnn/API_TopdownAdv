#include "stdafx.h"
#include "TreasureBox.h"
#include "RectCollider.h"

#include "BmpMgr.h"

CTreasureBox::CTreasureBox()
{
}

CTreasureBox::~CTreasureBox()
{
    Release();
}

void CTreasureBox::Initialize()
{
    m_eObjType = MAPOBJ;

    m_eState = ON;
    m_bActive = true;

    m_vSize = { 48, 48 };

    m_pCollider = new CRectCollider(this, { 48, 48 });

    InitializeImage();
}

int CTreasureBox::Update()
{
    CObj::UpdateRect();

    return SCENE_NOEVENT;
}

void CTreasureBox::LateUpdate()
{
    RunAnimation();
}

void CTreasureBox::Render(HDC hDC)
{
    m_pCollider->Render(hDC);

    CStaticObj::Render(hDC);
}

void CTreasureBox::Release()
{
    //for_each(m_vecFrame.begin(), m_vecFrame.end(), Safe_Delete<FRAME*>);
    //m_vecFrame.clear();
}

void CTreasureBox::OnCollision(CObj* _pOther)
{
}

void CTreasureBox::InitializeImage()
{
    m_hMemDC = CBmpMgr::GetInstance()->FindBmp(L"TREASURE");

    m_vecFrame.resize(ST_END);

    m_vecFrame[OFF] = new FRAME(0, 0, 0, false);
    m_vecFrame[ON] = new FRAME(0, 1, 1, false);
}
