#include "stdafx.h"
#include "Door.h"
#include "RectCollider.h"
#include "GameObj.h"

#include "BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"

CDoor::CDoor() :
    m_bOpen(false), m_bImage(false), m_bShifting(false),
    m_eNextScene(SC_END)
{
}

CDoor::~CDoor()
{
    Release();
}

void CDoor::Initialize()
{
    m_eObjType = MAPOBJ;

    m_eState = OFF;
    m_bActive = true;

    m_vSize = { 72, 48 };

    m_pCollider = new CRectCollider(this, m_vSize);

    InitializeImage();
}

int CDoor::Update()
{
    if (m_bShifting)
    {
        return (int)m_eNextScene;
    }

    return SCENE_NOEVENT;
}

void CDoor::LateUpdate()
{
}

void CDoor::Render(HDC hDC)
{
    int     iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int     iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    //if (g_bDebugMode)
    //{
    //    Rectangle(hDC,
    //        m_tRect.left + iScrollX,
    //        m_tRect.top + iScrollY,
    //        m_tRect.right + iScrollX,
    //        m_tRect.bottom + iScrollY
    //    );
    //}

    m_pCollider->Render(hDC);

    if(!m_bOpen && m_bImage)
        CStaticObj::Render(hDC);
}

void CDoor::Release()
{
}

void CDoor::OnCollision(CObj* _pOther)
{
    // OFF 상태면 플레이어 Push
    // ON 상태면 통과

    if (PLAYER == _pOther->GetType())
    {
         if (m_bOpen)
        {
            RECT rc = m_pCollider->GetOverlap();

            if (abs(rc.right - rc.left) > 50
                || abs(rc.bottom - rc.top) > 50)
                m_bShifting = true;
        }
        else
        {
            static_cast<CGameObj*>(_pOther)->CollisionPush(this);
        }
    }
}

void CDoor::InitializeImage()
{
    m_hMemDC = CBmpMgr::GetInstance()->FindBmp(L"DOOR");

    m_vecFrame.resize(1);

    m_vecFrame[OFF] = new FRAME(OFF, 0, 0, false);
}
