#include "stdafx.h"
#include "Arrow.h"
#include "SphereCollider.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CArrow::CArrow() : m_fOffset(0)
{
}

CArrow::~CArrow()
{
    Release();
}

void CArrow::Initialize()
{
    m_eObjType = PLAYERBULLET;

    m_bActive = false;

    m_vPos = {};
    m_vSize = { 48, 48 };
    m_fOffset = 20;

    m_fSpeed = 300.f;

    m_iAtk = 3;

    m_pCollider = new CSphereCollider(this, { 20, 20 });

    InitializeMotion();
}

int CArrow::Update()
{
    if (!m_bActive)
        return SCENE_NOEVENT;

    return CGameObj::Update();
}

void CArrow::LateUpdate()
{
    if (!m_bActive)
        return;

    m_vecMotion[0]->RunAnimation();
}

void CArrow::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    int     iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int     iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    m_pCollider->Render(hDC);

    m_vecMotion[0]->Render(hDC, iScrollX, iScrollY);
}

void CArrow::Release()
{
}

void CArrow::OnCollision(CObj* _pOther)
{
    if (ENEMY == _pOther->GetType() || BOSS == _pOther->GetType())
    {
        bool result = m_pCollider->AddHitted(_pOther);

        if (result)
            static_cast<CGameObj*>(_pOther)->TakeDamage(m_iAtk);

        CollisionGameObj();
    }

    else if (MAPOBJ == _pOther->GetType() || WALL == _pOther->GetType())
    {
        CollisionMapObj();
    }
}

void CArrow::CollisionMapObj()
{
    m_bActive = false;

    m_pCollider->SetActive(false);
}

void CArrow::CollisionGameObj()
{
    m_bActive = false;
    m_pCollider->SetActive(false);

    m_pCollider->ClearHitted();
}

void CArrow::ShootArrow(VEC2 _tPos, DIRECTION _eDir)
{
    m_vPos = _tPos;
    m_eDir = _eDir;

    SetDirection();

    m_bActive = true;

    m_vecMotion[0]->SetMotion(m_eDir);
}

void CArrow::SetDirection()
{
    switch (m_eDir)
    {
    case DOWN:
        m_vVelocity = { 0, +1 };
        break;

    case UP:
        m_vVelocity = { 0, -1 };
        break;

    case LEFT:
        m_vVelocity = { -1, 0 };
        break;

    case RIGHT:
        m_vVelocity = { +1, 0 };
        break;
    }

    m_pCollider->SetOffset(m_vVelocity * m_fOffset);
}

void CArrow::InitializeMotion()
{
    m_vecMotion.resize(1);
    m_vecMotion[0] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"ARROW"));
    m_vecMotion[0]->SetPos(&m_vPos);
    m_vecMotion[0]->SetSize(m_vSize);
    m_vecMotion[0]->SetRect(&m_tRect);
    m_vecMotion[0]->ResizeFrameVec(DIR_END);
    m_vecMotion[0]->SetFrame(DOWN, 0, 0, 0, false);
    m_vecMotion[0]->SetFrame(LEFT, 0, 1, 1, false);
    m_vecMotion[0]->SetFrame(UP, 0, 2, 2, false);
    m_vecMotion[0]->SetFrame(RIGHT, 0, 3, 3, false);
}
