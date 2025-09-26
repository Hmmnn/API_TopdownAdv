#pragma once

#include "Item.h"

// ������ / ��ü�� ������ �ٸ� Ŭ�������� ��û�� ������ �������� �������ִ� �Ŵ���
// �׷� Ű - ������ �̷��� ���� �־�߰ڳ� map���� ����
// �����۵� Ŭ������ ���� �ľ߰ڴ�
// �������� ��� ������ �Ŵ����� ���� �ֵ��� �����
// �÷��̾�� �κ��丮�� ������ �Ŵ����� �߰��� ���� ��ȣ�ۿ��ϵ���
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

	// ���ڸ� ���� �κ��� �ٷ� ���� �Լ��� �����
	// �κ��� �����ΰ�??

	CObj*		GetItem(const TCHAR* _pKey);

private:
	map<const TCHAR*, vector<CObj*>> m_mapItem;
};