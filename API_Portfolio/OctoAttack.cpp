#include "stdafx.h"
#include "OctoAttack.h"
#include "OctoBullet.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"

COctoAttack::COctoAttack()
{
}

COctoAttack::~COctoAttack()
{
	Release();
}

void COctoAttack::Initialize()
{
	m_vecBullet.resize(30);

	for (auto& Bullet : m_vecBullet)
	{
		Bullet = CAbstractFactory<COctoBullet>::Create();
		CObjMgr::GetInstance()->AddObj(ENEMYBULLET, Bullet);
		Bullet->SetActive(false);
	}
}

void COctoAttack::Release()
{
}

void COctoAttack::ActivateSkill()
{
	m_bActivated = true;
}

void COctoAttack::ExecuteSkill()
{
	if (!m_bActivated)
		return;

	DIRECTION	eTempDir = static_cast<CGameObj*>(m_pOwner)->GetDir();
	
	for (auto& Bullet : m_vecBullet)
	{
		if (Bullet->GetActive())
			continue;

		static_cast<COctoBullet*>(Bullet)->Shoot(m_pOwner->GetPos(), eTempDir);
		break;
	}
}

void COctoAttack::DeactivateSkill()
{
	m_bActivated = false;
}
