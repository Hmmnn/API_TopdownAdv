#pragma once

#include "Obj.h"

class CCollider;

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

	// CObj를 List로 넣을 거고
	// List-List 충돌 검사
	// CObj 충돌했을 시 실행할 함수를 가상함수로 만들기(GameObj / StaticObj 구분)
	// 상대 Collider의 Owner를 넘겨주기?

	static void		CollisionObj(list<CObj*>* _pHitterList, list<CObj*>* _pHittedList);

	static bool		CheckCollision(CObj* _pHitter, CObj* _pHitted);
	
	static bool		CollisionRect(CCollider* _pHitter, CCollider* _pHitted);
	static bool		CollisionSphere(CCollider* _pHitter, CCollider* _pHitted);
};