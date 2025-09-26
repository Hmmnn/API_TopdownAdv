#include "stdafx.h"
#include "EquipItem.h"
#include "RectCollider.h"
#include "AnimImage.h"
#include "GameObj.h"

#include "BmpMgr.h"
#include "Inventory.h"

CSwordItem::CSwordItem()
{
}

CSwordItem::~CSwordItem()
{
    Release();
}

void CSwordItem::Initialize()
{
    m_eObjType = ITEM;
    m_eItemType = EQUIP;

    m_szName = L"스미스의 검";
    m_szSkillKey = L"MELEE_ATK";

    m_vSize = { 48, 48 };

    m_iValue = 5;

    m_pCollider = new CRectCollider(this, { 40, 40 });

    m_pSprite = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"SWORD_ICON"));
    m_pSprite->ResizeFrameVec(1);
    m_pSprite->SetPos(&m_vPos);
    m_pSprite->SetSize(m_vSize);
    m_pSprite->SetRect(&m_tRect);
    m_pSprite->SetFrame(0, 0, 0, false);
    m_pSprite->SetMotion(0);

    m_tIcon.hIcon = CBmpMgr::GetInstance()->FindBmp(L"SWORD_ICON");
    m_tIcon.tSize = m_vSize;
}

void CSwordItem::ApplyAbility(CObj* _pTarget)
{
    //static_cast<CGameObj*>(_pTarget)->SetAtk(+m_iValue);
}

void CSwordItem::RevertAbility(CObj* _pTarget)
{
    //static_cast<CGameObj*>(_pTarget)->SetAtk(-m_iValue);
}

CBowItem::CBowItem()
{
}

CBowItem::~CBowItem()
{
    Release();
}

void CBowItem::Initialize()
{
    m_eObjType = ITEM;
    m_eItemType = EQUIP;

    m_szName = L"작은 활";
    m_szSkillKey = L"ARROW_ATK";

    m_vSize = { 48, 48 };

    m_iValue = 5;

    m_pCollider = new CRectCollider(this, { 40, 40 });

    m_pSprite = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"BOW_ICON"));
    m_pSprite->ResizeFrameVec(1);
    m_pSprite->SetPos(&m_vPos);
    m_pSprite->SetSize(m_vSize);
    m_pSprite->SetRect(&m_tRect);
    m_pSprite->SetFrame(0, 0, 0, false);
    m_pSprite->SetMotion(0);

    m_tIcon.hIcon = CBmpMgr::GetInstance()->FindBmp(L"BOW_ICON");
    m_tIcon.tSize = m_vSize;
}

CBoomrItem::CBoomrItem()
{
}

CBoomrItem::~CBoomrItem()
{
    Release();
}

void CBoomrItem::Initialize()
{
    m_eObjType = ITEM;
    m_eItemType = EQUIP;

    m_szName = L"부메랑";
    m_szSkillKey = L"BOO_ATK";

    m_vSize = { 48, 48 };

    m_iValue = 5;

    m_pCollider = new CRectCollider(this, { 40, 40 });

    m_pSprite = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"BOO_ICON"));
    m_pSprite->ResizeFrameVec(1);
    m_pSprite->SetPos(&m_vPos);
    m_pSprite->SetSize(m_vSize);
    m_pSprite->SetRect(&m_tRect);
    m_pSprite->SetFrame(0, 0, 0, false);
    m_pSprite->SetMotion(0);

    m_tIcon.hIcon = CBmpMgr::GetInstance()->FindBmp(L"BOO_ICON");
    m_tIcon.tSize = m_vSize;
}

CShieldItem::CShieldItem()
{
}

CShieldItem::~CShieldItem()
{
    Release();
}

void CShieldItem::Initialize()
{
    m_eObjType = ITEM;
    m_eItemType = EQUIP;

    m_szName = L"거울 방패";
    m_szSkillKey = L"GUARD_SKILL";

    m_vSize = { 48, 48 };

    m_iValue = 5;

    m_pCollider = new CRectCollider(this, { 40, 40 });

    m_pSprite = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"SHIELD_ICON"));
    m_pSprite->ResizeFrameVec(1);
    m_pSprite->SetPos(&m_vPos);
    m_pSprite->SetSize(m_vSize);
    m_pSprite->SetRect(&m_tRect);
    m_pSprite->SetFrame(0, 0, 0, false);
    m_pSprite->SetMotion(0);

    m_tIcon.hIcon = CBmpMgr::GetInstance()->FindBmp(L"SHIELD_ICON");
    m_tIcon.tSize = m_vSize;

}

CStaffItem::CStaffItem()
{
}

CStaffItem::~CStaffItem()
{
    Release();
}

void CStaffItem::Initialize()
{
    m_eObjType = ITEM;
    m_eItemType = EQUIP;

    m_szName = L"마법 지팡이";
    m_szSkillKey = L"MAGIC_ATK";

    m_vSize = { 48, 48 };

    m_iValue = 5;

    m_pCollider = new CRectCollider(this, { 40, 40 });

    m_pSprite = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"STAFF_ICON"));
    m_pSprite->ResizeFrameVec(1);
    m_pSprite->SetPos(&m_vPos);
    m_pSprite->SetSize(m_vSize);
    m_pSprite->SetRect(&m_tRect);
    m_pSprite->SetFrame(0, 0, 0, false);
    m_pSprite->SetMotion(0);

    m_tIcon.hIcon = CBmpMgr::GetInstance()->FindBmp(L"STAFF_ICON");
    m_tIcon.tSize = m_vSize;
}
