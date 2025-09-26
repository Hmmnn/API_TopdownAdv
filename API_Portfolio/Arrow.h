#pragma once

#include "GameObj.h"

class CArrow : public CGameObj
{
public:
	CArrow();
	~CArrow();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	OnCollision(CObj* _pOther) override;

	virtual void	CollisionMapObj() override;
	virtual void	CollisionGameObj() override;

	void			ShootArrow(VEC2 _tPos, DIRECTION _eDir);

private:
	void			SetDirection();
	void			InitializeMotion();

private:
	float			m_fOffset;
};