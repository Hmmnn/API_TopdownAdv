#pragma once

#include "Item.h"

class CSwordItem : public CItem
{
public:
	CSwordItem();
	~CSwordItem();

	virtual void	Initialize() override;

	virtual void	ApplyAbility(CObj* _pTarget) override;
	virtual void	RevertAbility(CObj* _pTarget) override;
};

class CBowItem : public CItem
{
public:
	CBowItem();
	~CBowItem();

	virtual void	Initialize() override;
};

class CBoomrItem : public CItem
{
public:
	CBoomrItem();
	~CBoomrItem();

	virtual void	Initialize() override;
};

class CShieldItem : public CItem
{
public:
	CShieldItem();
	~CShieldItem();

	virtual void	Initialize() override;
};

class CStaffItem : public CItem
{
public:
	CStaffItem();
	~CStaffItem();

	virtual void	Initialize() override;
};