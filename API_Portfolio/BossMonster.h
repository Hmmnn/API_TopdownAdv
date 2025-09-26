#pragma once

#include "GameObj.h"

class CBossMonster
{
	enum BOSS_PHASE { PHASE_1, PHASE_2, PHS_END };

public:
	CBossMonster();
	~CBossMonster();

	void		Initialize();
	void		CheckPhase();
	void		TriggerChange();
	void		Release();

private:
	void		ChangePhase();

private:;
	BOSS_PHASE		m_ePhase;

	vector<CObj*>	m_vecBoss;

	bool		m_bChanging;
};