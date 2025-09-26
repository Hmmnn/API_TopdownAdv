#pragma once

#include "Define.h"

class CAnimImage
{
public:
	CAnimImage();
	CAnimImage(HDC _hMemDC);
	~CAnimImage();

public:
	void		ResizeFrameVec(int _iIndex);

	int			RunAnimation();
	int			RunAnimation(int _iIndex);

	void		Render(HDC hDC, int& _iScrollX, int& _iScrollY);
	void		Release();

public:
	int			GetMotion()				{ return m_pCurFrame.iMotion; }
	float&		GetTime()				{ return m_pCurFrame.fTime; }

	void		SetPos(VEC2* _pPos)		{ m_pPos = _pPos; }
	void		SetSize(VEC2 _tSize)	{ m_vSize = _tSize; }
	void		SetRect(RECT* _pRect)	{ m_pRect = _pRect; }
	void		SetMemDC(HDC _hMemDC)	{ m_hMemDC = _hMemDC; }
	void		SetFrame(int _iMotion, int _iFirstFrame, int _iLastFrame, bool _bLoop = true, float _fFrameRate = (1.0f / 24.f))
	{
		m_vecFrame[_iMotion] = new FRAME;
		*m_vecFrame[_iMotion] = { _iMotion, _iFirstFrame, _iLastFrame, _bLoop, _fFrameRate, 0.f };
	}
	void		SetFrame(int _iIndex, int _iMotion, int _iFirstFrame, int _iLastFrame, bool _bLoop = true, float _fFrameRate = (1.f / 24.f))
	{
		m_vecFrame[_iIndex] = new FRAME;
		*m_vecFrame[_iIndex] = { _iMotion, _iFirstFrame, _iLastFrame, _bLoop, _fFrameRate, 0.f };
	}
	void		SetFrame(int _iIndex, FRAME* _tFrame)
	{
		m_vecFrame[_iIndex] = _tFrame;
	}
	void		SetMotion(int _iIndex) { m_pCurFrame = *m_vecFrame[_iIndex]; }
	void		SetActionFrame(int _iIndex, int _iActionStart, int _iActionEnd)
	{
		m_vecFrame[_iIndex]->iActionStart = _iActionStart;
		m_vecFrame[_iIndex]->iActionEnd = _iActionEnd;
	}

private:
	VEC2*		m_pPos;
	VEC2		m_vSize;
	RECT*		m_pRect;

	HDC			m_hMemDC;

	vector<FRAME*> m_vecFrame;
	FRAME		m_pCurFrame;
};