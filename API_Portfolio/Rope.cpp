#include "stdafx.h"
#include "Rope.h"
#include "RectCollider.h"
#include "RopeSkill.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SkillMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"
#include "ItemMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"

CRope::CRope() :
    m_pTarget(nullptr),
    m_ePreState(ST_END), m_eCurState(IDLE),
    m_fAtkTime(0), m_fAtkInterval(0),
    m_fHitTime(0), m_fHitInterval(0),
    m_fChaseTime(0), m_fChaseInterval(0), m_vChaseGoal(),
    m_pSkillSlot(nullptr), m_vPatrolStartPos(), m_fPatrolRange(0)
{
}

CRope::~CRope()
{
    Release();
}

void CRope::Initialize()
{
    m_eObjType = ENEMY;

    m_vSize = { 100, 100 };
    m_fSpeed = 50.f;

    m_vVelocity = { -1, 0 };

    m_pCollider = new CRectCollider(this, { 40, 40 });
    //m_pCollider->SetOffset({ 0, 20 });
    m_pCollider->SetActive(true);

    m_fAtkInterval = 3.f;
    m_fHitInterval = 1.5f;
    m_fChaseInterval = 2.f;

    m_iMaxHp = 10;
    m_iHp = m_iMaxHp;
    m_iAtk = 3;

    m_fPatrolRange = 150.f;

    InitializeMotion();
    InitializeSkill();
}

int CRope::Update()
{
    if (!m_bActive)
    {
        m_pCollider->SetActive(false);
        return SCENE_NOEVENT;
    }

    //if (m_bDead)
    //    return OBJ_DEAD;

    CheckState();

    if (m_ePreState != m_eCurState)
    {
        m_vecMotion[m_eDir]->SetMotion(m_eCurState);

        m_ePreState = m_eCurState;
    }

    ApplyState();


    return CGameObj::Update();
}

void CRope::LateUpdate()
{
    if (!m_bActive)
        return;

    m_iAnimState = m_vecMotion[m_eDir]->RunAnimation();
}

void CRope::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    int     iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int     iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    m_pCollider->Render(hDC);

    m_vecMotion[m_eDir]->Render(hDC, iScrollX, iScrollY);

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

void CRope::Release()
{
}

void CRope::OnCollision(CObj* _pOther)
{
    OBJTYPE eTempType = _pOther->GetType();

    if (PLAYERBULLET == eTempType || PLAYERWEAPON == eTempType)
    {
        m_pTarget = CObjMgr::GetInstance()->GetBack(PLAYER);
        m_vChaseGoal = m_pTarget->GetPos();
    }

    if (WALL == eTempType || MAPOBJ == eTempType)
    {
        CollisionPush(_pOther);
    }
}

void CRope::CollisionMapObj()
{
}

void CRope::CollisionGameObj()
{
}

void CRope::CollisionPush(CObj* _pOther)
{
    RECT rc = m_pCollider->GetOverlap();

    int iWidth = rc.right - rc.left;
    int iHeight = rc.bottom - rc.top;

    // 상하 충돌
    if (iWidth > iHeight)
    {
        if (m_vPos.fY > _pOther->GetPos().fY)
        {
            m_vPos.fY += rc.bottom - rc.top;
            m_vVelocity = { 0, +1 };
        }
        else if (m_vPos.fY < _pOther->GetPos().fY)
        {
            m_vPos.fY -= rc.bottom - rc.top;
            m_vVelocity = { 0, -1 };
        }
    }

    // 좌우 충돌
    else if (iWidth < iHeight)
    {
        if (m_vPos.fX > _pOther->GetPos().fX)
        {
            m_vPos.fX += rc.right - rc.left;
            m_vVelocity = { 0, +1 };
        }
        else if (m_vPos.fX < _pOther->GetPos().fX)
        {
            m_vPos.fX -= rc.right - rc.left;
            m_vVelocity = { 0, -1 };
        }
    }

    m_vPatrolStartPos = m_vPos;
}

void CRope::TakeDamage(int _iDamage)
{
    if (HIT == m_eCurState || DEAD == m_eCurState)
        return;

    m_iHp -= _iDamage;

    //CEffectMgr::GetInstance()->PlayEffect(L"HIT", m_vPos + VEC2(-5, -20));

    if (0 >= m_iHp)
    {
        m_iHp = 0;
        m_eCurState = DEAD;
        m_vecMotion[m_eDir]->SetMotion(DEAD);

        CSoundMgr::Get_Instance()->PlaySound(L"Monster.wav", SOUND_EFFECT, 1.f);
    }
}

