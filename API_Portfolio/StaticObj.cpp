#include "stdafx.h"
#include "StaticObj.h"
#include "RectCollider.h"
#include "SphereCollider.h"

#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "TimeMgr.h"

CStaticObj::CStaticObj() : 
	m_eState(OFF), m_hMemDC(nullptr)
{
	m_eRenderID = RENDER_GAMEOBJ;
}

CStaticObj::CStaticObj(float _fX, float _fY, float _fCX, float _fCY)
    : CObj(_fX, _fY, _fCX, _fCY), m_hMemDC(nullptr), m_eState(OFF)
{
	m_eRenderID = RENDER_GAMEOBJ;
}

CStaticObj::~CStaticObj()
{
    Release();
}

void CStaticObj::Initialize()
{
	m_eObjType = MAPOBJ;

	m_pCollider = new CRectCollider(this, m_vSize);

	UpdateRect();
}

int CStaticObj::Update()
{
    return SCENE_NOEVENT;
}

void CStaticObj::LateUpdate()
{
	RunAnimation();
}

void CStaticObj::Render(HDC hDC)
{
	m_pCollider->Render(hDC);

	int iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
	int iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

	if (m_hMemDC)
	{
		if (m_vecFrame.empty())
		{
			GdiTransparentBlt(hDC,
				m_tRect.left + iScrollX,
				m_tRect.top + iScrollY,
				(int)m_vSize.fX,
				(int)m_vSize.fY,
				m_hMemDC,
				0, 0,
				(int)m_vSize.fX,
				(int)m_vSize.fY,
				RGB(255, 0, 255)
			);
		}
		else
		{
			GdiTransparentBlt(
				hDC,
				(int)m_tRect.left + iScrollX,
				(int)m_tRect.top + iScrollY,
				(int)m_vSize.fX,
				(int)m_vSize.fY,
				m_hMemDC,
				m_vecFrame[m_eState]->iFirstFrame * (int)m_vSize.fX,
				m_vecFrame[m_eState]->iMotion * (int)m_vSize.fY,
				(int)m_vSize.fX,
				(int)m_vSize.fY,
				RGB(255, 0, 255)
			);
		}
	}
}

void CStaticObj::Release()
{
	for_each(m_vecFrame.begin(), m_vecFrame.end(), Safe_Delete<FRAME*>);
	m_vecFrame.clear();

	//Safe_Delete<CCollider*>(m_pCollider);

	if (m_pCollider)
	{
		delete m_pCollider;
		m_pCollider = nullptr;
	}
}

int CStaticObj::RunAnimation()
{
	if (m_vecFrame.empty())
		return ANIM_NOEVENT;

	m_vecFrame[m_eState]->fTime += DELTA;

	if (m_vecFrame[m_eState]->fFrameRate < m_vecFrame[m_eState]->fTime)
	{
		m_vecFrame[m_eState]->fTime -= m_vecFrame[m_eState]->fFrameRate;

		++m_vecFrame[m_eState]->iFirstFrame;

		if (m_vecFrame[m_eState]->iLastFrame < m_vecFrame[m_eState]->iFirstFrame)
		{
			if (!m_vecFrame[m_eState]->bLoop)
			{
				--m_vecFrame[m_eState]->iFirstFrame;
				return ANIM_END;
			}

			m_vecFrame[m_eState]->iFirstFrame = 0;
		}
	}

	return ANIM_NOEVENT;
}

void CStaticObj::SetCollider(CCollider::SHAPE _eShape, float _fCX, float _fCY)
{
	switch (_eShape)
	{
	case CCollider::SQUARE:
		m_pCollider = new CRectCollider(this, VEC2(_fCX, _fCY));
		break;

	case CCollider::SPHERE:
		m_pCollider = new CSphereCollider(this, VEC2(_fCX, _fCY));
		break;
	}

	m_pCollider->UpdateRect();
}
