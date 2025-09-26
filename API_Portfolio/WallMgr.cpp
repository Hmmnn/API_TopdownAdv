#include "stdafx.h"
#include "WallMgr.h"
#include "Wall.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

CWallMgr* CWallMgr::m_pInstance = nullptr;

CWallMgr::CWallMgr()
{
}

CWallMgr::~CWallMgr()
{
	Release();
}

void CWallMgr::Initialize()
{
}

void CWallMgr::Release()
{
	for (size_t i = 0; i < SC_END; ++i)
	{
		for_each(m_listWall[i].begin(), m_listWall[i].end(), Safe_Delete<CObj*>);
		m_listWall[i].clear();
	}
	m_listWall->clear();
}

void CWallMgr::InitializeField()
{
	CObjMgr::GetInstance()->SetList(WALL, &m_listWall[FIELD]);
}

void CWallMgr::InitializeTown()
{
	CObjMgr::GetInstance()->SetList(WALL, &m_listWall[TOWN]);
}

void CWallMgr::InitializeDungeon()
{
	CObjMgr::GetInstance()->SetList(WALL, &m_listWall[DUNGEON]);
}

void CWallMgr::InitializeBossStage()
{
	CObjMgr::GetInstance()->SetList(WALL, &m_listWall[BOSSSTAGE]);
}

void CWallMgr::AddTestWall(SCENEID _eID, CObj* _pWall)
{
	m_listWall[_eID].push_back(_pWall);
	CObjMgr::GetInstance()->AddObj(WALL, _pWall);
}

void CWallMgr::DeleteTestWall(SCENEID _eID)
{
	Safe_Delete(m_listWall[_eID].back());
	m_listWall[_eID].pop_back();

	// 에반데
	CObjMgr::GetInstance()->SetList(WALL, &m_listWall[_eID]);
}

void CWallMgr::AddWall(SCENEID _eID, CObj* _pWall)
{
	m_listWall[_eID].push_back(_pWall);
}

void CWallMgr::SaveWall(SCENEID _eID)
{
	TCHAR   szBuf[64] = L"";
	swprintf_s(szBuf, L"../Data/Walls%d.data", (int)_eID);

	//CDataMgr::GetInstance()->OpenFile(szBuf, GENERIC_WRITE);
	//CDataMgr::GetInstance()->SaveWall(_eID, &m_listWall[_eID]);
	//CDataMgr::GetInstance()->CloseFile();

	HANDLE	hFile = CreateFile(szBuf, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Open File"), L"Fail", MB_OKCANCEL);
		return;
	}

	DWORD	dwByte(0);

	for (auto& iter : m_listWall[_eID])
	{
		WriteFile(hFile, &_eID, sizeof(SCENEID), &dwByte, NULL);
		WriteFile(hFile, &iter->GetPos(), sizeof(VEC2), &dwByte, NULL);
		WriteFile(hFile, &iter->GetSize(), sizeof(VEC2), &dwByte, NULL);
	}

	CloseHandle(hFile);
}

void CWallMgr::LoadWall(SCENEID _eID)
{
	TCHAR   szBuf[64] = L"";
	swprintf_s(szBuf, L"../Data/Walls%d.data", (int)_eID);

	//CDataMgr::GetInstance()->OpenFile(szBuf, GENERIC_READ);
	//CDataMgr::GetInstance()->LoadWall();
	//CDataMgr::GetInstance()->CloseFile();

	HANDLE	hFile = CreateFile(szBuf, GENERIC_READ, NULL, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, _T("Open File"), L"Fail", MB_OKCANCEL);
		return;
	}

	CObj*	pTempWall(nullptr);
	int		iIDBuffer;
	VEC2	vPosBuffer, vSizeBuffer;

	DWORD	dwByte(0);

	while (true)
	{
		ReadFile(hFile, &iIDBuffer, sizeof(SCENEID), &dwByte, NULL);
		ReadFile(hFile, &vPosBuffer, sizeof(VEC2), &dwByte, NULL);
		ReadFile(hFile, &vSizeBuffer, sizeof(VEC2), &dwByte, NULL);

		if (0 == dwByte)
			break;

		pTempWall = CAbstractFactory<CWall>::Create(vPosBuffer.fX, vPosBuffer.fY, vSizeBuffer.fX, vSizeBuffer.fY);
		
		m_listWall[(SCENEID)iIDBuffer].push_back(pTempWall);
	}

	MessageBox(g_hWnd, _T("Load 성공"), L"성공", MB_OKCANCEL);

	CloseHandle(hFile);
}
