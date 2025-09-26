#pragma once

#include "StaticObj.h"

class CBrazier : public CStaticObj
{
public:
	CBrazier();
	~CBrazier();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void	OnCollision(CObj* _pOther) override;

protected:
	virtual void		InitializeImage() override;

};