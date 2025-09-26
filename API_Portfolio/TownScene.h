#pragma once

#include "Scene.h"

class CTownScene : public CScene
{
public:
	CTownScene();
	~CTownScene();

	virtual void Initialize() override;
	virtual SCENEID Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};