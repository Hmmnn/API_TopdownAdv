#pragma once

#include "Collider.h"

class CRectCollider : public CCollider
{
public:
	CRectCollider();
	CRectCollider(CObj* _pOwner, VEC2 _tSize);
	~CRectCollider();

	virtual void Render(HDC hDC) override;
};