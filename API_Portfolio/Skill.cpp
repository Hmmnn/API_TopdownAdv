#include "stdafx.h"
#include "Skill.h"

CSkill::CSkill() :
	m_pOwner(nullptr), m_bActivated(false), m_iMotionIndex(0), m_iChargeMotion(0),
	m_fChargeTime(0), m_bCharge(false)
{
}

CSkill::~CSkill()
{
}
