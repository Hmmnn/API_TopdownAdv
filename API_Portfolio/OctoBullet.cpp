#include "stdafx.h"
#include "OctoBullet.h"
#include "SphereCollider.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"

COctoBullet::COctoBullet()
{
}

COctoBullet::~COctoBullet()
{
    Release();
}

void COctoBullet::Initialize()
{
    m_eObjType = ENEMYBULLET;

    m_vSize = { 64, 64 };
    m_fSpeed = 300.f;
    m_iAtk = 1;

    m_pCollider = new CSphereCollider(this, { 30, 30 });

    InitializeMotion();
}

int COctoBullet::Update()
{
    if (!m_bActive)
        return SCENE_NOEVENT;

    return CGameObj::Update();
}

void COctoBullet::LateUpdate()
{
    if (!m_bActive)
        return;
}

void COctoBullet::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    int     iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int     iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    m_pCollider->Render(hDC);

    m_vecMotion[0]->Render(hDC, iScrollX, iScrollY);
}

void COctoBullet::Release()
{
}

void COctoBullet::OnCollision(CObj* _pOther)
{
    OBJTYPE eTempType = _pOther->GetType();

    if (PLAYER == eTempType)
    {
        bool result = m_pCollider->AddHitted(_pOther);

        if (result)
            static_cast<CGameObj*>(_pOther)->TakeDamage(m_iAtk);
        
        CollisionGameObj();
    }
    else if (WALL == eTempType)
    {
        m_bActive = false;
        m_pCollider->SetActive(false);
    }

}

void COctoBullet::CollisionMapObj()
{
}

void COctoBullet::CollisionGameObj()
{
    m_bActive = false;
    m_pCollider->ClearHitted();
}

void COctoBullet::Shoot(VEC2 _vPos, DIRECTION _eDir)
{
    VEC2    vOffset;

    switch (_eDir)
    {
    case DOWN:
        m_vVelocity = { 0, +1 };
        vOffset = { 0, 20 };
        break;

    case UP:
        m_vVelocity = { 0, -1 };
        vOffset = { 0, -20 };
        break;

    case LEFT:
        m_vVelocity = { -1, 0 };
        vOffset = { -20, 0 };
        break;

    case RIGHT:
        m_vVelocity = { +1, 0 };
        vOffset = { +20, 0 };
        break;
    }
    
    m_vPos = _vPos + vOffset;

    m_bActive = true;
}

void COctoBullet::InitializeMotion()
{
    m_vecMotion.resize(1);

    m_vecMotion[0] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"OCTO_BULLET"));
    m_vecMotion[0]->SetPos(&m_vPos);
    m_vecMotion[0]->SetSize(m_vSize);
    m_vecMotion[0]->SetRect(&m_tRect);
    m_vecMotion[0]->ResizeFrameVec(1);
    m_vecMotion[0]->SetFrame(0, 0, 2, true);

    m_vecMotion[0]->SetMotion(0);
}
