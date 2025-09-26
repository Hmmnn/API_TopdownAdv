#include "stdafx.h"
#include "Sword.h"
#include "Skill.h"
#include "AnimImage.h"
#include "GameObj.h"
#include "SphereCollider.h"
#include "TimeMgr.h"

CSword::CSword() :
    m_fStartAngle(0), m_fAngle(0), m_fAngleSpeed(0), m_fEndAngle(0),
    m_fDist(0), m_vOwnerPos()
{
}

CSword::~CSword()
{
    Release();
}

void CSword::Initialize()
{
    m_eObjType = PLAYERWEAPON;

    m_bActive = false;

    m_fAngleSpeed = 300.f;

    m_iAtk = 5;

    m_pCollider = new CSphereCollider(this, { 40, 40 });
    m_pCollider->SetActive(false);
}

int CSword::Update()
{
    if (!m_bActive)
    {
        m_pCollider->SetActive(false);

        return SCENE_NOEVENT;
    }

    MoveAround();

    CObj::UpdateRect();

    return SCENE_NOEVENT;
}

void CSword::LateUpdate()
{
}

void CSword::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    m_pCollider->Render(hDC);
}

void CSword::Release()
{
}

void CSword::OnCollision(CObj* _pOther)
{
    if (ENEMY == _pOther->GetType() || BOSS == _pOther->GetType())
    {
        bool bResult = m_pCollider->AddHitted(_pOther);

        if (bResult)
            static_cast<CGameObj*>(_pOther)->TakeDamage(m_iAtk);
    }
}

void CSword::MoveAround()
{
    if (!m_pCollider->GetActive())
    {
        m_fAngle = m_fStartAngle;
        m_pCollider->SetActive(true);
    }

    float fTempSpeed(m_fAngleSpeed);

    if (m_fStartAngle > m_fEndAngle)
        fTempSpeed *= -1;
    
    if (20.f < fabs(m_fEndAngle - m_fAngle))
        m_fAngle += fTempSpeed * DELTA;
     
    float fRadian = m_fAngle * PI / 180.f;
    
    if (PI < fRadian)
    {
        fRadian = fRadian - 2 * PI;
    }

    m_vPos = m_vOwnerPos + VEC2(cos(fRadian), -sin(fRadian)) * m_fDist;
}

void CSword::ClearHitList()
{
    m_pCollider->ClearHitted();
}
