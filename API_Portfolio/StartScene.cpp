#include "stdafx.h"
#include "StartScene.h"
#include "MyButton.h"

#include "Player.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "WallMgr.h"

CStartScene::CStartScene()
{
}

CStartScene::~CStartScene()
{
    Release();
}

void CStartScene::Initialize()
{
	CBmpMgr::GetInstance()->InsertBmp(L"TITLE_BG", L"../Sprites/TitleBG.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"TITLE", L"../Sprites/MinishCap.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"COMPANY", L"../Sprites/Company.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"FIELD", L"../Sprites/Field.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"TOWN", L"../Sprites/Town.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"TOWN_MISC", L"../Sprites/Town_misc.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"DUNGEON", L"../Sprites/Dungeon.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"DUN_MISC", L"../Sprites/Dungion_misc.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"BOSSSTAGE", L"../Sprites/BossArea.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"PLAYER_LEFT", L"../Sprites/Player_Left.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"PLAYER_RIGHT", L"../Sprites/Player_Right.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"PLAYER_UP", L"../Sprites/Player_Up.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"PLAYER_DOWN", L"../Sprites/Player_Down.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"ARROW", L"../Sprites/Arrow.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"BOOMERANG", L"../Sprites/BoomerangAni.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"MAGIC", L"../Sprites/Magic.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"TREASURE", L"../Sprites/TreasureBox.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"BRAZIER", L"../Sprites/brazier.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"BUTTON", L"../Sprites/Button.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"DOOR", L"../Sprites/Door.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"STONE_MOVE", L"../Sprites/StoneMove.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"OCTO_LEFT", L"../Sprites/Octorok_Left.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"OCTO_RIGHT", L"../Sprites/Octorok_Right.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"OCTO_UP", L"../Sprites/Octorok_Up.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"OCTO_DOWN", L"../Sprites/Octorok_Down.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"OCTO_BULLET", L"../Sprites/Octorok_Missile.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"ROPE_LEFT", L"../Sprites/Rope_Left.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"ROPE_RIGHT", L"../Sprites/Rope_Right.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"ROPE_UP", L"../Sprites/Rope_Up.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"ROPE_DOWN", L"../Sprites/Rope_Down.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"KEESE", L"../Sprites/Keese.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"BOSS1", L"../Sprites/Boss_Phase1.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"BOSS2", L"../Sprites/Boss_Phase2_2.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"TRAP", L"../Sprites/BossAura.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"SHEILDEYE", L"../Sprites/BossEyes.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"LASEREYE", L"../Sprites/EyeLaser.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"LASER", L"../Sprites/Laser.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"STONE", L"../Sprites/StoneAttack.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"INVEN_BG", L"../Sprites/BG_inven.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"INVEN", L"../Sprites/Inventory.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"ITEM_BG", L"../Sprites/Item_BackGround.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"INVEN_CURSOR", L"../Sprites/Select_Item.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"NUMBER", L"../Sprites/Number.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"HEART", L"../Sprites/Heart.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"BOO_ICON", L"../Sprites/Boomerang.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"BOW_ICON", L"../Sprites/Bow.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"POTION_ICON", L"../Sprites/Potion.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"RUPEE_ICON", L"../Sprites/rupee.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"SHIELD_ICON", L"../Sprites/Shield.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"STAFF_ICON", L"../Sprites/Staff.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"SWORD_ICON", L"../Sprites/Sword.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"ACTION_KEY", L"../Sprites/ActionKey.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"HEART_SPR", L"../Sprites/Heart_Field.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"RUPEE_SPR", L"../Sprites/Rupee_Field.bmp");

	CBmpMgr::GetInstance()->InsertBmp(L"MENU_EDIT", L"../Sprites/MenuEdit.bmp");
	CBmpMgr::GetInstance()->InsertBmp(L"MENU_START", L"../Sprites/MenuStart.bmp");

	CObj* TempObj = CAbstractFactory<CMyButton>::Create();
	CObjMgr::GetInstance()->AddObj(MISC, TempObj);
	CMyButton* Temp = static_cast<CMyButton*>(TempObj);
	Temp->SetMemDC(CBmpMgr::GetInstance()->FindBmp(L"MENU_EDIT"));
	Temp->SetPos(CENTERX, CENTERY+ 80);
	Temp->SetSize(240, 120);
	Temp->SetSceneID(EDIT);
	Temp->SetTitle(true);

	TempObj = CAbstractFactory<CMyButton>::Create();
	CObjMgr::GetInstance()->AddObj(MISC, TempObj);
	Temp = static_cast<CMyButton*>(TempObj);
	Temp->SetMemDC(CBmpMgr::GetInstance()->FindBmp(L"MENU_START"));
	Temp->SetPos(CENTERX, CENTERY + 180);
	Temp->SetSize(240, 120);
	Temp->SetSceneID(FIELD);
	Temp->SetTitle(true);

	CScrollMgr::GetInstance()->SetMapSize({ WINCX, WINCY });

	CSoundMgr::Get_Instance()->PlayBGM(L"Logo.wav", 1.f);
}

SCENEID CStartScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Enter", SOUND_EFFECT, 1.f);
		return FIELD;
	}

	int temp = CObjMgr::GetInstance()->Update();

    return (SCENEID)temp;
}

void CStartScene::LateUpdate()
{
	CObjMgr::GetInstance()->LateUpdate();
}

void CStartScene::Render(HDC hDC)
{
	HDC hBgDC = CBmpMgr::GetInstance()->FindBmp(L"TITLE_BG");
	HDC hTitleDC = CBmpMgr::GetInstance()->FindBmp(L"TITLE");
	HDC hCompanyDC = CBmpMgr::GetInstance()->FindBmp(L"COMPANY");

	BitBlt(hDC, 0, 0, 960, 640, hBgDC, 0, 0, SRCCOPY);
	GdiTransparentBlt(hDC, CENTERX - 250, CENTERY - 240, 501, 264, hTitleDC, 
		0, 0, 501, 264, RGB(255, 0, 255));
	GdiTransparentBlt(hDC, CENTERX - 200, WINCY - 80, 399, 48, hCompanyDC,
		0, 0, 399, 48, RGB(255, 0, 255));

	CObjMgr::GetInstance()->Render(hDC);
}

void CStartScene::Release()
{
	// 생성한 오브젝트 소멸

	CObjMgr::GetInstance()->DeleteObj(MISC);
	
	CSoundMgr::Get_Instance()->StopAll();
}
