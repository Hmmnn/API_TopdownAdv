#pragma once

#include "GameObj.h"

class CKeeseBody : public CGameObj
{
public:
	CKeeseBody();
	~CKeeseBody();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	OnCollision(CObj* _pOther) override;

	virtual void	CollisionMapObj() override;
	virtual void	CollisionGameObj() override;

	void			ClearHitted();

public:
	void			SetOwnerPos(const VEC2& _vPos) { m_vPos = _vPos; }

private:
	//VEC2			m_vOwnerPos;

	float			m_fAtkTime;
	float			m_fAtkLength;

};