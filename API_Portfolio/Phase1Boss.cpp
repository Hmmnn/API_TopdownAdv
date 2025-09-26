#include "stdafx.h"
#include "Phase1Boss.h"
#include "RectCollider.h"
#include "LaserEye.h"
#include "BossTrap.h"

#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "ObjMgr.h"

#include "KeyMgr.h"

CPhase1Boss::CPhase1Boss()
    : m_eState(IDLE), m_pTarget(nullptr), 
	m_fChaseTime(0), m_fChaseInterval(0),
	m_fHitTime(0), m_fHitInterval(0), 
	m_fAttackTime1(0), m_fAttackInterval1(0), 
	m_fAttackTime2(0), m_fAttackInterval2(0),
	m_bSheid(false), m_bAttacking(false)
{
}

CPhase1Boss::~CPhase1Boss()
{
    Release();
}

void CPhase1Boss::Initialize()
{
	m_eObjType = BOSS;

	m_vPos = { 600, 200 };
	m_vSize = { 208, 248 };

    m_bActive = true;
    m_bDead = false;
    m_fSpeed = 100.f;
    m_iMaxHp = 30;
	m_iHp = m_iMaxHp;

	m_vVelocity = { 0, 0 };

    m_iAnimState = ANIM_NOEVENT;

	m_fChaseInterval = 3.0f;
	m_fHitInterval = 0.5f;
	m_fAttackInterval1 = 2.0f;
	m_fAttackInterval2 = 1.0f;

	m_pCollider = new CRectCollider(this, VEC2(100, 200));
	m_pTarget = CObjMgr::GetInstance()->GetBack(PLAYER);

	InitializePatternObj();
	InitializeMotion();

	ChangeMotion(M_MOVE);
}

int CPhase1Boss::Update()
{
	if (!m_bActive)
	{
		for (auto& iter : m_vecLaserEye)
			iter->SetActive(false);
	}

	if (m_bDead)
	{
		m_bActive = false;

		for (auto& iter : m_vecLaserEye)
			iter->SetActive(false);

		return SCENE_NOEVENT;
	}

	if (KEY_DOWN(VK_F1))
		TakeDamage(2);

	if (KEY_DOWN(VK_F2))
		TakeDamage(10);

    return CGameObj::Update();
}

void CPhase1Boss::LateUpdate()
{
	if (!m_bActive)
		return;

	CheckState();
    
	m_iAnimState = m_vecMotion[m_eDir]->RunAnimation();

	int iCountActive(0);

	for (auto& Eye : m_vecLaserEye)
	{		
		if (Eye->GetActive())
			++iCountActive;
	}

	if (iCountActive)
		m_bSheid = false;
	else
		m_bSheid = true;
}

void CPhase1Boss::Render(HDC hDC)
{
	if (!m_bActive)
		return;

    int		iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int		iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    //Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
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

void CPhase1Boss::Release()
{
}

void CPhase1Boss::TakeDamage(int _iDamage)
{
    if (HIT == m_eState)
        return;

    m_iHp -= _iDamage;
	m_eState = HIT;
	ChangeMotion(M_HIT);

    if (0 >= m_iHp)
    {
        m_iHp = 0;
        m_eState = DEAD;
    }
}

void CPhase1Boss::OnCollision(CObj* _pOther)
{
}

void CPhase1Boss::CollisionPush(CObj* _pOther)
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
			m_vVelocity.fY = +1;
		}

		else if (m_vPos.fY < _pOther->GetPos().fY)
		{
			m_vPos.fY -= rc.bottom - rc.top;
			m_vVelocity.fY = -1;
		}
	}

	// 좌우 충돌
	else if (iWidth < iHeight)
	{
		if (m_vPos.fX > _pOther->GetPos().fX)
		{
			m_vPos.fX += rc.right - rc.left;
			m_vVelocity.fX = +1;
		}

		else if (m_vPos.fX < _pOther->GetPos().fX)
		{
			m_vPos.fX -= rc.right - rc.left;
			m_vVelocity.fX = -1;
		}
	}
}

