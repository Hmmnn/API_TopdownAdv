#pragma once

#include "Obj.h"

class CCollider
{
public:
	enum SHAPE { SQUARE, SPHERE, SHAPE_END };

public:
	CCollider();
	CCollider(CObj* _pOwner, VEC2 _Size);
	virtual ~CCollider();

	void	UpdateRect();

	virtual void	Render(HDC hDC)		PURE;

	void		DrawCollided(bool _bCollided);

	bool		AddHitted(CObj* _pOther);
	void		ClearHitted();

public:
	SHAPE		GetShape()		{ return m_eShape; }
	CObj*		GetOwner()		{ return m_pOwner; }
	bool		GetActive()		{ return m_bActive; }
	VEC2		GetPos()		{ return m_vPos; }
	VEC2		GetSize()		{ return m_vSize; }
	RECT		GetRect()		{ return m_tRect; }
	RECT		GetOverlap()	{ return m_tOverlap; }
	LONG		GetBottom()		{ return m_tRect.bottom; }
	
	void		SetOwner(CObj* _pOwner) { m_pOwner = _pOwner; }
	void		SetPos(VEC2 _tPos)		{ m_vPos = _tPos; }
	void		SetSize(VEC2 _tSize)	{ m_vSize = _tSize; }
	void		SetOffset(VEC2 _tOffset) { m_tOffset = _tOffset; }
	void		SetOverlap(RECT _tRc)	{ m_tOverlap = _tRc; }
	void		SetActive(bool _bActive) { m_bActive = _bActive; }

protected:
	SHAPE		m_eShape;

	CObj*		m_pOwner;
	bool		m_bActive = true;

	VEC2		m_vPos;
	VEC2		m_vSize;
	VEC2		m_tOffset;

	RECT		m_tRect;

	RECT		m_tOverlap;

	bool		m_bCollided;
	HBRUSH		m_hBrush;
	HBRUSH		m_hGreen;
	HBRUSH		m_hRed;

	set<CObj*>	m_setHitted;
};

