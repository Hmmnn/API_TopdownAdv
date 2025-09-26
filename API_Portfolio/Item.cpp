#include "stdafx.h"
#include "Item.h"
#include "AnimImage.h"
#include "Collider.h"
#include "Inventory.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"

CItem::CItem() :
    m_eItemType(IT_END), m_szName(L""),
    m_pSprite(nullptr), 
    m_szSkillKey(L""), m_iValue(0)
{
    ZeroMemory(&m_tIcon, sizeof(ICON));

    m_eRenderID = RENDER_GAMEOBJ;
}

CItem::~CItem()
{
    Release();
}

void CItem::Initialize()
{
}

int CItem::Update()
{
    if (!m_bActive)
        return SCENE_NOEVENT;

    CObj::UpdateRect();

    return SCENE_NOEVENT;
}

void CItem::LateUpdate()
{
    if (!m_bActive)
        return;

    m_pSprite->RunAnimation();
}

void CItem::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    m_pCollider->Render(hDC);

    int     iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int     iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    // 필드일 때
    m_pSprite->Render(hDC, iScrollX, iScrollY);
}

void CItem::Release()
{
    Safe_Delete<CAnimImage*>(m_pSprite);
}

void CItem::OnCollision(CObj* _pOther)
{
    if (PLAYER == _pOther->GetType())
    {
        // 플레이어 인벤에 추가
        CInventory::GetInstance()->AddItem(m_eItemType, this);

        m_bActive = false;
    }
}

void CItem::RenderIcon(HDC hDC, VEC2 _vPos)
{
    m_vPos = _vPos;

    m_tIcon.tRect =
    {
        (LONG)(_vPos.fX - m_vSize.fX * 0.5f),
        (LONG)(_vPos.fY - m_vSize.fY * 0.5f),
        (LONG)(_vPos.fX + m_vSize.fX * 0.5f),
        (LONG)(_vPos.fY + m_vSize.fY * 0.5f),
    };

    GdiTransparentBlt(hDC,
        (int)m_tIcon.tRect.left,
        (int)m_tIcon.tRect.top,
        (int)m_tIcon.tSize.fX,
        (int)m_tIcon.tSize.fY,
        m_tIcon.hIcon,
        0, 0,
        (int)m_tIcon.tSize.fX,
        (int)m_tIcon.tSize.fY,
        RGB(255, 0, 255)
    );
}
