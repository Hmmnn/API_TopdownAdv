#pragma once

#include "GameObj.h"

class CMagicBullet : public CGameObj
{
public:
	CMagicBullet();
	~CMagicBullet();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	OnCollision(CObj* _pOther) override;

	virtual void	CollisionMapObj() override;
	virtual void	CollisionGameObj() override;

	void		Shoot(VEC2 _vPos, DIRECTION _eDir);

private:
	void			InitializeMotion();
};