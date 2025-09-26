#pragma once

#include "Obj.h"

class CStoppedImage;

class CHeartHpBar : public CObj
{
public:
	CHeartHpBar();
	CHeartHpBar(int _iMaxHp);
	~CHeartHpBar();

	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void		SetHp(int* _pHp) { m_pHp = _pHp; }

private:
	list<CStoppedImage*>	m_listGraphic;

	int			m_iMaxHp;
	int*		m_pHp;

	const int	m_iOneHeart;
	int			m_iMaxCount;

	VEC2		m_vFirstPos;
};