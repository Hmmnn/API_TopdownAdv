#pragma once

#include "Obj.h"

class CStoppedImage;

class CKeyGuide : public CObj
{
public:
	CKeyGuide();
	~CKeyGuide();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	void		SetImage(int _iIndex, HDC _hImage);

private:
	vector<CStoppedImage*> m_vecAction;
	vector<CStoppedImage*> m_vecEquip;

	vector<VEC2>	m_vecPos;
	vector<VEC2>	m_vecOffset;
};