#pragma once

#include "Define.h"

class CCollider;

class CObj
{
public:
	CObj();
	CObj(float _fX, float _fY, float _fCX, float _fCY);
	virtual ~CObj();

public:
	virtual void	Initialize()		PURE;
	virtual int		Update()			PURE;
	virtual void	LateUpdate()		PURE;
	virtual void	Render(HDC hDC)		PURE;
	virtual void	Release()			PURE;

	virtual void	OnCollision(CObj* _pOther) {}

protected:
	void			UpdateRect();

public:
	OBJTYPE			GetType()		{ return m_eObjType; }
	bool			GetActive()		{ return m_bActive; }
	const VEC2&		GetPos()		{ return m_vPos; }
	const VEC2&		GetSize()		{ return m_vSize; }
	RECT			GetRect()		{ return m_tRect; }
	CCollider*		GetCollider()	{ return m_pCollider; }
	VEC2*			GetPosPointer() { return &m_vPos; }
	RENDERID		GetRenderID()	{ return m_eRenderID; }
	int				GetCellX()		{ return m_iCellX; }
	int				GetCellY()		{ return m_iCellY; }

	void			SetActive(bool _Value)			{ m_bActive = _Value; }
	virtual void	SetPos(float _fX, float _fY)	{ m_vPos = { _fX, _fY }; }
	virtual void	SetPos(VEC2 _vPos)				{ m_vPos = _vPos; }
	virtual void	SetSize(float _fCX, float _fCY) { m_vSize = { _fCX, _fCY }; }
	virtual void	SetSize(VEC2 _vSize)			{ m_vSize = _vSize; }
	void			SetCellX(int _iCellX)			{ m_iCellX = _iCellX; }
	void			SetCellY(int _iCellY)			{ m_iCellY = _iCellY; }

protected:
	OBJTYPE		m_eObjType;
	RENDERID	m_eRenderID;

	bool		m_bActive;

	VEC2		m_vPos;
	VEC2		m_vSize;
	RECT		m_tRect;

	CCollider*	m_pCollider = nullptr;

	int			m_iCellX;
	int			m_iCellY;
};

