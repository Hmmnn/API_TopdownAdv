#pragma once

#include "Skill.h"

class CArrowAttack : public CSkill
{
public:
	CArrowAttack();
	~CArrowAttack();

	virtual void Initialize() override;
	virtual void Release() override;

	virtual void ActivateSkill() override;
	virtual void ExecuteSkill() override;
	virtual void DeactivateSkill() override;

public:
	void			SetOffset(VEC2 _tOffset) { m_tOffset = _tOffset; }

private:
	vector<CObj*>		m_vecArrow;

	VEC2				m_tOffset;
};