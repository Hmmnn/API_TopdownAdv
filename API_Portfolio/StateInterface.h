#pragma once

#include "Define.h"

class CPlayer;

class IPlayerState
{
public:
	IPlayerState() {}
	virtual ~IPlayerState() {}

	virtual void		ChangeState(CPlayer* _pPlayer) {}
	virtual void		Update(CPlayer* _pPlayer) {}
};
