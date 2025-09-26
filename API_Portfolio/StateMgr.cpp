#include "stdafx.h"
#include "StateMgr.h"

CStateMgr* CStateMgr::m_pInstance = nullptr;

CStateMgr::CStateMgr()
{
}

CStateMgr::~CStateMgr()
{
	Release();
}

void CStateMgr::Initialize()
{
	m_pIdle = new CIdleState;
	m_pWalking = new CWalkState;
	m_pActing = new CActState;
	m_pRolling = new CRollState;
	m_pGetting = new CGetState;
	m_pCarrying = new CCarryState;
	m_pHitted = new CHitState;
	m_pDead = new CDeadState;
}

void CStateMgr::Release()
{
	Safe_Delete<CIdleState*>(m_pIdle);
	Safe_Delete<CWalkState*>(m_pWalking);
	Safe_Delete<CActState*>(m_pActing);
	Safe_Delete<CRollState*>(m_pRolling);
	Safe_Delete<CGetState*>(m_pGetting);
	Safe_Delete<CCarryState*>(m_pCarrying);
	Safe_Delete<CHitState*>(m_pHitted);
	Safe_Delete<CDeadState*>(m_pDead);
}

void CStateMgr::SetState(CPlayer* _pPlayer, IPlayerState*& _pState)
{
	_pState->ChangeState(_pPlayer);
}

void CStateMgr::Update(CPlayer* _pPlayer, IPlayerState*& _pState)
{
	_pState->ChangeState(_pPlayer);
}

void CStateMgr::ChangeState(int _iActionState, IPlayerState*& _State)
{
	switch (_iActionState)
	{
	case 0:
		_State = static_cast<IPlayerState*>(m_pIdle);
		break;

	case 1:
		_State = static_cast<IPlayerState*>(m_pWalking);
		break;

	case 2:
		_State = static_cast<IPlayerState*>(m_pActing);
		break;

	case 3:
		_State = static_cast<IPlayerState*>(m_pRolling);
		break;

	case 4:
		_State = static_cast<IPlayerState*>(m_pGetting);
		break;

	case 5:
		_State = static_cast<IPlayerState*>(m_pCarrying);
		break;

	case 6:
		_State = static_cast<IPlayerState*>(m_pHitted);
		break;

	case 7:
		_State = static_cast<IPlayerState*>(m_pDead);
		break;
	}
}
