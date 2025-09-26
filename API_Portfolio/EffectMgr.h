#pragma once

#include "Define.h"

class CEffect;

class CEffectMgr
{
	SINGLETON(CEffectMgr)

private:
	CEffectMgr();
	~CEffectMgr();

public:
	void		Initialize();
	void		Release();

	void		PlayEffect(const TCHAR* _szKey, VEC2 _vPos);

private:
	map<const TCHAR*, vector<CEffect*>> m_mapEffect;
};