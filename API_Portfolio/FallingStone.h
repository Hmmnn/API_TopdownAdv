#pragma once

#include "GameObj.h"

class CFallingStone : public CGameObj
{
	friend class CPhase2Boss;

public:
	CFallingStone();
	~CFallingStone();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	OnCollision(CObj* _pOther) override;

	virtual void	CollisionMapObj() override;
	virtual void	CollisionGameObj() override;

	void		StartFalling(int _iLeft, int _iTop, int _iRight, int _iBottom);

private:
	void		EndFalling();
	void		ChangeMotion(int _iIndex);

	void		InitializeMotion();

private:
	VEC2		m_tEndPos;

	bool		m_bLanded;
};