void CRope::CheckState()
{
    switch (m_eCurState)
    {
    case CRope::IDLE:
        
        CheckTargetDistance();

        break;

    case CRope::PATROL:

        if (m_iMaxHp != m_iHp)
        {
            m_eCurState = CHASE;
            m_vecMotion[m_eDir]->SetMotion(CHASE);
        }

        break;

    case CRope::CHASE:

        if (100.f > m_vPos.Distance(m_pTarget->GetPos()))
        {
            m_eCurState = ATTACK;
            m_vecMotion[m_eDir]->SetMotion(ATTACK);
            break;
        }

        m_fChaseTime += DELTA;

        if (m_fChaseInterval < m_fChaseTime)
        {
            m_fChaseTime -= m_fChaseInterval;

            m_vChaseGoal = m_pTarget->GetPos();
        }

        break;

    case CRope::ATTACK:
        
        if (ANIM_END == m_iAnimState && !m_pSkillSlot->GetActivated())
        {
            m_eCurState = IDLE;
            m_vecMotion[m_eDir]->SetMotion(IDLE);
        }
        
        break;

    case CRope::HIT:

        if (ANIM_END == m_iAnimState)
        {
            //m_eCurState = IDLE;
            //m_vecMotion[m_eDir]->SetMotion(IDLE);
            m_eCurState = CHASE;

        }

        break;

    case CRope::DEAD:
        
        m_bDead = true;

        break;
    }
}

void CRope::ApplyState()
{
    switch (m_eCurState)
    {
    case CRope::IDLE:
        break;

    case CRope::PATROL:
        
        Patrol();
        
        break;

    case CRope::CHASE:
        
        Chase();

        break;

    case CRope::ATTACK:
        
        if(!m_pSkillSlot->GetActivated())
            m_pSkillSlot->ActivateSkill();

        if (ANIM_ACTION == m_iAnimState)
        {    
            m_pSkillSlot->ExecuteSkill();
        }
        else if (ANIM_ACTEND == m_iAnimState)
        {
            m_pSkillSlot->DeactivateSkill();
        }

        break;

    case CRope::HIT:

        m_vVelocity = { 0,0 };

        break;

    case CRope::DEAD:
        m_vVelocity = { 0, 0 };

        if (m_bDead && ANIM_END == m_iAnimState)
        {
            m_bActive = false;
            CItemMgr::GetInstance()->SpawnRandomItem(m_vPos);
        }

        break;
    }

    if (VEC2(+1, 0) == m_vVelocity)
        m_eDir = RIGHT;

    else if (VEC2(-1, 0) == m_vVelocity)
        m_eDir = LEFT;

    else if (VEC2(0, +1) == m_vVelocity)
        m_eDir = DOWN;

    else if(VEC2(0, -1) == m_vVelocity)
        m_eDir = UP;
}

void CRope::CheckTargetDistance()
{
    float fDist = m_vPos.Distance(m_pTarget->GetPos());

    if (400.f < fDist)
    {
        m_eCurState = IDLE;
        m_vecMotion[m_eDir]->SetMotion(IDLE);
    }
    
    else if (400.f >= fDist)
    {
        m_eCurState = PATROL;
        m_vPatrolStartPos = m_vPos;

        m_vecMotion[m_eDir]->SetMotion(PATROL);
    }
}

void CRope::Patrol()
{
    VEC2    vLeft = { m_vPatrolStartPos.fX - m_fPatrolRange, m_vPatrolStartPos.fY };
    VEC2    vRight = { m_vPatrolStartPos.fX + m_fPatrolRange, m_vPatrolStartPos.fY };

    if (30.f > m_vPos.Distance(vLeft) && LEFT == m_eDir)
    {
        m_vVelocity *= -1;
        m_eDir = RIGHT;
        m_vecMotion[m_eDir]->SetMotion(m_eCurState);
    }
    else if (30.f > m_vPos.Distance(vRight) && RIGHT == m_eDir)
    {
        m_vVelocity *= -1;
        m_eDir = LEFT;
        m_vecMotion[m_eDir]->SetMotion(m_eCurState);
    }
}

void CRope::Chase()
{
    VEC2    vDeltaPos = m_vChaseGoal - m_vPos;

    if (50.f < vDeltaPos.Length())
    {
        int     iRandom = rand() % 2;

        if (10.f > fabs(m_vChaseGoal.fX - m_vPos.fX))
        {
            if (m_vChaseGoal.fY > m_vPos.fY)
                m_vVelocity = { 0, +1 };
            else if (m_vChaseGoal.fY < m_vPos.fY)
                m_vVelocity = { 0, -1 };
        }
        else// if (10.f > fabs(m_vChaseGoal.fY - m_vPos.fY))
        {
            if (m_vChaseGoal.fX > m_vPos.fX)
                m_vVelocity = { +1, 0 };
            else if (m_vChaseGoal.fX < m_vPos.fX)
                m_vVelocity = { -1, 0 };
        }

    }
    else
        m_eCurState = ATTACK;

}

