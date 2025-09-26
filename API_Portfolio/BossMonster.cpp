#include "stdafx.h"
#include "BossMonster.h"
#include "Phase1Boss.h"
#include "Phase2Boss.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

CBossMonster::CBossMonster() :
    m_bChanging(false)
{
}

CBossMonster::~CBossMonster()
{
    Release();
}

void CBossMonster::Initialize()
{
    m_vecBoss.resize(PHS_END);

    m_vecBoss[PHASE_1] = CAbstractFactory<CPhase1Boss>::Create();
    CObjMgr::GetInstance()->AddObj(BOSS, m_vecBoss[PHASE_1]);
    m_vecBoss[PHASE_1]->SetPos(504, 384 - 200);
    m_vecBoss[PHASE_1]->SetActive(true);

    m_vecBoss[PHASE_2] = CAbstractFactory<CPhase2Boss>::Create();
    CObjMgr::GetInstance()->AddObj(BOSS, m_vecBoss[PHASE_2]);
    m_vecBoss[PHASE_2]->SetActive(false);

    m_ePhase = PHASE_1;
}

void CBossMonster::CheckPhase()
{
    if (!m_vecBoss[PHASE_1]->GetActive() && !m_bChanging)
        m_bChanging = true;
}

void CBossMonster::TriggerChange()
{
    if (m_bChanging && !m_vecBoss[PHASE_2]->GetActive())
        ChangePhase();
}

void CBossMonster::Release()
{
}

void CBossMonster::ChangePhase()
{
    m_ePhase = PHASE_2;

    static_cast<CPhase2Boss*>(m_vecBoss[PHASE_2])->SetvecTrap(static_cast<CPhase1Boss*>(m_vecBoss[PHASE_1])->GetvecTraps());
    m_vecBoss[PHASE_2]->SetPos(m_vecBoss[PHASE_1]->GetPos());
    m_vecBoss[PHASE_2]->SetActive(true);
}
