#include "stdafx.h"
#include "FieldScene.h"
#include "Player.h"
#include "PlayerState.h"
#include "TreasureBox.h"
#include "Octorok.h"
#include "Rope.h"
#include "Keese.h"
#include "Door.h"

#include "Inventory.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "AbstractFactory.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "SoundMgr.h"
#include "WallMgr.h"
#include "UIMgr.h"

#include "KeyMgr.h"
#include "ItemMgr.h"

CFieldScene::CFieldScene()
{
}

CFieldScene::~CFieldScene()
{
    //Release();
}

void CFieldScene::Initialize()
{
	CWallMgr::GetInstance()->LoadWall(FIELD);
	CWallMgr::GetInstance()->InitializeField();

	auto TempListPointer = CObjMgr::GetInstance()->GetList(PLAYER);

	if (TempListPointer->empty())
	{
		CObjMgr::GetInstance()->AddObj(PLAYER, CAbstractFactory<CPlayer>::Create());
		CObjMgr::GetInstance()->GetBack(PLAYER)->SetPos(1960, 1240);
		CUIMgr::GetInstance()->InitializePlayerHp(static_cast<CGameObj*>(CObjMgr::GetInstance()->GetBack(PLAYER))->GetHpPointer());
	}

	CScrollMgr::GetInstance()->SetMapSize(VEC2(3021, 2067));
	CScrollMgr::GetInstance()->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER)->GetPosPointer());

	CObj* pTempObj = CAbstractFactory<COctorok>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMY, pTempObj);
	pTempObj->SetPos(1514, 300);
	COctorok* pTempOcto = static_cast<COctorok*>(pTempObj);
	pTempOcto->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER));
	
	pTempObj = CAbstractFactory<COctorok>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMY, pTempObj);
	pTempObj->SetPos(2600, 350);
	pTempOcto = static_cast<COctorok*>(pTempObj);
	pTempOcto->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER));

	pTempObj = CAbstractFactory<CRope>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMY, pTempObj);
	pTempObj->SetPos(1500, 1850);
	CRope* pTempRope = static_cast<CRope*>(pTempObj);
	pTempRope->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER));

	pTempObj = CAbstractFactory<CRope>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMY, pTempObj);
	pTempObj->SetPos(1300, 1300);
	pTempRope = static_cast<CRope*>(pTempObj);
	pTempRope->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER));

	pTempObj = CAbstractFactory<CRope>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMY, pTempObj);
	pTempObj->SetPos(630, 800);
	pTempRope = static_cast<CRope*>(pTempObj);
	pTempRope->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER));

	pTempObj = CAbstractFactory<CRope>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMY, pTempObj);
	pTempObj->SetPos(2700, 390);
	pTempRope = static_cast<CRope*>(pTempObj);
	pTempRope->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER));

	pTempObj = CAbstractFactory<CRope>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMY, pTempObj);
	pTempObj->SetPos(2600, 700);
	pTempRope = static_cast<CRope*>(pTempObj);
	pTempRope->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER));

	pTempObj = CAbstractFactory<CRope>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMY, pTempObj);
	pTempObj->SetPos(2900, 1260);
	pTempRope = static_cast<CRope*>(pTempObj);
	pTempRope->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER));

	pTempObj = CAbstractFactory<CRope>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMY, pTempObj);
	pTempObj->SetPos(1740, 1620);
	pTempRope = static_cast<CRope*>(pTempObj);
	pTempRope->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER));

	pTempObj = CAbstractFactory<CRope>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMY, pTempObj);
	pTempObj->SetPos(1646, 652);
	pTempRope = static_cast<CRope*>(pTempObj);
	pTempRope->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER));

	pTempObj = CAbstractFactory<CRope>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMY, pTempObj);
	pTempObj->SetPos(2622, 1711);
	pTempRope = static_cast<CRope*>(pTempObj);
	pTempRope->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER));

	pTempObj = CAbstractFactory<CKeese>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMY, pTempObj);
	pTempObj->SetPos(1000, 600);
	CKeese* pTempKeese = static_cast<CKeese*>(pTempObj);
	pTempKeese->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER));

	pTempObj = CAbstractFactory<CKeese>::Create();
	CObjMgr::GetInstance()->AddObj(ENEMY, pTempObj);
	pTempObj->SetPos(3000, 1200);
	pTempKeese = static_cast<CKeese*>(pTempObj);
	pTempKeese->SetTarget(CObjMgr::GetInstance()->GetBack(PLAYER));


	CObj* pTemp = CAbstractFactory<CDoor>::Create();
	CObjMgr::GetInstance()->AddObj(MAPOBJ, pTemp);
	CDoor* pTempDoor = dynamic_cast<CDoor*>(pTemp);
	pTemp->SetPos({ 1510, 0 });
	pTemp->SetSize({ 400, 200 });

	if (pTempDoor)
	{
		pTempDoor->SetNextScene(TOWN);
		pTempDoor->SetOpen(true);
		pTempDoor->SetImage(false);
	}

	//CItemMgr::GetInstance()->SpawnItem(L"스미스의 검", { 1786, 1324 });
	CInventory::GetInstance()->AddItem(CItem::EQUIP, CItemMgr::GetInstance()->GetItem(L"스미스의 검"));

	CUIMgr::GetInstance()->InitializeKeyGuide();
	CUIMgr::GetInstance()->InitializeBudget();
	CUIMgr::GetInstance()->SetBudget(CInventory::GetInstance()->GetRupeePointer());

	CSoundMgr::Get_Instance()->PlayBGM(L"Field.wav", 0.5f);
}

