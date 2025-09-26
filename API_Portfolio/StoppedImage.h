#pragma once

#include "Define.h"

class CStoppedImage
{
public:
	CStoppedImage();
	CStoppedImage(HDC _hMemDC, VEC2 _vFullSize, int _iLastFrame);
	~CStoppedImage();

	void		Initialize();
	void		Render(HDC hDC);
	void		Release();

	void		SetNewSprite(HDC _hMemDC, VEC2 _vFullSize, int _iLastFrame);

private:
	void		UpdateRect();

public:
	int			GetLastFrame()	{ return m_iLastFrame; }
	int			GetCurFrame()	{ return m_iCurFrame; }
	VEC2		GetPos()		{ return m_vPos; }

	void		SetPos(VEC2 _vPos) { m_vPos = _vPos; UpdateRect(); }
	void		SetCurFrame(int _iCurFrame) { m_iCurFrame = _iCurFrame; }
	void		SetScroll(bool _bScroll) { m_bScroll = _bScroll; }

private:
	HDC			m_hMemDC;
	
	VEC2		m_vPos;
	VEC2		m_vSize;
	RECT		m_tRect;
	VEC2		m_vFullSize;
	
	int			m_iCurFrame;
	int			m_iLastFrame;

	bool		m_bScroll;
};