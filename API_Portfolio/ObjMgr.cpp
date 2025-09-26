#include "stdafx.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"
#include "Inventory.h"
#include "SceneMgr.h"
#include "Collider.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::AddObj(OBJTYPE _eObjID, CObj* _pObj)
{
	if (!_pObj)
		return;

	//m_ObjList[_eObjID].push_back(_pObj);

	bool	bCheck = false;

	for (auto& iter : m_ObjList[_eObjID])
	{
		if (!iter)
		{
			iter = _pObj;
			return;
		}
	}

	m_ObjList[_eObjID].push_back(_pObj);
}

void CObjMgr::DeleteObj(OBJTYPE _eObjID)
{
	//if (m_ObjList[_eObjID].empty())
	//	return;
	//
	//for_each(m_ObjList[_eObjID].begin(), m_ObjList[_eObjID].end(), Safe_Delete<CObj*>);
	//m_ObjList[_eObjID].clear();
	//
	//if (m_ObjList[_eObjID].empty())
	//	return;
	//
	//for (auto iter = m_ObjList[_eObjID].begin();
	//	iter != m_ObjList[_eObjID].end(); ++iter)
	//{
	//	Safe_Delete<CObj*>(*iter);
	//}
	//m_ObjList[_eObjID].clear();

	for (auto& iter : m_ObjList[_eObjID])
		Safe_Delete(iter);

	m_ObjList[_eObjID].clear();
}

int CObjMgr::Update()
{
	if (CInventory::GetInstance()->GetActive())
		return SCENE_NOEVENT;

	//for (auto& List : m_ObjList)
	//{
	//	if (List.empty())
	//		continue;
	//
	//	for (auto iter = List.begin();
	//		iter != List.end(); ++iter)
	//	{
	//		//if (CScrollMgr::GetInstance()->IsCulling((*iter)->GetPos(), (*iter)->GetSize()))
	//		//	continue;
	//
	//		int iResult = (*iter)->Update();
	//
	//		if (SCENE_NOEVENT != iResult)
	//			return iResult;
	//	}
	//}

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		if (WALL == i)
			continue;

		if (m_ObjList[i].empty())
			continue;

		for (auto& iter : m_ObjList[i])
		{
			int iResult = iter->Update();

			if (SCENE_NOEVENT != iResult)
				return iResult;
		}
	}

	return SCENE_NOEVENT;
}

void CObjMgr::LateUpdate()
{
	if (CInventory::GetInstance()->GetActive())
		return;

	for (auto& List : m_ObjList)
	{
		if (List.empty())
			continue;

		for (auto& iter = List.begin();
			iter != List.end(); ++iter)
		{
			//if (CScrollMgr::GetInstance()->IsCulling((*iter)->GetPos(), (*iter)->GetSize()))
			//	continue;

			(*iter)->LateUpdate();

			RENDERID eID = (*iter)->GetRenderID();

			m_RenderList[eID].push_back(*iter);
		}
	}

	UpdateCollision();
}

void CObjMgr::Render(HDC hDC)
{
	if (CInventory::GetInstance()->GetActive())
		return;

	//for (auto& List : m_RenderList)
	//{
	//	if (List.empty())
	//		continue;
	//
	//	List.sort([](CObj* _pLeft, CObj* _pRight) {
	//		
	//		return (_pLeft->GetCollider()->GetBottom() < _pRight->GetCollider()->GetBottom());
	//		});
	//
	//	for (auto iter = List.begin();
	//		iter != List.end(); ++iter)
	//	{
	//		if (CScrollMgr::GetInstance()->IsCulling((*iter)->GetPos(), (*iter)->GetSize()))
	//			continue;
	//
	//		(*iter)->Render(hDC);
	//	}
	//
	//	List.clear();
	//}

	for (size_t i = 0; i < RENDER_END; ++i)
	{
		if (m_RenderList[i].empty())
			continue;

		if (i != RENDER_MISC)
		{
			m_RenderList[i].sort([](CObj* _pLeft, CObj* _pRight) {

				if (!_pLeft->GetCollider() || !_pRight->GetCollider())
					return (_pLeft->GetRect().bottom < _pRight->GetRect().bottom);

				return (_pLeft->GetCollider()->GetBottom() < _pRight->GetCollider()->GetBottom());
			});
		}

		for (auto iter = m_RenderList[i].begin();
			iter != m_RenderList[i].end(); ++iter)
		{
			if (CScrollMgr::GetInstance()->IsCulling((*iter)->GetPos(), (*iter)->GetSize()))
				continue;

			(*iter)->Render(hDC);
		}

		m_RenderList[i].clear();
	}

	m_RenderList->clear();
}

