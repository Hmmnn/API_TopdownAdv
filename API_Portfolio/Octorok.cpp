#include "stdafx.h"
#include "Octorok.h"
#include "RectCollider.h"
#include "OctoAttack.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SkillMgr.h"
#include "TimeMgr.h"
#include "ItemMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"

COctorok::COctorok() :
    m_ePreState(ST_END), m_eCurState(IDLE),
    m_fAtkTime(0), m_fAtkInterval(0),
    m_fHitTime(0), m_fHitInterval(0),
    m_pTarget(nullptr), m_pSkillSlot(nullptr)
{
}

COctorok::~COctorok()
{
    Release();
}

void COctorok::Initialize()
{
    m_eObjType = ENEMY;

    m_vSize = { 100, 100 };

    m_pCollider = new CRectCollider(this, { 40, 40 });
    m_pCollider->SetActive(true);

    m_fAtkInterval = 3.f;
    m_fHitInterval = 1.5f;

    m_iMaxHp = 10;
    m_iHp = m_iMaxHp;

    InitializeMotion();
    InitializeSkill();
}

int COctorok::Update()
{
    if (!m_bActive)
        return SCENE_NOEVENT;

    //if (m_bDead)
    //    return OBJ_DEAD;
    
    ApplyState();

    return CGameObj::Update();
}

void COctorok::LateUpdate()
{
    if (!m_bActive)
        return;

    CheckState();

    if (m_ePreState != m_eCurState)
    {
        m_vecMotion[m_eDir]->SetMotion(m_eCurState);

        m_ePreState = m_eCurState;
    }

    m_iAnimState = m_vecMotion[m_eDir]->RunAnimation();
}

void COctorok::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    int     iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int     iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    m_pCollider->Render(hDC);

    m_vecMotion[m_eDir]->Render(hDC, iScrollX, iScrollY);

    TCHAR   szBuf[64] = L"";
   // swprintf_s(szBuf, L"HP : %d", m_iHp);

    RECT    rc{
        m_tRect.left - 50 + iScrollX,
        m_tRect.top - 20 + iScrollY,
        m_tRect.right + 50 + iScrollX,
        m_tRect.top - 5 + iScrollY
    };

    DrawText(hDC, szBuf, lstrlen(szBuf), &rc, DT_CENTER);
}

void COctorok::Release()
{
}

void COctorok::OnCollision(CObj* _pOther)
{
    OBJTYPE eTempType = _pOther->GetType();

    //if (PLAYERBULLET == eTempType || PLAYERWEAPON == eTempType)
    //{
    //    TakeDamage(static_cast<CGameObj*>(_pOther)->GetAtk());
    //}
    

}

void COctorok::CollisionMapObj()
{
}

void COctorok::CollisionGameObj()
{
}

void COctorok::TakeDamage(int _iDamage)
{
    if (HIT == m_eCurState || DEAD == m_eCurState)
        return;

    m_iHp -= _iDamage;
    //CEffectMgr::GetInstance()->PlayEffect(L"HIT", m_vPos + VEC2(-10, -10));

    if (0 >= m_iHp)
    {
        m_iHp = 0;
        m_eCurState = DEAD;

        CSoundMgr::Get_Instance()->PlaySound(L"Monster.wav", SOUND_EFFECT, 1.f);
    }

}

void COctorok::CheckState()
{
    // 상태 전이는 LateUpdate 상태 이행은 Update에서 해야 함
    
    switch (m_eCurState)
    {
    case COctorok::IDLE:
        
        CheckTargetDistance();

        break;

    case COctorok::ATTACK:
        
        if (ANIM_END == m_iAnimState || ANIM_ACTEND == m_iAnimState)
        {
            m_eCurState = IDLE;
            break;
        }

        //m_fAtkTime += DELTA;
        //
        //if (m_fAtkInterval < m_fAtkTime)
        //{
        //    m_fAtkTime -= m_fAtkInterval;
        //}
        //else
        //{
        //    m_eCurState = IDLE;
        //}
        
        break;

    case COctorok::HIT:

        if (ANIM_END == m_iAnimState)
        {
            m_eCurState = IDLE;
        }

        m_fHitTime += DELTA;

        if (m_fHitInterval > m_fHitTime)
            break;

        m_fHitTime -= m_fHitInterval;

        m_vVelocity = { 0, 0 };

        m_eCurState = IDLE;        

        break;

    case COctorok::DEAD:
        m_bDead = true;

        break;
    }
}

void COctorok::CheckTargetDistance()
{
    float fTargetDist = m_vPos.Distance(m_pTarget->GetPos());

    if (500.f < fTargetDist)
    {
        m_eCurState = IDLE;
    }
    else if (500.f > fTargetDist)
    {
        m_fAtkTime += DELTA;

        if (m_fAtkInterval < m_fAtkTime)
        {
            m_fAtkTime -= m_fAtkInterval;
            
            m_eCurState = ATTACK;
        }
        else
        {
            m_eCurState = IDLE;
        }
    }
}

