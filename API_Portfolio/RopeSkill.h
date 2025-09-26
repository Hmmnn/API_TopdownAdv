#pragma once

#include "Skill.h"

class CRopeSkill : public CSkill
{
public:
	CRopeSkill();
	~CRopeSkill();

	virtual void Initialize() override;
	virtual void Release() override;

	virtual void ActivateSkill() override;
	virtual void ExecuteSkill() override;
	virtual void DeactivateSkill() override;

private:
	CObj*		m_pHead;

	float		m_fDefaultSpeed;
};