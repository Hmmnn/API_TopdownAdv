#pragma once

#include "Obj.h"

class CSkill
{
public:
	CSkill();
	virtual ~CSkill();

	virtual void		Initialize()		PURE;
	virtual void		Release()			PURE;
	
	virtual void		ActivateSkill()		PURE;
	virtual void		ExecuteSkill()		PURE;
	virtual void		DeactivateSkill()	PURE;

	virtual void		ActivateDefaultSkill()	{}
	virtual void		ActivateChargeSkill()	{}
	virtual void		CheckChargeTime()		{}

public:
	void		SetOwner(CObj* _pOwner)		{ m_pOwner = _pOwner; }
	void		SetMotionIndex(int _iIndex) { m_iMotionIndex = _iIndex; }
	void		SetChargeMotion(int _iIndex) { m_iChargeMotion = _iIndex; }
	void		SetActivated(bool _bActive) { m_bActivated = _bActive; }

	int			GetMotionIndex()	{ return m_iMotionIndex; }
	int			GetChargeMotion()	{ return m_iChargeMotion; }
	float		GetChargeTime()		{ return m_fChargeTime; }
	bool		GetActivated()		{ return m_bActivated; }

protected:
	CObj*			m_pOwner;
	int				m_iMotionIndex;
	int				m_iChargeMotion;

	bool			m_bActivated;

	float			m_fChargeTime;

	bool			m_bCharge;

	//set<CObj*>		m_setCollided;
};