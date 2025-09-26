#include "stdafx.h"
#include "Player.h"
#include "RectCollider.h"
#include "ArrowAttack.h"
#include "MeleeAttack.h"
#include "BoomerangAttack.h"
#include "GuardSkill.h"
#include "MagicAttack.h"

#include "StateMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "TimeMgr.h"
#include "SkillMgr.h"
#include "SoundMgr.h"
#include "EffectMgr.h"

CPlayer::CPlayer() : 
	m_eMotionState(MOTION_END), m_ePreActionST(ACT_END), m_eCurActionST(ACT_END),
	m_fHitTime(0), m_pUsingSkill(nullptr), m_pState(nullptr)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_eObjType = PLAYER;

	m_vPos = { WINCX / 2.f, WINCY / 2.f };
	m_vSize = { 200.f, 200.f };
	m_bActive = true;
	m_bDead = false;

	m_fSpeed = DEF_SPEED; //500;
	m_iMaxHp = 20;
	m_iHp = m_iMaxHp;

	m_eMotionState = IDLE;
	m_eCurActionST = ACT_IDLE;
	m_ePreActionST = m_eCurActionST;

	m_pCollider = new CRectCollider(this, VEC2(45.f, 70.f));

	InitializeMotion();
	InitializeSkill();

	ChangeMotion(m_eMotionState);

	//m_vecSkillSlot[0] = CSkillMgr::GetInstance()->FindSkill(L"ARROW_ATK");
	//m_vecSkillSlot[0] = CSkillMgr::GetInstance()->FindSkill(L"MELEE_ATK");

	//m_vecSkillSlot[1] = CSkillMgr::GetInstance()->FindSkill(L"BOO_ATK");
	//m_vecSkillSlot[1] = CSkillMgr::GetInstance()->FindSkill(L"MAGIC_ATK");
	//m_vecSkillSlot[1] = CSkillMgr::GetInstance()->FindSkill(L"GUARD_SKILL");

	CStateMgr::GetInstance()->ChangeState((int)ACT_IDLE, m_pState);
}

int CPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (KEY_UP('P'))
		m_eCurActionST = ACT_IDLE;

	//KeyInput();
	//CheckMotionState();
	m_pState->ChangeState(this);
	TransitActionState();
	m_pState->Update(this);

	return CGameObj::Update();
}

void CPlayer::LateUpdate()
{
	//CheckMotionState();
	m_iAnimState = m_vecMotion[m_eDir]->RunAnimation();

	//Scroll();

#ifdef _DEBUG

	static float time = 0;

	time += DELTA;

	if (1.f < time)
	{
		cout << "플레이어 좌표 : " << m_vPos.fX << "\t" << m_vPos.fY << endl;

		time -= 1.f;
	}

#endif

}

void CPlayer::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
	int		iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();
	
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	m_pCollider->Render(hDC);

	m_vecMotion[m_eDir]->Render(hDC, iScrollX, iScrollY);

	TCHAR   szBuf[64] = L"";
	//swprintf_s(szBuf, L"HP : %d\nATK : %d", m_iHp, m_iAtk);

	RECT    rc{ 
		m_tRect.left - 50 + iScrollX, 
		m_tRect.top - 20 + iScrollY,
		m_tRect.right + 50 + iScrollX, 
		m_tRect.top - 5 + iScrollY
	};

	DrawText(hDC, szBuf, lstrlen(szBuf), &rc, DT_CENTER);
}

void CPlayer::Release()
{
}

void CPlayer::OnCollision(CObj* _pOther)
{
	if (WALL == _pOther->GetType())
	{
		CollisionPush(_pOther);
	}
	else if (MAPOBJ == _pOther->GetType())
	{

	}
	else if (SWITCH == _pOther->GetType())
	{ 
		
	}
	else if (ENEMY == _pOther->GetType() || BOSS == _pOther->GetType())
	{
		TakeDamage(static_cast<CGameObj*>(_pOther)->GetAtk());
	}
	else if (ENEMYBULLET == _pOther->GetType() || ENEMYWEAPON == _pOther->GetType())
	{
		CGameObj* pTemp = dynamic_cast<CGameObj*>(_pOther);

		if(pTemp)
			TakeDamage(pTemp->GetAtk());
	}
}

