#include "stdafx.h"
#include "Tree.h"
#include "Define.h"


CTree::CTree()
{
}


CTree::~CTree()
{
}

void CTree::Initialize()
{
	m_iRand = rand() % 3;
	m_tInfo.fY = 550.0f + m_iRand*10.0f;
	m_tInfo.fCX = 20.0f;
	m_tInfo.fCY = 20.0f;


}

int CTree::Update()
{
	m_tInfo.fX -= 3;

	if (m_tInfo.fX < -200.0f)
	{
		m_tInfo.fX = 1000.0f;
	}

	Update_Rect();

	return 0;
}

void CTree::Late_Update()
{

}

void CTree::Render(HDC hdc)
{

	MoveToEx(hdc, m_tInfo.fX, m_tInfo.fY - 100, nullptr);
	LineTo(hdc,
		m_tInfo.fX + cosf((60.0f)*RADIAN)*100.0f,
		m_tInfo.fY + sinf((60.0f)*RADIAN)*100.0f);
	MoveToEx(hdc, m_tInfo.fX, m_tInfo.fY - 100, nullptr);
	LineTo(hdc,
		m_tInfo.fX + cosf((120.0f)*RADIAN)*100.0f,
		m_tInfo.fY + sinf((120.0f)*RADIAN)*100.0f);
	Ellipse(hdc,
		m_tRect.left,
		m_tRect.top - 100,
		m_tRect.right,
		m_tRect.bottom - 100);
}

void CTree::Release()
{
}

void CTree::CollisionEvent(CObj * _obj)
{
}
