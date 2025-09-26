#pragma once

#include "Obj.h"

class CStoppedImage;

class CEffect : public CObj
{
public:
	CEffect();
	CEffect(HDC _hMemDC, VEC2 _vFullSize, int _iLastFrame);
	~CEffect();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

	virtual void SetPos(VEC2 _vPos) override { m_vPos = _vPos; CObj::UpdateRect(); }

	void	Play(VEC2 _vPos);

private:
	CStoppedImage* m_pSprite;

	float	m_fTime;
	float	m_fFrameRate;
	int		m_iCurFrame;
};