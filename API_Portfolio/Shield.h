#pragma once

#include "StaticObj.h"

class CShield : public CStaticObj
{
public:
	CShield();
	~CShield();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	OnCollision(CObj* _pOther) override;

	void		SetShieldDir(DIRECTION _eDir, VEC2 _vOwnerPos);

private:
	void		CheckTimeLimit();

public:
	void		SetOffset(VEC2 _vOffset) { m_vOffset = _vOffset; }

	VEC2		GetOffset() { return m_vOffset; }

private:
	VEC2		m_vOffset;

	float		m_fAtkTime;
	float		m_fTimeLimit;
};