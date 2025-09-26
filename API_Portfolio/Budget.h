#pragma once

#include "Obj.h"

class CStoppedImage;

class CBudget : public CObj
{
public:
	CBudget();
	~CBudget();

	void Initialize() override;
	int Update() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void	SetNumberImage();

public:
	void	SetBudget(const int* _pBudget) { m_pBudget = _pBudget; }

private:
	list<CStoppedImage*> m_listNumber;

	HDC		m_hNumberImage;
	HDC		m_hRupeeIcon;

	const int*	m_pBudget;
	int		m_iPreBudget;
};