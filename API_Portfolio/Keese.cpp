#include "stdafx.h"
#include "Keese.h"
#include "RectCollider.h"
#include "KeeseSkill.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TimeMgr.h"
#include "SkillMgr.h"
#include "ItemMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"

CKeese::CKeese() :
    m_pTarget(nullptr), m_pSkillSlot(nullptr),
    m_ePreState(ST_END), m_eCurState(IDLE),
    m_fChaseTime(0), m_fChaseInterval(0), m_vChaseGoal(),
    m_fDefaultSpeed(0), m_fDashSpeed(0)
{
}

CKeese::~CKeese()
{
    Release();
}

void CKeese::Initialize()
{
    m_eObjType = ENEMY;

    m_vSize = { 60, 60 };
    m_fDefaultSpeed = 150.f;
    m_fSpeed = m_fDefaultSpeed;
    m_fDashSpeed = 300.f;

    m_pCollider = new CRectCollider(this, { 40, 40 });

    m_iMaxHp = 1;
    m_iHp = m_iMaxHp;

    m_fChaseInterval = 1.f;

    InitializeMotion();
    InitializeSkill();
}

int CKeese::Update()
{
    if (!m_bActive)
        return SCENE_NOEVENT;

    //if (m_bDead)
    //    return OBJ_DEAD;

    CheckState();

    if (m_ePreState != m_eCurState)
    {
        m_vecMotion[0]->SetMotion(m_eCurState);

        m_ePreState = m_eCurState;
    }

    ApplyState();

    return CGameObj::Update();
}

void CKeese::LateUpdate()
{
    if (!m_bActive)
        return;

    m_iAnimState = m_vecMotion[0]->RunAnimation();
}

void CKeese::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    int     iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int     iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    //m_pCollider->Render(hDC);

    m_vecMotion[0]->Render(hDC, iScrollX, iScrollY);

    TCHAR   szBuf[64] = L"";
    //swprintf_s(szBuf, L"HP : %d", m_iHp);

    RECT    rc{
        m_tRect.left - 50 + iScrollX,
        m_tRect.top - 20 + iScrollY,
        m_tRect.right + 50 + iScrollX,
        m_tRect.top - 5 + iScrollY
    };

    DrawText(hDC, szBuf, lstrlen(szBuf), &rc, DT_CENTER);
}

void CKeese::Release()
{
}

void CKeese::OnCollision(CObj* _pOther)
{
    OBJTYPE eTempType = _pOther->GetType();

    if (PLAYERBULLET == eTempType || PLAYERWEAPON == eTempType)
    {
        TakeDamage(static_cast<CGameObj*>(_pOther)->GetAtk());
    }
}

void CKeese::CollisionMapObj()
{
}

void CKeese::CollisionGameObj()
{
}

void CKeese::TakeDamage(int _iDamage)
{
    if (DEAD == m_eCurState)
        return;

    m_iHp -= _iDamage;
    //CEffectMgr::GetInstance()->PlayEffect(L"HIT", m_vPos + VEC2( - 10, -10));

    if (0 >= m_iHp)
    {
        m_iHp = 0;
        m_eCurState = DEAD;
       // m_vecMotion[0]->SetMotion(DEAD);
        
        CSoundMgr::Get_Instance()->PlaySound(L"Monster.wav", SOUND_EFFECT, 1.f);
    }

}

void CKeese::CheckState()
{
    switch (m_eCurState)
    {
    case CKeese::IDLE:

        CheckTargetDistance();

        break;

    case CKeese::CHASE:

        if (100.f > m_vPos.Distance(m_pTarget->GetPos()))
        {
            m_eCurState = ATTACK;
            //m_vecMotion[0]->SetMotion(IDLE);
            break;
        }
        else if (300.f < m_vPos.Distance(m_pTarget->GetPos()))
        {
            m_eCurState = IDLE;
            //m_vecMotion[0]->SetMotion(IDLE);
            break;
        }

        m_fChaseTime += DELTA;

        if (m_fChaseInterval < m_fChaseTime)
        {
            m_fChaseTime -= m_fChaseInterval;
            m_vChaseGoal = m_pTarget->GetPos();

            break;
        }

        break;

    case CKeese::ATTACK:

        if (!m_pSkillSlot->GetActivated())
        //if (ANIM_END == m_iAnimState)
        //if (!m_pSkillSlot->GetActivated() && ANIM_END == m_iAnimState)
        {
            m_eCurState = CHASE;
            //m_vecMotion[0]->SetMotion(IDLE);
        }

        break;

    case CKeese::DEAD:

        m_bDead = true;

        break;
    }
}

void CKeese::ApplyState()
{
    switch (m_eCurState)
    {
    case CKeese::IDLE:

        m_vVelocity = { 0, 0 };

        break;

    case CKeese::CHASE:

        Chase();

        break;

    case CKeese::ATTACK:

        if (ANIM_ACTION == m_iAnimState)
        {
            if(!m_pSkillSlot->GetActivated())
                m_pSkillSlot->ActivateSkill();

            m_pSkillSlot->ExecuteSkill();
        }

        else if (ANIM_ACTEND == m_iAnimState)
        {
            m_pSkillSlot->DeactivateSkill();
        }

        break;

    case CKeese::DEAD:
        m_vVelocity = { 0, 0 };
        if (m_bDead && ANIM_END == m_iAnimState)
        {
            m_bActive = false;

            CItemMgr::GetInstance()->SpawnRandomItem(m_vPos);
        }

        break;
    }
}

void CKeese::CheckTargetDistance()
{
    float fDist = m_vPos.Distance(m_pTarget->GetPos());

    if (400.f < fDist)
    {
        m_eCurState = IDLE;
        //m_vecMotion[0]->SetMotion(IDLE);
    }

    else if (400.f >= fDist)
    {
        m_eCurState = CHASE;
        //m_vecMotion[0]->SetMotion(IDLE);
    }

}

void CKeese::Chase()
{
    VEC2    vDelta = m_pTarget->GetPos() - m_vPos;

    if (50.f < vDelta.Length())
    {
        m_vVelocity = vDelta.Normalized();
    }
    else
    {
        m_vVelocity = { 0, 0 };
        m_eCurState = ATTACK;
    }
}

void CKeese::InitializeMotion()
{
    m_vecMotion.resize(1);

    m_vecMotion[0] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"KEESE"));
    m_vecMotion[0]->SetPos(&m_vPos);
    m_vecMotion[0]->SetSize(m_vSize);
    m_vecMotion[0]->SetRect(&m_tRect);
    m_vecMotion[0]->ResizeFrameVec(ST_END);
    m_vecMotion[0]->SetFrame(IDLE, 0, 5, true);
    m_vecMotion[0]->SetFrame(CHASE, 0, 0, 5, true);
    m_vecMotion[0]->SetFrame(ATTACK, 0, 0, 5, false);
    m_vecMotion[0]->SetActionFrame(ATTACK, 2, 4);
    m_vecMotion[0]->SetFrame(DEAD, 1, 0, 12, false);

    m_vecMotion[0]->SetMotion(IDLE);
}

void CKeese::InitializeSkill()
{
    m_pSkillSlot = CSkillMgr::GetInstance()->FindSkill(L"KEESE_ATK");

    if (!m_pSkillSlot)
    {
        m_pSkillSlot = new CKeeseSkill;
        m_pSkillSlot->Initialize();
        m_pSkillSlot->SetMotionIndex((int)ATTACK);
        m_pSkillSlot->SetOwner(this);
        CSkillMgr::GetInstance()->AddSkill(L"KEESE_ATK", m_pSkillSlot);
    }
}
