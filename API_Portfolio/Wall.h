#pragma once

#include "Obj.h"

class CWall : public CObj
{
public:
	CWall();
	CWall(float _fX, float _fY, float _fCX, float _fCY);
	~CWall();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void	SetPos(float _fX, float _fY) override;
	virtual void	SetPos(VEC2 _vPos) override;
	virtual void	SetSize(float _fCX, float _fCY) override;
	virtual void	SetSize(VEC2 _vSize) override;

};