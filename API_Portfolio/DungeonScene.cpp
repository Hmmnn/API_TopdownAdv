#include "stdafx.h"
#include "DungeonScene.h"
#include "ObjMgr.h"
#include "WallMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "AbstractFactory.h"
#include "Door.h"

CDungeonScene::CDungeonScene()
{
}

CDungeonScene::~CDungeonScene()
{
    //Release();
}

void CDungeonScene::Initialize()
{
    CWallMgr::GetInstance()->LoadWall(DUNGEON);
    CWallMgr::GetInstance()->InitializeDungeon();

	CObjMgr::GetInstance()->GetBack(PLAYER)->SetPos(800, 5100);

	CScrollMgr::GetInstance()->SetMapSize({ 1776, 5232 });

	CObj* pTemp = CAbstractFactory<CDoor>::Create();
	CObjMgr::GetInstance()->AddObj(MAPOBJ, pTemp);
	CDoor* pTempDoor = dynamic_cast<CDoor*>(pTemp);
	pTemp->SetPos({ 850, 100 });
	pTemp->SetSize({ 400, 200 });

	if (pTempDoor)
	{
		pTempDoor->SetNextScene(BOSSSTAGE);
		pTempDoor->SetOpen(true);
		pTempDoor->SetImage(false);
	}
}

SCENEID CDungeonScene::Update()
{
    int iResult = CObjMgr::GetInstance()->Update();

    if (SCENE_NOEVENT != iResult)
        return (SCENEID)iResult;

    return DUNGEON;
}

void CDungeonScene::LateUpdate()
{
    CObjMgr::GetInstance()->LateUpdate();
}

void CDungeonScene::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
	int		iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

	HDC hMemDC = CBmpMgr::GetInstance()->FindBmp(L"DUNGEON");

	BitBlt(hDC,
		iScrollX,
		iScrollY,
		1776, 5232,
		hMemDC, 0, 0, SRCCOPY);

	CObjMgr::GetInstance()->Render(hDC);

	HDC hMiscDC = CBmpMgr::GetInstance()->FindBmp(L"DUN_MISC");

	GdiTransparentBlt(hDC,
		iScrollX,
		iScrollY,
		1776, 5232,
		hMiscDC,
		0, 0,
		1776, 5232,
		RGB(255, 0, 255)
	);

}

void CDungeonScene::Release()
{
	CObjMgr::GetInstance()->ClearRenderList();

	//CObjMgr::GetInstance()->DeleteObj(WALL);
	CObjMgr::GetInstance()->DeleteObj(MAPOBJ);

}
