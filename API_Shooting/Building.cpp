#include "stdafx.h"
#include "Building.h"


CBuilding::CBuilding()
{
}


CBuilding::~CBuilding()
{
}

void CBuilding::Initialize()
{
	int iRand = rand() % 5;

	m_tInfo.fY = 600.0f+ iRand *50;

	m_tInfo.fCX = 110.0f - iRand*10;

	m_tInfo.fCY = 400.0f;
}

int CBuilding::Update()
{
	m_tInfo.fX -= 2;
	if (m_tInfo.fX < -200.0f)
	{
		m_tInfo.fX = 1000.0f;
		Initialize();
	}
	Update_Rect_Bottom_Pivot();
	return 0;
}

void CBuilding::Late_Update()
{
}

void CBuilding::Render(HDC hdc)
{
	Rectangle(hdc,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CBuilding::Release()
{
}

void CBuilding::CollisionEvent(CObj * _obj)
{
}

void CBuilding::Update_Rect_Bottom_Pivot()
{
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 1.0f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.0f));
}
