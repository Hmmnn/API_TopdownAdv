#pragma once

#include "GameObj.h"

class CSword : public CGameObj
{
public:
	CSword();
	~CSword();

	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	LateUpdate() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	virtual void	OnCollision(CObj* _pOther);

	void			ClearHitList();

private:
	void			MoveAround();

public:
	void		SetStartAngle(float _fAngle)		{ m_fStartAngle = _fAngle; }
	void		SetEndAngle(float _fAngle)			{ m_fEndAngle = _fAngle; }
	void		SetAngleSpeed(float _fAngleSpeed)	{ m_fAngleSpeed = _fAngleSpeed; }
	void		SetDistance(float _fDist)			{ m_fDist = _fDist; }
	void		SetOwnerPos(VEC2 _pPos)				{ m_vOwnerPos = _pPos; }

private:
	float		m_fStartAngle;
	float		m_fEndAngle;
	float		m_fAngle;
	float		m_fAngleSpeed;
	float		m_fDist;

	VEC2		m_vOwnerPos;
};

