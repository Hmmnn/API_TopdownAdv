#include "stdafx.h"
#include "ShieldEye.h"
#include "SphereCollider.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TimeMgr.h"

CShieldEye::CShieldEye() :
    m_eCurState(SPAWN), m_ePreState(ST_END),
    m_vOwnerPos(nullptr), m_vOffset(),
    m_bSelected(false)
{
}

CShieldEye::~CShieldEye()
{
    Release();
}

void CShieldEye::Initialize()
{
    m_eObjType = ENEMYSHIELD;

    m_bActive = false;

    m_vPos = {};
    m_vSize = {100, 100};

    m_vVelocity = { 0, 0 };

    m_iMaxHp = 2;
    m_iHp = m_iMaxHp;

    m_pCollider = new CSphereCollider(this, { 50, 50 });
    m_pCollider->SetOwner(this);

    InitializeMotion();

    m_vecMotion[0]->SetMotion(SPAWN);
}

int CShieldEye::Update()
{
    if (!m_bActive)
        return SCENE_NOEVENT;

    CheckState();

    if (m_ePreState != m_eCurState)
    {
        m_vecMotion[0]->SetMotion(m_eCurState);

        m_ePreState = m_eCurState;
    }


    m_vPos = *m_vOwnerPos + m_vOffset;

    return CGameObj::Update();
}

void CShieldEye::LateUpdate()
{
    if (!m_bActive)
        return;

    m_iAnimState = m_vecMotion[0]->RunAnimation();
}

void CShieldEye::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    int iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    m_pCollider->Render(hDC);

    m_vecMotion[0]->Render(hDC, iScrollX, iScrollY);
}

void CShieldEye::Release()
{
}

void CShieldEye::OnCollision(CObj* _pOther)
{
    if (PLAYERBULLET == _pOther->GetType())
    {
        TakeDamage(1);
        _pOther->SetActive(false);
    }
}

void CShieldEye::TakeDamage(int _iDamage)
{
    if (!m_bSelected)
    {
        m_eCurState = BLANK;
        return;
    }

    if (IDLE == m_eCurState || ANSWER == m_eCurState)
    {
        m_iHp -= _iDamage;
        m_eCurState = HIT;

        if (0 >= m_iHp)
        {
            m_iHp = 0;
            m_eCurState = DESTROYED;
        }
    }
}

void CShieldEye::Respawn()
{
    m_iHp = m_iMaxHp;
    m_eCurState = SPAWN;
    m_bSelected = false;

    m_bActive = true;
    m_pCollider->SetActive(true);
}

void CShieldEye::Destroy()
{
    m_eCurState = DESTROYED;
}

void CShieldEye::CheckState()
{
    switch (m_eCurState)
    {
    case CShieldEye::SPAWN:
        
        if (ANIM_END == m_iAnimState)
            m_eCurState = IDLE;

        break;

    case CShieldEye::IDLE:
        break;

    case CShieldEye::BLANK:
        break;

    case CShieldEye::TURNNING:
       
        if (ANIM_END == m_iAnimState)
            m_eCurState = ANSWER;

        break;

    case CShieldEye::ANSWER:
        break;

    case CShieldEye::HIT:

        if (m_bSelected)
            m_eCurState = TURNNING;
        else
            m_eCurState = BLANK;

        break;

    case CShieldEye::DESTROYED:
        
        if (ANIM_END == m_iAnimState)
        {
            m_eCurState = IDLE;
            m_bActive = false;
            m_pCollider->SetActive(false);
        }
        
        break;
    }
}

void CShieldEye::InitializeMotion()
{
    m_vecMotion.resize(1);

    m_vecMotion[0] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"SHEILDEYE"));
    m_vecMotion[0]->SetPos(&m_vPos);
    m_vecMotion[0]->SetSize(m_vSize);
    m_vecMotion[0]->SetRect(&m_tRect);
    m_vecMotion[0]->ResizeFrameVec(ST_END);
    
    m_vecMotion[0]->SetFrame(SPAWN, 0, 2, false);
    m_vecMotion[0]->SetFrame(IDLE, 0, 0, true);
    m_vecMotion[0]->SetFrame(BLANK, 0, 0, false);
    m_vecMotion[0]->SetFrame(TURNNING, 0, 6, false);
    m_vecMotion[0]->SetFrame(ANSWER, 0, 0, false);
    m_vecMotion[0]->SetFrame(HIT, 0, 3, false);
    m_vecMotion[0]->SetFrame(DESTROYED, 0, 7, false);
}
