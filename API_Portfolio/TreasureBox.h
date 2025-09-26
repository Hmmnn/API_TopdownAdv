#pragma once

#include "StaticObj.h"

class CTreasureBox : public CStaticObj
{
public:
	CTreasureBox();
	~CTreasureBox();

	virtual void		Initialize() override;
	virtual int			Update() override;
	virtual void		LateUpdate() override;
	virtual void		Render(HDC hDC) override;
	virtual void		Release() override;

	virtual void		OnCollision(CObj* _pOther) override;

private:
	virtual void		InitializeImage() override;

private:
	CObj*		m_pTreasure;
};