void CPlayer::TakeDamage(int _iDamage)
{
	if (HIT == m_eMotionState || DEAD == m_eMotionState || ROLL == m_eMotionState || GUARD == m_eMotionState)
		return;

	if (0 == _iDamage)
		return;

	m_eMotionState = HIT;
	m_iHp -= _iDamage;
	ChangeMotion(HIT);
	//CEffectMgr::GetInstance()->PlayEffect(L"HIT", m_vPos + VEC2(-10, -10));

	// 넉백 추가 필요

	if (0 >= m_iHp)
	{
		m_iHp = 0;
		m_eMotionState = DEAD;
	}

	CSoundMgr::Get_Instance()->PlaySound(L"Sick.wav", SOUND_EFFECT, 1.f);
}

void CPlayer::SetSkill(int _iSlotNum, const TCHAR* _pKey)
{
	m_vecSkillSlot[_iSlotNum] = CSkillMgr::GetInstance()->FindSkill(_pKey);
}

void CPlayer::CheckMotionState()
{
#pragma region 접기
	//switch (m_eMotionState)
	//{
	//case CPlayer::IDLE:

	//	if (FLT_EPSILON < abs(m_vVelocity.fX) || FLT_EPSILON < abs(m_vVelocity.fY))
	//	{
	//		ChangeMotion(WALK);
	//		break;
	//	}

	//	break;

	//case CPlayer::WALK:
	//	if (WALK != m_vecMotion[m_eDir]->GetMotion())
	//		ChangeMotion(WALK);

	//	if (VEC2(0, 0) == m_vVelocity)
	//	{
	//		ChangeMotion(IDLE);
	//		break;
	//	}
	//	
	//	break;

	//case CPlayer::MELEE:
	//	if (ANIM_ACTION == m_iAnimState)
	//	{
	//		m_pUsingSkill->ActivateSkill();
	//	}
	//	else if (ANIM_ACTEND == m_iAnimState)
	//	{
	//		m_pUsingSkill->DeactivateSkill();
	//		m_pUsingSkill = nullptr;
	//	}
	//	else if (ANIM_END == m_iAnimState)
	//	{
	//		ChangeMotion(IDLE);
	//		break;
	//	}

	//	break;

	//case CPlayer::ROLL:
	//	if (ANIM_END == m_iAnimState)
	//	{
	//		ChangeMotion(IDLE);
	//		m_fSpeed = DEF_SPEED;
	//		break;
	//	}

	//	m_fSpeed = 500.f;

	//	switch (m_eDir)
	//	{
	//	case DOWN:
	//		m_vVelocity = { 0, 1 };
	//		break;
	//	case UP:
	//		m_vVelocity = { 0, -1 };
	//		break;
	//	case LEFT:
	//		m_vVelocity = { -1, 0 };
	//		break;
	//	case RIGHT:
	//		m_vVelocity = { 1, 0 };
	//		break;
	//	}
	//	break;

	//case CPlayer::HIT:

	//	if (ANIM_END == m_iAnimState)
	//	{
	//		ChangeMotion(IDLE);
	//		break;
	//	}

	//	m_vVelocity = { 0, 0 };
	//	
	//	break;

	//case CPlayer::DEAD:
	//	//if (m_bMotionEnd)
	//	//{
	//	//	ChangeMotion(IDLE);
	//	//	break;
	//	//}
	//	
	//	break;
	//	
	//case CPlayer::ARROW:
	//	if (ANIM_ACTION == m_iAnimState)
	//	{
	//		m_pUsingSkill->ActivateSkill();
	//	}
	//	else if (ANIM_ACTEND == m_iAnimState)
	//	{
	//		m_pUsingSkill = nullptr;
	//	}
	//	else if (ANIM_END == m_iAnimState)
	//	{
	//		ChangeMotion(IDLE);
	//		break;
	//	}

	//	break;

	//case CPlayer::SHIELD:
	//	if (ANIM_END == m_iAnimState)
	//	{
	//		ChangeMotion(IDLE);
	//		break;
	//	}
	//	
	//	break;

	//case CPlayer::BOOMERANG:
	//	if (ANIM_END == m_iAnimState)
	//	{
	//		ChangeMotion(IDLE);
	//		break;
	//	}
	//	
	//	break;

	//case CPlayer::MAGIC:
	//	if (ANIM_END == m_iAnimState)
	//	{
	//		ChangeMotion(IDLE);
	//		break;
	//	}
	//	
	//	break;

	//case CPlayer::SPIN:
	//	if (ANIM_ACTION == m_iAnimState)
	//	{
	//		m_pUsingSkill->ActivateChargeSkill();
	//	}
	//	else if (ANIM_ACTEND == m_iAnimState)
	//	{
	//		m_pUsingSkill->DeactivateSkill();
	//		m_pUsingSkill = nullptr;
	//	}
	//	else if (ANIM_END == m_iAnimState)
	//	{
	//		ChangeMotion(IDLE);
	//		break;
	//	}
	//	break;

	//case CPlayer::GET:
	//	if (ANIM_END == m_iAnimState)
	//	{
	//		ChangeMotion(IDLE);
	//		break;
	//	}

	//	break;

	//case CPlayer::PUSH:
	//	if (ANIM_END == m_iAnimState)
	//	{
	//		ChangeMotion(IDLE);
	//		break;
	//	}

	//	break;

	//case CPlayer::PULL:
	//	if (ANIM_END == m_iAnimState)
	//	{
	//		ChangeMotion(IDLE);
	//		break;
	//	}
	//	
	//	break;
	//}
#pragma endregion 접기
}

