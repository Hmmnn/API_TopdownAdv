#pragma once

#include "Obj.h"

class CMyButton : public CObj
{
public:
	CMyButton();
	~CMyButton();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	bool		GetSelected() { return m_bSelected;}
	bool		GetChecked() { return m_bChecked; }

	void		SetSelected(bool _bSelected) { m_bSelected = _bSelected; }
	void		SetChecked(bool _bChecked) { m_bChecked = _bChecked; }

	void		SetMemDC(HDC _hMemDC) { m_hMemDC = _hMemDC; }
	void		SetSceneID(SCENEID _eID) { m_eNextScene = _eID; }
	void		SetTitle(bool _bTitle) { m_bTitle = _bTitle; }

private:
	bool		m_bSelected;
	bool		m_bChecked;

	HBRUSH		m_hBrush;
	HBRUSH		m_hGreen;
	HBRUSH		m_hRed;
	HBRUSH		m_hBlue;

	HDC			m_hMemDC;

	SCENEID		m_eNextScene;
	bool m_bTitle;
	bool m_bShift;
};