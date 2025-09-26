#include "stdafx.h"
#include "Inventory.h"
#include "AnimImage.h"
#include "Player.h"

#include "TimeMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "UIMgr.h"

CInventory* CInventory::m_pInstance = nullptr;

CInventory::CInventory() :
	m_bActive(false), m_hInvenBG(NULL), m_hInven(NULL),
	m_tCursor(nullptr), m_iCount(0), m_iRupee(0),
	m_iSlotZ(-1), m_iSlotX(-1)
{
}

CInventory::~CInventory()
{
	Release();
}

void CInventory::Initialize()
{
	m_hInvenBG = CBmpMgr::GetInstance()->FindBmp(L"INVEN_BG");
	m_hInven = CBmpMgr::GetInstance()->FindBmp(L"INVEN");
	
	VEC2	vFirstPos = { 264, 172 };
	
	m_tCursor = new CURSOR(CBmpMgr::GetInstance()->FindBmp(L"INVEN_CURSOR"),
		new FRAME(0, 0, 1, true, 1.f / 5.f));
	m_tCursor->vPos = vFirstPos;
	m_tCursor->vSize = { 98, 84 };
	m_tCursor->hImage->SetSize(m_tCursor->vSize);
	m_tCursor->UpdateRect();

	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			m_Slots[i][j] = new ITSLOT;
			m_Slots[i][j]->bSeleted = false;
			m_Slots[i][j]->eType = CItem::IT_END;
			m_Slots[i][j]->iCount = 0;
			m_Slots[i][j]->pItem = nullptr;
			m_Slots[i][j]->hBG = CBmpMgr::GetInstance()->FindBmp(L"ITEM_BG");
			m_Slots[i][j]->vPos = { vFirstPos.fX + j * 146, vFirstPos.fY + i * 93 };
			m_Slots[i][j]->vSize = { 104, 76 };
		}
	}
}

void CInventory::Release()
{
	Safe_Delete<CURSOR*>(m_tCursor);
	
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			Safe_Delete<ITSLOT*>(m_Slots[i][j]);
		}
	}
}

void CInventory::EnterInventory()
{
	CTimeMgr::GetInstance()->Pause();

	m_bActive = true;
}

void CInventory::ExitInventory()
{
	CTimeMgr::GetInstance()->Resume();

	m_bActive = false;
}

bool CInventory::AddItem(CItem::ITEMTYPE _eType, CObj* _pObj)
{
	if (CItem::RUPEE == _eType)
	{
		m_iRupee += static_cast<CItem*>(_pObj)->GetValue();

		return true;
	}
	else
	{
		// 인벤이 가득 차 있는 경우
		if (12 <= m_iCount)
			return false;

		int i(0), j(0);

		for (; i < 3; ++i)
		{
			for (; j < 4; ++j)
			{
				if (!m_Slots[i][j]->pItem)
					continue;

				const TCHAR* szLeft = static_cast<CItem*>(m_Slots[i][j]->pItem)->GetName();
				const TCHAR* szRight = static_cast<CItem*>(_pObj)->GetName();

				if (!lstrcmp(szLeft, szRight))
				{
					m_Slots[i][j]->iCount += 1;
					return true;
				}
			}
		}

		m_Slots[m_iCount / 4][m_iCount % 4]->eType = _eType;
		m_Slots[m_iCount / 4][m_iCount % 4]->pItem = _pObj;
		m_Slots[m_iCount / 4][m_iCount % 4]->iCount += 1;

		++m_iCount;

		return true;
	}
	
	return false;
}

void CInventory::ApplyItem(CItem::ITEMTYPE _eType, CObj* _pTarget)
{
	for (auto& Slots : m_Slots)
	{
		auto iter = find_if(Slots.begin(), Slots.end(), [=](ITSLOT* pSlot) {
			return (pSlot->eType == _eType);
			});

		if (iter != Slots.end())
		{
			static_cast<CItem*>((*iter)->pItem)->ApplyAbility(_pTarget);
			--(*iter)->iCount;

			if (0 >= (*iter)->iCount)
			{
				(*iter)->bSeleted = false;
				(*iter)->eType = CItem::IT_END;
				(*iter)->iCount = 0;
				(*iter)->pItem = nullptr;
			}

			return;
		}
	}
}

