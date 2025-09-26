#pragma once

#include "Scene.h"

class CBossMonster;

class CBossScene : public CScene
{
public:
	CBossScene();
	~CBossScene();

	virtual void Initialize() override;
	virtual SCENEID Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	CBossMonster*	m_pBossMon;
};