void CPhase1Boss::CheckState()
{
	switch (m_eState)
	{
	case CPhase1Boss::IDLE:

		if (m_iMaxHp != m_iHp)
		{
			m_eState = CHASE;
			ChangeMotion(M_MOVE);
		}

		if (FLT_EPSILON < abs(m_vVelocity.fX) || FLT_EPSILON < abs(m_vVelocity.fY))
		{
			ChangeMotion(M_MOVE);
			break;
		}
		
		break;

	case CPhase1Boss::CHASE:	// 눈알이 빙빙 도는 채로 추격
	{
		m_fChaseTime += DELTA;

		if (m_fChaseInterval < m_fChaseTime)
		{
			m_fChaseTime -= m_fChaseInterval;

			if (m_iMaxHp * 0.75f < (float)m_iHp)
			{
				ChangeMotion(M_MOVE);
				m_vVelocity = (m_pTarget->GetPos() - m_vPos).Normalized();
			}

			else if (m_iMaxHp * 0.75f >= (float)m_iHp && m_iMaxHp * 0.5f < (float)m_iHp)
			{
				m_eState = ATTACK1;
				ChangeMotion(M_ATTACK);
			}

			else if (m_iMaxHp * 0.5f >= (float)m_iHp)
			{
				m_eState = ATTACK2;
				ChangeMotion(M_ATTACK);
			}

			break;	
		}
	}
		break;

	case CPhase1Boss::ATTACK1:	// 눈알에서 레이저 주기적으로
		
		if (m_bAttacking)
		{
			m_fAttackTime1 += DELTA;

			if (m_fAttackInterval1 < m_fAttackTime1)
			{
				m_fAttackTime1 -= m_fAttackInterval1;

				m_eState = CHASE;
				ChangeMotion(M_MOVE);

				for (auto& iter : m_vecLaserEye)
					static_cast<CLaserEye*>(iter)->m_eState = CLaserEye::IDLE;

				m_vVelocity = (m_pTarget->GetPos() - m_vPos).Normalized();

				m_bAttacking = false;
			}
		}
		else
		{
			m_bAttacking = true;

			m_vVelocity = { 0, 0 };

			for (auto& iter : m_vecLaserEye)
			{
				static_cast<CLaserEye*>(iter)->m_eState = CLaserEye::SHOOT;
				static_cast<CLaserEye*>(iter)->ShootLaser();
			}
		}

		if (m_iMaxHp * 0.25f >= m_iHp)
		{
			m_fAttackTime2 += DELTA;
		}

		break;

	case CPhase1Boss::ATTACK2:	// 중앙으로 이동? 장판 깔고 레이저 발사
		
		//m_fAttackTime2 += DELTA;

		if (m_fAttackInterval2 < m_fAttackTime2)
		{
			m_fAttackTime2 -= m_fAttackInterval2;

			for (auto& iter : m_vecBossTrap)
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
			m_eState = ATTACK1;
		}

		break;

	case CPhase1Boss::HIT:
	{
		m_fHitTime += DELTA;

		if (m_fHitInterval < m_fHitTime)
		{
			m_fHitTime -= m_fHitInterval;
			m_eState = IDLE;
			break;
		}

		m_vVelocity = { 0, 0 };

		if (ANIM_END == m_iAnimState)
			m_eState = IDLE;
	}
		break;

	case CPhase1Boss::DEAD:
		m_bDead = true;
		break;
	}
}

void CPhase1Boss::ChangeMotion(B1_MOTIONID _eMotionID)
{
	m_vecMotion[m_eDir]->SetMotion(_eMotionID);
	m_iAnimState = ANIM_NOEVENT;
}

void CPhase1Boss::InitializePatternObj()
{
	for (size_t i = 0; i < 4; ++i)
	{
		CObj* pTempEye = CAbstractFactory<CLaserEye>::Create();

		static_cast<CLaserEye*>(pTempEye)->m_pOwner = this;
		static_cast<CLaserEye*>(pTempEye)->m_fAngle = i * 90.f;

		m_vecLaserEye.push_back(pTempEye);
		CObjMgr::GetInstance()->AddObj(ENEMYBULLET, pTempEye);
	}

	for (size_t i = 0; i < 5; ++i)
	{
		CObj* pTempTrap = CAbstractFactory<CBossTrap>::Create();

		static_cast<CBossTrap*>(pTempTrap)->m_pOwner = this;

		m_vecBossTrap.push_back(pTempTrap);
		CObjMgr::GetInstance()->AddObj(ENEMYBULLET, pTempTrap);
	}
}

void CPhase1Boss::InitializeMotion()
{
	m_vecMotion.resize(1);

	m_vecMotion[DOWN] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"BOSS1"));
	m_vecMotion[DOWN]->SetPos(&m_vPos);
	m_vecMotion[DOWN]->SetSize(m_vSize);
	m_vecMotion[DOWN]->SetRect(&m_tRect);
	m_vecMotion[DOWN]->ResizeFrameVec(MT_END);
	m_vecMotion[DOWN]->SetFrame(M_MOVE, 0, 11, true, 1.f / 10.f);
	m_vecMotion[DOWN]->SetFrame(M_ATTACK, 0, 5, false);
	m_vecMotion[DOWN]->SetFrame(M_HIT, 0, 11, false);
}
