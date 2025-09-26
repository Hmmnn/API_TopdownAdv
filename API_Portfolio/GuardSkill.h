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

	// ���� �ð� �ʿ�
	// �� �ݶ��̴��� �浹�ϸ� ����� ��ȿ
};