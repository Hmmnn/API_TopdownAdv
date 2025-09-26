#pragma once

#include "Scene.h"

class CDungeonScene : public CScene
{
public:
	CDungeonScene();
	~CDungeonScene();

	virtual void Initialize() override;
	virtual SCENEID Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};