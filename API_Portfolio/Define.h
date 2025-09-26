  #pragma once

#define WINCX		960
#define WINCY		640
#define CENTERX		(WINCX *0.5f)
#define CENTERY		(WINCY *0.5f)

#define PI			3.14f

#define LERP(s, e, t)	(s + (e - s) * t)

#define PURE		= 0

#define SCENE_NOEVENT	0
#define OBJ_DEAD		1

#define	ANIM_NOEVENT	0
#define ANIM_END		1
#define ANIM_ACTION		2
#define ANIM_ACTEND		3

#define KEY_MAX		0xff

#define KEY_DOWN(k)		(CKeyMgr::GetInstance()->KeyDown(k))
#define KEY_UP(k)		(CKeyMgr::GetInstance()->KeyUp(k))
#define KEY_PRESS(k)	(CKeyMgr::GetInstance()->KeyPressing(k))

#define SINGLETON(t)	public:	static t* GetInstance()	{ if (!m_pInstance)	m_pInstance = new t; return m_pInstance; }\
						static void DestroyInstance()	{ if (m_pInstance) { delete m_pInstance;	m_pInstance = nullptr; } }\
						private: static t* m_pInstance;

#define DELTA			(CTimeMgr::GetInstance()->GetDeltaTime())


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

struct tagFinder
{
public:
	tagFinder(const TCHAR* _pString) : m_pString(_pString) {}

public:
	template<typename T>
	bool	operator()(T& _Pair)
	{
		return !lstrcmp(m_pString, _Pair.first);
	}

private:
	const TCHAR*	m_pString;
};

typedef struct tagFrame
{
	bool	bLoop;
	int		iMotion;
	int		iFirstFrame;
	int		iLastFrame;
	int		iActionStart;
	int		iActionEnd;
	float	fFrameRate;
	float	fTime;

	tagFrame() 
		: bLoop(true), iMotion(0), iFirstFrame(0), iLastFrame(0), fFrameRate(1.f / 24.f), fTime(0.f), 
		iActionStart(-1), iActionEnd(-1)
	{}
	
	tagFrame(int _iMotion, int _iFirstFrame, int _iLastFrame, 
		bool _bLoop = true, float _fFrameRate = 1.f / 24.f, float _fTime = 0.f)
		: bLoop(_bLoop), iMotion(_iMotion), iFirstFrame(_iFirstFrame), iLastFrame(_iLastFrame), 
		fFrameRate(_fFrameRate), fTime(0.f), iActionStart(-1), iActionEnd(-1)
	{}

	tagFrame(tagFrame& _rhs)
	{
		bLoop		 = _rhs.bLoop;
		iMotion		 = _rhs.iMotion;
		iFirstFrame	 = _rhs.iFirstFrame;
		iLastFrame	 = _rhs.iLastFrame;
		iActionStart = _rhs.iActionStart;
		iActionEnd	 = _rhs.iActionEnd;
		fFrameRate	 = _rhs.fFrameRate;
		fTime		 = _rhs.fTime;
	}

	~tagFrame() {}

}FRAME;

enum DIRECTION { DOWN, UP, LEFT, RIGHT, DIR_END };

enum SCENEID
{
	TITLE,
	FIELD,
	TOWN,
	DUNGEON,
	BOSSSTAGE,
	EDIT,
	SC_END
};

enum OBJTYPE
{
	PLAYER,
	WALL,
	SWITCH,
	MAPOBJ,
	ITEM,
	ENEMY,
	BOSS,
	PLAYERWEAPON,
	ENEMYWEAPON,
	PLAYERSHIELD,
	ENEMYSHIELD,
	PLAYERBULLET,
	ENEMYBULLET,
	MISC,
	OBJ_END
};

enum RENDERID
{
	RENDER_BACKGROUND,
	RENDER_GAMEOBJ,
	RENDER_MISC,
	RENDER_EFFECT,
	RENDER_UI,
	RENDER_END
};

enum CHANNELID
{
	SOUND_EFFECT,
	SOUND_BGM,
	MAXCHANNEL
};

extern HWND g_hWnd;
extern bool g_bDebugMode;