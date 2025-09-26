#pragma once

#include "GameObj.h"

class CBoomerang : public CGameObj
{
public:
	CBoomerang();
	~CBoomerang();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	OnCollision(CObj* _pOther) override;

	virtual void	CollisionMapObj() override;
	virtual void	CollisionGameObj() override;

	void		ThrowBoomerang(VEC2 _vVelocity);

	void		ClearHitted();

private:
	void		ReturnToOwner();

	void		InitializeMotion();

public:
	void		SetOwner(CObj* _pOwner) { m_pOwner = _pOwner; }

private:
	CObj*		m_pOwner;
	
	CObj*		m_pTarget;

	float		m_fRange;
	VEC2		m_vPeak;

	bool		m_bReturning;
	
};