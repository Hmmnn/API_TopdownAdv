#pragma once

#include "GameObj.h"

class CKeese : public CGameObj
{
	enum	KEESE_ST {IDLE, CHASE, ATTACK, DEAD, ST_END};

public:
	CKeese();
	~CKeese();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	OnCollision(CObj* _pOther) override;

	virtual void	CollisionMapObj() override;
	virtual void	CollisionGameObj() override;

	virtual void	TakeDamage(int _iDamage) override;

protected:
	void			CheckState();
	void			ApplyState();
	void			CheckTargetDistance();

	void			Chase();

	virtual void	InitializeMotion() override;
	void			InitializeSkill();

public:
	void			SetTarget(CObj* _pTarget) { m_pTarget = _pTarget; }

private:
	CObj*			m_pTarget;

	class CSkill*	m_pSkillSlot;

	KEESE_ST		m_ePreState;
	KEESE_ST		m_eCurState;

	VEC2			m_vChaseGoal;
	float			m_fChaseTime;
	float			m_fChaseInterval;

	float			m_fDefaultSpeed;
	float			m_fDashSpeed;
};