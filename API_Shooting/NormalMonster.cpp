#include "stdafx.h"
#include "NormalMonster.h"
#include "MonsterPatternMgr.h"
#include "AbstractFactory.h"
#include "StageMgr.h"

CNormalMonster::CNormalMonster()
{
	m_tInfo = { 850.f ,-50.f,  30.f , 30.f };
	m_fSpeed = 3.f;
	m_fAngle = 0.f;
}


CNormalMonster::~CNormalMonster()
{
	Release();
}

void CNormalMonster::Initialize()
{
	m_iMaxHp = 2;
	m_iHp = m_iMaxHp;
}

int CNormalMonster::Update()
{
	if (0 >= m_iHp)
	{
		CStageMgr::Get_Instacne()->Set_Score(m_iMaxHp);
		return OBJ_DEAD;
	}
	if (m_bDelete)
		return OBJ_DELETE;

	switch (m_ePattern)
	{
	case PATTERN_A:
		if (m_tInfo.fX < 800)
		{
			if (0 >= m_tInfo.fY || WINCY <= m_tInfo.fY)
				m_fSpeed *= -1;
		}
		m_tInfo.fX -= fabs(m_fSpeed * 0.5f);
		m_tInfo.fY += m_fSpeed * 2.f;
		break;
	case PATTERN_B:
		if (m_fSpeed == 1)
		{
			m_tInfo.fX = WINCX - (WINCX - 400) * cosf(m_fAngle * PI / 180);
			m_tInfo.fY = (WINCY - 250) * sinf(m_fAngle * PI / 180);
			++m_fAngle;
		}
		else
		{
			m_tInfo.fX = WINCX - (WINCX - 400) * cosf(m_fAngle * PI / 180);
			m_tInfo.fY = WINCY - (WINCY - 250) * sinf(m_fAngle * PI / 180);
			++m_fAngle;
		}
		break;
	default:
		break;
	}


	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CNormalMonster::Late_Update()
{
	if (-100 > m_tRect.left || WINCX + 100 < m_tRect.right ||
		-100 > m_tRect.top || WINCY + 100 < m_tRect.bottom)
		m_bDelete = true;
}

void CNormalMonster::Render(HDC hdc)
{
	Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(hdc, m_tRect.left, m_tInfo.fY, nullptr);
	LineTo(hdc, m_tRect.left - m_tInfo.fCX * 0.5f, m_tRect.top);
	LineTo(hdc, m_tRect.left - m_tInfo.fCX * 0.5f, m_tRect.bottom);
	LineTo(hdc, m_tRect.left, m_tInfo.fY);
	MoveToEx(hdc, m_tRect.right, m_tInfo.fY, nullptr);
	LineTo(hdc, m_tRect.right + m_tInfo.fCX * 0.5f, m_tRect.top);
	LineTo(hdc, m_tRect.right + m_tInfo.fCX * 0.5f, m_tRect.bottom);
	LineTo(hdc, m_tRect.right, m_tInfo.fY);
}

void CNormalMonster::Release()
{
}

void CNormalMonster::CollisionEvent(CObj * _obj)
{
	if (_obj->Get_ObjID() == BULLET)
	{
		if (static_cast<CBullet*>(_obj)->GetBulletID() != BULLET_TARGET)
		{
			m_iHp -= static_cast<CWeapon*>(_obj)->Get_Dmg();
		}
		for (int i = 0; i < 6; i++)
		{
			CObjMgr::Get_Instance()->Get_ObjList(PARTICLE)->push_back(CAbstractFactory<CParticle>::Create(m_tInfo.fX, m_tInfo.fY));
			float radius = (rand() + GetTickCount()) % 30;
			static_cast<CParticle*>(CObjMgr::Get_Instance()->Get_ObjList(PARTICLE)->back())->SetParticle_Option(
				radius, radius, (rand() + GetTickCount()) % 360, (rand() + GetTickCount()) % 3
				);
		}
	}
	else if (_obj->Get_ObjID() == BOMB || _obj->Get_ObjID() == SHIELD)
	{
		m_iHp -= static_cast<CWeapon*>(_obj)->Get_Dmg();

		for (int i = 0; i < 6; i++)
		{
			CObjMgr::Get_Instance()->Get_ObjList(PARTICLE)->push_back(CAbstractFactory<CParticle>::Create(m_tInfo.fX, m_tInfo.fY));
			float radius = (rand() + GetTickCount()) % 30;
			static_cast<CParticle*>(CObjMgr::Get_Instance()->Get_ObjList(PARTICLE)->back())->SetParticle_Option(
				radius, radius, (rand() + GetTickCount()) % 360, (rand() + GetTickCount()) % 3
				);
		}
	}
}