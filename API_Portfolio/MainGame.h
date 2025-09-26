#pragma once

#include "Define.h"
#include "Player.h"
#include "SceneMgr.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render();
	void		Release();

private:
	HDC			m_DC;
	HDC			hBackBuffer;

	//CSceneMgr* 	m_pSceneMgr;
};
