#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet() :m_eBulletID()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_iDmg = 1;
	m_eOBJID = BULLET;
	m_tInfo.fCX = 10;
	m_tInfo.fCY = 10;
	m_fSpeed = 10.f;
	m_fRotSpeed = 3.f;
	m_fDir = 0 * RADIAN;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	//불릿의 이동 타입에 따른 이동운동
	switch (m_eBulletID)
	{
	case BULLET_CHASE:
	{
		if (m_pTarget != nullptr)
		{

			float width = abs(m_tInfo.fX - m_pTarget->Get_Info().fX);//밑변
			float height = abs(m_tInfo.fY + -m_pTarget->Get_Info().fY);//높이
			float fDiagonal = sqrtf(powf(width, 2) + powf(height, 2));//거리
			if (m_tInfo.fX<m_pTarget->Get_Info().fX && fDiagonal < 150.f)
			{
				//각도구하기
				m_fDir = acosf(width / fDiagonal);

				if (m_pTarget->Get_Info().fY < m_tInfo.fY)
					m_fDir = 2 * PI - m_fDir;

				m_tInfo.fX += cos(m_fDir)*m_fSpeed;
				m_tInfo.fY += sin(m_fDir)*m_fSpeed;
			}
			else
			{
				m_tInfo.fX += cos(m_fDir)*m_fSpeed;
				m_tInfo.fY += sin(m_fDir)*m_fSpeed;
			}
		}
		else
		{
			m_tInfo.fX += cos(m_fDir)*m_fSpeed;
			m_tInfo.fY += sin(m_fDir)*m_fSpeed;
		}
		break;
	}


	case BULLET_TARGET:
		MBullet();
		break;
	case BULLET_BOSS:
		BBullet();
		break;
	default:
		m_tInfo.fX += m_fSpeed;
		break;
	}

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	if (0 > m_tRect.left || WINCX < m_tRect.right ||
		0 > m_tRect.top || WINCY < m_tRect.bottom)
		m_bDead = OBJ_DEAD;
}

void CBullet::Render(HDC hdc)
{
	Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release()
{
}

void CBullet::CollisionEvent(CObj * _obj)
{
	if (m_eBulletID == BULLET_TARGET)
	{
		if (_obj->Get_ObjID() == PLAYER || _obj->Get_ObjID() == SHIELD || _obj->Get_ObjID() == BOMB)
		{
			Set_Dead();
		}
	}
	else if (m_eBulletID != BULLET_PIERCE)
		Set_Dead();
}

void CBullet::MBullet()
{
	if (m_fDir == 0)
	{
		float width = fabs(m_tInfo.fX - m_fPX);//밑변
		float height = fabs(m_tInfo.fY - m_fPY);//높이
		float fDiagonal = sqrtf(powf(width, 2) + powf(height, 2));//거리

		m_fDir = acosf(width / fDiagonal);

		if (m_tInfo.fY > m_fPY)
			m_fDir = 2 * PI - m_fDir;
	}

	m_tInfo.fX -= cos(m_fDir)*m_fSpeed;
	m_tInfo.fY += sin(m_fDir)*m_fSpeed;
}

void CBullet::BBullet()
{
	m_tInfo.fX -= m_fSpeed * cosf(m_fAngle);
	m_tInfo.fY += m_fSpeed * sinf(m_fAngle);
}
