#pragma once

#include "GameObj.h"

class CPhase2Boss : public CGameObj
{
private:
	enum BOSS_STATE { TRANSFORM, IDLE, CHASE, ATTACK1, ATTACK2, GROGGY, HIT, DEAD, ST_END };
	enum MOTIONID { M_TRANS, M_IDLE, M_GROGGY, M_HIT, M_ATTACK, MT_END };

public:
	CPhase2Boss();
	~CPhase2Boss();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	CollisionMapObj() override;
	virtual void	CollisionGameObj() override;

	virtual void	TakeDamage(int _iDamage) override;

private:
	void		CheckState();
	void		ApplyState();
	void		ChangeMotion();

	void		SelectEyes();
	bool		CheckEyes();

	void		InitializePatternObj();
	void		InitializeMotion();

public:
	void		SetvecTrap(vector<CObj*>* _pTraps) { m_pTraps = _pTraps; }

private:
	BOSS_STATE	m_eCurState;
	BOSS_STATE	m_ePreState;

	CObj*		m_pTarget;

	bool		m_bTransforming;
	float		m_fTestTime;

	float		m_fChaseTime;
	float		m_fChaseInterval;

	float		m_fHitTime;
	float		m_fHitInterval;

	float		m_fAttackTime1;
	float		m_fAttackInterval1;

	float		m_fAttackTime2;
	float		m_fAttackInterval2;

	vector<CObj*> m_vecEye;
	vector<CObj*> m_vecStone;
	vector<CObj*>* m_pTraps;

	VEC2		m_tEyeOffset;
};