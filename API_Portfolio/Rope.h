#pragma once

#include "GameObj.h"

class CRope : public CGameObj
{
private:
	enum ROPE_ST { IDLE, PATROL, CHASE, ATTACK, HIT, DEAD, ST_END };

public:
	CRope();
	~CRope();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	OnCollision(CObj* _pOther) override;

	virtual void	CollisionMapObj() override;
	virtual void	CollisionGameObj() override;

	virtual void	CollisionPush(CObj* _pOther) override;

	virtual void	TakeDamage(int _iDamage) override;

private:
	void			CheckState();
	void			ApplyState();
	void			CheckTargetDistance();

	void			Patrol();
	void			Chase();

	virtual void	InitializeMotion() override;
	void			InitializeSkill();

public:
	void		SetTarget(CObj* _pTarget) { m_pTarget = _pTarget; }

private:
	ROPE_ST		m_ePreState;
	ROPE_ST		m_eCurState;

	float		m_fAtkTime;
	float		m_fAtkInterval;

	float		m_fHitTime;
	float		m_fHitInterval;

	class CSkill* m_pSkillSlot;

	CObj*		m_pTarget;

	VEC2		m_vPatrolStartPos;
	float		m_fPatrolRange;

	float		m_fChaseTime;
	float		m_fChaseInterval;
	VEC2		m_vChaseGoal;

};