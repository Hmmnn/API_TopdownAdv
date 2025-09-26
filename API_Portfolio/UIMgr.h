#pragma once

#include "Define.h"

class CUIMgr
{
	SINGLETON(CUIMgr)

private:
	CUIMgr();
	~CUIMgr();

public:
	void		InitializePlayerHp(int* _pHp);
	void		InitializeKeyGuide();
	void		InitializeBudget();

	void		SetActionKeyGuide(int _iIndex, HDC _hImage);
	void		RenderActionKey(HDC hDC);
	void		SetBudget(const int* _pBudget);

private:


	class CHeartHpBar*	m_pPlayerHpBar;
	class CKeyGuide*	m_pKeyGuide;
	class CBudget*		m_pBudget;
};