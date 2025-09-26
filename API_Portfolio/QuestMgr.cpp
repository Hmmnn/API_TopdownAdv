#include "stdafx.h"
#include "QuestMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

CQuestMgr::CQuestMgr()
{
}

CQuestMgr::~CQuestMgr()
{
	Release();
}

void CQuestMgr::Initialize()
{
}

void CQuestMgr::Release()
{
	for (auto& Pair : m_mapScript)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}

	m_mapScript.clear();
}

void CQuestMgr::EnterScript(const TCHAR* _szKey)
{
	m_bActive = true;

	CTimeMgr::GetInstance()->Pause();

	SetNextScript(_szKey);
}

void CQuestMgr::ExitScript()
{

}

void CQuestMgr::SetNextScript(const TCHAR* _szKey)
{
	if (!m_bActive)
		return;
}
