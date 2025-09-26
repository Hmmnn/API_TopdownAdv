#pragma once

#include "Define.h"

class CObj;

// Grid�� �������̽��� �ΰ� �� ���� �׸��带 ������ �ϳ�?
// �����̳� ũ�⸸ �ٸ��� �Լ��� ���� �Ȱ���...�������̽��� �ƴϴ�
class CGrid
{
public:
	CGrid();
	~CGrid();

	virtual void		Initialize();
	virtual void		Release();

	// Obj�� �ڱ� ���� ���� �ְ� Grid�� ���ؼ� Cell�� ������Ʈ �޴� �������?
	// Obj �Ŵ�����?? ������Ʈ �����ϰ� �������� �ϴ� �� Obj�Ŵ����ε�
	virtual void		Add(CObj* _pObj);
	virtual void		Move(CObj* _pObj);

protected:
	const int		m_iCellSize;

	using CellList = list<CObj*>;
	vector<vector<CellList>> m_listCells;
};

class CFieldGrid : public CGrid
{
public:
	CFieldGrid();
	~CFieldGrid();

	virtual void		Initialize() override;
	virtual void		Release() override;

private:
	const int		m_iFieldX;
	const int		m_iFieldY;
};