void CInventory::ControlCursor()
{
	if (!m_bActive)
		return;

	int iCurY(m_tCursor->iIndex / 4), iCurX(m_tCursor->iIndex % 4);

	if (KEY_DOWN(VK_UP))
	{
		if (0 <= iCurY - 1)
		{
			iCurY -= 1;
			m_tCursor->iIndex -= 4;
		}
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		if (3 > iCurY + 1)
		{
			iCurY += 1;
			m_tCursor->iIndex += 4;
		}
	}
	else if (KEY_DOWN(VK_LEFT))
	{
		if (0 <= iCurX - 1)
		{
			iCurX -= 1;
			m_tCursor->iIndex -= 1;
		}
	}
	else if (KEY_DOWN(VK_RIGHT))
	{
		if (4 > iCurX + 1 && 12 > m_tCursor->iIndex + 1)
		{
			iCurX += 1;
			m_tCursor->iIndex += 1;
		}
	}
	else if (KEY_DOWN('C'))
	{
		m_Slots[iCurY][iCurX]->bSeleted = true;
	}
	else if (KEY_DOWN('V'))
	{
		m_Slots[iCurY][iCurX]->bSeleted = false;
	}

	else if (KEY_DOWN('Z'))
	{
		if (m_Slots[iCurY][iCurX]->bSeleted && CItem::EQUIP == m_Slots[iCurY][iCurX]->eType)
		{
			if (-1 != m_iSlotZ)
			{
				m_Slots[m_iSlotZ / 4][m_iSlotZ % 4]->bSeleted = false;
			}
		
			CItem* pTempItem = static_cast<CItem*>(m_Slots[iCurY][iCurX]->pItem);
			static_cast<CPlayer*>(CObjMgr::GetInstance()->GetBack(PLAYER))->SetSkill(0, pTempItem->GetSkillName());

			m_iSlotZ = iCurY * 4 + iCurX;

			CUIMgr::GetInstance()->SetActionKeyGuide(0, pTempItem->GetIconDC());
		}
	}

	else if (KEY_DOWN('X'))
	{
		if (m_Slots[iCurY][iCurX]->bSeleted && CItem::EQUIP == m_Slots[iCurY][iCurX]->eType)
		{
			if (-1 != m_iSlotX)
			{
				m_Slots[m_iSlotX / 4][m_iSlotX % 4]->bSeleted = false;
			}

			CItem* pTempItem = static_cast<CItem*>(m_Slots[iCurY][iCurX]->pItem);
			static_cast<CPlayer*>(CObjMgr::GetInstance()->GetBack(PLAYER))->SetSkill(1, pTempItem->GetSkillName());

			m_iSlotX = iCurY * 4 + iCurX;
			
			CUIMgr::GetInstance()->SetActionKeyGuide(1, pTempItem->GetIconDC());
		}
	}

	m_tCursor->vPos = m_Slots[iCurY][iCurX]->vPos;
	m_tCursor->UpdateRect();

	m_tCursor->hImage->GetTime() += 0.03;
	m_tCursor->hImage->RunAnimation();
}

void CInventory::RenderItems(HDC hDC)
{
	if (!m_bActive)
		return;

	BitBlt(hDC, 0, 0, 960, 640, m_hInvenBG, 0, 0, SRCCOPY);
	GdiTransparentBlt(hDC, 0, 0, 960, 640, m_hInven, 0, 0, 960, 640, RGB(255, 0, 255));

	for (auto& Slots : m_Slots)
	{
		for (auto& Slot : Slots)
		{
			if (!Slot->pItem)
				continue;

			if (Slot->bSeleted)
			{
				GdiTransparentBlt(hDC,
					Slot->vPos.fX - Slot->vSize.fX * 0.5f,
					Slot->vPos.fY - Slot->vSize.fY * 0.5f,
					Slot->vSize.fX,
					Slot->vSize.fY,
					Slot->hBG,
					0, 0,
					Slot->vSize.fX,
					Slot->vSize.fY,
					RGB(255, 0, 255)
				);
			}

			static_cast<CItem*>(Slot->pItem)->RenderIcon(hDC, Slot->vPos);
		}
	}

	int iBuffer(0);
	m_tCursor->hImage->Render(hDC, iBuffer, iBuffer);

	CUIMgr::GetInstance()->RenderActionKey(hDC);
}

