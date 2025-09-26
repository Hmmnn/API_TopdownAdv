#include "stdafx.h"
#include "TownScene.h"
#include "Door.h"

#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "WallMgr.h"
#include "AbstractFactory.h"
#include "SoundMgr.h"
#include "ItemMgr.h"

CTownScene::CTownScene()
{
}

CTownScene::~CTownScene()
{
    //Release();
}

void CTownScene::Initialize()
{
	CWallMgr::GetInstance()->LoadWall(TOWN);

	CScrollMgr::GetInstance()->SetMapSize({ 3024, 2880 });

	CObjMgr::GetInstance()->GetBack(PLAYER)->SetPos(1512, 2500);

	CObj* pTemp = CAbstractFactory<CDoor>::Create();
	CObjMgr::GetInstance()->AddObj(MAPOBJ, pTemp);
	CDoor* pTempDoor = dynamic_cast<CDoor*>(pTemp);
	pTemp->SetPos({ 1500, 100 });
	pTemp->SetSize({ 200, 100 });

	if (pTempDoor)
	{
		pTempDoor->SetNextScene(BOSSSTAGE);
		pTempDoor->SetOpen(true);
		pTempDoor->SetImage(false);
	}

	pTemp = CAbstractFactory<CDoor>::Create();
	CObjMgr::GetInstance()->AddObj(MAPOBJ, pTemp);
	pTempDoor = dynamic_cast<CDoor*>(pTemp);
	pTemp->SetPos({ 1500, 2700 });
	pTemp->SetSize({ 200, 100 });

	if (pTempDoor)
	{
		pTempDoor->SetNextScene(FIELD);
		pTempDoor->SetOpen(true);
		pTempDoor->SetImage(false);
	}


	CItemMgr::GetInstance()->SpawnItem(L"작은 활", { 1630, 1500 });
	CItemMgr::GetInstance()->SpawnItem(L"부메랑", { 1630, 1730 });
	//CItemMgr::GetInstance()->SpawnItem(L"거울 방패", { 1390, 1730 });
	CItemMgr::GetInstance()->SpawnItem(L"마법 지팡이", { 1390, 1500 });

	CWallMgr::GetInstance()->InitializeTown();

	CSoundMgr::Get_Instance()->PlayBGM(L"House.wav", 0.8f);
}

SCENEID CTownScene::Update()
{
    int iResult = CObjMgr::GetInstance()->Update();

    if (SCENE_NOEVENT != iResult)
        return (SCENEID)iResult;

    return TOWN;
}

void CTownScene::LateUpdate()
{
    CObjMgr::GetInstance()->LateUpdate();
}

void CTownScene::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
	int		iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

	HDC hMemDC = CBmpMgr::GetInstance()->FindBmp(L"TOWN");

	BitBlt(hDC,
		iScrollX,
		iScrollY,
		3024, 2880,
		hMemDC, 0, 0, SRCCOPY);

	CObjMgr::GetInstance()->Render(hDC);

	HDC hMiscDC = CBmpMgr::GetInstance()->FindBmp(L"TOWN_MISC");

	GdiTransparentBlt(hDC,
		iScrollX, 
		iScrollY,
		3024, 2880,
		hMiscDC,
		0, 0,
		3024, 2880,
		RGB(255, 0, 255)
	);
}

void CTownScene::Release()
{
	CObjMgr::GetInstance()->ClearRenderList();

	//CObjMgr::GetInstance()->DeleteObj(WALL);
	CObjMgr::GetInstance()->DeleteObj(MAPOBJ);

	CSoundMgr::Get_Instance()->StopAll();
}
