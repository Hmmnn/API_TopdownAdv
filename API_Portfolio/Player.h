#pragma once

#include "GameObj.h"
#include "PlayerState.h"

class CRectCollider;
class CSkill;
//class IPlayerState;

#define DEF_SPEED 200.f

class CPlayer :	public CGameObj
{
private:	
	enum MOTION_ST { IDLE, WALK, MELEE, ROLL, HIT, DEAD,
		ARROW, GUARD, BOOMERANG, MAGIC, SPIN, GET, PUSH, PULL, MOTION_END };
	
	enum ACTION_ST { ACT_IDLE, ACT_WALK, ACT_ACTION, ACT_ROLL,
		ACT_GET, ACT_CARRY, ACT_HIT, ACT_DEAD, ACT_END };

public:
	CPlayer();
	~CPlayer();

public:
	virtual void		Initialize() override;
	virtual int			Update() override;
	virtual void		LateUpdate() override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release() override;

	//virtual void		CollisionMapObj() override;
	//virtual void		CollisionGameObj() override;

	virtual void		OnCollision(CObj* _pOther) override;
	virtual void		TakeDamage(int _iDamage) override;

	void				SetSkill(int _iSlotNum, const TCHAR* _pKey);

private:
	void		CheckMotionState();
	void		TransitActionState();
	void		ChangeState();
	void		ChangeMotion(MOTION_ST _eState);
	void		Scroll();

	void		InitializeMotion();
	void		InitializeSkill();

private:
	MOTION_ST		m_eMotionState;

	ACTION_ST		m_ePreActionST;
	ACTION_ST		m_eCurActionST;

	float			m_fHitTime;

	vector<CSkill*> m_vecSkillSlot;
	CSkill*			m_pUsingSkill;

	IPlayerState*	m_pState;
	
	friend class CIdleState;
	friend class CWalkState;
	friend class CActState;
	friend class CRollState;
	friend class CGetState;
	friend class CCarryState;
	friend class CHitState;
	friend class CDeadState;
};

