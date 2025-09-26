#include "stdafx.h"
#include "Effect.h"
#include "StoppedImage.h"

#include "TimeMgr.h"
#include "ObjMgr.h"

CEffect::CEffect() :
    m_pSprite(nullptr), m_fTime(0), m_fFrameRate(0), m_iCurFrame(0)
{
}

CEffect::CEffect(HDC _hMemDC, VEC2 _vFullSize, int _iLastFrame) :
    m_fTime(0), m_fFrameRate(0), m_iCurFrame(0)
{
    m_pSprite = new CStoppedImage(_hMemDC, _vFullSize, _iLastFrame);
    m_pSprite->Initialize();
    m_pSprite->SetScroll(true);
}

CEffect::~CEffect()
{
    Release();
}

void CEffect::Initialize()
{
    m_eObjType = MISC;
    m_eRenderID = RENDER_EFFECT;

    m_bActive = false;

    m_fFrameRate = 1.f / 16.f;

    CObjMgr::GetInstance()->AddObj(MISC, this);
}

int CEffect::Update()
{
    return SCENE_NOEVENT;
}

void CEffect::LateUpdate()
{
    if (!m_bActive)
        return;

    m_fTime += DELTA;

    if (m_fFrameRate < m_fTime)
    {
        m_fTime -= m_fFrameRate;

        m_pSprite->SetCurFrame(m_iCurFrame++);

        if (m_pSprite->GetLastFrame() < m_iCurFrame)
        {
            m_bActive = false;
            m_iCurFrame = 0;
        }
    }
}

void CEffect::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    m_pSprite->Render(hDC);
}

void CEffect::Release()
{
    Safe_Delete<CStoppedImage*>(m_pSprite);
}

void CEffect::Play(VEC2 _vPos)
{
    m_pSprite->SetPos(_vPos);
    m_bActive = true;
}
