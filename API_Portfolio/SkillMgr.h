#pragma once

#include "Skill.h"

class CSkillMgr
{
	SINGLETON(CSkillMgr)

private:
	CSkillMgr();
	~CSkillMgr();

public:
	void		AddSkill(const TCHAR* _pKey, CSkill* _pSkill);
	CSkill*		FindSkill(const TCHAR* _pKey);

private:
	void		Release();

private:
	unordered_map<const TCHAR*, CSkill*>		m_mapSkill;
};