#include "stdafx.h"
#include "Grid.h"
#include "Obj.h"

CGrid::CGrid() :
	m_iCellSize(64)
{
}

CGrid::~CGrid()
{
}

void CGrid::Initialize()
{
}

void CGrid::Release()
{
}

void CGrid::Add(CObj* _pObj)
{
	int		x = (int)(_pObj->GetPos().fX / m_iCellSize);
	int		y = (int)(_pObj->GetPos().fY / m_iCellSize);

	m_listCells[y][x].push_back(_pObj);

	_pObj->SetCellX(x);
	_pObj->SetCellY(y);
}

void CGrid::Move(CObj* _pObj)
{
	int		x = (int)(_pObj->GetPos().fX / m_iCellSize);
	int		y = (int)(_pObj->GetPos().fY / m_iCellSize);

	int		oldX = _pObj->GetCellX();
	int		oldY = _pObj->GetCellY();

	if (oldX != x || oldY != y)
	{
		auto iter = find(m_listCells[oldY][oldX].begin(), m_listCells[oldY][oldX].end(), _pObj);
		
		if(iter != m_listCells[oldY][oldX].end())
			iter = m_listCells[oldY][oldX].erase(iter);

		m_listCells[y][x].push_back(_pObj);
	}
}

CFieldGrid::CFieldGrid() :
	m_iFieldX(15), m_iFieldY(10)
{
}

CFieldGrid::~CFieldGrid()
{
}

void CFieldGrid::Initialize()
{
	m_listCells.resize(m_iFieldY);

	for (auto& iter : m_listCells)
	{
		iter.resize(m_iFieldX);
	}
}

void CFieldGrid::Release()
{
}
