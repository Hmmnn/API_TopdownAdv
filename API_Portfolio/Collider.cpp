#include "stdafx.h"
#include "Collider.h"

CCollider::CCollider() : 
	m_eShape(SHAPE_END), m_pOwner(nullptr), m_bActive(true), 
	m_vPos(), m_vSize(), m_tOffset(), m_bCollided(false)
{
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tOverlap, sizeof(RECT));

	m_hGreen = CreateSolidBrush(RGB(0, 255, 0));
	m_hRed = CreateSolidBrush(RGB(255, 0, 0));

	m_hBrush = m_hGreen;
}

CCollider::CCollider(CObj* _pOwner, VEC2 _Size) : 
	m_eShape(SHAPE_END), m_bActive(true), m_pOwner(_pOwner), 
	m_vSize(_Size), m_tOffset(), m_bCollided(false)
{
	ZeroMemory(&m_tOverlap, sizeof(RECT));

	m_hGreen = CreateSolidBrush(RGB(0, 255, 0));
	m_hRed = CreateSolidBrush(RGB(255, 0, 0));

	m_hBrush = m_hGreen;

	m_vPos = _pOwner->GetPos() + m_tOffset;

	UpdateRect();
}

CCollider::~CCollider()
{
	DeleteObject(m_hGreen);
	DeleteObject(m_hRed);
}

void CCollider::UpdateRect()
{
	m_vPos = m_pOwner->GetPos() + m_tOffset;

	m_tRect.left	= LONG(m_vPos.fX - (m_vSize.fX * 0.5f));
	m_tRect.top		= LONG(m_vPos.fY - (m_vSize.fY * 0.5f));
	m_tRect.right	= LONG(m_vPos.fX + (m_vSize.fX * 0.5f));
	m_tRect.bottom	= LONG(m_vPos.fY + (m_vSize.fY * 0.5f));
}

void CCollider::DrawCollided(bool _bCollided)
{
	m_bCollided = _bCollided;

	/*if (_bCollided)
		m_hBrush = m_hRed;
	else
		m_hBrush = m_hGreen;*/
}

bool CCollider::AddHitted(CObj* _pOther)
{
	auto result = m_setHitted.insert(_pOther);

	return result.second;
}

void CCollider::ClearHitted()
{
	m_setHitted.clear();
}
