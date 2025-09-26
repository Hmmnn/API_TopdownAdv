#pragma once

#include "GameObj.h"

class CLaserEye;
class CBossTrap;

class CPhase1Boss : public CGameObj
{
private:
	enum BOSS_STATE		{ IDLE, CHASE, ATTACK1, ATTACK2, HIT, DEAD, BST_END };
	enum B1_MOTIONID	{ M_MOVE, M_ATTACK, M_HIT, MT_END };
	
public:
	CPhase1Boss();
	~CPhase1Boss();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	TakeDamage(int _iDamage) override;

	virtual void	OnCollision(CObj* _pOther) override;

	//virtual void	CollisionMapObj() override;
	//virtual void	CollisionGameObj() override;

	void		CollisionPush(CObj* _pOther);

private:
	void		CheckState();
	void		ChangeMotion(B1_MOTIONID _eMotionID);

	void		InitializePatternObj();
	void		InitializeMotion();

public:
	vector<CObj*>* GetvecTraps() { return &m_vecBossTrap; }

private:
	BOSS_STATE	m_eState;

	CObj*		m_pTarget;

	float		m_fChaseTime;
	float		m_fChaseInterval;

	float		m_fHitTime;
	float		m_fHitInterval;

	float		m_fAttackTime1;
	float		m_fAttackInterval1;

	float		m_fAttackTime2;
	float		m_fAttackInterval2;

	vector<CObj*> m_vecLaserEye;
	vector<CObj*> m_vecBossTrap;

	bool		m_bSheid;
	bool		m_bAttacking;
};