#include "stdafx.h"
#include "SkillMgr.h"

CSkillMgr* CSkillMgr::m_pInstance = nullptr;

CSkillMgr::CSkillMgr()
{
}

CSkillMgr::~CSkillMgr()
{
    Release();
}

void CSkillMgr::AddSkill(const TCHAR* _pKey, CSkill* _pSkill)
{
    auto iter = find_if(m_mapSkill.begin(), m_mapSkill.end(), [&](auto& Pair) {

        return !lstrcmp(_pKey, Pair.first);
    });

    if (iter != m_mapSkill.end())
        return;

    m_mapSkill.insert({ _pKey, _pSkill });
}

CSkill* CSkillMgr::FindSkill(const TCHAR* _pKey)
{
    auto iter = find_if(m_mapSkill.begin(), m_mapSkill.end(), [&](auto& Pair) {

        return !lstrcmp(_pKey, Pair.first);
    });

    if (iter != m_mapSkill.end())
        return (*iter).second;

    return nullptr;
}

void CSkillMgr::Release()
{
    for_each(m_mapSkill.begin(), m_mapSkill.end(), [](auto& Pair) {
    
        if (Pair.second)
        {
            delete Pair.second;
            Pair.second = nullptr;
        }
    });

    m_mapSkill.clear();
}