void CPlayer::TransitActionState()
{
	//if (m_ePreActionST != m_eCurActionST)
	//	m_pState->ChangeState(this);

	CStateMgr::GetInstance()->ChangeState((int)m_eCurActionST, m_pState);
	m_ePreActionST = m_eCurActionST;

	//switch (m_eActionState)
	//{
	//case CPlayer::ACT_IDLE:
	//	m_State = CStateMgr::GetInstance()->Idle;
	//	break;
	//
	//case CPlayer::ACT_WALK:
	//	m_State = CStateMgr::GetInstance()->Walking;
	//	break;
	//
	//case CPlayer::ACT_ACTION:
	//	m_State = CStateMgr::GetInstance()->Acting;
	//	break;
	//
	//case CPlayer::ACT_GET:
	//	m_State = CStateMgr::GetInstance()->Getting;
	//	break;
	//
	//case CPlayer::ACT_CARRY:
	//	m_State = CStateMgr::GetInstance()->Carrying;
	//	break;
	//
	//case CPlayer::ACT_HIT:
	//	m_State = CStateMgr::GetInstance()->Hitted;
	//	break;
	//
	//case CPlayer::ACT_DEAD:
	//	m_State = CStateMgr::GetInstance()->Dead;
	//	break;
	//}
}

void CPlayer::ChangeState()
{
	/*if (DEAD == m_eMotionState || HIT == m_eMotionState || SPIN == m_eMotionState)
		return;

	if (IDLE == m_eMotionState || WALK == m_eMotionState || PUSH == m_eMotionState || PULL == m_eMotionState)
	{
		if (KEY_PRESS(VK_UP))
		{
			m_eDir = UP;
			m_vVelocity = { 0, -1 };
		}

		else if (KEY_PRESS(VK_DOWN))
		{
			m_eDir = DOWN;
			m_vVelocity = { 0, +1 };
		}

		else if (KEY_PRESS(VK_LEFT))
		{
			m_eDir = LEFT;
			m_vVelocity = { -1, 0 };
		}

		else if (KEY_PRESS(VK_RIGHT))
		{
			m_eDir = RIGHT;
			m_vVelocity = { +1, 0 };
		}		

		else
		{
			m_vVelocity = { 0.f, 0.f };
		}
	}
	
	if (IDLE == m_eMotionState)
	{
		if (KEY_DOWN('Z'))
		{
			m_vecMotion[m_eDir]->SetMotion(m_vecSkillSlot[0]->GetMotionIndex());
			m_eMotionState = (MOTION_ST)m_vecSkillSlot[0]->GetMotionIndex();
			m_pUsingSkill = m_vecSkillSlot[0];
		}

		if (KEY_DOWN('X'))
		{
			m_vecMotion[m_eDir]->SetMotion(m_vecSkillSlot[1]->GetMotionIndex());
			m_eMotionState = (MOTION_ST)m_vecSkillSlot[1]->GetMotionIndex();
			m_pUsingSkill = m_vecSkillSlot[1];
		}
	}*/
}

