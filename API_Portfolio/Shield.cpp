#include "stdafx.h"
#include "Shield.h"
#include "RectCollider.h"
#include "TimeMgr.h"

CShield::CShield() :
	m_vOffset(), m_fAtkTime(0), m_fTimeLimit(0)
{
}

CShield::~CShield()
{
	Release();
}

void CShield::Initialize()
{
	m_eObjType = PLAYERSHIELD;

	m_fTimeLimit = 2.f;

	m_pCollider = new CRectCollider(this, { 45, 45 });
	m_pCollider->SetOffset({ 0, -10 });
}

int CShield::Update()
{
	if (!m_bActive)
		return SCENE_NOEVENT;

	if (!m_pCollider->GetActive())
		m_pCollider->SetActive(true);

	m_fAtkTime += DELTA;

	CheckTimeLimit();

	CObj::UpdateRect();

	return SCENE_NOEVENT;
}

void CShield::LateUpdate()
{
	if (!m_bActive)
		return;


}

void CShield::Render(HDC hDC)
{
	if (!m_bActive)
		return;

	m_pCollider->Render(hDC);
}

void CShield::Release()
{
}

void CShield::OnCollision(CObj* _pOther)
{
	// 상대 처리할 게 있나?
	// 넉백 혹은 튕겨내기
	// 방패보다 플레이어 콜라이더가 먼저 닿았을 경우 예외 처리
}

void CShield::SetShieldDir(DIRECTION _eDir, VEC2 _vOwnerPos)
{
	switch (_eDir)
	{
	case DOWN:
		m_vOffset = { 0, +30 };
		break;

	case UP:
		m_vOffset = { 0, 10 };
		break;

	case LEFT:
		m_vOffset = { -10, +20 };
		break;

	case RIGHT:
		m_vOffset = { +10, +20 };
		break;
	}

	m_vPos = _vOwnerPos + m_vOffset;
	m_bActive = true;

	CObj::UpdateRect();
}

void CShield::CheckTimeLimit()
{
	if (m_fTimeLimit > m_fAtkTime)
		return;

	m_fAtkTime = 0;

	m_bActive = false;
	m_pCollider->SetActive(false);
}
