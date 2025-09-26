#pragma once

#include "Obj.h"

class CCollider;

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

	// CObj�� List�� ���� �Ű�
	// List-List �浹 �˻�
	// CObj �浹���� �� ������ �Լ��� �����Լ��� �����(GameObj / StaticObj ����)
	// ��� Collider�� Owner�� �Ѱ��ֱ�?

	static void		CollisionObj(list<CObj*>* _pHitterList, list<CObj*>* _pHittedList);

	static bool		CheckCollision(CObj* _pHitter, CObj* _pHitted);
	
	static bool		CollisionRect(CCollider* _pHitter, CCollider* _pHitted);
	static bool		CollisionSphere(CCollider* _pHitter, CCollider* _pHitted);
};