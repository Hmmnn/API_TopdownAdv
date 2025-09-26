#pragma once

#include "Define.h"

class CScene
{
public:
	CScene();
	virtual ~CScene();

	virtual void		Initialize()		PURE;
	virtual SCENEID		Update()			PURE;
	virtual void		LateUpdate()		PURE;
	virtual void		Render(HDC hDC)		PURE;
	virtual void		Release()			PURE;
};