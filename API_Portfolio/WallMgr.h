#pragma once

#include "Obj.h"

class CWallMgr
{
	SINGLETON(CWallMgr)

private:
	CWallMgr();
	~CWallMgr();

	void		Initialize();
	void		Release();

public:
	void		InitializeField();
	void		InitializeTown();
	void		InitializeDungeon();
	void		InitializeBossStage();

	void		AddTestWall(SCENEID _eID, CObj* _pWall);
	void		DeleteTestWall(SCENEID _eID);
	void		AddWall(SCENEID _eID, CObj* _pWall);

	void		SaveWall(SCENEID _eID);
	void		LoadWall(SCENEID _eID);

private:
	list<CObj*>	m_listWall[SC_END];
};