#include "stdafx.h"
#include "FallingStone.h"
#include "RectCollider.h"

#include "BmpMgr.h"
#include "ScrollMgr.h"

CFallingStone::CFallingStone()
	: m_tEndPos(), m_bLanded(false)
{
}

CFallingStone::~CFallingStone()
{
    Release();
}

void CFallingStone::Initialize()
{
	m_eObjType = ENEMYBULLET;
	m_eRenderID = RENDER_EFFECT;

	m_vSize = { 150, 150 };

	m_fSpeed = 300.f;
	m_vVelocity = { 0, 1 };

	m_pCollider = new CRectCollider(this, {50, 50});

	m_bActive = false;
	m_bLanded = false;

    InitializeMotion();

	m_vecMotion[0]->SetMotion((int)m_bLanded);
}

int CFallingStone::Update()
{
	if (!m_bActive)
		return SCENE_NOEVENT;

    return CGameObj::Update();
}

void CFallingStone::LateUpdate()
{
	if (!m_bActive)
		return;

	EndFalling();

	m_iAnimState = m_vecMotion[0]->RunAnimation();

	if (m_bLanded && ANIM_END == m_iAnimState)
	{
		m_bActive = false;
		m_bLanded = false;
		m_iAnimState = ANIM_NOEVENT;
	}
}

void CFallingStone::Render(HDC hDC)
{
	if (!m_bActive)
		return;

	int iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
	int iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

	m_pCollider->Render(hDC);

	m_vecMotion[0]->Render(hDC, iScrollX, iScrollY);
}

void CFallingStone::Release()
{
}

void CFallingStone::OnCollision(CObj* _pOther)
{
	if (PLAYER == _pOther->GetType())
	{
		bool result = m_pCollider->AddHitted(_pOther);

		if (result)
			static_cast<CGameObj*>(_pOther)->TakeDamage(m_iAtk);

		CollisionGameObj();
	}
}

void CFallingStone::CollisionMapObj()
{
}

void CFallingStone::CollisionGameObj()
{
	ChangeMotion((int)m_bLanded);
}

void CFallingStone::StartFalling(int _iLeft, int _iTop, int _iRight, int _iBottom)
{
	int iCX = _iRight - _iLeft;
	int iCY = _iBottom - _iTop;

	m_vPos.fX = (float)(rand() % iCX + _iLeft);
	m_vPos.fY = (float)(_iTop);

	m_tEndPos.fX = m_vPos.fX;
	m_tEndPos.fY = (float)(rand() % iCY + _iTop);

	m_bActive = true;

	m_vVelocity = { 0, +1 };
	ChangeMotion((int)m_bLanded);
}

void CFallingStone::EndFalling()
{
	if (50.f > m_vPos.Distance(m_tEndPos) && !m_bLanded)
	{
		m_vVelocity = { 0, 0 };
		m_bLanded = true;
		ChangeMotion((int)m_bLanded);
	}
}

void CFallingStone::ChangeMotion(int _iIndex)
{
	m_vecMotion[0]->SetMotion(_iIndex);
}

void CFallingStone::InitializeMotion()
{
	m_vecMotion.resize(1);

	m_vecMotion[0] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"STONE"));
	m_vecMotion[0]->SetPos(&m_vPos);
	m_vecMotion[0]->SetSize(m_vSize);
	m_vecMotion[0]->SetRect(&m_tRect);
	m_vecMotion[0]->ResizeFrameVec(2);
	m_vecMotion[0]->SetFrame(0, 0, 0, 0, true);
	m_vecMotion[0]->SetFrame(1, 0, 0, 6, false);
}
