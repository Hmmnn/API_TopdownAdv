#pragma once

#include "Define.h"
#include "StoppedImage.h"

class CQuestMgr
{
	SINGLETON(CQuestMgr)

	typedef struct tagScriptInfo
	{
		int		iPauseFrame;
		int		iLastFrame;
		VEC2	vFullSize;
		CStoppedImage* pScript;

		tagScriptInfo() : iPauseFrame(0), iLastFrame(0), vFullSize(), pScript(nullptr)	{}
		tagScriptInfo(HDC hMemDC, VEC2 _vFullSize, int _iPauseFrame, int _iLastFrame) :
			iPauseFrame(_iPauseFrame), iLastFrame(_iLastFrame), vFullSize(_vFullSize)
		{
			pScript = new CStoppedImage(hMemDC, _vFullSize, _iLastFrame);
		}

		~tagScriptInfo()
		{
			Safe_Delete<CStoppedImage*>(pScript);
		}

	}SCRIPT;

private:
	CQuestMgr();
	~CQuestMgr();

public:
	void		Initialize();
	void		Release();

	void		EnterScript(const TCHAR* _szKey);
	void		ExitScript();

private:
	void		SetNextScript(const TCHAR* _szKey);

private:
	bool		m_bActive;

	const TCHAR* m_szCurKey;
	map<const TCHAR*, SCRIPT*>	m_mapScript;
};
