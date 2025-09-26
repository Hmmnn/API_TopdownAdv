#include "stdafx.h"
#include "LaserEye.h"
#include "TimeMgr.h"
#include "ScrollMgr.h"
#include "RectCollider.h"
#include "BmpMgr.h"
#include "LaserBullet.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CLaserEye::CLaserEye() : 
    m_pOwner(nullptr), m_eState(IDLE), m_fAngle(0), m_fDist(0), m_fAngleSpeed(0),
    m_tInitColSize(), m_tInitColOffset(), m_pLaserBullet(nullptr),
    m_fDeadTime(0), m_fRespawnTime(0)
{
}

CLaserEye::~CLaserEye()
{
    Release();
}

void CLaserEye::Initialize()
{
    m_eObjType = ENEMYBULLET;

    m_vSize = { 94, 42 };
    m_fAngleSpeed = 200.f;

    m_fDist = 150.f;

    m_iMaxHp = 2;
    m_iHp = m_iMaxHp;

    m_iAtk = 1;

    m_fRespawnTime = 2.f;

    m_tInitColSize = { 25, 25 };
    m_pCollider = new CRectCollider(this, m_tInitColSize);

    m_tInitColOffset = { 0, -10 };
    m_pCollider->SetOffset(m_tInitColOffset);

    m_pLaserBullet = CAbstractFactory<CLaserBullet>::Create();
    CObjMgr::GetInstance()->AddObj(ENEMYBULLET, m_pLaserBullet);

    InitializeMotion();
}

int CLaserEye::Update()
{
    if (m_bDead)
    {
        m_bActive = false;

        m_fDeadTime += DELTA;

        if (m_fRespawnTime < m_fDeadTime)
        {
            m_fDeadTime = 0;

            m_bDead = false;
            m_bActive = true;
        }
    }

    if (!m_bActive)
    {
        m_pLaserBullet->SetActive(false);

        return SCENE_NOEVENT;
    }

    if (IDLE == m_eState)
        MoveAround();
    else if (SHOOT == m_eState)
        ShootLaser();

    return CGameObj::Update();
}

void CLaserEye::LateUpdate()
{
}

void CLaserEye::Render(HDC hDC)
{
    if (!m_bActive)
        return;

    int		iScrollX = (int)CScrollMgr::GetInstance()->GetScrollX();
    int		iScrollY = (int)CScrollMgr::GetInstance()->GetScrollY();

    //Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
    m_pCollider->Render(hDC);

    m_vecMotion[m_eDir]->Render(hDC, iScrollX, iScrollY);
}

void CLaserEye::Release()
{
}

void CLaserEye::TakeDamage(int _iDamage)
{
    m_iHp -= _iDamage;

    if (0 >= m_iHp)
    {
        m_bDead = true;
    }
}

void CLaserEye::OnCollision(CObj* _pOther)
{
    if (PLAYERWEAPON == _pOther->GetType())
    {
        TakeDamage(1);
    }
}

void CLaserEye::CollisionGameObj()
{
    // TakeDamage È£Ãâ
}

void CLaserEye::MoveAround()
{
    //m_pCollider->SetSize(m_tInitColSize);
    //m_pCollider->SetOffset(m_tInitColOffset);

    static_cast<CLaserBullet*>(m_pLaserBullet)->Reset();
               
    m_fAngle += m_fAngleSpeed * DELTA;

    if (360.f < m_fAngle)
        m_fAngle -= 360.f;

    float fRadian = m_fAngle * PI / 180.f;

    m_vPos = m_pOwner->GetPos() + VEC2{ 1, acos(fRadian) } * m_fDist;

    m_vPos.fX = m_pOwner->GetPos().fX + m_fDist * cos(fRadian);
    m_vPos.fY = m_pOwner->GetPos().fY - m_fDist * sin(fRadian);
}

void CLaserEye::ShootLaser()
{
    if (!m_bActive)
        return;

    m_vVelocity = { 0, 0 }; 

    static_cast<CLaserBullet*>(m_pLaserBullet)->Shooted(m_vPos);
    
    //VEC2 tTempSize = m_pCollider->GetSize();
    //float fTempCY = tTempSize.fY + DELTA * 500.f;
    //m_pCollider->SetSize(VEC2(tTempSize.fX, fTempCY));
    //m_pCollider->SetOffset(VEC2(m_tInitColOffset.fX, m_tInitColOffset.fY + fTempCY * 0.5f));
}

void CLaserEye::InitializeMotion()
{
    m_vecMotion.resize(2);

    m_vecMotion[0] = new CAnimImage(CBmpMgr::GetInstance()->FindBmp(L"LASEREYE"));
    m_vecMotion[0]->SetPos(&m_vPos);
    m_vecMotion[0]->SetSize(m_vSize);
    m_vecMotion[0]->SetRect(&m_tRect);
    m_vecMotion[0]->ResizeFrameVec(2);
    m_vecMotion[0]->SetFrame(0, 0, 0, true);
    m_vecMotion[0]->SetFrame(1, 0, 3, false);
}
