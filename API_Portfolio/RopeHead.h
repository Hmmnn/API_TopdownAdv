#pragma once

#include "GameObj.h"

class CRopeHead : public CGameObj
{
public:
	CRopeHead();
	~CRopeHead();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void	OnCollision(CObj* _pOther) override;

	void		ClearHitted();

	void		SetDirOffset(VEC2 _vPos, DIRECTION _eDir);

private:
	VEC2		m_vOffset;
};