void COctorok::ApplyState()
{
    switch (m_eCurState)
    {
    case COctorok::IDLE:
        break;

    case COctorok::ATTACK:

        m_vVelocity = { 0, 0 };

        if (ANIM_ACTION == m_iAnimState)
        {
            m_pSkillSlot->ActivateSkill();
            m_pSkillSlot->ExecuteSkill();
        }
        else if (ANIM_ACTEND == m_iAnimState)
        {
            m_pSkillSlot->DeactivateSkill();
        }

        break;

    case COctorok::HIT:
        break;

    case COctorok::DEAD:
        m_vVelocity = { 0, 0 };

        if (m_bDead && ANIM_END == m_iAnimState)
        {
            m_bActive = false;
            CItemMgr::GetInstance()->SpawnRandomItem(m_vPos);
        }

        break;
    }
}

void COctorok::InitializeMotion()
{
    m_vecMotion.resize(4);

    m_vecMotion[DOWN] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"OCTO_DOWN"));
    m_vecMotion[DOWN]->SetPos(&m_vPos);
    m_vecMotion[DOWN]->SetSize(m_vSize);
    m_vecMotion[DOWN]->SetRect(&m_tRect);
    m_vecMotion[DOWN]->ResizeFrameVec(4);
    m_vecMotion[DOWN]->SetFrame(IDLE, 0, 1, true, 1.f / 10.f);
    m_vecMotion[DOWN]->SetFrame(ATTACK, 0, 3, true);
    m_vecMotion[DOWN]->SetActionFrame(ATTACK, 2, 3);
    m_vecMotion[DOWN]->SetFrame(HIT, 0, 1, false);
    m_vecMotion[DOWN]->SetFrame(DEAD, 0, 12, false);

    m_vecMotion[UP] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"OCTO_UP"));
    m_vecMotion[UP]->SetPos(&m_vPos);
    m_vecMotion[UP]->SetSize(m_vSize);
    m_vecMotion[UP]->SetRect(&m_tRect);
    m_vecMotion[UP]->ResizeFrameVec(4);
    m_vecMotion[UP]->SetFrame(IDLE, 0, 1, true, 1.f / 10.f);
    m_vecMotion[UP]->SetFrame(ATTACK, 0, 3, true);
    m_vecMotion[UP]->SetActionFrame(ATTACK, 2, 3);
    m_vecMotion[UP]->SetFrame(HIT, 0, 1, false);
    m_vecMotion[UP]->SetFrame(DEAD, 0, 12, false);

    m_vecMotion[LEFT] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"OCTO_LEFT"));
    m_vecMotion[LEFT]->SetPos(&m_vPos);
    m_vecMotion[LEFT]->SetSize(m_vSize);
    m_vecMotion[LEFT]->SetRect(&m_tRect);
    m_vecMotion[LEFT]->ResizeFrameVec(4);
    m_vecMotion[LEFT]->SetFrame(IDLE, 0, 1, true, 1.f / 10.f);
    m_vecMotion[LEFT]->SetFrame(ATTACK, 0, 3, true);
    m_vecMotion[LEFT]->SetActionFrame(ATTACK, 2, 3);
    m_vecMotion[LEFT]->SetFrame(HIT, 0, 1, false);
    m_vecMotion[LEFT]->SetFrame(DEAD, 0, 12, false);

    m_vecMotion[RIGHT] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"OCTO_RIGHT"));
    m_vecMotion[RIGHT]->SetPos(&m_vPos);
    m_vecMotion[RIGHT]->SetSize(m_vSize);
    m_vecMotion[RIGHT]->SetRect(&m_tRect);
    m_vecMotion[RIGHT]->ResizeFrameVec(4);
    m_vecMotion[RIGHT]->SetFrame(IDLE, 0, 1, true, 1.f / 10.f);
    m_vecMotion[RIGHT]->SetFrame(ATTACK, 0, 3, true);
    m_vecMotion[RIGHT]->SetActionFrame(ATTACK, 2, 3);
    m_vecMotion[RIGHT]->SetFrame(HIT, 0, 1, false);
    m_vecMotion[RIGHT]->SetFrame(DEAD, 0, 12, false);
}

void COctorok::InitializeSkill()
{
    m_pSkillSlot = CSkillMgr::GetInstance()->FindSkill(L"OCTO_ATK");

    if (!m_pSkillSlot)
    {
        m_pSkillSlot = new COctoAttack;
        m_pSkillSlot->Initialize();
        m_pSkillSlot->SetMotionIndex((int)ATTACK);
        m_pSkillSlot->SetOwner(this);
        CSkillMgr::GetInstance()->AddSkill(L"OCTO_ATK", m_pSkillSlot);
    }
}
