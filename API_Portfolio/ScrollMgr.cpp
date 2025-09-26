#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;

CScrollMgr::CScrollMgr() : 
	m_fScrollX(0.f), m_fScrollY(0.f), 
	m_tMapSize(),
	m_bTarget(false), m_pTargetPos()
{
}

CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::UpdateScroll()
{
	if (!m_bTarget)
		return;

	m_fScrollX = -(m_pTargetPos->fX - CENTERX);
	m_fScrollY = -(m_pTargetPos->fY - CENTERY);
}

void CScrollMgr::ScrollLock()
{
	if (0.f < m_fScrollX)
		m_fScrollX = 0.f;

	if (0.f < m_fScrollY)
		m_fScrollY = 0.f;

	if (WINCX - m_tMapSize.fX > m_fScrollX)
		m_fScrollX = WINCX - m_tMapSize.fX;

	if (WINCY - m_tMapSize.fY > m_fScrollY)
		m_fScrollY = WINCY - m_tMapSize.fY;
}

bool CScrollMgr::IsCulling(VEC2 _vPos, VEC2 _vSize)
{
	VEC2 vOffset = { 100, 100 };

	if (-(m_fScrollX + vOffset.fX) > _vPos.fX - (_vSize.fX * 0.5f) 
		|| -(m_fScrollX - vOffset.fX) + WINCX < _vPos.fX + (_vSize.fX * 0.2f))
		return true;

	if (-(m_fScrollY + vOffset.fY) > _vPos.fY - (_vSize.fY * 0.5f) 
		|| -(m_fScrollY - vOffset.fY) + WINCY < _vPos.fY + (_vSize.fY * 0.2f))
		return true;

	return false;
}
