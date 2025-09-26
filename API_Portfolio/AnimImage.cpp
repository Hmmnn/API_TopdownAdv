#include "stdafx.h"
#include "AnimImage.h"
#include "TimeMgr.h"

CAnimImage::CAnimImage()
    : m_pPos(nullptr), m_vSize(), m_hMemDC(nullptr), m_pRect(nullptr)
{
}

CAnimImage::CAnimImage(HDC _hMemDC)
    : m_pPos(nullptr), m_vSize(), m_hMemDC(_hMemDC), m_pRect(nullptr)
{
}

CAnimImage::~CAnimImage()
{
    Release();
}

void CAnimImage::ResizeFrameVec(int _iIndex)
{
    m_vecFrame.resize(_iIndex);
}

int CAnimImage::RunAnimation()
{
    m_pCurFrame.fTime += DELTA;

    if (m_pCurFrame.fTime > m_pCurFrame.fFrameRate)
    {
        m_pCurFrame.fTime -= m_pCurFrame.fFrameRate;

        ++m_pCurFrame.iFirstFrame;

        if (m_pCurFrame.iActionStart == m_pCurFrame.iFirstFrame)
            return ANIM_ACTION;

        if (m_pCurFrame.iActionEnd == m_pCurFrame.iFirstFrame)
            return ANIM_ACTEND;

        if (m_pCurFrame.iLastFrame < m_pCurFrame.iFirstFrame)
        {
            if (!m_pCurFrame.bLoop)
            {
                --m_pCurFrame.iFirstFrame;
                return ANIM_END;
            }

            m_pCurFrame.iFirstFrame = 0;
        }
    }

    return ANIM_NOEVENT;
}

int CAnimImage::RunAnimation(int _iIndex)
{
    m_vecFrame[_iIndex]->fTime += DELTA;

    if (m_vecFrame[_iIndex]->fTime > m_vecFrame[_iIndex]->fFrameRate)
    {
        m_vecFrame[_iIndex]->fTime -= m_vecFrame[_iIndex]->fFrameRate;

        ++m_vecFrame[_iIndex]->iFirstFrame;

        if (m_vecFrame[_iIndex]->iLastFrame == m_vecFrame[_iIndex]->iFirstFrame)
        {
            if (!m_vecFrame[_iIndex]->bLoop)
            {
                --m_vecFrame[_iIndex]->iFirstFrame;
                return ANIM_END;
            }

            m_vecFrame[_iIndex]->iFirstFrame = 0;
        }
    }

    return ANIM_NOEVENT;
}

void CAnimImage::Render(HDC hDC, int& _iScrollX, int& _iScrollY)
{
    GdiTransparentBlt(
        hDC,
        (int)(*m_pRect).left + _iScrollX,
        (int)(*m_pRect).top + _iScrollY,
        (int)m_vSize.fX,
        (int)m_vSize.fY,
        m_hMemDC,
        m_pCurFrame.iFirstFrame * (int)m_vSize.fX,
        m_pCurFrame.iMotion * (int)m_vSize.fY,
        (int)m_vSize.fX,
        (int)m_vSize.fY,
        RGB(255, 0, 255)
    );
}

void CAnimImage::Release()
{
    for_each(m_vecFrame.begin(), m_vecFrame.end(), Safe_Delete<FRAME*>);
    m_vecFrame.clear();

    //ReleaseDC(g_hWnd, m_hMemDC);
}
