#pragma once

#include "Obj.h"

class CAnimImage;

class CItem : public CObj
{
public:
	enum ITEMTYPE { HEART, POTION, RUPEE, 
		/*SWORD, BOW, BOOMR, STAFF, SHIELD,*/ EQUIP, IT_END };

protected:
	typedef struct tagIcon
	{
		HDC			hIcon;
		VEC2		tPos;
		VEC2		tSize;
		RECT		tRect;

	}ICON;

public:
	CItem();
	virtual ~CItem();

	virtual void	Initialize() override;
	virtual int		Update() override;
	virtual void	LateUpdate() override;
	virtual void	Render(HDC hDC) override;
	virtual void	Release() override;

	virtual void	OnCollision(CObj* _pOther) override;
	virtual void	CollisionGameObj() {}

	void			RenderIcon(HDC hDC, VEC2 _vPos);

	virtual void	ApplyAbility(CObj* _pTarget) {}
	virtual void	RevertAbility(CObj* _pTarget) {}

public:
	int				GetValue()				{ return m_iValue; }
	const TCHAR*	GetSkillName()			{ return m_szSkillKey; }
	const TCHAR*	GetName()				{ return m_szName; }
	HDC				GetIconDC()				{ return m_tIcon.hIcon; }
	
	void			SetValue(int _iValue)	{ m_iValue = _iValue; }
	void			SetIconPos(VEC2 _vPos)	{ m_tIcon.tPos = _vPos; }

protected:
	// 맵에 노출될 이미지, 인벤에 노출될 이미지, 아이템 기능, 아이템 능력치
	ITEMTYPE		m_eItemType;
	const TCHAR*	m_szName;

	ICON			m_tIcon;
	CAnimImage*		m_pSprite;
	
	const TCHAR*	m_szSkillKey;
	int				m_iValue;
};