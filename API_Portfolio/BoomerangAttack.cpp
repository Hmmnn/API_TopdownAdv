#include "stdafx.h"
#include "BoomerangAttack.h"
#include "Boomerang.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CBoomerangAttack::CBoomerangAttack() :
	m_pBoomerang(nullptr)
{
}

CBoomerangAttack::~CBoomerangAttack()
{
	Release();
}

void CBoomerangAttack::Initialize()
{
	m_pBoomerang = CAbstractFactory<CBoomerang>::Create();
	CObjMgr::GetInstance()->AddObj(PLAYERWEAPON, m_pBoomerang);
}

void CBoomerangAttack::Release()
{
}

void CBoomerangAttack::ActivateSkill()
{
	DIRECTION	TempDir = static_cast<CGameObj*>(m_pOwner)->GetDir();
    CBoomerang* pTempBoo = static_cast<CBoomerang*>(m_pBoomerang);

    pTempBoo->SetOwner(m_pOwner);
    pTempBoo->SetPos(m_pOwner->GetPos());

  	switch (TempDir)
	{
    case DOWN:
        pTempBoo->ThrowBoomerang({ 0, +1 });
        break;

    case UP:
        pTempBoo->ThrowBoomerang({ 0, -1 });
        break;

    case LEFT:
        pTempBoo->ThrowBoomerang({ -1, 0 });
        break;

    case RIGHT:
        pTempBoo->ThrowBoomerang({ +1, 0 });
        break;
    }

    m_bActivated = true;
}

void CBoomerangAttack::ExecuteSkill()
{
    m_pBoomerang->SetActive(true);
}

void CBoomerangAttack::DeactivateSkill()
{
	//m_pBoomerang->SetActive(false);

    m_bActivated = false;

    static_cast<CBoomerang*>(m_pBoomerang)->ClearHitted();
}
