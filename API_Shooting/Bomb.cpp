#include "stdafx.h"
#include "Bomb.h"


CBomb::CBomb() :m_fBackMove_timer(0.1f), m_fFrontMove_timer(1.f), m_fSplash_timer(1.f), m_eState(Back)
{
}


CBomb::~CBomb()
{
}

void CBomb::Initialize()
{
	m_eOBJID = BOMB;
	m_iDmg = 10;
	m_fSpeed = 3.0;
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;
}

int CBomb::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	switch (m_eState)
	{
	case Back:
		m_tInfo.fX -= 2.f;
		m_tInfo.fY += 8.f;
		if (m_dwTime + 1000 * m_fBackMove_timer<GetTickCount())
		{
			m_eState = Front;
			m_dwTime = GetTickCount();
		}
		break;
	case Front:
		m_tInfo.fX += 5.f;
		m_tInfo.fY -= 1.f;
		if (m_dwTime + 1000 * m_fFrontMove_timer<GetTickCount())
		{
			m_eState = Splash;
			m_dwTime = GetTickCount();
		}
		break;
	case Splash:
		m_tInfo.fCX += m_fSpeed += 0.08f;
		m_tInfo.fCY += m_fSpeed += 0.08f;
		if (m_dwTime + 1000 * m_fSplash_timer<GetTickCount())
		{
			m_eState = End;
			m_dwTime = GetTickCount();
		}
		break;
	case End:
		Set_Dead();
		break;
	}
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CBomb::Late_Update()
{
}

void CBomb::Render(HDC hdc)
{
	Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBomb::Release()
{
}

void CBomb::CollisionEvent(CObj * _obj)
{
}
