#pragma once

#include "StaticObj.h"

class CNPC : public CStaticObj
{
public:
	CNPC();
	CNPC(HDC _hImage, const TCHAR* _szKey);
	~CNPC();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Release() override;

	virtual void	OnCollision(CObj* _pOther) override;

private:
	const TCHAR*		m_szKey;
};