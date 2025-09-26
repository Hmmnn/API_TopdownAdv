#pragma once

#include "StaticObj.h"

class CButtonObj : public CStaticObj
{
public:
	CButtonObj();
	~CButtonObj();

	virtual void		Initialize() override;
	virtual int			Update() override;
	virtual void		LateUpdate() override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release() override;

	virtual void		OnCollision(CObj* _pOther) override;

private:
	virtual void		InitializeImage() override;

private:
	bool			m_bPushed;
};