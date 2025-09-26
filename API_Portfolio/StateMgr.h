#pragma once

#include "Define.h"
#include "PlayerState.h"

class CStateMgr
{
	SINGLETON(CStateMgr)

private:
	CStateMgr();
	~CStateMgr();

public:
	void		Initialize();
	void		Release();

	void		SetState(CPlayer* _pPlayer, IPlayerState*& _pState);
	void		Update(CPlayer* _pPlayer, IPlayerState*& _pState);

	void		ChangeState(int _iActionState, IPlayerState*& _pState);

private:
	CIdleState*		m_pIdle;
	CWalkState*		m_pWalking;
	CActState*		m_pActing;
	CRollState*		m_pRolling;
	CGetState*		m_pGetting;
	CCarryState*	m_pCarrying;
	CHitState*		m_pHitted;
	CDeadState*		m_pDead;
};
