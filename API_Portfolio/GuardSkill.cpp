#include "stdafx.h"
#include "GuardSkill.h"
#include "Shield.h"
#include "GameObj.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CGuardSkill::CGuardSkill() :
	m_pShield(nullptr)
{
}

CGuardSkill::~CGuardSkill()
{
	Release();
}

void CGuardSkill::Initialize()
{
	m_pShield = CAbstractFactory<CShield>::Create();
	CObjMgr::GetInstance()->AddObj(PLAYERSHIELD, m_pShield);
	m_pShield->SetActive(false);
}

void CGuardSkill::Release()
{
}

void CGuardSkill::ActivateSkill()
{
	CGameObj* pTempGame = static_cast<CGameObj*>(m_pOwner);
	DIRECTION eTempDir = pTempGame->GetDir();
	static_cast<CShield*>(m_pShield)->SetShieldDir(eTempDir, pTempGame->GetPos());

	m_bActivated = true;
}

void CGuardSkill::ExecuteSkill()
{
	if (m_bActivated)
	{
		m_pShield->SetActive(true);
		CSoundMgr::Get_Instance()->PlaySound(L"Shield.wav", SOUND_EFFECT, 1);
	}
}

void CGuardSkill::DeactivateSkill()
{
	m_bActivated = false;

	m_pShield->SetActive(false);
}
