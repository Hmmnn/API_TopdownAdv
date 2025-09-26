#pragma once

#include "Collider.h"

class CSphereCollider : public CCollider
{
public:
	CSphereCollider();
	CSphereCollider(CObj* _pOwner, VEC2 _tSize);
	~CSphereCollider();

	void Render(HDC hDC) override;

};