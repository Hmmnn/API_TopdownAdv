#pragma once

#include "GameObj.h"

class COctoBullet : public CGameObj
{
public:
	COctoBullet();
	~COctoBullet();
	
	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	OnCollision(CObj* _pOther) override;

	virtual void	CollisionMapObj() override;
	virtual void	CollisionGameObj() override;

	void			Shoot(VEC2 _vPos, DIRECTION _eDir);

private:
	virtual void	InitializeMotion() override;

};