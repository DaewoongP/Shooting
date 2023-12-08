#include "stdafx.h"
#include "FallingStar.h"
#include "ObjMgr.h"
#include "Monster.h"


CFallingStar::CFallingStar()
{
}


CFallingStar::~CFallingStar()
{

}

void CFallingStar::Initialize()
{

	m_tInfo.fX = (float)(rand() % 1500 + 300);
	m_tInfo.fY = -100.0f;
	m_fSpeed = 2.0f;
	m_tInfo.fCY = m_tInfo.fCX = (float)(rand() % 10 * 5);

}

int CFallingStar::Update()
{
	m_fSpeed = static_cast<CMonster*>(CObjMgr::Get_Instance()->Get_ObjList(MONSTER)->front())->Get_CurrentStage() / 2 + 1;

	//이동 
	m_tInfo.fX += m_fDirX * m_fSpeed;
	m_tInfo.fY += m_fDirY * m_fSpeed;

	//회전 각
	m_iRotation += 2;

	if (700.0f <= m_tInfo.fY)
	{
		m_tInfo.fX += 1400.0f;
		m_tInfo.fY = -100.0f;
	}

	return 0;
}

void CFallingStar::Late_Update()
{
}

void CFallingStar::Render(HDC hdc)
{
	int iStage = static_cast<CMonster*>(CObjMgr::Get_Instance()->Get_ObjList(MONSTER)->front())->Get_CurrentStage() % 2;

	switch (iStage)
	{
	case 1:
		MoveToEx(hdc, m_tInfo.fX + cosf(m_iRotation*RADIAN)*m_tInfo.fCX, m_tInfo.fY + sinf(m_iRotation*RADIAN)*m_tInfo.fCY, nullptr);
		for (int i = 1; i <= 5; i++)
		{
			LineTo(hdc, m_tInfo.fX + cosf((m_iRotation + i * 144)*RADIAN)*m_tInfo.fCX, m_tInfo.fY + sinf((m_iRotation + i * 144)*RADIAN)*m_tInfo.fCY);
		}
		break;
	case 0:
		MoveToEx(hdc, m_tInfo.fX + cosf(m_iRotation*RADIAN)*m_tInfo.fCX, m_tInfo.fY + sinf(m_iRotation*RADIAN)*m_tInfo.fCY, nullptr);
		for (int i = 1; i <= 3; i++)
		{
			LineTo(hdc, m_tInfo.fX + cosf((m_iRotation + i * 120)*RADIAN)*m_tInfo.fCX, m_tInfo.fY + sinf((m_iRotation + i * 120)*RADIAN)*m_tInfo.fCY);
		}
		MoveToEx(hdc, m_tInfo.fX + cosf((m_iRotation + 180)*RADIAN)*m_tInfo.fCX, m_tInfo.fY + sinf((m_iRotation + 180)*RADIAN)*m_tInfo.fCY, nullptr);
		for (int i = 1; i <= 3; i++)
		{
			LineTo(hdc, m_tInfo.fX + cosf(((m_iRotation + 180) + i * 120)*RADIAN)*m_tInfo.fCX, m_tInfo.fY + sinf(((m_iRotation + 180) + i * 120)*RADIAN)*m_tInfo.fCY);
		}
		break;
	default:
		break;
	}

}

void CFallingStar::Release()
{
}

void CFallingStar::CollisionEvent(CObj * _obj)
{
}
