#include "stdafx.h"
#include "MyButton.h"
#include "RectCollider.h"

#include "KeyMgr.h"
#include "ScrollMgr.h"

CMyButton::CMyButton() :
    m_bSelected(false), m_bChecked(false),
    m_hBrush(nullptr), m_hGreen(nullptr), m_hRed(nullptr), m_hBlue(nullptr),
    m_hMemDC(nullptr), m_eNextScene(TITLE), m_bTitle(false), m_bShift(false)
{
}

CMyButton::~CMyButton()
{
    Release();
}

void CMyButton::Initialize()
{
    m_eObjType = MISC;
    m_eRenderID = RENDER_UI;

    m_vSize = { 48, 48 };

    m_hGreen = CreateSolidBrush(RGB(0, 255, 0));
    m_hRed = CreateSolidBrush(RGB(255, 0, 0));
    m_hBlue = CreateSolidBrush(RGB(0, 0, 255));
}

int CMyButton::Update()
{
    CObj::UpdateRect();

    if (m_bShift)
        return m_eNextScene;

    return SCENE_NOEVENT;
}

void CMyButton::LateUpdate()
{
    POINT	pt{};
    GetCursorPos(&pt);
    ScreenToClient(g_hWnd, &pt);

    if (!m_bTitle)
    {
        pt.x -= (int)CScrollMgr::GetInstance()->GetScrollX();
        pt.y -= (int)CScrollMgr::GetInstance()->GetScrollY();

    }
    

    if (PtInRect(&m_tRect, pt))
    {
        if (KEY_PRESS(VK_LBUTTON))
        {
            m_bSelected = true;

            if (m_bTitle)
            {
                m_bShift = true;
            }
        }
    }
    
    if (m_bSelected)
        m_hBrush = m_hRed;
    else
        m_hBrush = m_hGreen;

    
}

void CMyButton::Render(HDC hDC)
{
    int     iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int     iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    if (m_hMemDC)
    {
        POINT	pt{};
        GetCursorPos(&pt);
        ScreenToClient(g_hWnd, &pt);

        int iIndex(0);

        if (PtInRect(&m_tRect, pt))
            iIndex = 1;

        GdiTransparentBlt(hDC,
            m_tRect.left,
            m_tRect.top,
            m_vSize.fX, m_vSize.fY,
            m_hMemDC,
            0, m_vSize.fY * iIndex,
            m_vSize.fX, m_vSize.fY,
            RGB(255, 0, 255)
        );
    }
    else
    {
        RECT    tTempRect = {
        m_tRect.left + iScrollX,
        m_tRect.top + iScrollY,
        m_tRect.right + iScrollX,
        m_tRect.bottom + iScrollY
        };

        HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, m_hBrush);

        FrameRect(hDC, &tTempRect, m_hBrush);

        SelectObject(hDC, hOldBrush);

    }

}

void CMyButton::Release()
{
    DeleteObject(m_hGreen);
    DeleteObject(m_hRed);
}
