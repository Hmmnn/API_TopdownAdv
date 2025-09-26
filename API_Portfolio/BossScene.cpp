#include "stdafx.h"
#include "BossScene.h"
#include "StaticObj.h"
#include "BossMonster.h"

#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "WallMgr.h"
#include "SoundMgr.h"

CBossScene::CBossScene()
    : m_pBossMon(nullptr)
{
}

CBossScene::~CBossScene()
{
    //Release();
}

void CBossScene::Initialize()
{
    CWallMgr::GetInstance()->LoadWall(BOSSSTAGE);

    m_pBossMon = new CBossMonster();
    m_pBossMon->Initialize();

    //CObjMgr::GetInstance()->AddObj(BOSS, CAbstractFactory<CPhase1Boss>::Create());
    //CObjMgr::GetInstance()->GetBack(BOSS)->SetActive(false);
    //vector<CObj*>* pTemp = static_cast<CPhase1Boss*>(CObjMgr::GetInstance()->GetBack(BOSS))->GetvecTraps();
    //
    //CObjMgr::GetInstance()->AddObj(BOSS, CAbstractFactory<CPhase2Boss>::Create());
    //static_cast<CPhase2Boss*>(CObjMgr::GetInstance()->GetBack(BOSS))->SetvecTrap(pTemp);
    //CObjMgr::GetInstance()->GetBack(BOSS)->SetActive(true);

    CWallMgr::GetInstance()->InitializeBossStage();

    CObjMgr::GetInstance()->GetBack(PLAYER)->SetPos(504, 384 + 100);
    static_cast<CGameObj*>(CObjMgr::GetInstance()->GetBack(PLAYER))->SetDir(UP);

    CScrollMgr::GetInstance()->SetMapSize(VEC2(1008, 768));

    CWallMgr::GetInstance()->InitializeBossStage();

    CSoundMgr::Get_Instance()->PlayBGM(L"Cave.wav", 1.f);
}

SCENEID CBossScene::Update()
{
    m_pBossMon->TriggerChange();

    CObjMgr::GetInstance()->Update();

    return BOSSSTAGE;
}

void CBossScene::LateUpdate()
{
    CObjMgr::GetInstance()->LateUpdate();

    m_pBossMon->CheckPhase();
}

void CBossScene::Render(HDC hDC)
{
    int		iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int		iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    HDC hMemDC = CBmpMgr::GetInstance()->FindBmp(L"BOSSSTAGE");

    BitBlt(hDC,
        iScrollX,
        iScrollY,
        (int)CScrollMgr::GetInstance()->GetMapSize().fX,
        (int)CScrollMgr::GetInstance()->GetMapSize().fY,
        hMemDC, 0, 0, SRCCOPY);

    CObjMgr::GetInstance()->Render(hDC);
}

void CBossScene::Release()
{
    //CObjMgr::GetInstance()->DeleteObj(WALL);
    CObjMgr::GetInstance()->DeleteObj(MAPOBJ);
    CObjMgr::GetInstance()->DeleteObj(BOSS);
    CObjMgr::GetInstance()->DeleteObj(ENEMYBULLET);
    CObjMgr::GetInstance()->DeleteObj(ENEMYSHIELD);

    Safe_Delete<CBossMonster*>(m_pBossMon);
}
