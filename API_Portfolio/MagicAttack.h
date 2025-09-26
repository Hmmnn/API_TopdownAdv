#pragma once

#include "Skill.h"

class CMagicAttack : public CSkill
{
public:
	CMagicAttack();
	~CMagicAttack();

	virtual void Initialize() override;
	virtual void Release() override;

	virtual void ActivateSkill() override;
	virtual void ExecuteSkill() override;
	virtual void DeactivateSkill() override;

private:
	vector<CObj*>	m_vecMagic;
};