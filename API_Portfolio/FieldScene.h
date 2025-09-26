#pragma once

#include "Scene.h"

class CCollider;

class CFieldScene : public CScene
{
public:
	CFieldScene();
	~CFieldScene();

	virtual void Initialize() override;
	virtual SCENEID Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};