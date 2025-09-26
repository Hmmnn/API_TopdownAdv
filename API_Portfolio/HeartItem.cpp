#include "stdafx.h"
#include "HeartItem.h"
#include "GameObj.h"
#include "RectCollider.h"

#include "BmpMgr.h"

CHeartItem::CHeartItem()
{
}

CHeartItem::~CHeartItem()
{
    Release();
}

void CHeartItem::Initialize()
{
    m_eObjType = ITEM;
    m_eItemType = HEART;

    m_szName = L"ปýธํทย";
    
    m_vSize = { 48, 48 };

    m_iValue = 4;

    m_pCollider = new CRectCollider(this, { 40, 40 });

    m_pSprite = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"HEART_SPR"));
    m_pSprite->ResizeFrameVec(1);
    m_pSprite->SetPos(&m_vPos);
    m_pSprite->SetSize(m_vSize);
    m_pSprite->SetRect(&m_tRect);
    m_pSprite[0].SetFrame(0, 0, 7, true, 1.f / 12.f);
    m_pSprite[0].SetMotion(0);
}

void CHeartItem::Release()
{
}

void CHeartItem::OnCollision(CObj* _pOther)
{
    if (PLAYER == _pOther->GetType())
    {
        ApplyAbility(_pOther);

        m_bActive = false;
    }
}

void CHeartItem::CollisionGameObj()
{
    m_bActive = false;
}

void CHeartItem::ApplyAbility(CObj* _pTarget)
{
    static_cast<CGameObj*>(_pTarget)->HealHp(m_iValue);
}
