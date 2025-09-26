#include "stdafx.h"
#include "MagicAttack.h"
#include "MagicBullet.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"

CMagicAttack::CMagicAttack()
{
}

CMagicAttack::~CMagicAttack()
{
	Release();
}

void CMagicAttack::Initialize()
{
	m_vecMagic.resize(30);

	for (auto& Bullet : m_vecMagic)
	{
		Bullet = CAbstractFactory<CMagicBullet>::Create();
		CObjMgr::GetInstance()->AddObj(PLAYERBULLET, Bullet);
	}
}

void CMagicAttack::Release()
{
}

void CMagicAttack::ActivateSkill()
{
	m_bActivated = true;
}

void CMagicAttack::ExecuteSkill()
{
	if (!m_bActivated)
		return;

	CGameObj* pTempGame = static_cast<CGameObj*>(m_pOwner);

	for (auto& Bullet : m_vecMagic)
	{
		if (Bullet->GetActive())
			continue;

		static_cast<CMagicBullet*>(Bullet)->Shoot(m_pOwner->GetPos(), pTempGame->GetDir());
		return;
	}
}

void CMagicAttack::DeactivateSkill()
{
	m_bActivated = false;
}
