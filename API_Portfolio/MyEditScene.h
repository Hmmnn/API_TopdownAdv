#pragma once

#include "Scene.h"

class CMyEditScene : public CScene
{
public:
	CMyEditScene();
	~CMyEditScene();

	virtual void Initialize() override;
	virtual SCENEID Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	void		ControlScroll();
	void		AddRect(VEC2 _vLeftTop, VEC2 _vRightBottom);

private:
	class CButtonMgr* m_pBtnMgr;
};