#include "stdafx.h"
#include "NPC.h"
#include "GameObj.h"
#include "RectCollider.h"
#include "KeyMgr.h"

CNPC::CNPC() :
    m_szKey(nullptr)
{
}

CNPC::CNPC(HDC _hImage, const TCHAR* _szKey) :
    m_szKey(_szKey)
{
    m_hMemDC = _hImage;
}

CNPC::~CNPC()
{
    Release();
}

void CNPC::Initialize()
{
    m_pCollider = new CRectCollider(this, { 100, 100 });
    m_pCollider->SetOffset({ 0, 20 });
}

int CNPC::Update()
{
    if (ON == m_eState)
    {
        //if(KEY_DOWN('C'))
            // 스크립트 출력
    }

    return SCENE_NOEVENT;
}

void CNPC::Release()
{
}

void CNPC::OnCollision(CObj* _pOther)
{
    if (PLAYER == _pOther->GetType())
    {
        RECT rc = m_pCollider->GetOverlap();

        if (abs(rc.right - rc.left) > abs(rc.bottom - rc.top)
            && m_vPos.fY < _pOther->GetPos().fY
            && UP == static_cast<CGameObj*>(_pOther)->GetDir())
        {
            m_eState = ON;
        }
        else
            m_eState = OFF;
    }
}
