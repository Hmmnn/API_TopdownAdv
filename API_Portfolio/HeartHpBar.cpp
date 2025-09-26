#include "stdafx.h"
#include "HeartHpBar.h"
#include "StoppedImage.h"

#include "BmpMgr.h"

CHeartHpBar::CHeartHpBar() :
    m_iMaxHp(0), m_pHp(nullptr), m_iOneHeart(4), m_iMaxCount(0),
    m_vFirstPos()
{
}

CHeartHpBar::CHeartHpBar(int _iMaxHp) :
    m_iMaxHp(_iMaxHp), m_pHp(nullptr), m_iOneHeart(4), m_iMaxCount(0),
    m_vFirstPos()
{
}

CHeartHpBar::~CHeartHpBar()
{
    Release();
}

void CHeartHpBar::Initialize()
{
    m_eObjType = MISC;
    m_eRenderID = RENDER_UI;

    m_iMaxCount = m_iMaxHp / m_iOneHeart;
    
    if (m_iMaxHp % m_iOneHeart)
        m_iMaxCount += 1;

    m_vFirstPos = { 50, 50 };

    m_listGraphic.resize(m_iMaxCount);

    int iCnt(0);
    HDC hTemp = CBmpMgr::GetInstance()->FindBmp(L"HEART");

    for (auto& iter : m_listGraphic)
    {
        iter = new CStoppedImage(hTemp, {150, 30}, 4);
        iter->Initialize();
        iter->SetPos(m_vFirstPos + VEC2(40 * iCnt++, 0));
    }
}

int CHeartHpBar::Update()
{
    return SCENE_NOEVENT;
}

void CHeartHpBar::LateUpdate()
{
    int     iFull = (*m_pHp) / m_iOneHeart;
    int     iPiece = (*m_pHp) % m_iOneHeart;

    int iCnt(0);

    for (auto& iter : m_listGraphic)
    {
        if (iFull > iCnt)
        {
            iter->SetCurFrame(0);
        }
        else if(iFull == iCnt)
        {
            iter->SetCurFrame(iter->GetLastFrame() - iPiece);
        }
        else
        {
            iter->SetCurFrame(iter->GetLastFrame());
        }

        ++iCnt;
    }
}

void CHeartHpBar::Render(HDC hDC)
{
    for (auto& iter : m_listGraphic)
    {
        iter->Render(hDC);
    }
}

void CHeartHpBar::Release()
{
    for_each(m_listGraphic.begin(), m_listGraphic.end(), Safe_Delete<CStoppedImage*>);
    m_listGraphic.clear();
}
