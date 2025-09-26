#include "stdafx.h"
#include "EffectMgr.h"
#include "Effect.h"

#include "BmpMgr.h"

CEffectMgr* CEffectMgr::m_pInstance = nullptr;

CEffectMgr::CEffectMgr()
{
	CBmpMgr::GetInstance()->InsertBmp(L"HIT", L"../Sprites/Vfx/hit.bmp");
}

CEffectMgr::~CEffectMgr()
{
	Release();
}

void CEffectMgr::Initialize()
{
	vector<CEffect*> vecTemp;

	HDC Temp = CBmpMgr::GetInstance()->FindBmp(L"HIT");

	for (size_t i = 0; i < 10; ++i)
	{
		vecTemp.emplace_back(new CEffect(Temp, { 500, 52 }, 4));
		vecTemp.back()->Initialize();
	}

	m_mapEffect.insert({ L"HIT", vecTemp });
}

void CEffectMgr::Release()
{
	//for_each(m_mapEffect.begin(), m_mapEffect.end(), [](auto& Pair) {
	//	if (!Pair.second.empty())
	//	{
	//		for_each(Pair.second.begin(), Pair.second.end(), Safe_Delete<CEffect*>);
	//	}
	//	});
}

void CEffectMgr::PlayEffect(const TCHAR* _szKey, VEC2 _vPos)
{
	auto Result = find_if(m_mapEffect.begin(), m_mapEffect.end(), [&](auto& Pair) {

		return !lstrcmp(Pair.first, _szKey);
		});

	if (Result == m_mapEffect.end())
		return;

	for (auto iter = (*Result).second.begin();
		iter != (*Result).second.end(); ++iter)
	{
		if (!(*iter)->GetActive())
		{
			(*iter)->Play(_vPos);
			return;
		}
	}
}
