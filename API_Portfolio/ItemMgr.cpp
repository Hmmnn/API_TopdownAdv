#include "stdafx.h"
#include "ItemMgr.h"
#include "HeartItem.h"
#include "RupeeItem.h"
#include "EquipItem.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"

CItemMgr* CItemMgr::m_pInstance = nullptr;

CItemMgr::CItemMgr()
{
}

CItemMgr::~CItemMgr()
{
}

void CItemMgr::Initialize()
{
	vector<CObj*> vecHeart(10);
	for (CObj*& Obj : vecHeart)
	{
		Obj = CAbstractFactory<CHeartItem>::Create();
		CObjMgr::GetInstance()->AddObj(ITEM, Obj);
		Obj->SetActive(false);
	}
	m_mapItem.insert({ L"�����", vecHeart });

	vector<CObj*> vecRupee(10);
	for (CObj*& Obj : vecRupee)
	{
		Obj = CAbstractFactory<CRupeeItem>::Create();
		CObjMgr::GetInstance()->AddObj(ITEM, Obj);
		Obj->SetActive(false);
	}
	m_mapItem.insert({ L"����", vecRupee });

	CObj* pTempItem = CAbstractFactory<CSwordItem>::Create();
	m_mapItem[L"���̽��� ��"].push_back(pTempItem);
	CObjMgr::GetInstance()->AddObj(ITEM, pTempItem);
	pTempItem->SetActive(false);

	pTempItem = CAbstractFactory<CBowItem>::Create();
	m_mapItem[L"���� Ȱ"].push_back(pTempItem);
	CObjMgr::GetInstance()->AddObj(ITEM, pTempItem);
	pTempItem->SetActive(false);

	pTempItem = CAbstractFactory<CBoomrItem>::Create();
	m_mapItem[L"�θ޶�"].push_back(pTempItem);
	CObjMgr::GetInstance()->AddObj(ITEM, pTempItem);
	pTempItem->SetActive(false);

	pTempItem = CAbstractFactory<CShieldItem>::Create();
	m_mapItem[L"�ſ� ����"].push_back(pTempItem);
	CObjMgr::GetInstance()->AddObj(ITEM, pTempItem);
	pTempItem->SetActive(false);

	pTempItem = CAbstractFactory<CStaffItem>::Create();
	m_mapItem[L"���� ������"].push_back(pTempItem);
	CObjMgr::GetInstance()->AddObj(ITEM, pTempItem);
	pTempItem->SetActive(false);

}

void CItemMgr::Release()
{
}

void CItemMgr::SpawnItem(const TCHAR* _pKey, VEC2 _vPos)
{
	for (CObj*& pItem : m_mapItem[_pKey])
	{
		if (pItem->GetActive())
			continue;

		pItem->SetPos(_vPos);
		pItem->SetActive(true);

		return;
	}

}

void CItemMgr::SpawnRandomItem(VEC2 _vPos)
{
	int iRandom = rand() % 100;

	if (20 > iRandom)
	{
		return;
	}
	else if (60 > iRandom)
	{
		for (CObj*& pItem : m_mapItem[L"�����"])
		{
			if (pItem->GetActive())
				continue;

			pItem->SetPos(_vPos);
			pItem->SetActive(true);

			return;
		}

	}
	else
	{
		for (CObj*& pItem : m_mapItem[L"����"])
		{
			if (pItem->GetActive())
				continue;

			pItem->SetPos(_vPos);
			pItem->SetActive(true);

			return;
		}

	}
}

CObj* CItemMgr::GetItem(const TCHAR* _pKey)
{
	if(m_mapItem.count(_pKey) > 0)
		return m_mapItem[_pKey].back();

	return nullptr;
}
