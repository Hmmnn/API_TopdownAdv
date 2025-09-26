#pragma once

#include "Skill.h"

class CMeleeAttack : public CSkill
{
public:
	CMeleeAttack();
	~CMeleeAttack();

	virtual void		Initialize()		override;
	virtual void		Release()			override;
	
	virtual void		ActivateSkill()		override;
	virtual void		ExecuteSkill()		override;
	virtual void		DeactivateSkill()	override;

	virtual void		ActivateDefaultSkill() override;
	virtual void		ActivateChargeSkill() override;
	virtual void		CheckChargeTime()	override;

private:
	void		InitializeMelee();
	void		InitializeSpin();

private:
	float		m_fAngleSpeed;
	float		m_fDist;

	CObj*		m_pSword;

	bool		m_bSpin;
};