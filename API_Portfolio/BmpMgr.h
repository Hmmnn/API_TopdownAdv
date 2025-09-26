#pragma once

#include "MyBmp.h"

class CBmpMgr
{
	SINGLETON(CBmpMgr)

private:
	CBmpMgr();
	~CBmpMgr();

public:
	void		InsertBmp(const TCHAR* _pKey, const TCHAR* _pFilePath);
	HDC			FindBmp(const TCHAR* _pKey);

	void		Release();

private:
	map<const TCHAR*, CMyBmp*>	m_BmpMap;
};