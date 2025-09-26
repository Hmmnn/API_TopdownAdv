#pragma once

#include "Define.h"

class CObj;

// Grid를 인터페이스로 두고 씬 별로 그리드를 만들어야 하나?
// 컨테이너 크기만 다르고 함수는 완전 똑같음...인터페이스는 아니다
class CGrid
{
public:
	CGrid();
	~CGrid();

	virtual void		Initialize();
	virtual void		Release();

	// Obj가 자기 셀을 갖고 있고 Grid를 통해서 Cell을 업데이트 받는 방식으로?
	// Obj 매니저는?? 업데이트 렌더하고 해제까지 하는 건 Obj매니저인데
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