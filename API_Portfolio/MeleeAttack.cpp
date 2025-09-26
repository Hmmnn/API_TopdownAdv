#include "stdafx.h"
#include "MeleeAttack.h"
#include "Sword.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "SoundMgr.h"

CMeleeAttack::CMeleeAttack() :
	m_fAngleSpeed(0), m_fDist(0), m_pSword(nullptr),
	m_bSpin(false)
{
}

CMeleeAttack::~CMeleeAttack()
{
	Release();
}

void CMeleeAttack::Initialize()
{
	m_fAngleSpeed = 800.f;
	m_fDist = 60.f;
	m_fChargeTime = 1.5f;

	m_pSword = CAbstractFactory<CSword>::Create();
	CSword* TempSword = static_cast<CSword*>(m_pSword);
	TempSword->SetAngleSpeed(m_fAngleSpeed);
	TempSword->SetDistance(m_fDist);

	CObjMgr::GetInstance()->AddObj(PLAYERWEAPON, TempSword); 
	//TempSword->SetCollided(&m_setCollided);
}

void CMeleeAttack::Release()
{
}

void CMeleeAttack::ActivateSkill()
{
	if (m_bCharge)
		ActivateChargeSkill();
	else
		ActivateDefaultSkill();
}

void CMeleeAttack::ExecuteSkill()
{
	m_pSword->SetActive(true);
}

void CMeleeAttack::DeactivateSkill()
{
	m_bActivated = false;

	m_pSword->SetActive(false);
	static_cast<CSword*>(m_pSword)->ClearHitList();
}

void CMeleeAttack::ActivateDefaultSkill()
{
	InitializeMelee();

	m_bActivated = true;

	CSoundMgr::Get_Instance()->PlaySound(L"Attack.wav", SOUND_EFFECT, 1);
}

void CMeleeAttack::ActivateChargeSkill()
{
	InitializeSpin();

	m_bActivated = true;
}

void CMeleeAttack::CheckChargeTime()
{
	m_fChargeTime += DELTA;
}

void CMeleeAttack::InitializeMelee()
{
	//m_pSword->SetActive(true);

	DIRECTION TempDir = static_cast<CGameObj*>(m_pOwner)->GetDir();
	CSword* TempSword = static_cast<CSword*>(m_pSword);
	
	TempSword->SetOwnerPos(m_pOwner->GetPos());

	switch (TempDir)
	{
	case DOWN:
		TempSword->SetStartAngle(225.f);
		TempSword->SetEndAngle(345.f);
		break;

	case UP:
		TempSword->SetStartAngle(45.f);
		TempSword->SetEndAngle(255.f);
		break;

	case LEFT:
		TempSword->SetStartAngle(135.f);
		TempSword->SetEndAngle(245.f);
		break;

	case RIGHT:
		TempSword->SetStartAngle(45.f);
		TempSword->SetEndAngle(-75.f);
		break;
	}
}

void CMeleeAttack::InitializeSpin()
{
	DIRECTION TempDir = static_cast<CGameObj*>(m_pOwner)->GetDir();
	CSword* TempSword = static_cast<CSword*>(m_pSword);

	TempSword->SetOwnerPos(m_pOwner->GetPos());

	TempSword->SetStartAngle(45.f);
	TempSword->SetEndAngle(-405.f);

	//switch (TempDir)
	//{
	//case DOWN:
	//	TempSword->SetStartAngle(225.f);
	//	TempSword->SetEndAngle(345.f);
	//	break;
	//
	//case UP:
	//	TempSword->SetStartAngle(45.f);
	//	TempSword->SetEndAngle(255.f);
	//	break;
	//
	//case LEFT:
	//	TempSword->SetStartAngle(135.f);
	//	TempSword->SetEndAngle(245.f);
	//	break;
	//
	//case RIGHT:
	//	TempSword->SetStartAngle(45.f);
	//	TempSword->SetEndAngle(-75.f);
	//	break;
	//}
}