// ChangeAction 필요
void CPlayer::ChangeMotion(MOTION_ST _eState)
{
	m_eMotionState = _eState;
	m_vecMotion[m_eDir]->SetMotion(m_eMotionState);
	m_iAnimState = ANIM_NOEVENT;
}

void CPlayer::Scroll()
{
	int iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
	int iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

	int iScrollMinX = 200;
	int iScrollMaxX = 600;
	int iScrollMinY = 200;
	int iScrollMaxY = 400;

	if (iScrollMinX + iScrollX > m_vPos.fX || iScrollMaxX + iScrollX < m_vPos.fX)
		CScrollMgr::GetInstance()->SetScrollX(-m_vVelocity.fX * m_fSpeed * DELTA);
	
	if (iScrollMinY + iScrollY > m_vPos.fY || iScrollMaxY + iScrollY < m_vPos.fY)
		CScrollMgr::GetInstance()->SetScrollY(-m_vVelocity.fY * m_fSpeed * DELTA);
}

void CPlayer::InitializeMotion()
{
	m_vecMotion.resize(DIR_END);

	m_vecMotion[DOWN] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"PLAYER_DOWN"));
	m_vecMotion[DOWN]->SetPos(&m_vPos);
	m_vecMotion[DOWN]->SetSize(m_vSize);
	m_vecMotion[DOWN]->SetRect(&m_tRect);
	m_vecMotion[DOWN]->ResizeFrameVec(MOTION_END);
	m_vecMotion[DOWN]->SetFrame(IDLE, 0, 9, true);
	m_vecMotion[DOWN]->SetFrame(WALK, 0, 9, true);
	m_vecMotion[DOWN]->SetFrame(MELEE, 0, 7, false);
	m_vecMotion[DOWN]->SetActionFrame(MELEE, 1, 6);
	m_vecMotion[DOWN]->SetFrame(ROLL, 0, 7, false);
	m_vecMotion[DOWN]->SetFrame(HIT, 0, 7, false);
	m_vecMotion[DOWN]->SetFrame(DEAD, 0, 4, false);
	m_vecMotion[DOWN]->SetFrame(ARROW, 0, 9, false, 1.f / 30.f);
	m_vecMotion[DOWN]->SetActionFrame(ARROW, 2, 7);
	m_vecMotion[DOWN]->SetFrame(GUARD, 0, 11, false);
	m_vecMotion[DOWN]->SetActionFrame(GUARD, 3, 11);
	m_vecMotion[DOWN]->SetFrame(BOOMERANG, 0, 5, false);
	m_vecMotion[DOWN]->SetActionFrame(BOOMERANG, 2, 7);
	m_vecMotion[DOWN]->SetFrame(MAGIC, 0, 10, false);
	m_vecMotion[DOWN]->SetActionFrame(MAGIC, 4, 7);
	m_vecMotion[DOWN]->SetFrame(SPIN, 0, 12, false);
	m_vecMotion[DOWN]->SetActionFrame(SPIN, 2, 4);
	m_vecMotion[DOWN]->SetFrame(GET, 0, 2, false);
	m_vecMotion[DOWN]->SetFrame(PUSH, 0, 8, false);
	m_vecMotion[DOWN]->SetFrame(PULL, 0, 7, false);

	m_vecMotion[UP] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"PLAYER_UP"));
	m_vecMotion[UP]->SetPos(&m_vPos);
	m_vecMotion[UP]->SetSize(m_vSize);
	m_vecMotion[UP]->SetRect(&m_tRect);
	m_vecMotion[UP]->ResizeFrameVec(MOTION_END);
	m_vecMotion[UP]->SetFrame(IDLE, 0, 1, true);
	m_vecMotion[UP]->SetFrame(WALK, 0, 9, true);
	m_vecMotion[UP]->SetFrame(MELEE, 0, 7, false);
	m_vecMotion[UP]->SetActionFrame(MELEE, 1, 6);
	m_vecMotion[UP]->SetFrame(ROLL, 0, 7, false);
	m_vecMotion[UP]->SetFrame(HIT, 0, 7, false);
	m_vecMotion[UP]->SetFrame(DEAD, 0, 4, false);
	m_vecMotion[UP]->SetFrame(ARROW, 0, 8, false, 1.f / 30.f);
	m_vecMotion[UP]->SetActionFrame(ARROW, 2, 5);
	m_vecMotion[UP]->SetFrame(GUARD, 0, 11, false);
	m_vecMotion[UP]->SetActionFrame(GUARD, 3, 11);
	m_vecMotion[UP]->SetFrame(BOOMERANG, 0, 5, false);
	m_vecMotion[UP]->SetActionFrame(BOOMERANG, 2, 4);
	m_vecMotion[UP]->SetFrame(MAGIC, 0, 10, false);
	m_vecMotion[UP]->SetActionFrame(MAGIC, 5, 7);
	m_vecMotion[UP]->SetFrame(SPIN, 0, 12, false);
	m_vecMotion[UP]->SetActionFrame(SPIN, 2, 11);
	m_vecMotion[UP]->SetFrame(GET, 0, 2, false);
	m_vecMotion[UP]->SetFrame(PUSH, 0, 8, false);
	m_vecMotion[UP]->SetFrame(PULL, 0, 7, false);

	m_vecMotion[LEFT] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"PLAYER_LEFT"));
	m_vecMotion[LEFT]->SetPos(&m_vPos);
	m_vecMotion[LEFT]->SetSize(m_vSize);
	m_vecMotion[LEFT]->SetRect(&m_tRect);
	m_vecMotion[LEFT]->ResizeFrameVec(MOTION_END);
	m_vecMotion[LEFT]->SetFrame(IDLE, 0, 9, true);
	m_vecMotion[LEFT]->SetFrame(WALK, 0, 9, true);
	m_vecMotion[LEFT]->SetFrame(MELEE, 0, 7, false);
	m_vecMotion[LEFT]->SetActionFrame(MELEE, 1, 6);
	m_vecMotion[LEFT]->SetFrame(ROLL, 0, 7, false);
	m_vecMotion[LEFT]->SetFrame(HIT, 0, 7, false);
	m_vecMotion[LEFT]->SetFrame(DEAD, 0, 4, false);
	m_vecMotion[LEFT]->SetFrame(ARROW, 0, 7, false, 1.f / 30.f);
	m_vecMotion[LEFT]->SetActionFrame(ARROW, 2, 5);
	m_vecMotion[LEFT]->SetFrame(GUARD, 0, 11, false);
	m_vecMotion[LEFT]->SetActionFrame(GUARD, 3, 11);
	m_vecMotion[LEFT]->SetFrame(BOOMERANG, 0, 5, false);
	m_vecMotion[LEFT]->SetActionFrame(BOOMERANG, 2, 4);
	m_vecMotion[LEFT]->SetFrame(MAGIC, 0, 10, false);
	m_vecMotion[LEFT]->SetActionFrame(MAGIC, 5, 7);
	m_vecMotion[LEFT]->SetFrame(SPIN, 0, 12, false);
	m_vecMotion[LEFT]->SetActionFrame(SPIN, 2, 11);
	m_vecMotion[LEFT]->SetFrame(GET, 0, 2, false);
	m_vecMotion[LEFT]->SetFrame(PUSH, 0, 8, false);
	m_vecMotion[LEFT]->SetFrame(PULL, 0, 7, false);

	m_vecMotion[RIGHT] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"PLAYER_RIGHT"));
	m_vecMotion[RIGHT]->SetPos(&m_vPos);
	m_vecMotion[RIGHT]->SetSize(m_vSize);
	m_vecMotion[RIGHT]->SetRect(&m_tRect);
	m_vecMotion[RIGHT]->ResizeFrameVec(MOTION_END);
	m_vecMotion[RIGHT]->SetFrame(IDLE, 0, 9, true);
	m_vecMotion[RIGHT]->SetFrame(WALK, 0, 9, true);
	m_vecMotion[RIGHT]->SetFrame(MELEE, 0, 7, false);
	m_vecMotion[RIGHT]->SetActionFrame(MELEE, 1, 6);
	m_vecMotion[RIGHT]->SetFrame(ROLL, 0, 7, false);
	m_vecMotion[RIGHT]->SetFrame(HIT, 0, 7, false);
	m_vecMotion[RIGHT]->SetFrame(DEAD, 0, 4, false);
	m_vecMotion[RIGHT]->SetFrame(ARROW, 0, 7, false, 1.f / 30.f);
	m_vecMotion[RIGHT]->SetActionFrame(ARROW, 2, 5);
	m_vecMotion[RIGHT]->SetFrame(GUARD, 0, 11, false);
	m_vecMotion[RIGHT]->SetActionFrame(GUARD, 3, 11);
	m_vecMotion[RIGHT]->SetFrame(BOOMERANG, 0, 5, false);
	m_vecMotion[RIGHT]->SetActionFrame(BOOMERANG, 2, 4);
	m_vecMotion[RIGHT]->SetFrame(MAGIC, 0, 10, false);
	m_vecMotion[RIGHT]->SetActionFrame(MAGIC, 5, 7);
	m_vecMotion[RIGHT]->SetFrame(SPIN, 0, 12, false);
	m_vecMotion[RIGHT]->SetActionFrame(SPIN, 2, 11);
	m_vecMotion[RIGHT]->SetFrame(GET, 0, 2, false);
	m_vecMotion[RIGHT]->SetFrame(PUSH, 0, 8, false);
	m_vecMotion[RIGHT]->SetFrame(PULL, 0, 7, false);
}

