#include "stdafx.h"
#include "KeeseBody.h"
#include "RectCollider.h"

#include "TimeMgr.h"

CKeeseBody::CKeeseBody() :
    m_fAtkTime(0), m_fAtkLength(0)
{
}

CKeeseBody::~CKeeseBody()
{
    Release();
}

void CKeeseBody::Initialize()
{
    m_eObjType = ENEMYWEAPON;

    m_bActive = false;

    m_iAtk = 1;
    m_fAtkLength = 1.f;

    m_pCollider = new CRectCollider(this, { 40, 40 });
}

int CKeeseBody::Update()
{
    if (!m_bActive)
    {
        m_pCollider->SetActive(false);
        return SCENE_NOEVENT;
    }

    m_fAtkTime += DELTA;

    m_pCollider->SetActive(true);

    //m_vPos = m_vOwnerPos;

    return CGameObj::Update();
}

void CKeeseBody::LateUpdate()
{
    if (!m_bActive)
        return;

    if (m_fAtkLength < m_fAtkTime)
    {
        m_fAtkTime -= m_fAtkLength;

        m_bActive = false;
        m_pCollider->SetActive(false);
    }
}

void CKeeseBody::Render(HDC hDC)
{
    if (!m_bActive)
        return;
     
    m_pCollider->Render(hDC);
}

void CKeeseBody::Release()
{
}

void CKeeseBody::OnCollision(CObj* _pOther)
{
    if (PLAYER == _pOther->GetType())
    {
        bool result = m_pCollider->AddHitted(_pOther);

        if(result)
            static_cast<CGameObj*>(_pOther)->TakeDamage(m_iAtk);
    }
}

void CKeeseBody::CollisionMapObj()
{
}

void CKeeseBody::CollisionGameObj()
{
}

void CKeeseBody::ClearHitted()
{
    m_pCollider->ClearHitted();
}
