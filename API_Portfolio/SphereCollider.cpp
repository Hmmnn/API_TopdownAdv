#include "stdafx.h"
#include "SphereCollider.h"
#include "ScrollMgr.h"

CSphereCollider::CSphereCollider()
{
    m_eShape = CCollider::SPHERE;
}

CSphereCollider::CSphereCollider(CObj* _pOwner, VEC2 _tSize)
    : CCollider(_pOwner, _tSize)
{
    m_eShape = CCollider::SPHERE;
}

CSphereCollider::~CSphereCollider()
{
}

void CSphereCollider::Render(HDC hDC)
{
    if (!g_bDebugMode)
        return;

    if (!m_bActive)
        return;

    int iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, m_hBrush);

    Ellipse(hDC,
        m_tRect.left + iScrollX,
        m_tRect.top + iScrollY,
        m_tRect.right + iScrollX,
        m_tRect.bottom + iScrollY
    );

    SelectObject(hDC, hOldBrush);
}
