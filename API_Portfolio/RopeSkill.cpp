#include "stdafx.h"
#include "RopeSkill.h"
#include "RopeHead.h"
#include "GameObj.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"

CRopeSkill::CRopeSkill() :
	m_pHead(nullptr), m_fDefaultSpeed(0)
{
}

CRopeSkill::~CRopeSkill()
{
	Release();
}

void CRopeSkill::Initialize()
{
	m_pHead = CAbstractFactory<CRopeHead>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMYWEAPON, m_pHead);
}

void CRopeSkill::Release()
{
}

void CRopeSkill::ActivateSkill()
{
	m_bActivated = true;

	m_fDefaultSpeed = static_cast<CGameObj*>(m_pOwner)->GetSpeed();
}

void CRopeSkill::ExecuteSkill()
{
	CGameObj* pTempGame = static_cast<CGameObj*>(m_pOwner);
	static_cast<CRopeHead*>(m_pHead)->SetDirOffset(m_pOwner->GetPos(), pTempGame->GetDir());
	pTempGame->SetSpeed(500.f);

	m_pHead->SetActive(true);
}

void CRopeSkill::DeactivateSkill()
{
	m_bActivated = false;

	static_cast<CGameObj*>(m_pOwner)->SetSpeed(m_fDefaultSpeed);
	m_pHead->SetActive(false);
	static_cast<CRopeHead*>(m_pHead)->ClearHitted();
}
