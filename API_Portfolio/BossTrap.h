#pragma once

#include "StaticObj.h"

class CBossTrap : public CStaticObj
{
	friend class CPhase1Boss;

public:
	CBossTrap();
	~CBossTrap();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void	OnCollision(CObj* _pOther) override;

private:
	void		InitFrame();

private:
	CObj*		m_pOwner;

	float		m_fActiveTime;
	float		m_fActiveInterval;

	bool		m_bReady;
	float		m_fPreTime;
	float		m_fReadyTime;

	int			m_iAtk;

	HBRUSH		m_hRed;
};