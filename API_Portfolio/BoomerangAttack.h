#pragma once

#include "Skill.h"

class CBoomerangAttack : public CSkill
{
public:
	CBoomerangAttack();
	~CBoomerangAttack();

	virtual void Initialize() override;
	virtual void Release() override;

	virtual void ActivateSkill() override;
	virtual void ExecuteSkill() override;
	virtual void DeactivateSkill() override;

private:
	CObj*		m_pBoomerang;
};