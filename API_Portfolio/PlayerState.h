#pragma once

#include "StateInterface.h"

class CIdleState : public IPlayerState
{
public:
	virtual void		ChangeState(CPlayer* _pPlayer) override;
	virtual void		Update(CPlayer* _pPlayer) override;
};

class CWalkState : public IPlayerState
{
public:
	virtual void		ChangeState(CPlayer* _pPlayer) override;
	virtual void		Update(CPlayer* _pPlayer) override;
};

class CActState : public IPlayerState
{
public:
	virtual void		ChangeState(CPlayer* _pPlayer) override;
	virtual void		Update(CPlayer* _pPlayer) override;

private:
	float		m_fAtkTime = 0.f;
	float		m_fChargeTime = 1.5f;
	bool		m_bCharge = false;
};

class CRollState : public IPlayerState
{
public:
	virtual void		ChangeState(CPlayer* _pPlayer) override;
	virtual void		Update(CPlayer* _pPlayer) override;

};

class CGetState : public IPlayerState
{
public:
	virtual void		ChangeState(CPlayer* _pPlayer) override;
	virtual void		Update(CPlayer* _pPlayer) override;
};

class CCarryState : public IPlayerState
{
public:
	virtual void		ChangeState(CPlayer* _pPlayer) override;
	//virtual void		Update(CPlayer* _pPlayer, IPlayerState& _State) override;
};

class CHitState : public IPlayerState
{
public:
	//virtual void		SetState(CPlayer* _pPlayer, IPlayerState& _State) override;
	virtual void		Update(CPlayer* _pPlayer) override;
};

class CDeadState : public IPlayerState
{
public:
	//virtual void		SetState(CPlayer* _pPlayer, IPlayerState& _State) override;
	//virtual void		Update(CPlayer* _pPlayer, IPlayerState& _State) override;
};