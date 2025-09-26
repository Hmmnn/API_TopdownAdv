#include "stdafx.h"
#include "Phase2Boss.h"
#include "SphereCollider.h"
#include "FallingStone.h"
#include "ShieldEye.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "KeyMgr.h"

CPhase2Boss::CPhase2Boss() :
    m_eCurState(BOSS_STATE::IDLE), m_ePreState(BOSS_STATE::ST_END), m_pTarget(nullptr), 
    m_fHitTime(0), m_fHitInterval(0), m_fTestTime(0), m_bTransforming(false),
    m_tEyeOffset(), m_fChaseTime(0), m_fChaseInterval(0),
    m_fAttackTime1(0), m_fAttackInterval1(0), 
    m_fAttackTime2(0), m_fAttackInterval2(0),
    m_pTraps(nullptr)
{
}

CPhase2Boss::~CPhase2Boss()
{
    Release();
}

void CPhase2Boss::Initialize()
{
    m_eObjType = BOSS;

    m_vPos = { 608, 448 };
    m_vSize = { 250, 250 };

    m_bActive = false;
    m_bDead = false;
    m_fSpeed = 100.f;
    m_iMaxHp = 30;
    m_iHp = m_iMaxHp;
    m_iAtk = 4;

    m_vVelocity = { 0, 0 };

    m_iAnimState = ANIM_NOEVENT;

    m_fHitInterval = 0.5f;
    m_fChaseInterval = 3.0f;
    m_fAttackInterval1 = 5.f;
    m_fAttackInterval2 = 0.5f;

    m_pCollider = new CSphereCollider(this, {120, 120});
    m_pTarget = CObjMgr::GetInstance()->GetBack(PLAYER);

    m_tEyeOffset = { 30, 70 };

    InitializeMotion();
    InitializePatternObj();

    m_eCurState = TRANSFORM;
}

int CPhase2Boss::Update()
{
    if (m_bDead)
    {
        m_bActive = false;
        
        for (auto& iter : m_vecEye)
            iter->SetActive(false);

        return SCENE_NOEVENT;
    }

    if (!m_bActive)
        return SCENE_NOEVENT;

    if (KEY_DOWN(VK_F3))
        TakeDamage(2);

    CheckState();

    if (m_ePreState != m_eCurState)
    {
        ChangeMotion();
    
        m_ePreState = m_eCurState;
    }


    return CGameObj::Update();
}

void CPhase2Boss::LateUpdate()
{
    if (!m_bActive)
        return;  

    m_iAnimState = m_vecMotion[0]->RunAnimation();
}

void CPhase2Boss::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    int     iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int     iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    m_pCollider->Render(hDC);

    m_vecMotion[0]->Render(hDC, iScrollX, iScrollY);

    //TCHAR   szBuf[64] = L"";
    //swprintf_s(szBuf, L"HP : %d", m_iHp);
    //
    //RECT    rc{
    //    m_tRect.left - 50 + iScrollX,
    //    m_tRect.top - 20 + iScrollY,
    //    m_tRect.right + 50 + iScrollX,
    //    m_tRect.top - 5 + iScrollY
    //};
    //
    //DrawText(hDC, szBuf, lstrlen(szBuf), &rc, DT_CENTER);
}

void CPhase2Boss::Release()
{
}

void CPhase2Boss::CollisionMapObj()
{
}

void CPhase2Boss::CollisionGameObj()
{
}

void CPhase2Boss::TakeDamage(int _iDamage)
{
    if (GROGGY != m_eCurState)
        return;

    m_iHp -= _iDamage;
    m_eCurState = HIT;
    ChangeMotion();

    if (0 >= m_iHp)
    {
        m_iHp = 0;
        m_eCurState = DEAD;
    }
}

