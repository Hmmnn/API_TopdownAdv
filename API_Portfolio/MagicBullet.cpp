#include "stdafx.h"
#include "MagicBullet.h"
#include "SphereCollider.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"

CMagicBullet::CMagicBullet()
{
}

CMagicBullet::~CMagicBullet()
{
    Release();
}

void CMagicBullet::Initialize()
{
    m_eObjType = PLAYERBULLET;

    m_bActive = false;

    m_vSize = { 45, 45 };
    m_fSpeed = 300.f;
    
    m_iAtk = 2;

    m_pCollider = new CSphereCollider(this, { 25, 25 });

    InitializeMotion();
}

int CMagicBullet::Update()
{
    if (!m_bActive)
        return SCENE_NOEVENT;

    return CGameObj::Update();
}

void CMagicBullet::LateUpdate()
{
    if (!m_bActive)
        return;

    m_vecMotion[0]->RunAnimation();
}

void CMagicBullet::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    int iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    m_pCollider->Render(hDC);

    m_vecMotion[0]->Render(hDC, iScrollX, iScrollY);
}

void CMagicBullet::Release()
{
}

void CMagicBullet::OnCollision(CObj* _pOther)
{
    OBJTYPE eType = _pOther->GetType();

    if (ENEMY == eType || BOSS == eType)
    {
        bool result = m_pCollider->AddHitted(_pOther);

        if (result)
            static_cast<CGameObj*>(_pOther)->TakeDamage(m_iAtk);

        CollisionGameObj();
    }

    else if (MAPOBJ == eType || WALL == eType)
    {
        CollisionMapObj();
    }
}

void CMagicBullet::CollisionMapObj()
{
    m_bActive = false;
    m_pCollider->SetActive(false);
}

void CMagicBullet::CollisionGameObj()
{
    m_bActive = false;
    m_pCollider->SetActive(false);
}

void CMagicBullet::Shoot(VEC2 _vPos, DIRECTION _eDir)
{
    switch (_eDir)
    {
    case DOWN:
        m_pCollider->SetOffset({ 0, 10 });
        m_vVelocity = { 0, 1 };
        m_vecMotion[0]->SetMotion(DOWN);
        break;

    case UP:
        m_pCollider->SetOffset({ 0, -10 });
        m_vVelocity = { 0, -1 };
        m_vecMotion[0]->SetMotion(UP);
        break;

    case LEFT:
        m_pCollider->SetOffset({ -10, 0 });
        m_vVelocity = { -1, 0 };
        m_vecMotion[0]->SetMotion(LEFT);
        break;

    case RIGHT: 
        m_pCollider->SetOffset({ 10, 0 });
        m_vVelocity = { +1, 0 };
        m_vecMotion[0]->SetMotion(RIGHT);
        break;
    }

    m_vPos = _vPos;
    m_bActive = true;
    m_pCollider->SetActive(true);
}

void CMagicBullet::InitializeMotion()
{
    m_vecMotion.resize(1);

    m_vecMotion[0] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"MAGIC"));
    m_vecMotion[0]->SetPos(&m_vPos);
    m_vecMotion[0]->SetSize(m_vSize);
    m_vecMotion[0]->SetRect(&m_tRect);
    m_vecMotion[0]->ResizeFrameVec(DIR_END);
    m_vecMotion[0]->SetFrame(DOWN, 0, 1, true, 1.f / 5.f);
    m_vecMotion[0]->SetFrame(UP, 0, 1, true, 1.f / 5.f);
    m_vecMotion[0]->SetFrame(LEFT, 0, 1, true, 1.f / 5.f);
    m_vecMotion[0]->SetFrame(RIGHT, 0, 1, true, 1.f / 5.f);
}
