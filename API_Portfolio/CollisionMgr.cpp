#include "stdafx.h"
#include "CollisionMgr.h"
#include "GameObj.h"
#include "StaticObj.h"
#include "ScrollMgr.h"

CCollisionMgr::CCollisionMgr()
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionObj(list<CObj*>* _pDstList, list<CObj*>* _pSrcList)
{
	if (_pDstList->empty() || _pSrcList->empty())
		return;

	for (auto& Dst : *_pDstList)
	{
		if (!Dst->GetActive() /* || CScrollMgr::GetInstance()->IsCulling(Dst->GetPos(), Dst->GetSize())*/)
			continue;

		for (auto& Src : *_pSrcList)
		{
			if (!Src->GetActive() /* || CScrollMgr::GetInstance()->IsCulling(Src->GetPos(), Src->GetSize())*/)
				continue;

			if (CheckCollision(Dst, Src))
			{
				Dst->OnCollision(Src);
				Src->OnCollision(Dst);
			}
		}
	}
}

bool CCollisionMgr::CheckCollision(CObj* _pHitter, CObj* _pHitted)
{
	switch (_pHitter->GetCollider()->GetShape())
	{
	case CCollider::SQUARE:
		return CollisionRect(_pHitter->GetCollider(), _pHitted->GetCollider());

	case CCollider::SPHERE:
		return CollisionSphere(_pHitter->GetCollider(), _pHitted->GetCollider());
	}

	return false;
}

bool CCollisionMgr::CollisionRect(CCollider* _pHitter, CCollider* _pHitted)
{
	if (!_pHitter->GetActive() || !_pHitted->GetActive())
		return false;

	float fR = (float)min(_pHitter->GetRect().right, _pHitted->GetRect().right);
	float fL = (float)max(_pHitter->GetRect().left, _pHitted->GetRect().left);
	float fB = (float)min(_pHitter->GetRect().bottom, _pHitted->GetRect().bottom);
	float fT = (float)max(_pHitter->GetRect().top, _pHitted->GetRect().top);

	if (0 <= fR - fL && 0 <= fB - fT)
	{
		RECT rc = { (LONG)fL, (LONG)fT, (LONG)fR, (LONG)fB };

		_pHitter->SetOverlap(rc);
		_pHitted->SetOverlap(rc);

		_pHitter->DrawCollided(true);
		_pHitted->DrawCollided(true);

		return true;
	}

	_pHitter->DrawCollided(false);
	_pHitted->DrawCollided(false);

	return false;
}

bool CCollisionMgr::CollisionSphere(CCollider* _pHitter, CCollider* _pHitted)
{
	if (!_pHitter->GetActive() || !_pHitted->GetActive())
		return false;

	VEC2 Dst = { _pHitter->GetPos().fX, _pHitter->GetPos().fY };
	VEC2 Src = { _pHitted->GetPos().fX, _pHitted->GetPos().fY };

	if ((_pHitter->GetSize().fX + _pHitted->GetSize().fX) * 0.5f >= Dst.Distance(Src))
	{
		_pHitter->DrawCollided(true);
		_pHitted->DrawCollided(true);

		return true;
	}

	_pHitter->DrawCollided(false);
	_pHitted->DrawCollided(false);

	return false;
}
