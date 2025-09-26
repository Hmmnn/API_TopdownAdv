#pragma once

#include "Scene.h"

class CSceneMgr
{
	SINGLETON(CSceneMgr)

private:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render(HDC hDC);
	void		Release();

	void		ChangeScene(SCENEID _eNextScene);

public:
	SCENEID		GetCurSceneID() { return m_eCurID; }

private:
	vector<CScene*>		m_SceneVec;

	CScene*			m_CurScene;
	SCENEID			m_eCurID;
};