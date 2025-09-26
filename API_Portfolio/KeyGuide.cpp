#include "stdafx.h"
#include "KeyGuide.h"
#include "StoppedImage.h"
#include "BmpMgr.h"

CKeyGuide::CKeyGuide()
{
}

CKeyGuide::~CKeyGuide()
{
    Release();
}

void CKeyGuide::Initialize()
{
    m_eObjType = MISC;
    m_eRenderID = RENDER_UI;

    m_vecPos = { { WINCX - 180, 50 }, { WINCX - 80, 50 } };
    m_vecOffset = { { 20, 15 }, { 20, 15 } };

    int iCnt(0);

    m_vecAction.resize(2);
    for (auto& iter : m_vecAction)
    {
        iter = new CStoppedImage(CBmpMgr::GetInstance()->FindBmp(L"ACTION_KEY"),
            { 72, 42 }, 1);
        iter->SetPos(m_vecPos[iCnt]);
        iter->SetCurFrame(iCnt++);
        iter->Initialize();
    }

    iCnt = 0;
    m_vecEquip.resize(2);
    for (auto& iter : m_vecEquip)
    {
        iter = new CStoppedImage();
        iter->SetPos(m_vecPos[iCnt] + m_vecOffset[iCnt]);
        iter->SetCurFrame(0);
        iter->Initialize();
        ++iCnt;
    }
}

int CKeyGuide::Update()
{
    return SCENE_NOEVENT;
}

void CKeyGuide::LateUpdate()
{
}

void CKeyGuide::Render(HDC hDC)
{
    for (auto& iter : m_vecAction)
    {
        iter->Render(hDC);
    }

    for (auto& iter : m_vecEquip)
    {
        iter->Render(hDC);
    }
}

void CKeyGuide::Release()
{
    for_each(m_vecAction.begin(), m_vecAction.end(), Safe_Delete<CStoppedImage*>);
    for_each(m_vecEquip.begin(), m_vecEquip.end(), Safe_Delete<CStoppedImage*>);

}

void CKeyGuide::SetImage(int _iIndex, HDC _hImage)
{
    m_vecEquip[_iIndex]->SetNewSprite(_hImage, { 48, 48 }, 0);
}
