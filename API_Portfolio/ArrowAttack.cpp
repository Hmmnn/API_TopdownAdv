#include "stdafx.h"
#include "ArrowAttack.h"
#include "Arrow.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CArrowAttack::CArrowAttack()
{
}

CArrowAttack::~CArrowAttack()
{
	Release();
}

void CArrowAttack::Initialize()
{
	m_vecArrow.resize(30);

	for (size_t i = 0; i < m_vecArrow.size(); ++i)
	{
		m_vecArrow[i] = CAbstractFactory<CArrow>::Create();
		CObjMgr::GetInstance()->AddObj(PLAYERBULLET, m_vecArrow[i]);
	}
}

void CArrowAttack::Release()
{
}

void CArrowAttack::ActivateSkill()
{
	m_bActivated = true;
}

void CArrowAttack::ExecuteSkill()
{
	VEC2 TempPos = m_pOwner->GetPos();
	DIRECTION TempDir = static_cast<CGameObj*>(m_pOwner)->GetDir();

	if (LEFT == TempDir || RIGHT == TempDir)
		TempPos += VEC2(0, 10);

	for (size_t i = 0; i < m_vecArrow.size(); ++i)
	{
		if (m_vecArrow[i]->GetActive())
			continue;

		static_cast<CArrow*>(m_vecArrow[i])->ShootArrow(TempPos + m_tOffset, TempDir);
		break;
	}

	CSoundMgr::Get_Instance()->PlaySound(L"Attack.wav", SOUND_EFFECT, 1.f);

}

void CArrowAttack::DeactivateSkill()
{
	m_bActivated = false;
}
