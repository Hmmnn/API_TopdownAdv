#include "stdafx.h"
#include "RopeHead.h"
#include "SphereCollider.h"

#include "ScrollMgr.h"

CRopeHead::CRopeHead() :
    m_vOffset()
{
}

CRopeHead::~CRopeHead()
{
    Release();
}

void CRopeHead::Initialize()
{
    m_eObjType = ENEMYWEAPON;

    m_pCollider = new CSphereCollider(this, { 30, 30 });
}

int CRopeHead::Update()
{
    if (!m_bActive)
        return SCENE_NOEVENT;

    CObj::UpdateRect();

    return SCENE_NOEVENT;
}

void CRopeHead::LateUpdate()
{
}

void CRopeHead::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    int     iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int     iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    m_pCollider->Render(hDC);
}

void CRopeHead::Release()
{
}

void CRopeHead::OnCollision(CObj* _pOther)
{
    if (PLAYER == _pOther->GetType())
    {
        bool result = m_pCollider->AddHitted(_pOther);

        if (result)
            static_cast<CGameObj*>(_pOther)->TakeDamage(m_iAtk);
    }
}

void CRopeHead::ClearHitted()
{
    m_pCollider->ClearHitted();
}

void CRopeHead::SetDirOffset(VEC2 _vPos, DIRECTION _eDir)
{
    VEC2    vOffset{};

    switch (_eDir)
    {
    case DOWN:
        vOffset = { 0, +20 };
        break;

    case UP:
        vOffset = { 0, -20 };
        break;

    case LEFT:
        vOffset = { -20, 0 };
        break;

    case RIGHT:
        vOffset = { +20, 0 };
        break;
    }

    m_vPos = _vPos + vOffset;

    CObj::UpdateRect();
}
