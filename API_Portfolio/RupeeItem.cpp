#include "stdafx.h"
#include "RupeeItem.h"
#include "GameObj.h"
#include "RectCollider.h"

#include "BmpMgr.h"
#include "Inventory.h"

CRupeeItem::CRupeeItem()
{
}

CRupeeItem::~CRupeeItem()
{
    Release();
}

void CRupeeItem::Initialize()
{
    m_eObjType = ITEM;
    m_eItemType = RUPEE;

    m_szName = L"루피";

    m_vSize = { 40, 40 };

    m_iValue = 10;

    m_pCollider = new CRectCollider(this, { 40, 40 });

    m_pSprite = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"RUPEE_SPR"));
    m_pSprite->ResizeFrameVec(1);
    m_pSprite->SetPos(&m_vPos);
    m_pSprite->SetSize(m_vSize);
    m_pSprite->SetRect(&m_tRect);
    m_pSprite[0].SetFrame(0, 0, 3, true, 1.f / 12.f);
    m_pSprite[0].SetMotion(0);
}

void CRupeeItem::Render(HDC hDC)
{
    CItem::Render(hDC);
}

void CRupeeItem::Release()
{
}

void CRupeeItem::OnCollision(CObj* _pOther)
{
    if (PLAYER == _pOther->GetType())
    {
        // 플레이어 인벤에 추가
        CInventory::GetInstance()->AddItem(m_eItemType, this);

        m_bActive = false;
    }
}