void CRope::InitializeMotion()
{
    m_vecMotion.resize(4);

    m_vecMotion[DOWN] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"ROPE_DOWN"));
    m_vecMotion[DOWN]->ResizeFrameVec(ST_END);
    m_vecMotion[DOWN]->SetPos(&m_vPos);
    m_vecMotion[DOWN]->SetSize(m_vSize);
    m_vecMotion[DOWN]->SetRect(&m_tRect);
    m_vecMotion[DOWN]->SetFrame(IDLE, 0, 3, true, 1.f / 10.f);
    m_vecMotion[DOWN]->SetFrame(PATROL, 0, 0, 3, true, 1.f / 10.f);
    m_vecMotion[DOWN]->SetFrame(CHASE, 0, 0, 3, true);
    m_vecMotion[DOWN]->SetFrame(ATTACK, 0, 0, 3, false);
    m_vecMotion[DOWN]->SetActionFrame(ATTACK, 1, 3);
    m_vecMotion[DOWN]->SetFrame(HIT, 1, 0, 3, false);
    m_vecMotion[DOWN]->SetFrame(DEAD, 2, 0, 12, false);

    m_vecMotion[UP] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"ROPE_UP"));
    m_vecMotion[UP]->ResizeFrameVec(ST_END);
    m_vecMotion[UP]->SetPos(&m_vPos);
    m_vecMotion[UP]->SetSize(m_vSize);
    m_vecMotion[UP]->SetRect(&m_tRect);
    m_vecMotion[UP]->SetFrame(IDLE, 0, 3, true, 1.f / 10.f);
    m_vecMotion[UP]->SetFrame(PATROL, 0, 0, 3, true, 1.f / 10.f);
    m_vecMotion[UP]->SetFrame(CHASE, 0, 0, 3, true);
    m_vecMotion[UP]->SetFrame(ATTACK, 0, 0, 3, false);
    m_vecMotion[UP]->SetActionFrame(ATTACK, 1, 3);
    m_vecMotion[UP]->SetFrame(HIT, 1, 0, 3, false);
    m_vecMotion[UP]->SetFrame(DEAD, 2, 0, 12, false);

    m_vecMotion[LEFT] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"ROPE_LEFT"));
    m_vecMotion[LEFT]->ResizeFrameVec(ST_END);
    m_vecMotion[LEFT]->SetPos(&m_vPos);
    m_vecMotion[LEFT]->SetSize(m_vSize);
    m_vecMotion[LEFT]->SetRect(&m_tRect);
    m_vecMotion[LEFT]->SetFrame(IDLE, 0, 3, true, 1.f / 10.f);
    m_vecMotion[LEFT]->SetFrame(PATROL, 0, 0, 3, true, 1.f / 10.f);
    m_vecMotion[LEFT]->SetFrame(CHASE, 0, 0, 3, true);
    m_vecMotion[LEFT]->SetFrame(ATTACK, 0, 0, 3, false);
    m_vecMotion[LEFT]->SetActionFrame(ATTACK, 1, 3);
    m_vecMotion[LEFT]->SetFrame(HIT, 1, 0, 3, false);
    m_vecMotion[LEFT]->SetFrame(DEAD, 2, 0, 12, false);

    m_vecMotion[RIGHT] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"ROPE_RIGHT"));
    m_vecMotion[RIGHT]->ResizeFrameVec(ST_END);
    m_vecMotion[RIGHT]->SetPos(&m_vPos);
    m_vecMotion[RIGHT]->SetSize(m_vSize);
    m_vecMotion[RIGHT]->SetRect(&m_tRect);
    m_vecMotion[RIGHT]->SetFrame(IDLE, 0, 3, true, 1.f / 10.f);
    m_vecMotion[RIGHT]->SetFrame(PATROL, 0, 0, 3, true, 1.f / 10.f);
    m_vecMotion[RIGHT]->SetFrame(CHASE, 0, 0, 3, true);
    m_vecMotion[RIGHT]->SetFrame(ATTACK, 0, 0, 3, false);
    m_vecMotion[RIGHT]->SetActionFrame(ATTACK, 1, 3);
    m_vecMotion[RIGHT]->SetFrame(HIT, 1, 0, 3, false);
    m_vecMotion[RIGHT]->SetFrame(DEAD, 2, 0, 12, false);
}

void CRope::InitializeSkill()
{
    m_pSkillSlot = CSkillMgr::GetInstance()->FindSkill(L"ROPE_ATK");

    if (!m_pSkillSlot)
    {
        m_pSkillSlot = new CRopeSkill;
        m_pSkillSlot->Initialize();
        m_pSkillSlot->SetMotionIndex((int)ATTACK);
        m_pSkillSlot->SetOwner(this);
        CSkillMgr::GetInstance()->AddSkill(L"ROPE_ATK", m_pSkillSlot);
    }
}
