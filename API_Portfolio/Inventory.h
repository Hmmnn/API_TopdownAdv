#pragma once

#include "Obj.h"
#include "Item.h"
#include "AnimImage.h"

class CInventory
{
	SINGLETON(CInventory)

	typedef struct tagItemSlot
	{
		bool				bSeleted;
		CItem::ITEMTYPE		eType;
		int					iCount;
		CObj*				pItem;
		HDC					hBG;
		VEC2				vPos;
		VEC2				vSize;

	}ITSLOT;

	typedef struct tagCursor
	{
		int			iIndex;
		VEC2		vPos;
		VEC2		vSize;
		RECT		tRect;
		CAnimImage* hImage;

		tagCursor(HDC _hMemDC, FRAME* _tFrame) : iIndex(0), vPos(), vSize()
		{
			ZeroMemory(&tRect, sizeof(RECT));
			hImage = new CAnimImage(_hMemDC);
			hImage->ResizeFrameVec(1);
			hImage->SetPos(&vPos);
			hImage->SetSize(vSize);
			hImage->SetRect(&tRect);
			hImage->SetFrame(0, _tFrame);
			hImage->SetMotion(0);
		}
			
		~tagCursor()
		{
			Safe_Delete<CAnimImage*>(hImage);
		}

		void	UpdateRect()
		{
			tRect.left		= (LONG)(vPos.fX - vSize.fX * 0.5f);
			tRect.top		= (LONG)(vPos.fY - vSize.fY * 0.5f);
			tRect.right		= (LONG)(vPos.fX + vSize.fX * 0.5f);
			tRect.bottom	= (LONG)(vPos.fY + vSize.fY * 0.5f);
		}

	}CURSOR;

private:
	CInventory();
	~CInventory();

public:
	void		Initialize();
	void		Release();

	void		EnterInventory();
	void		ExitInventory();

	bool		AddItem(CItem::ITEMTYPE _eType, CObj* _pItem); 
	void		ApplyItem(CItem::ITEMTYPE _eType, CObj* _pTarget);

	void		ControlCursor();
	void		RenderItems(HDC hDC);

public:
	bool		GetActive()			{ return m_bActive; }
	const int*	GetRupeePointer()	{ return &m_iRupee; }

private:
	bool		m_bActive;

	HDC			m_hInvenBG;
	HDC			m_hInven;

	CURSOR*		m_tCursor;

	array<array<ITSLOT*, 4>, 3> m_Slots;

	int			m_iCount;

	int			m_iRupee;

	int			m_iSlotZ;
	int			m_iSlotX;
};