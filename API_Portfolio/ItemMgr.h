#pragma once

#include "Item.h"

// 데이터 / 객체를 가지고 다른 클래스에서 요청을 받으면 아이템을 스폰해주는 매니저
// 그럼 키 - 아이템 이렇게 갖고 있어야겠네 map으로 쓰고
// 아이템도 클래스를 각각 파야겠다
// 아이템은 모두 아이템 매니저가 갖고 있도록 만들기
// 플레이어와 인벤토리가 아이템 매니저를 중간에 끼고 상호작용하도록
class CItemMgr
{
	SINGLETON(CItemMgr)

public:

private:
	CItemMgr();
	~CItemMgr();

public:
	void		Initialize();
	void		Release();
	
	void		SpawnItem(const TCHAR* _pKey, VEC2 _vPos);
	void		SpawnRandomItem(VEC2 _vPos);

	// 상자를 열면 인벤에 바로 들어가는 함수도 만들기
	// 인벤이 먼저인가??

	CObj*		GetItem(const TCHAR* _pKey);

private:
	map<const TCHAR*, vector<CObj*>> m_mapItem;
};