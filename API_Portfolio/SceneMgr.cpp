#include "stdafx.h"
#include "SceneMgr.h"
#include "StartScene.h"
#include "FieldScene.h"
#include "TownScene.h"
#include "DungeonScene.h"
#include "BossScene.h"
#include "MyEditScene.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() : m_CurScene(nullptr), m_eCurID(SC_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Initialize()
{
	m_SceneVec.resize(SC_END);

	m_SceneVec[TITLE] = new CStartScene;
	m_SceneVec[FIELD] = new CFieldScene;
	m_SceneVec[TOWN] = new CTownScene;
	m_SceneVec[DUNGEON] = new CDungeonScene;
	m_SceneVec[BOSSSTAGE] = new CBossScene;
	m_SceneVec[EDIT] = new CMyEditScene;

	m_eCurID = TITLE;
	m_CurScene = m_SceneVec[m_eCurID];

	m_CurScene->Initialize();

	//ChangeScene(FIELD);
	//ChangeScene(DUNGEON);
	//ChangeScene(BOSSSTAGE);
	//ChangeScene(EDIT);
}

void CSceneMgr::Update()
{
	SCENEID eResult = m_CurScene->Update();

	if (m_eCurID != eResult)
	{
		ChangeScene(eResult);
		m_CurScene->Update();
	}
}

void CSceneMgr::LateUpdate()
{
	m_CurScene->LateUpdate();
}

void CSceneMgr::Render(HDC hDC)
{
	m_CurScene->Render(hDC);
}

void CSceneMgr::Release()
{
	for_each(m_SceneVec.begin(), m_SceneVec.end(), Safe_Delete<CScene*>);
	m_SceneVec.clear();
}

void CSceneMgr::ChangeScene(SCENEID _eNextScene)
{
	m_CurScene->Release();

	m_CurScene = m_SceneVec[_eNextScene];
	m_CurScene->Initialize();

	m_eCurID = _eNextScene;
}
