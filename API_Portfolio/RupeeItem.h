#pragma once

#include "Item.h"

class CRupeeItem : public CItem
{
public:
	CRupeeItem();
	~CRupeeItem();

	virtual void	Initialize() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	virtual void	OnCollision(CObj* _pOther) override;
};