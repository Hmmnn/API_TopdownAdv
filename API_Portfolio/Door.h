#pragma once

#include "StaticObj.h"

class CDoor : public CStaticObj
{
public:
	CDoor();
	~CDoor();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void	OnCollision(CObj* _pOther) override;

protected:
	virtual void	InitializeImage() override;

public:
	void		SetNextScene(SCENEID _eID) { m_eNextScene = _eID; }
	void		SetOpen(bool _bOpen) { m_bOpen = _bOpen; }
	void		SetImage(bool _bImage) { m_bImage = _bImage; }

	virtual void	SetPos(VEC2 _vPos) override
	{
		m_vPos = _vPos;
		UpdateRect();
	}

	virtual void	SetSize(VEC2 _vSize) override
	{
		m_vSize = _vSize;
		m_pCollider->SetSize(_vSize);
		UpdateRect();
	}

private:
	bool		m_bOpen;
	bool		m_bImage;
	bool		m_bShifting;

	SCENEID		m_eNextScene;
};