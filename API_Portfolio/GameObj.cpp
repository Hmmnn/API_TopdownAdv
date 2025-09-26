#include "stdafx.h"
#include "GameObj.h"
#include "Collider.h"
#include "TimeMgr.h"
#include "ScrollMgr.h"

CGameObj::CGameObj() :
    m_bDead(false), m_vVelocity({0, 0}), m_fSpeed(0), 
    m_bRight(true), m_eDir(DOWN),
    m_iAnimState(ANIM_NOEVENT), 
    m_iMaxHp(0), m_iHp(0), m_iAtk(0)
{
    m_eRenderID = RENDER_GAMEOBJ;
}

CGameObj::~CGameObj()
{
    Release();
}

void CGameObj::Initialize()
{
}

int CGameObj::Update()
{
    m_vPos += m_vVelocity * m_fSpeed * DELTA;

    CObj::UpdateRect();

    return SCENE_NOEVENT;
}

void CGameObj::LateUpdate()
{
}

void CGameObj::Render(HDC hDC)
{
    int iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    Rectangle(hDC, 
        m_tRect.left + iScrollX, 
        m_tRect.top + iScrollY, 
        m_tRect.right + iScrollX, 
        m_tRect.bottom + iScrollY
    );
}

void CGameObj::Release()
{
    for_each(m_vecMotion.begin(), m_vecMotion.end(), Safe_Delete<CAnimImage*>);
    m_vecMotion.clear();

    Safe_Delete<CCollider*>(m_pCollider);
}

void CGameObj::CollisionPush(CObj* _pOther)
{
    RECT rc = m_pCollider->GetOverlap();

    int iWidth = rc.right - rc.left;
    int iHeight = rc.bottom - rc.top;

    // 상하 충돌
    if (iWidth > iHeight)
    {
        if (m_vPos.fY > _pOther->GetPos().fY)
            m_vPos.fY += rc.bottom - rc.top;

        else if (m_vPos.fY < _pOther->GetPos().fY)
            m_vPos.fY -= rc.bottom - rc.top;
    }

    // 좌우 충돌
    else if (iWidth < iHeight)
    {
        if (m_vPos.fX > _pOther->GetPos().fX)
            m_vPos.fX += rc.right - rc.left;

        else if (m_vPos.fX < _pOther->GetPos().fX)
            m_vPos.fX -= rc.right - rc.left;
    }
}

void CGameObj::HealHp(int _iValue)
{
    m_iHp += _iValue;

    if (m_iMaxHp < m_iHp)
        m_iHp = m_iMaxHp;
}
