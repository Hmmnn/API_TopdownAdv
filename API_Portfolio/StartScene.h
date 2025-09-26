#pragma once

#include "Scene.h"

class CStartScene : public CScene
{
public:
	CStartScene();
	~CStartScene();

	void Initialize() override;
	SCENEID Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;
};