void CPhase2Boss::CheckState()
{
    if (0 >= m_iHp)
        m_eCurState = DEAD;

    if (CheckEyes())
    {
        m_eCurState = GROGGY;
    }

    switch (m_eCurState)
    {
    case CPhase2Boss::TRANSFORM:

        if (!m_bTransforming)
        {
            m_bTransforming = true;
        }
        else
        {
            if (ANIM_END == m_iAnimState)
            {
                m_eCurState = IDLE;

                for (auto& iter : m_vecEye)
                    static_cast<CShieldEye*>(iter)->Respawn();

                SelectEyes();

            }
        }
        break;

    case CPhase2Boss::IDLE:

        m_eCurState = CHASE;

        break;

    case CPhase2Boss::CHASE:

        m_fChaseTime += DELTA;

        if (m_fChaseInterval < m_fChaseTime)
        {
            m_fChaseTime -= m_fChaseInterval;

            if (m_iMaxHp * 0.75f < (float)m_iHp)
            {
                m_vVelocity = (m_pTarget->GetPos() - m_vPos).Normalized();
            }

            else if (m_iMaxHp * 0.75f >= (float)m_iHp && m_iMaxHp * 0.5f < (float)m_iHp)
            {
                m_eCurState = ATTACK1;
            }

            else if (m_iMaxHp * 0.5f >= (float)m_iHp)
            {
                m_eCurState = ATTACK2;
            }

            break;
        }

        break;

    case CPhase2Boss::ATTACK1:
        m_fAttackTime1 += DELTA;
        //m_fAttackTime2 += DELTA;

        if (m_fAttackInterval1 < m_fAttackTime1)
        {
            m_fAttackTime1 -= m_fAttackInterval1;

            for (auto& iter : *m_pTraps)
            {
                VEC2 tempPos = {
                    (float)(rand() % 850 + 150),
                    (float)(rand() % 550 + 150)
                };
                iter->SetPos(tempPos.fX, tempPos.fY);
                iter->SetActive(true);
            }

        }
        else
        {
            m_eCurState = ATTACK2;
        }

        break;

    case CPhase2Boss::ATTACK2:
        m_fAttackTime2 += DELTA;

        if (m_fAttackInterval2 < m_fAttackTime2)
        {
            m_fAttackTime2 -= m_fAttackInterval2;

            for (auto& Stone : m_vecStone)
            {
                if (Stone->GetActive())
                    continue;

                static_cast<CFallingStone*>(Stone)->StartFalling(150, 150, 1000, 700);
                Stone->SetActive(true);
                break;
            }
        }
        else
        {
            m_eCurState = ATTACK1;
        }

        break;

    case CPhase2Boss::GROGGY:

        m_vVelocity = { 0, 0 };
        m_iAtk = 0;

        for (auto& iter : m_vecEye)
            iter->SetActive(false);

        m_fTestTime += DELTA;

        if (m_fTestTime > 3.f)
        {
            m_fTestTime = 0;

            for (auto& iter : m_vecEye)
                static_cast<CShieldEye*>(iter)->Respawn();

            SelectEyes();

            m_eCurState = CHASE;
            m_iAtk = 4;
        }

        break;

    case CPhase2Boss::HIT:
    {
        m_fHitTime += DELTA;

        if (m_fHitInterval < m_fHitTime)
        {
            m_fHitTime -= m_fHitInterval;
            m_eCurState = CHASE;
            break;
        }

        m_vVelocity = { 0, 0 };

        if (ANIM_END == m_iAnimState)
            m_eCurState = CHASE;
    }
        break;

    case CPhase2Boss::DEAD:
        if (ANIM_END == m_iAnimState)
            m_bDead = true;

        break;
    }
}

void CPhase2Boss::ApplyState()
{

}

void CPhase2Boss::ChangeMotion()
{
    switch (m_eCurState)
    {
    case CPhase2Boss::TRANSFORM:
        m_vecMotion[0]->SetMotion(M_TRANS);
        break;

    case CPhase2Boss::IDLE:
        m_vecMotion[0]->SetMotion(M_IDLE);
        break;

    case CPhase2Boss::CHASE:
        m_vecMotion[0]->SetMotion(M_IDLE);
        break;

    case CPhase2Boss::ATTACK1:
        m_vecMotion[0]->SetMotion(M_ATTACK);
        break;

    case CPhase2Boss::ATTACK2:
        m_vecMotion[0]->SetMotion(M_ATTACK);
        break;

    case CPhase2Boss::GROGGY:
        m_vecMotion[0]->SetMotion(M_GROGGY);
        break;

    case CPhase2Boss::HIT:
        m_vecMotion[0]->SetMotion(M_HIT);
        break;

    case CPhase2Boss::DEAD:
        m_vecMotion[0]->SetMotion(M_HIT);
        break;
    }
}

