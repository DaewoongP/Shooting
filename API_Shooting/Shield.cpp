#include "stdafx.h"
#include "Shield.h"
#include "ObjMgr.h"

CShield::CShield() : m_fAngle(0), m_fDistance(0)
{
}


CShield::~CShield()
{
	Release();
}

void CShield::Initialize()
{
	m_iDmg = 2;
	m_eOBJID = SHIELD;
	m_iGardCount = 1;
	m_fDistance = 100.f;
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	m_tInfo = INFO{ 100.f,100.f,30.f,10.f };
	m_fSpeed = 10.f;

}

int CShield::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fAngle += m_fSpeed;

	if (m_pTarget != nullptr)
	{
		m_ePos.x = m_pTarget->Get_Info().fX;
		m_ePos.y = m_pTarget->Get_Info().fY;
	}
	else
	{
		m_ePos.x += m_fSpeed;
	}

	m_tInfo.fX = m_ePos.x + (cosf(m_fAngle*RADIAN)*m_fDistance);
	m_tInfo.fY = m_ePos.y + (sinf(m_fAngle*RADIAN)*m_fDistance);

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CShield::Late_Update()
{
	if (-100 > m_tRect.left || WINCX + 100 < m_tRect.right ||
		-100 > m_tRect.top || WINCY + 100 < m_tRect.bottom)
		m_bDead = OBJ_DEAD;
}

void CShield::Render(HDC hdc)
{
	Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void CShield::Release()
{

}

void CShield::CollisionEvent(CObj * _obj)
{
	if (_obj->Get_ObjID() == MONSTER || _obj->Get_ObjID() == ENEMYBULLET)
	{
		m_iGardCount -= 1;
		if (m_iGardCount <= 0)
			Set_Dead();
	}
}