void CPlayer::InitializeSkill()
{
	m_vecSkillSlot.resize(2);

	CSkill* pTempSkill = new CArrowAttack;
	pTempSkill->Initialize();
	pTempSkill->SetMotionIndex((int)ARROW);
	pTempSkill->SetOwner(this);
	CSkillMgr::GetInstance()->AddSkill(L"ARROW_ATK", pTempSkill);

	pTempSkill = new CMeleeAttack;
	pTempSkill->Initialize();
	pTempSkill->SetMotionIndex((int)MELEE);
	pTempSkill->SetChargeMotion((int)SPIN);
	pTempSkill->SetOwner(this);
	CSkillMgr::GetInstance()->AddSkill(L"MELEE_ATK", pTempSkill);

	pTempSkill = new CBoomerangAttack;
	pTempSkill->Initialize();
	pTempSkill->SetMotionIndex((int)BOOMERANG);
	pTempSkill->SetOwner(this);
	CSkillMgr::GetInstance()->AddSkill(L"BOO_ATK", pTempSkill);

	pTempSkill = new CGuardSkill;
	pTempSkill->Initialize();
	pTempSkill->SetMotionIndex((int)GUARD);
	pTempSkill->SetOwner(this);
	CSkillMgr::GetInstance()->AddSkill(L"GUARD_SKILL", pTempSkill);

	pTempSkill = new CMagicAttack;
	pTempSkill->Initialize();
	pTempSkill->SetMotionIndex((int)MAGIC);
	pTempSkill->SetOwner(this);
	CSkillMgr::GetInstance()->AddSkill(L"MAGIC_ATK", pTempSkill);
}
