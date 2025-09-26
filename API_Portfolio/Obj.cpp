#include "stdafx.h"
#include "Obj.h"
#include "Collider.h"

CObj::CObj() : 
	m_eObjType(OBJ_END), m_bActive(true), m_pCollider(nullptr),
	m_eRenderID(RENDER_END)
{
	ZeroMemory(&m_tRect, sizeof(RECT));
}

CObj::CObj(float _fX, float _fY, float _fCX, float _fCY) : 
	m_eObjType(OBJ_END), m_bActive(true), m_pCollider(nullptr),
	m_eRenderID(RENDER_END)
{
	m_vPos = { _fX, _fY };
	m_vSize = { _fCX, _fCY };

	UpdateRect();
}

CObj::~CObj()
{
	Safe_Delete<CCollider*>(m_pCollider);
}

void CObj::UpdateRect()
{
	m_tRect.left	= LONG(m_vPos.fX - (m_vSize.fX * 0.5f));
	m_tRect.top		= LONG(m_vPos.fY - (m_vSize.fY * 0.5f));
	m_tRect.right	= LONG(m_vPos.fX + (m_vSize.fX * 0.5f));
	m_tRect.bottom	= LONG(m_vPos.fY + (m_vSize.fY * 0.5f));

	if(m_pCollider)
		m_pCollider->UpdateRect();
}