void CPhase2Boss::SelectEyes()
{
    //int     iCnt = 0;
    //
    //while (iCnt < 4)
    //{
    //    for (auto& iter : m_vecEye)
    //    {
    //        CShieldEye* pTemp = static_cast<CShieldEye*>(iter);
    //        
    //        if (rand() % 2 && !pTemp->GetSelected())
    //        {
    //            static_cast<CShieldEye*>(iter)->SetSelected(true);
    //            ++iCnt;
    //        }
    //    }
    //}

    int     iIndex[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

    for (size_t i = 0; i < 20; ++i)
    {
        int iDest = rand() % 8;
        int iSrc = rand() % 8;
        int iTemp(0);

        iTemp = iIndex[iDest];
        iIndex[iDest] = iIndex[iSrc];
        iIndex[iSrc] = iTemp;
    }

    for (size_t i = 0; i < 4; ++i)
    {
        static_cast<CShieldEye*>(m_vecEye[iIndex[i]])->SetSelected(true);
    }
}

bool CPhase2Boss::CheckEyes()
{
    int     iCnt = 0;

    for (auto& iter : m_vecEye)
    {
        if (static_cast<CShieldEye*>(iter)->GetSelected() && !iter->GetActive())
            ++iCnt;
    }

    return 4 <= iCnt;
}

void CPhase2Boss::InitializePatternObj()
{
    m_vecEye.resize(8);

    for (size_t i = 0; i < m_vecEye.size(); ++i)
    {
        m_vecEye[i] = CAbstractFactory<CShieldEye>::Create();
        CObjMgr::GetInstance()->AddObj(ENEMYSHIELD, m_vecEye[i]);
        static_cast<CShieldEye*>(m_vecEye[i])->SetOwnerPos(&m_vPos);
    }

    static_cast<CShieldEye*>(m_vecEye[0])->SetOffset({ +m_tEyeOffset.fX, +m_tEyeOffset.fY });
    static_cast<CShieldEye*>(m_vecEye[1])->SetOffset({ -m_tEyeOffset.fX, -m_tEyeOffset.fY });
    static_cast<CShieldEye*>(m_vecEye[2])->SetOffset({ +m_tEyeOffset.fX, -m_tEyeOffset.fY });
    static_cast<CShieldEye*>(m_vecEye[3])->SetOffset({ -m_tEyeOffset.fX, +m_tEyeOffset.fY });
    static_cast<CShieldEye*>(m_vecEye[4])->SetOffset({ +m_tEyeOffset.fY, +m_tEyeOffset.fX });
    static_cast<CShieldEye*>(m_vecEye[5])->SetOffset({ -m_tEyeOffset.fY, -m_tEyeOffset.fX });
    static_cast<CShieldEye*>(m_vecEye[6])->SetOffset({ +m_tEyeOffset.fY, -m_tEyeOffset.fX });
    static_cast<CShieldEye*>(m_vecEye[7])->SetOffset({ -m_tEyeOffset.fY, +m_tEyeOffset.fX });

    m_vecStone.resize(20);

    for (size_t i = 0; i < m_vecStone.size(); ++i)
    {
        m_vecStone[i] = CAbstractFactory<CFallingStone>::Create();
        CObjMgr::GetInstance()->AddObj(ENEMYBULLET, m_vecStone[i]);
    }
}

void CPhase2Boss::InitializeMotion()
{
    m_vecMotion.resize(1);

    m_vecMotion[0] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"BOSS2"));
    
    m_vecMotion[0]->SetPos(&m_vPos);
    m_vecMotion[0]->SetSize(m_vSize);
    m_vecMotion[0]->SetRect(&m_tRect);
    m_vecMotion[0]->ResizeFrameVec(MT_END);
    m_vecMotion[0]->SetFrame(M_TRANS, 0, 30, false);
    m_vecMotion[0]->SetFrame(M_IDLE, 0, 3, true);
    m_vecMotion[0]->SetFrame(M_GROGGY, 0, 1, true);
    m_vecMotion[0]->SetFrame(M_HIT, 2, 0, 7, false);
    m_vecMotion[0]->SetFrame(M_ATTACK, 3, 0, 3, true);
}
