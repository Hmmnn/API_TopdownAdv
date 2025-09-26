#pragma once

#include "GameObj.h"

class CShieldEye : public CGameObj
{
	enum EYESTATE { SPAWN, IDLE, BLANK, TURNNING, ANSWER, HIT, DESTROYED, ST_END };

public:
	CShieldEye();
	~CShieldEye();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	OnCollision(CObj* _pOther) override;

	virtual void	TakeDamage(int _iDamage) override;

	void		Respawn();
	void		Destroy();

public:
	bool		GetSelected() { return m_bSelected; }

	void		SetOwnerPos(VEC2* _pPos) { m_vOwnerPos = _pPos; }
	void		SetOffset(VEC2 _tOffset) { m_vOffset = _tOffset; }
	void		SetSelected(bool _bSelected) { m_bSelected = _bSelected; }

private:
	void		CheckState();

	void		InitializeMotion();

private:
	EYESTATE	m_eCurState;
	EYESTATE	m_ePreState;

	VEC2*		m_vOwnerPos;
	VEC2		m_vOffset;

	bool		m_bSelected;
};