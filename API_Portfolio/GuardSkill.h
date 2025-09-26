#pragma once

#include "Skill.h"

class CGuardSkill : public CSkill
{
public:
	CGuardSkill();
	~CGuardSkill();

	virtual void Initialize() override;
	virtual void Release() override;
	
	virtual void ActivateSkill() override;
	virtual void ExecuteSkill() override;
	virtual void DeactivateSkill() override;

private:
	CObj*		m_pShield;

	// 제한 시간 필요
	// 적 콜라이더와 충돌하면 대미지 무효
};