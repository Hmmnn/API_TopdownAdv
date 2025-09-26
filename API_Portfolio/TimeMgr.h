#pragma once

#include "Define.h"

class CTimeMgr
{
	SINGLETON(CTimeMgr)

private:
	CTimeMgr();
	~CTimeMgr();

public:
	void		Update();

	void		Pause()		{ m_bStopped = true; }
	void		Resume()	{ m_bStopped = false; }

	float		GetDeltaTime()	{ return (m_fTimeElapsed > 0.05f) ? 0.05f : m_fTimeElapsed; }
	int			GetFPS()		{ return m_iFrameRate; }

	void		SetFPSLock(float _Value) { m_fFPSLock = _Value; }

private:
	float		m_fTimeScale;
	float		m_fTimeElapsed;

	__int64		m_iCurTime;
	__int64		m_iPrevTime;
	__int64		m_iPeriodPrequency;

	int			m_iFrameCount;
	int			m_iFrameRate;

	float		m_fOneSecond;

	bool		m_bStopped;

	float		m_fFPSLock;
};
