#include "stdafx.h"
#include "PlayerState.h"
#include "Player.h"
#include "Skill.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "StateMgr.h"
#include "SoundMgr.h"

void CIdleState::ChangeState(CPlayer* _pPlayer)
{
	// 스킬 사용
	if (KEY_PRESS('Z'))
	{
		_pPlayer->m_pUsingSkill = _pPlayer->m_vecSkillSlot[0];

		if (_pPlayer->m_pUsingSkill)
		{
			_pPlayer->ChangeMotion((CPlayer::MOTION_ST)_pPlayer->m_pUsingSkill->GetMotionIndex());
			_pPlayer->m_eCurActionST = CPlayer::ACT_ACTION;
		}
	}

	else if (KEY_PRESS('X'))
	{
		_pPlayer->m_pUsingSkill = _pPlayer->m_vecSkillSlot[1];

		if (_pPlayer->m_pUsingSkill)
		{
			_pPlayer->ChangeMotion((CPlayer::MOTION_ST)_pPlayer->m_pUsingSkill->GetMotionIndex());
			_pPlayer->m_eCurActionST = CPlayer::ACT_ACTION;
		}
	}

	// 이동
	else if (KEY_PRESS(VK_UP))
	{
		_pPlayer->SetDir(UP);
		_pPlayer->SetVelocity({ 0, -1 });
	}
	else if (KEY_PRESS(VK_DOWN))
	{
		_pPlayer->SetDir(DOWN);
		_pPlayer->SetVelocity({ 0, +1 });
	}
	else if (KEY_PRESS(VK_LEFT))
	{
		_pPlayer->SetDir(LEFT);
		_pPlayer->SetVelocity({ -1, 0 });
	}
	else if (KEY_PRESS(VK_RIGHT))
	{
		_pPlayer->SetDir(RIGHT);
		_pPlayer->SetVelocity({ +1, 0 });
	}
	else
		_pPlayer->SetVelocity({ 0, 0 });

	// 구르기
	if (KEY_PRESS(VK_SPACE))
	{
		_pPlayer->ChangeMotion(CPlayer::ROLL);
		_pPlayer->m_eCurActionST = CPlayer::ACT_ROLL;
		CSoundMgr::Get_Instance()->PlaySound(L"Roll.wav", SOUND_EFFECT, 1.f);
	}

	// Pull, Push 조건
}

void CIdleState::Update(CPlayer* _pPlayer)
{
	if (FLT_EPSILON < abs(_pPlayer->GetVelocity().fX)
		|| FLT_EPSILON < abs(_pPlayer->GetVelocity().fY))
	{
		_pPlayer->ChangeMotion(CPlayer::WALK);
		_pPlayer->m_eCurActionST = CPlayer::ACT_WALK;
	}
}

void CWalkState::ChangeState(CPlayer* _pPlayer)
{
	if (KEY_PRESS('Z'))
	{
		_pPlayer->m_pUsingSkill = _pPlayer->m_vecSkillSlot[0];
		
		if (_pPlayer->m_pUsingSkill)
		{
			_pPlayer->ChangeMotion((CPlayer::MOTION_ST)_pPlayer->m_pUsingSkill->GetMotionIndex());
			_pPlayer->m_eCurActionST = CPlayer::ACT_ACTION;
		}
	}
	else if (KEY_PRESS('X'))
	{
		_pPlayer->m_pUsingSkill = _pPlayer->m_vecSkillSlot[1];
		
		if (_pPlayer->m_pUsingSkill)
		{
			_pPlayer->ChangeMotion((CPlayer::MOTION_ST)_pPlayer->m_pUsingSkill->GetMotionIndex());
			_pPlayer->m_eCurActionST = CPlayer::ACT_ACTION;
		}
	}

	else if (KEY_PRESS(VK_SPACE))
	{
		_pPlayer->ChangeMotion(CPlayer::ROLL);
		_pPlayer->m_eCurActionST = CPlayer::ACT_ROLL;
	}

	else if (KEY_PRESS(VK_UP))
	{
		_pPlayer->SetDir(UP);
		_pPlayer->SetVelocity({ 0, -1 });
	}
	else if (KEY_PRESS(VK_DOWN))
	{
		_pPlayer->SetDir(DOWN);
		_pPlayer->SetVelocity({ 0, +1 });
	}
	else if (KEY_PRESS(VK_LEFT))
	{
		_pPlayer->SetDir(LEFT);
		_pPlayer->SetVelocity({ -1, 0 });
	}
	else if (KEY_PRESS(VK_RIGHT))
	{
		_pPlayer->SetDir(RIGHT);
		_pPlayer->SetVelocity({ +1, 0 });
	}
	else
		_pPlayer->SetVelocity({ 0, 0 });

}

void CWalkState::Update(CPlayer* _pPlayer)
{
	if (CPlayer::MOTION_ST::WALK != _pPlayer->m_vecMotion[_pPlayer->m_eDir]->GetMotion())
	{
		_pPlayer->ChangeMotion(CPlayer::WALK);
	}

	if (VEC2(0, 0) == _pPlayer->GetVelocity())
	{
		_pPlayer->ChangeMotion(CPlayer::IDLE);
		_pPlayer->m_eCurActionST = CPlayer::ACT_IDLE;
	}
}

