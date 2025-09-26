#include "stdafx.h"
#include "RectCollider.h"
#include "ScrollMgr.h"

CRectCollider::CRectCollider()
{
    m_eShape = CCollider::SQUARE;


}

CRectCollider::CRectCollider(CObj* _pOwner, VEC2 _tSize)
    : CCollider(_pOwner, _tSize)
{
    m_eShape = CCollider::SQUARE;
}

CRectCollider::~CRectCollider()
{
}

void CRectCollider::Render(HDC hDC)
{
    if (!g_bDebugMode)
        return;

    if (!m_bActive)
        return;

    int iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    //Rectangle(hDC, 
    //    m_tRect.left + iScrollX, 
    //    m_tRect.top + iScrollY, 
    //    m_tRect.right + iScrollX, 
    //    m_tRect.bottom + iScrollY
    //);
    
    //HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, m_hBrush);
    HBRUSH hOldBrush;
    
    if (m_bCollided)
    {
        m_hBrush = m_hRed;
        hOldBrush = (HBRUSH)SelectObject(hDC, m_hRed);
        //m_hBrush = m_hRed;
    }
    else
    {
        m_hBrush = m_hGreen;
        hOldBrush = (HBRUSH)SelectObject(hDC, m_hGreen);
        //m_hBrush = m_hGreen;
    }
    

    RECT tTempRect = 
    {
        m_tRect.left + iScrollX,
        m_tRect.top + iScrollY,
        m_tRect.right + iScrollX,
        m_tRect.bottom + iScrollY
    };

    FrameRect(hDC, &tTempRect, m_hBrush);

    SelectObject(hDC, hOldBrush);
}
