#pragma once

#include "Skill.h"

class CKeeseSkill : public CSkill
{
public:
	CKeeseSkill();
	~CKeeseSkill();

	virtual void Initialize() override;
	virtual void Release() override;

	virtual void ActivateSkill() override;
	virtual void ExecuteSkill() override;
	virtual void DeactivateSkill() override;

private:
	CObj*		m_pBody;

	float		m_fDefaultSpeed;
	float		m_fDashSpeed;
};