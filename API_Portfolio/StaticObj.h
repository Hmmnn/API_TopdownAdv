#pragma once

#include "Obj.h"
#include "RectCollider.h"

class CStaticObj : public CObj
{
protected:
	enum STATE { OFF, ON, ST_END };

public:
	CStaticObj();
	CStaticObj(float _fX, float _fY, float _fCX, float _fCY);
	virtual ~CStaticObj();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void		ChangeState(bool _bValue) { m_eState = (_bValue) ? ON : OFF; }

protected:
	int			RunAnimation();

	virtual void		InitializeImage() {}

public:
	void		SetCollider(CCollider::SHAPE _eShape, float _fCX, float _fCY);
	void		SetMemDC(HDC _hMemDC) { m_hMemDC = _hMemDC; }
	void		SetFrame(FRAME* _pFrame) { m_vecFrame.push_back(_pFrame); }

protected:
	STATE		m_eState;

	HDC			m_hMemDC;
	
	vector<FRAME*> m_vecFrame;
	//FRAME*		m_pCurFrame;
};