void CActState::ChangeState(CPlayer* _pPlayer)
{
	//if (KEY_PRESS('Z'))
	//{
	//	m_bCharge = true;
	//
	//	m_fAtkTime += DELTA;
	//
	//	if (_pPlayer->m_pUsingSkill->GetChargeTime() < m_fAtkTime)
	//		_pPlayer->m_pUsingSkill->ActivateChargeSkill();
	//	else 
	//		_pPlayer->m_pUsingSkill->ActivateDefaultSkill();
	//}
	//
	//if (KEY_UP('Z'))
	//{
	//	if (_pPlayer->m_pUsingSkill->GetChargeTime() < m_fAtkTime)
	//	{
	//		//_pPlayer->m_pUsingSkill->ActivateChargeSkill();
	//		_pPlayer->m_eMotionState = CPlayer::SPIN;
	//	}
	//
	//	m_bCharge = false;
	//	m_fAtkTime = 0.f;
	//}
	
	//else if (KEY_PRESS('X'))
	//{
	//	m_bCharge = true;
	//
	//	m_fAtkTime += DELTA;
	//
	//	if (_pPlayer->m_pUsingSkill->GetChargeTime() < m_fAtkTime)
	//		_pPlayer->m_pUsingSkill->ActivateChargeSkill();
	//
	//}

	//else if (KEY_UP('X'))
	//{
	//	if (_pPlayer->m_pUsingSkill->GetChargeTime() < m_fTime)
	//		_pPlayer->m_pUsingSkill->ActivateChargeSkill();
	//
	//	m_bCharge = false;
	//	m_fTime = 0.f;
	//}

	//else
	//{
	//	_pPlayer->m_pUsingSkill->ActivateDefaultSkill();
	//}

	//if (_pPlayer->m_pUsingSkill->GetActivated())
	//{
	//	// 왜 키 업이 안 잡히지?????
	//	if (KEY_UP('Z') || KEY_UP('X'))
	//	{
	//		m_bCharge = false;
	//		m_fAtkTime = 0;
	//
	//		_pPlayer->m_pUsingSkill->SetActivated(false);
	//	}
	//}
}

void CActState::Update(CPlayer* _pPlayer)
{
	_pPlayer->m_vVelocity = { 0, 0 };

	if(!_pPlayer->m_pUsingSkill->GetActivated())
		_pPlayer->m_pUsingSkill->ActivateSkill();

	if (ANIM_ACTION == _pPlayer->m_iAnimState)
	{
		_pPlayer->m_pUsingSkill->ExecuteSkill();
	}
	else if (ANIM_ACTEND == _pPlayer->m_iAnimState)
	{
		_pPlayer->m_pUsingSkill->DeactivateSkill();
	}
	else if (ANIM_END == _pPlayer->m_iAnimState)
	{
		//if(!_pPlayer->m_pUsingSkill->GetActivated())
		//if(!m_bCharge)
		{
			_pPlayer->ChangeMotion(CPlayer::IDLE);
			_pPlayer->m_eCurActionST = CPlayer::ACT_IDLE;
		}
	}
}

void CRollState::ChangeState(CPlayer* _pPlayer)
{
	// 조작 불가능
}

void CRollState::Update(CPlayer* _pPlayer)
{
	// 모션 끝나면 IDLE
	// 구르기 속도가 따로 있음

	if (ANIM_END == _pPlayer->m_iAnimState)
	{
		_pPlayer->ChangeMotion(CPlayer::IDLE);
		_pPlayer->m_eCurActionST = CPlayer::ACT_IDLE;
		_pPlayer->m_fSpeed = DEF_SPEED;
		_pPlayer->m_vVelocity = { 0, 0 };
		return;
	}

	_pPlayer->m_fSpeed = 500.f;

	switch (_pPlayer->m_eDir)
	{
	case DOWN:
		_pPlayer->m_vVelocity = { 0, 1 };
		break;
	case UP:
		_pPlayer->m_vVelocity = { 0, -1 };
		break;
	case LEFT:
		_pPlayer->m_vVelocity = { -1, 0 };
		break;
	case RIGHT:
		_pPlayer->m_vVelocity = { 1, 0 };
		break;
	}
}

void CGetState::ChangeState(CPlayer* _pPlayer)
{
	// 인터페이스 들어가면 수정 : C는 확인 키
	if (KEY_DOWN('C') && ANIM_END == _pPlayer->m_iAnimState)
	{
		_pPlayer->ChangeMotion(CPlayer::IDLE);
		_pPlayer->m_eCurActionST = CPlayer::ACT_IDLE;
	}
}

void CGetState::Update(CPlayer* _pPlayer)
{
}

void CCarryState::ChangeState(CPlayer* _pPlayer)
{
	// 오브젝트 밀고 당기는 함수 구현하기
	if (KEY_PRESS(VK_UP))
	{
		
	}
	else if (KEY_PRESS(VK_DOWN))
	{

	}
	else if (KEY_PRESS(VK_LEFT))
	{

	}
	else if (KEY_PRESS(VK_RIGHT))
	{

	}
	else
	{
		_pPlayer->SetSpeed(DEF_SPEED);
		_pPlayer->ChangeMotion(CPlayer::IDLE);
		_pPlayer->m_eCurActionST = CPlayer::ACT_IDLE;
	}
}

void CHitState::Update(CPlayer* _pPlayer)
{
	if (ANIM_END == _pPlayer->m_iAnimState)
	{
		_pPlayer->ChangeMotion(CPlayer::IDLE);
		_pPlayer->m_eCurActionST = CPlayer::ACT_IDLE;

		if (0 >= _pPlayer->m_iHp)
		{
			_pPlayer->ChangeMotion(CPlayer::DEAD);
			_pPlayer->m_eCurActionST = CPlayer::ACT_DEAD;
		}
	}
}
