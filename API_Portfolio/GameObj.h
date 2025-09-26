#pragma once

#include "Obj.h"
#include "AnimImage.h"

class CCollider;

class CGameObj : public CObj
{
public:
	CGameObj();
	virtual ~CGameObj();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	CollisionMapObj()	{}
	virtual void	CollisionGameObj()	{}

	virtual void	CollisionPush(CObj* _pOther);


	virtual void	TakeDamage(int _iDamage) {}

	void			HealHp(int _iValue);

protected:
	virtual void	InitializeMotion() {}

public:
	float			GetSpeed()		{ return m_fSpeed; }
	DIRECTION		GetDir()		{ return m_eDir; }
	int				GetAtk()		{ return m_iAtk; }
	const VEC2&		GetVelocity()	{ return m_vVelocity; }
	int*			GetHpPointer()	{ return &m_iHp; }

	void			SetSpeed(float _Value) { m_fSpeed = _Value; }
	void			SetDir(DIRECTION _eDir) { m_eDir = _eDir; }
	void			SetVelocity(VEC2 _vVelocity) { m_vVelocity = _vVelocity; }
	void			SetAtk(int _iDelta) { m_iAtk += _iDelta; }

protected:
	bool			m_bDead;

	VEC2			m_vVelocity;
	float			m_fSpeed;
	bool			m_bRight;

	DIRECTION		m_eDir;

	vector<CAnimImage*> m_vecMotion;
	int				m_iAnimState;

	int				m_iMaxHp;
	int				m_iHp;

	int				m_iAtk;
};