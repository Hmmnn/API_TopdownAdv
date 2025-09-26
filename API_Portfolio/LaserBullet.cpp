#include "stdafx.h"
#include "LaserBullet.h"
#include "ScrollMgr.h"
#include "RectCollider.h"
#include "BmpMgr.h"
#include "TimeMgr.h"

CLaserBullet::CLaserBullet() : 
	m_vInitColSize(),/* m_vCurSize(),*/ m_bWall(false),
	m_hTexture(NULL), m_iCurFrame(0), m_iLastFrame(0),
	m_fTime(0), m_fFrameRate(0), m_vColPos(),
	m_fAttackTime(0), m_fAttackInterval(0)
{
}

CLaserBullet::~CLaserBullet()
{
	Release();
}

void CLaserBullet::Initialize()
{
	m_eObjType = ENEMYBULLET;
	m_eRenderID = RENDER_EFFECT;

	m_bActive = false;

	m_vSize = { 100, 700 };
	m_vInitColSize = { 30, 25 };
	//m_vCurSize = m_vInitColSize;

	m_fSpeed = 700.f;

	m_iAtk = 1;
	m_fAttackInterval = 0.5f;

	m_pCollider = new CRectCollider(this, m_vInitColSize);

	m_hTexture = CBmpMgr::GetInstance()->FindBmp(L"LASER");
	m_iLastFrame = 1;
	m_fFrameRate = 1.f / 16.f;
}

int CLaserBullet::Update()
{
	if (!m_bActive)
	{
		m_pCollider->SetActive(false);

		return SCENE_NOEVENT;
	}

	return CGameObj::Update();
}

void CLaserBullet::LateUpdate()
{
	if (!m_bActive)
		return;

	m_fTime += DELTA;

	if (m_fFrameRate < m_fTime)
	{
		m_fTime -= m_fFrameRate;

		++m_iCurFrame;

		if (m_iLastFrame < m_iCurFrame)
			m_iCurFrame = 0;
	}
}

void CLaserBullet::Render(HDC hDC)
{
	if (!m_bActive)
		return;

	int		iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
	int		iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	m_pCollider->Render(hDC);

	GdiTransparentBlt(hDC,
		(int)m_tRect.left + iScrollX,
		(int)m_tRect.top + iScrollY,
		(int)m_vSize.fX,
		(int)m_vSize.fY,
		m_hTexture,
		(int)m_vSize.fX * m_iCurFrame, 0,
		(int)m_vSize.fX,
		(int)m_vSize.fY,
		RGB(255, 0, 255)
	);
}

void CLaserBullet::Release()
{
}

void CLaserBullet::OnCollision(CObj* _pOther)
{
	if (PLAYER == _pOther->GetType())
	{
		m_fAttackTime += DELTA;

		if (m_fAttackInterval < m_fAttackTime)
		{
			m_fAttackTime = 0;

			static_cast<CGameObj*>(_pOther)->TakeDamage(m_iAtk);

		}
	}
}

void CLaserBullet::Shooted(VEC2 _tPos)
{
	// 크기, 위치 조정

	m_vSize = { m_vSize.fX, 700 - _tPos.fY };
	m_vPos = _tPos + VEC2( 0, m_vSize.fY * 0.5f );
	
	m_pCollider->SetSize({m_vInitColSize.fX, m_vSize.fY});
	m_pCollider->SetPos(m_vPos);
	m_pCollider->UpdateRect();

	m_bActive = true;
	m_pCollider->SetActive(true);
}

void CLaserBullet::Reset()
{
	m_bActive = false;
	m_pCollider->SetSize(m_vInitColSize);
	m_pCollider->SetActive(false);
}
