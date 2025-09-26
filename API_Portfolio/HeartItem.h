#pragma once

#include "Item.h"

class CHeartItem : public CItem
{
public:
	CHeartItem();
	~CHeartItem();

	virtual void	Initialize() override;
	virtual void	Release() override;

	virtual void	OnCollision(CObj* _pOther) override;
	virtual void	CollisionGameObj() override;
	
	virtual void	ApplyAbility(CObj* _pTarget) override;

private:
};