void CObjMgr::Release()
{
	//for (auto& List : m_ObjList)
	//{
	//	if (List.empty())
	//		continue;
	//
	//	for_each(List.begin(), List.end(), Safe_Delete<CObj*>);
	//	List.clear();
	//}

	for (size_t i = 0; i < OBJ_END; ++i)
	{
		if (WALL == i)
			continue;

		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}

	/*for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
			iter != m_ObjList[i].end(); ++iter)
		{
			if (*iter)
			{
				delete* iter;
				*iter = nullptr;
			}
		}
		m_ObjList[i].clear();
	}*/

	m_ObjList->clear();
}

void CObjMgr::UpdateCollision()
{
	CCollisionMgr::CollisionObj(&m_ObjList[WALL], &m_ObjList[PLAYER]);
	CCollisionMgr::CollisionObj(&m_ObjList[MAPOBJ], &m_ObjList[PLAYER]);
	CCollisionMgr::CollisionObj(&m_ObjList[MAPOBJ], &m_ObjList[ENEMYBULLET]);
	CCollisionMgr::CollisionObj(&m_ObjList[PLAYER], &m_ObjList[ITEM]);
	CCollisionMgr::CollisionObj(&m_ObjList[PLAYER], &m_ObjList[ENEMYWEAPON]);
	CCollisionMgr::CollisionObj(&m_ObjList[PLAYER], &m_ObjList[ENEMYBULLET]);

	SCENEID		eCurSCID = CSceneMgr::GetInstance()->GetCurSceneID();

	if (FIELD == eCurSCID)
	{
		CCollisionMgr::CollisionObj(&m_ObjList[WALL], &m_ObjList[ENEMY]);
		CCollisionMgr::CollisionObj(&m_ObjList[PLAYERBULLET], &m_ObjList[ENEMY]);
		CCollisionMgr::CollisionObj(&m_ObjList[PLAYERWEAPON], &m_ObjList[ENEMY]);
		
	}
	else if (DUNGEON == eCurSCID)
	{
		CCollisionMgr::CollisionObj(&m_ObjList[WALL], &m_ObjList[ENEMY]);
		CCollisionMgr::CollisionObj(&m_ObjList[PLAYERBULLET], &m_ObjList[ENEMY]);
		CCollisionMgr::CollisionObj(&m_ObjList[PLAYERWEAPON], &m_ObjList[ENEMY]);
		CCollisionMgr::CollisionObj(&m_ObjList[ENEMYBULLET], &m_ObjList[MAPOBJ]);
	}
	else if (BOSSSTAGE == eCurSCID)
	{
		CCollisionMgr::CollisionObj(&m_ObjList[WALL], &m_ObjList[BOSS]);
		CCollisionMgr::CollisionObj(&m_ObjList[PLAYER], &m_ObjList[BOSS]);
		CCollisionMgr::CollisionObj(&m_ObjList[BOSS], &m_ObjList[MAPOBJ]);
		CCollisionMgr::CollisionObj(&m_ObjList[PLAYERBULLET], &m_ObjList[BOSS]);
		CCollisionMgr::CollisionObj(&m_ObjList[PLAYERWEAPON], &m_ObjList[BOSS]);
		CCollisionMgr::CollisionObj(&m_ObjList[PLAYERBULLET], &m_ObjList[ENEMYBULLET]);
		CCollisionMgr::CollisionObj(&m_ObjList[PLAYERWEAPON], &m_ObjList[ENEMYBULLET]);
		CCollisionMgr::CollisionObj(&m_ObjList[PLAYERBULLET], &m_ObjList[ENEMYSHIELD]);
		CCollisionMgr::CollisionObj(&m_ObjList[PLAYERWEAPON], &m_ObjList[ENEMYSHIELD]);
	}
}

void CObjMgr::ClearRenderList()
{
	m_RenderList->clear();
}

void CObjMgr::ResizeObjList(OBJTYPE _eID, int _iSize)
{
	//m_ObjList[_eID].clear();

	m_ObjList[_eID].resize(_iSize);
}

void CObjMgr::SetActive(OBJTYPE _eObjID, bool _bActive)
{
	for (auto& iter : m_ObjList[_eObjID])
	{
		iter->SetActive(_bActive);
	}
}

CObj* CObjMgr::GetBack(OBJTYPE _eObjID)
{
	if (m_ObjList[_eObjID].empty())
		return nullptr;

	return m_ObjList[_eObjID].back();
}

list<CObj*>* CObjMgr::GetList(OBJTYPE _eObjID)
{
	return &(m_ObjList[_eObjID]);
}

void CObjMgr::SetList(OBJTYPE _eObjID, list<CObj*>* _pList)
{
	// 복사해 온 게 아니라 포인터를 넘겨준 거 아닌가?? 배열이 아니라 list라서 다른가?
	m_ObjList[_eObjID] = *_pList;
}
