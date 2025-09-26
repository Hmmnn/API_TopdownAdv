#pragma once

#include "GameObj.h"

class CLaserBullet;

class CLaserEye : public CGameObj
{
	friend class CPhase1Boss;

	enum LASERSTATE { IDLE, SHOOT, LST_END };

public:
	CLaserEye();
	~CLaserEye();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	TakeDamage(int _iDamage) override;

	virtual void	OnCollision(CObj* _pOther) override;
	virtual void	CollisionGameObj() override;

private:
	void		MoveAround();
	void		ShootLaser();

	void		InitializeMotion();

private:
	CObj*		m_pOwner;

	LASERSTATE	m_eState;

	VEC2		m_tInitColSize;
	VEC2		m_tInitColOffset;

	float		m_fAngle;
	float		m_fDist;
	float		m_fAngleSpeed;

	CObj*		m_pLaserBullet;

	float		m_fDeadTime;
	float		m_fRespawnTime;
};