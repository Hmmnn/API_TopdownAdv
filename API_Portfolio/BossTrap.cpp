#include "stdafx.h"
#include "BossTrap.h"
#include "GameObj.h"
#include "BmpMgr.h"
#include "TimeMgr.h"
#include "ScrollMgr.h"

CBossTrap::CBossTrap() 
    : m_pOwner(nullptr), m_fActiveTime(0), m_fActiveInterval(0),
    m_iAtk(0), m_fPreTime(0), m_fReadyTime(0), m_bReady(true)
{
}

CBossTrap::~CBossTrap()
{
    Release();
}

void CBossTrap::Initialize()
{
    m_eObjType = ENEMYBULLET;
    m_eRenderID = RENDER_BACKGROUND;

    m_bActive = false;

    m_vSize = { 250, 250 };
    m_fActiveInterval = 1.5f;

    m_iAtk = 1;

    m_fReadyTime = 1.5f;

    m_pCollider = new CRectCollider(this, VEC2(200, 200));
    m_pCollider->SetActive(false);

    InitFrame();

    m_hRed = CreateSolidBrush(RGB(255, 0, 0));
}

int CBossTrap::Update()
{
    if(!m_bActive)
        return SCENE_NOEVENT;
    
    if (m_bReady && m_bActive)
    {
        m_fPreTime += DELTA;

        if (m_fReadyTime < m_fPreTime)
        {
            m_fPreTime -= m_fReadyTime;

            m_bReady = false;
            m_pCollider->SetActive(true);
        }
        else
            return SCENE_NOEVENT;
    }

    m_fActiveTime += DELTA;

    if (m_fActiveInterval < m_fActiveTime)
    {
        m_fActiveTime -= m_fActiveInterval;

        m_bActive = false;
        m_pCollider->SetActive(false);
        m_bReady = true;
    }

    CObj::UpdateRect();

    return SCENE_NOEVENT;
}

void CBossTrap::LateUpdate()
{
    if (!m_bActive)
        return;

    CObj::UpdateRect();

    CStaticObj::LateUpdate();
}

void CBossTrap::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    if (m_bReady)
    {
        int iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
        int iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

        HBRUSH OldBrush = (HBRUSH)SelectObject(hDC, m_hRed);

        RECT rc = {
            m_tRect.left + iScrollX,
            m_tRect.top + iScrollY,
            m_tRect.right + iScrollX,
            m_tRect.bottom + iScrollY
        };

        FrameRect(hDC, &rc, m_hRed);

        SelectObject(hDC, OldBrush);

        return;
    }

    CStaticObj::Render(hDC);
}

void CBossTrap::Release()
{
    for_each(m_vecFrame.begin(), m_vecFrame.end(), Safe_Delete<FRAME*>);
    m_vecFrame.clear();
}

void CBossTrap::OnCollision(CObj* _pOther)
{
    if (PLAYER == _pOther->GetType())
    {
        bool bResult = m_pCollider->AddHitted(_pOther);

        if (bResult)
            static_cast<CGameObj*>(_pOther)->TakeDamage(m_iAtk);
    }
}

void CBossTrap::InitFrame()
{
    m_vecFrame.resize(1);

    m_hMemDC = CBmpMgr::GetInstance()->FindBmp(L"TRAP");
    m_vecFrame[0] = new FRAME();
    m_vecFrame[0]->iMotion = 0;
    m_vecFrame[0]->iFirstFrame = 0;
    m_vecFrame[0]->iLastFrame = 7;
    m_vecFrame[0]->fTime = 0.f;
    m_vecFrame[0]->fFrameRate = 1.f / 16.f;
    m_vecFrame[0]->bLoop = true;
}
