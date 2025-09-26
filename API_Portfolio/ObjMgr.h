#pragma once

#include "Obj.h"

class CObjMgr
{
	//SINGLETON(CObjMgr)

private:
	CObjMgr();
	~CObjMgr();

public:
	void		AddObj(OBJTYPE _eObjID, CObj* _pObj);
	void		DeleteObj(OBJTYPE _eObjID);
	
	int			Update();
	void		LateUpdate();
	void		Render(HDC hDC);
	void		Release();

	void		ClearRenderList();
	void		ResizeObjList(OBJTYPE _eID, int _iSize);
	void		SetActive(OBJTYPE _eObjID, bool _bActive);
	
private:
	void		UpdateCollision();

public:
	CObj*			GetBack(OBJTYPE _eObjID);
	list<CObj*>*	GetList(OBJTYPE _eObjID);

	void			SetList(OBJTYPE _eObjID, list<CObj*>* _pList);

public:
	static CObjMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}

	static void		DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr* m_pInstance;

	list<CObj*>		m_ObjList[OBJ_END];
	list<CObj*>		m_RenderList[RENDER_END];
};