#include "stdafx.h"
#include "Wall.h"
#include "RectCollider.h"
#include "ScrollMgr.h"

CWall::CWall()
{
    m_eRenderID = RENDER_MISC;
}

CWall::CWall(float _fX, float _fY, float _fCX, float _fCY)
{
    m_eRenderID = RENDER_MISC;

    m_vPos = { _fX, _fY };
    m_vSize = { _fCX, _fCY };

    CObj::UpdateRect();
}

CWall::~CWall()
{
    Release();
}

void CWall::Initialize()
{
    m_eObjType = WALL;

    m_pCollider = new CRectCollider(this, m_vSize);
}

int CWall::Update()
{
    return SCENE_NOEVENT;
}

void CWall::LateUpdate()
{
}

void CWall::Render(HDC hDC)
{
    if (!g_bDebugMode)
        return;

    int     iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int     iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    m_pCollider->Render(hDC);

    if (g_bDebugMode)
    {
        Rectangle(hDC,
            m_tRect.left + iScrollX,
            m_tRect.top + iScrollY,
            m_tRect.right + iScrollX,
            m_tRect.bottom + iScrollY
        );
    }
}

void CWall::Release()
{
}

void CWall::SetPos(float _fX, float _fY)
{
    m_vPos = { _fX, _fY };

    //CObj::UpdateRect();
}

void CWall::SetPos(VEC2 _vPos)
{
    m_vPos = _vPos;

    //CObj::UpdateRect();
}

void CWall::SetSize(float _fCX, float _fCY)
{
    m_vSize = { _fCX, _fCY };

    CObj::UpdateRect();
}

void CWall::SetSize(VEC2 _vSize)
{
    m_vSize = _vSize;

    CObj::UpdateRect();
}
