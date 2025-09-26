#include "stdafx.h"
#include "ButtonMgr.h"
#include "MyButton.h"
#include "Wall.h"

#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "WallMgr.h"
#include "AbstractFactory.h"

CButtonMgr::CButtonMgr() :
	m_eEditingMap(SC_END),
	m_bLeftSelected(false), m_bRight(false),
	vLeftTop(), vRightBottom(),
	bComplete(false)
{
}

CButtonMgr::~CButtonMgr()
{
	Release();
}

void CButtonMgr::Initialize()
{
	EditField();
}

void CButtonMgr::Update()
{
	if (KEY_DOWN('1'))
	{
		m_eEditingMap = FIELD;
		EditField();
	}
	else if (KEY_DOWN('2'))
	{
		m_eEditingMap = TOWN;
		EditTown();
	}
	else if (KEY_DOWN('3'))
	{
		m_eEditingMap = DUNGEON;
		EditDungeon();
	}
	else if (KEY_DOWN('4'))
	{
		m_eEditingMap = BOSSSTAGE;
		EditBossStage();
	}

	if(KEY_DOWN(VK_F1))
		CWallMgr::GetInstance()->SaveWall(m_eEditingMap);

	if (KEY_DOWN(VK_BACK))
		CWallMgr::GetInstance()->DeleteTestWall(m_eEditingMap);

	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		for (size_t j = 0; j < m_vecButton[i].size(); ++j)
		{
			m_vecButton[i][j]->Update();
		}
	}
}

void CButtonMgr::LateUpdate()
{
	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		for (size_t j = 0; j < m_vecButton[i].size(); ++j)
		{
			m_vecButton[i][j]->LateUpdate();

			if (m_vecButton[i][j]->GetSelected() && !m_vecButton[i][j]->GetChecked())
			{
				if (m_bLeftSelected)
				{
					vRightBottom = { 
						(float)m_vecButton[i][j]->GetRect().right, 
						(float)m_vecButton[i][j]->GetRect().bottom 
					};

					m_bLeftSelected = false;
					bComplete = true;

					m_vecButton[i][j]->SetSelected(false);
					m_vecButton[i][j]->SetChecked(true);

					break;
				}
				else
				{
					vLeftTop = { 
						(float)m_vecButton[i][j]->GetRect().left,
						(float)m_vecButton[i][j]->GetRect().top
					};

					m_bLeftSelected = true;

					m_vecButton[i][j]->SetSelected(false);
					m_vecButton[i][j]->SetChecked(true);

				}
			}
		}

		if (bComplete)
			break;
	}

	if (bComplete)
	{
		float fX = (vLeftTop.fX + vRightBottom.fX) * 0.5f;
		float fY = (vLeftTop.fY + vRightBottom.fY) * 0.5f;
		float fCX = fabs(vRightBottom.fX - vLeftTop.fX);
		float fCY = fabs(vRightBottom.fY - vLeftTop.fY);

		CObj* pTempWall = CAbstractFactory<CWall>::Create(fX, fY, fCX, fCY);

		CWallMgr::GetInstance()->AddTestWall(m_eEditingMap, pTempWall);

		bComplete = false;
		m_bLeftSelected = false;
	}

}

void CButtonMgr::Render(HDC hDC)
{
	HDC hMemDC = NULL; //= CBmpMgr::GetInstance()->FindBmp(L"FIELD");

	int xy[2] = { 0, 0 };

	if (FIELD == m_eEditingMap)
	{
		hMemDC = CBmpMgr::GetInstance()->FindBmp(L"FIELD");
		xy[0] = 3024;
		xy[1] = 2064;
	}
	else if (TOWN == m_eEditingMap)
	{
		hMemDC = CBmpMgr::GetInstance()->FindBmp(L"TOWN");
		xy[0] = 3024;
		xy[1] = 2880;
	}
	else if(DUNGEON == m_eEditingMap)
	{
		hMemDC = CBmpMgr::GetInstance()->FindBmp(L"DUNGEON");
		xy[0] = 1776;
		xy[1] = 5232;
	}
	else if(BOSSSTAGE == m_eEditingMap)
	{
		hMemDC = CBmpMgr::GetInstance()->FindBmp(L"BOSSSTAGE");
		xy[0] = 1008;
		xy[1] = 768;
	}

	CScrollMgr::GetInstance()->SetMapSize({ (float)xy[0], (float)xy[1] });

	int		iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
	int		iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

	BitBlt(hDC,
		iScrollX,
		iScrollY,
		xy[0], xy[1],
		hMemDC, 0, 0, SRCCOPY);

	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		for (size_t j = 0; j < m_vecButton[i].size(); ++j)
		{
			m_vecButton[i][j]->Render(hDC);
		}
	}

}

void CButtonMgr::Release()
{
	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		for (size_t j = 0; j < m_vecButton[i].size(); ++j)
		{
			Safe_Delete<CMyButton*>(m_vecButton[i][j]);
		}
		m_vecButton[i].clear();
	}
	m_vecButton.clear();
}

void CButtonMgr::EditField()
{		
	if (SC_END != m_eEditingMap)
		Release();

	m_vecButton.resize(43);

	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		m_vecButton[i].resize(63);

		for (size_t j = 0; j < m_vecButton[i].size(); ++j)
		{
			m_vecButton[i][j] = new CMyButton;
			m_vecButton[i][j]->Initialize();
			m_vecButton[i][j]->SetPos((float)(24 + j * 48), (float)(24 + i * 48));
		}
	}

	m_eEditingMap = FIELD;
}

void CButtonMgr::EditTown()
{
	if (SC_END != m_eEditingMap)
		Release();

	m_vecButton.resize(60);

	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		m_vecButton[i].resize(63);

		for (size_t j = 0; j < m_vecButton[i].size(); ++j)
		{
			m_vecButton[i][j] = new CMyButton;
			m_vecButton[i][j]->Initialize();
			m_vecButton[i][j]->SetPos((float)(24 + j * 48), (float)(24 + i * 48));
		}
	}

	m_eEditingMap = TOWN;
}

void CButtonMgr::EditDungeon()
{
	if (SC_END != m_eEditingMap)
		Release();

	m_vecButton.resize(109);

	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		m_vecButton[i].resize(37);

		for (size_t j = 0; j < m_vecButton[i].size(); ++j)
		{
			m_vecButton[i][j] = new CMyButton;
			m_vecButton[i][j]->Initialize();
			m_vecButton[i][j]->SetPos((float)(24 + j * 48), (float)(24 + i * 48));
		}
	}

	m_eEditingMap = DUNGEON;
}

void CButtonMgr::EditBossStage()
{
	if (SC_END != m_eEditingMap)
		Release();

	m_vecButton.resize(16);

	for (size_t i = 0; i < m_vecButton.size(); ++i)
	{
		m_vecButton[i].resize(21);

		for (size_t j = 0; j < m_vecButton[i].size(); ++j)
		{
			m_vecButton[i][j] = new CMyButton;
			m_vecButton[i][j]->Initialize();
			m_vecButton[i][j]->SetPos((float)(24 + j * 48), (float)(24 + i * 48));
		}
	}

	m_eEditingMap = BOSSSTAGE;
}
