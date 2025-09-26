#pragma once
#pragma once

#include "Define.h"

class CScrollMgr
{
	SINGLETON(CScrollMgr)

private:
	CScrollMgr();
	~CScrollMgr();

public:
	void		UpdateScroll();
	void		ScrollLock();

	bool		IsCulling(VEC2 _vPos, VEC2 _vSize);

public:
	float		GetScrollX() const	{ return m_fScrollX; }
	float		GetScrollY() const	{ return m_fScrollY; }
	VEC2		GetMapSize() const	{ return m_tMapSize; }
	
	void		SetScrollX(float _fX)	{ m_fScrollX += _fX; }
	void		SetScrollY(float _fY)	{ m_fScrollY += _fY; }

	void		SetMapSize(VEC2 _tMapSize) { m_tMapSize = _tMapSize; }
	void		SetPos(VEC2 _tPos) 
	{
		m_fScrollX = _tPos.fX;
		m_fScrollY = _tPos.fY;
	}

	void		SetTarget(VEC2* _vPos) 
	{ 
		m_pTargetPos = _vPos; 
		m_bTarget = (_vPos != nullptr) ? true : false;
	}

private:	
	float		m_fScrollX;
	float		m_fScrollY;

	VEC2		m_tMapSize;

	bool		m_bTarget;
	VEC2*		m_pTargetPos;
};

