#pragma once

#include "Define.h"

class CKeyMgr
{
	SINGLETON(CKeyMgr)

private:
	CKeyMgr();
	~CKeyMgr();

public:
	bool		KeyDown(int _key);
	bool		KeyUp(int _key);
	bool		KeyPressing(int _key);

private:
	bool		m_KeyStates[KEY_MAX];
};