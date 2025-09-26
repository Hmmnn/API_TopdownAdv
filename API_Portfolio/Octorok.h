#pragma once

#include "GameObj.h"

class COctorok : public CGameObj
{
	enum OCTO_ST { IDLE, ATTACK, HIT, DEAD, ST_END };

public:
	COctorok();
	~COctorok();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	OnCollision(CObj* _pOther) override;

	virtual void	CollisionMapObj() override;
	virtual void	CollisionGameObj() override;

	virtual void	TakeDamage(int _iDamage) override;

private:
	void			CheckState();
	void			CheckTargetDistance();
	void			ApplyState();

	virtual void	InitializeMotion() override;
	void			InitializeSkill();

public:
	void		SetTarget(CObj* _pTarget) { m_pTarget = _pTarget; }

private:
	OCTO_ST		m_ePreState;
	OCTO_ST		m_eCurState;

	float		m_fAtkTime;
	float		m_fAtkInterval;

	float		m_fHitTime;
	float		m_fHitInterval;

	CObj*		m_pTarget;

	class CSkill*	m_pSkillSlot;
};