#include "stdafx.h"
#include "KeeseSkill.h"
#include "SphereCollider.h"
#include "KeeseBody.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"

CKeeseSkill::CKeeseSkill() :
	m_pBody(nullptr),
	m_fDefaultSpeed(0), m_fDashSpeed(0)
{
}

CKeeseSkill::~CKeeseSkill()
{
	Release();
}

void CKeeseSkill::Initialize()
{
	m_fDashSpeed = 300.f;

	m_pBody = CAbstractFactory<CKeeseBody>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMYWEAPON, m_pBody);
}

void CKeeseSkill::Release()
{
}

void CKeeseSkill::ActivateSkill()
{
	m_bActivated = true;

	m_fDefaultSpeed = static_cast<CGameObj*>(m_pOwner)->GetSpeed();
}

void CKeeseSkill::ExecuteSkill()
{
	if (m_pBody->GetActive())
		return;

	static_cast<CKeeseBody*>(m_pBody)->SetOwnerPos(m_pOwner->GetPos());
	static_cast<CGameObj*>(m_pOwner)->SetSpeed(m_fDashSpeed);

	m_pBody->SetActive(true);
	m_pBody->GetCollider()->SetActive(true);
}

void CKeeseSkill::DeactivateSkill()
{
	//m_bActivated = false;
	//
	//static_cast<CGameObj*>(m_pOwner)->SetSpeed(m_fDefaultSpeed);
	//m_pBody->SetActive(false);
	//m_pBody->GetCollider()->SetActive(false);

	if (!m_pBody->GetActive())
	{
		static_cast<CGameObj*>(m_pOwner)->SetSpeed(m_fDefaultSpeed);
		m_bActivated = false;

		static_cast<CKeeseBody*>(m_pBody)->ClearHitted();
	}
}
