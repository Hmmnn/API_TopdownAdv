#pragma once

#include "GameObj.h"

class CLaserBullet : public CGameObj
{
	enum PART { FIRST, SECOND, LAST, PART_END };

public:
	CLaserBullet();
	~CLaserBullet();

	virtual void	Initialize()	override;
	virtual int		Update()		override;
	virtual void	LateUpdate()	override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release()		override;

	virtual void	OnCollision(CObj* _pOther) override;

	void		Shooted(VEC2 _tPos);
	void		Reset();

private:
	VEC2		m_vInitColSize;
	VEC2		m_vColPos;
	//VEC2		m_vCurSize;

	bool		m_bWall;

	HDC			m_hTexture;
	int			m_iCurFrame;
	int			m_iLastFrame;
	float		m_fTime;
	float		m_fFrameRate;

	float		m_fAttackTime;
	float		m_fAttackInterval;
};