#include "stdafx.h"
#include "TimeMgr.h"

CTimeMgr* CTimeMgr::m_pInstance = nullptr;

CTimeMgr::CTimeMgr()
	: m_fTimeScale(0.f), m_fTimeElapsed(0.f), m_iCurTime(0), m_iPrevTime(0), m_iPeriodPrequency(0),
	m_iFrameCount(0), m_iFrameRate(0), m_fOneSecond(0.f), m_bStopped(false), m_fFPSLock(0.f)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_iPeriodPrequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_iPrevTime);

	m_fTimeScale = 1.0f / (float)m_iPeriodPrequency;
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::Update()
{
	if (m_bStopped)
	{
		m_fTimeElapsed = 0.f;
		return;
	}

	QueryPerformanceCounter((LARGE_INTEGER*)&m_iCurTime);
	m_fTimeElapsed = (float)(m_iCurTime - m_iPrevTime) * m_fTimeScale;

	if (0 != m_fFPSLock)
	{
		while (m_fTimeElapsed < (1.0f / m_fFPSLock))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&m_iCurTime);
			m_fTimeElapsed = (float)(m_iCurTime - m_iPrevTime) * m_fTimeScale;
		}
	}

	m_iPrevTime = m_iCurTime;

	++m_iFrameCount;
	m_fOneSecond += m_fTimeElapsed;

	if (m_fOneSecond > 1.0f)
	{
		m_iFrameRate = m_iFrameCount;
		m_iFrameCount = 0;
		m_fOneSecond -= 1.f;
	}
}