SCENEID CFieldScene::Update()
{
	//if (KEY_DOWN('1'))
	//	return BOSSSTAGE;
	//
	//if (KEY_DOWN('T'))
	//{
	//	CItemMgr::GetInstance()->SpawnItem(L"스미스의 검", { 1960, 1530 });
	//	CItemMgr::GetInstance()->SpawnItem(L"루피", { 1960, 1630 });
	//	CItemMgr::GetInstance()->SpawnItem(L"작은 활", { 1760, 1530 });
	//	CItemMgr::GetInstance()->SpawnItem(L"부메랑", { 1560, 1530 });
	//	CItemMgr::GetInstance()->SpawnItem(L"거울 방패", { 1360, 1530 });
	//	CItemMgr::GetInstance()->SpawnItem(L"마법 지팡이", { 1160, 1530 });
	//}

    int iResult = CObjMgr::GetInstance()->Update();

	if (SCENE_NOEVENT != iResult)
		return (SCENEID)iResult;

    return FIELD;
}

void CFieldScene::LateUpdate()
{
    CObjMgr::GetInstance()->LateUpdate();

	//CInventory::GetInstance()->ControlCursor();
}

void CFieldScene::Render(HDC hDC)
{
	int		iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
	int		iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

	HDC hMemDC = CBmpMgr::GetInstance()->FindBmp(L"FIELD");

	BitBlt(hDC, 
		iScrollX, 
		iScrollY, 
		3024, 2064,
		hMemDC, 0, 0, SRCCOPY);

	CObjMgr::GetInstance()->Render(hDC);

	//CInventory::GetInstance()->RenderItems(hDC);
}

void CFieldScene::Release()
{
	//CObjMgr::GetInstance()->DeleteObj(WALL);
	CObjMgr::GetInstance()->DeleteObj(MAPOBJ);
	CObjMgr::GetInstance()->DeleteObj(ENEMY);

	CObjMgr::GetInstance()->ClearRenderList();

	CObjMgr::GetInstance()->SetActive(PLAYERBULLET, false);
	CObjMgr::GetInstance()->SetActive(ENEMYBULLET, false);

	CSoundMgr::Get_Instance()->StopAll();
}
