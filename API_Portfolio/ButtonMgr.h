#pragma once

#include "Define.h"

class CButtonMgr
{
public:
	CButtonMgr();
	~CButtonMgr();

	void		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render(HDC hDC);
	void		Release();

	void		EditField();
	void		EditTown();
	void		EditDungeon();
	void		EditBossStage();

private:
	vector<vector<class CMyButton*>> m_vecButton;

	SCENEID		m_eEditingMap;
	bool		m_bLeftSelected;
	bool		m_bRight;

	VEC2		vLeftTop, vRightBottom;
	bool		bComplete;
};