#include "stdafx.h"
#include "StoppedImage.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"

CStoppedImage::CStoppedImage() :
	m_hMemDC(NULL), m_vPos(), m_vSize(), m_vFullSize(),
	m_iCurFrame(0), m_iLastFrame(0),
	m_bScroll(false)
{
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CStoppedImage::CStoppedImage(HDC _hMemDC, VEC2 _vFullSize, int _iLastFrame) :
	m_hMemDC(_hMemDC), m_vPos(), m_vFullSize(_vFullSize), 
	m_iCurFrame(0), m_iLastFrame(_iLastFrame),
	m_bScroll(false)
{
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CStoppedImage::~CStoppedImage()
{
	Release();
}

void CStoppedImage::Initialize()
{
	m_vSize = { m_vFullSize.fX / (m_iLastFrame + 1), m_vFullSize.fY };

	UpdateRect();
}

void CStoppedImage::Render(HDC hDC)
{
	if (m_bScroll)
	{
		int iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
		int iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

		GdiTransparentBlt(hDC,
			(int)m_tRect.left + iScrollX,
			(int)m_tRect.top + iScrollY,
			(int)m_vSize.fX,
			(int)m_vSize.fY,
			m_hMemDC,
			(int)m_iCurFrame * m_vSize.fX, 0,
			(int)m_vSize.fX,
			(int)m_vSize.fY,
			RGB(255, 0, 255));
	}
	else
	{
		GdiTransparentBlt(hDC,
			(int)m_tRect.left,
			(int)m_tRect.top,
			(int)m_vSize.fX,
			(int)m_vSize.fY,
			m_hMemDC,
			(int)m_iCurFrame * m_vSize.fX, 0,
			(int)m_vSize.fX,
			(int)m_vSize.fY,
			RGB(255, 0, 255));
	}

	
}

void CStoppedImage::Release()
{
}

void CStoppedImage::UpdateRect()
{
	m_tRect.left	= LONG(m_vPos.fX - (m_vSize.fX * 0.5f));
	m_tRect.top		= LONG(m_vPos.fY - (m_vSize.fY * 0.5f));
	m_tRect.right	= LONG(m_vPos.fX + (m_vSize.fX * 0.5f));
	m_tRect.bottom	= LONG(m_vPos.fY + (m_vSize.fY * 0.5f));
}

void CStoppedImage::SetNewSprite(HDC _hMemDC, VEC2 _vFullSize, int _iLastFrame)
{
	m_hMemDC = _hMemDC;

	m_vFullSize = _vFullSize;

	m_iCurFrame = 0;
	m_iLastFrame = _iLastFrame;

	Initialize();
}
