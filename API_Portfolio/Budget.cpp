#include "stdafx.h"
#include "Budget.h"
#include "StoppedImage.h"

#include "BmpMgr.h"

CBudget::CBudget() :
    m_hRupeeIcon(NULL), m_pBudget(nullptr), m_iPreBudget(0)
{
}

CBudget::~CBudget()
{
    Release();
}

void CBudget::Initialize()
{
    m_eObjType = MISC;
    m_eRenderID = RENDER_UI;

    m_vPos = { WINCX - 40, WINCY - 60 };
    m_vSize = { 240, 24 };

    m_hRupeeIcon = CBmpMgr::GetInstance()->FindBmp(L"RUPEE_ICON");

    m_hNumberImage = CBmpMgr::GetInstance()->FindBmp(L"NUMBER");

    m_listNumber.resize(3);

    int iCnt(0);
    auto iter = m_listNumber.begin();

    while (iter != m_listNumber.end())
    {
        *iter = new CStoppedImage(m_hNumberImage, { 240, 24 }, 9);
        (*iter)->SetPos({ WINCX - 50 - (float)(24 * iCnt++), WINCY - 50 });
        (*iter)->Initialize();

        ++iter;
    }

    CObj::UpdateRect();
}

int CBudget::Update()
{
    return SCENE_NOEVENT;
}

void CBudget::LateUpdate()
{
    if (m_iPreBudget == *m_pBudget)
        return;

    SetNumberImage();
}

void CBudget::Render(HDC hDC)
{
    GdiTransparentBlt(hDC,
        m_tRect.left,
        m_tRect.top,
        48, 48,
        m_hRupeeIcon,
        0, 0,
        48, 48,
        RGB(255, 0, 255)
    );

    for (auto& iter : m_listNumber)
        iter->Render(hDC);
}

void CBudget::Release()
{
    for_each(m_listNumber.begin(), m_listNumber.end(), Safe_Delete<CStoppedImage*>);
    m_listNumber.clear();
}

void CBudget::SetNumberImage()
{
    m_iPreBudget = *m_pBudget;

    int iTempBudget = m_iPreBudget;

    auto&   CurNumber = m_listNumber.begin();

    while (iTempBudget >= 10)
    {
        if (CurNumber == m_listNumber.end())
        {
            m_listNumber.push_back(new CStoppedImage(m_hNumberImage, { 240, 24 }, 9));

            VEC2 vTemp = (*--CurNumber)->GetPos();
            ++CurNumber;
            
            (*CurNumber)->SetPos(vTemp + VEC2(24, 0));
            (*CurNumber)->Initialize();
        }

        (*CurNumber)->SetCurFrame(iTempBudget % 10);

        iTempBudget /= 10;
        ++CurNumber;
    }

    if (CurNumber == m_listNumber.end())
    {
        m_listNumber.push_back(new CStoppedImage(m_hNumberImage, { 240, 24 }, 9));

        VEC2 vTemp = (*--CurNumber)->GetPos();
        ++CurNumber;

        (*CurNumber)->SetPos(vTemp + VEC2(24, 0));
        (*CurNumber)->Initialize();
    }

    (*CurNumber)->SetCurFrame(iTempBudget % 10);

}
