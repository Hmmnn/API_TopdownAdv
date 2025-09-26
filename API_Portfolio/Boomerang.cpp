#include "stdafx.h"
#include "Boomerang.h"
#include "SphereCollider.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TimeMgr.h"

CBoomerang::CBoomerang() :
    m_pOwner(nullptr), m_fRange(0), m_pTarget(nullptr),
    m_bReturning(false)
{
}

CBoomerang::~CBoomerang()
{
    Release();
}

void CBoomerang::Initialize()
{
    m_eObjType = PLAYERWEAPON;

    m_bActive = false;

    m_vSize = { 48, 48 };

    m_fSpeed = 300.f;
    m_iAtk = 3;

    m_fRange = 400.f;
    
    m_pCollider = new CSphereCollider(this, { 30, 30 });

    InitializeMotion();
}

int CBoomerang::Update()
{
    if (!m_bActive)
        return SCENE_NOEVENT;

    ReturnToOwner();

    //m_vPos.fX = LERP(m_vPos.fX, m_vPeak.fX, m_fSpeed * DELTA);
    //m_vPos.fY = LERP(m_vPos.fY, m_vPeak.fY, m_fSpeed * DELTA);
    //
    //CGameObj::UpdateRect();
    
    return CGameObj::Update();

    return SCENE_NOEVENT;
}

void CBoomerang::LateUpdate()
{
    if (!m_bActive)
        return;

    m_vecMotion[0]->RunAnimation();
}

void CBoomerang::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    int     iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int     iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    m_pCollider->Render(hDC);

    m_vecMotion[0]->Render(hDC, iScrollX, iScrollY);
}

void CBoomerang::Release()
{
}

void CBoomerang::OnCollision(CObj* _pOther)
{
    // 아이템과 충돌했을 경우 부메랑 위치로 설정
    // 적과 충돌했을 경우 대미지

    OBJTYPE TempType = _pOther->GetType();

    //if (PLAYER == TempType)
    //{
    //    m_bActive = false;
    //    m_bReturning = false;
    //    m_vVelocity = { 0, 0 };
    //    m_vPos = _pOther->GetPos();
    //    m_pCollider->ClearHitted();
    //}

    if (ENEMY == TempType || BOSS == TempType)
    {
        auto result = m_pCollider->AddHitted(_pOther);

        if (result)
            static_cast<CGameObj*>(_pOther)->TakeDamage(m_iAtk);
    }
}

void CBoomerang::CollisionMapObj()
{
}

void CBoomerang::CollisionGameObj()
{
}

void CBoomerang::ThrowBoomerang(VEC2 _vVelocity)
{
    m_vVelocity = _vVelocity;
    m_vPos = m_pOwner->GetPos();
    m_vPeak = m_pOwner->GetPos() + (_vVelocity * m_fRange);
}

void CBoomerang::ClearHitted()
{
    m_pCollider->ClearHitted();
}

void CBoomerang::ReturnToOwner()
{
    if (!m_bReturning && 10.f > m_vPos.Distance(m_vPeak))
    {
        m_bReturning = true;
        m_pCollider->ClearHitted();
    }
    
    if (m_bReturning)
    {
        m_vVelocity = (m_pOwner->GetPos() - m_vPos).Normalized();

        if (10.f > m_vPos.Distance(m_pOwner->GetPos()))
        {
            m_bActive = false;
            m_bReturning = false;
            m_vVelocity = { 0, 0 };
            m_pCollider->ClearHitted();
        }
    }
}

void CBoomerang::InitializeMotion()
{
    m_vecMotion.resize(1);

    m_vecMotion[0] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"BOOMERANG"));
    m_vecMotion[0]->SetPos(&m_vPos);
    m_vecMotion[0]->SetRect(&m_tRect);
    m_vecMotion[0]->SetSize(m_vSize);
    m_vecMotion[0]->ResizeFrameVec(1);
    m_vecMotion[0]->SetFrame(0, 0, 3, true);

    m_vecMotion[0]->SetMotion(0);
}
