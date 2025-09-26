#pragma once

#include "Define.h"

class CMyBmp
{
public:
	CMyBmp();
	~CMyBmp();

	void		LoadBmp(const TCHAR* _pFilePath);
	void		Release();
	
	HDC			GetMemDC() { return m_hMemDC; }

private:
	HDC			m_hMemDC;
	HBITMAP		m_hBitmap;
	HBITMAP		m_hOldBmp;
};