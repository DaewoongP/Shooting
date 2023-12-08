#include "stdafx.h"
#include "BulletMonster.h"
#include "AbstractFactory.h" 
#include "ObjMgr.h"
#include "MonsterPatternMgr.h"
#include "StageMgr.h"


CBulletMonster::CBulletMonster()
	:m_eBulletID(BULLET_TARGET)
{
}


CBulletMonster::~CBulletMonster()
{
	Release();
}

void CBulletMonster::Initialize()
{
	m_bulletList = CObjMgr::Get_Instance()->Get_ObjList(ENEMYBULLET);
	m_iMaxHp = 5;
	m_iHp = m_iMaxHp;
}

int CBulletMonster::Update()
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
	case PATTERN_NONE:
		break;
	case PATTERN_C:
		m_tInfo.fX -= m_fSpeed;
		if (m_tInfo.fX < 650.f)
		{
			m_tInfo.fX += m_fSpeed;
			if (m_dwTime + 4000 < GetTickCount())
			{
				FireToTarget();
				m_dwTime = GetTickCount();
				m_fSpeed *= -1;
			}
		}
		break;
	case PATTERN_D:
		m_tInfo.fX -= m_fSpeed;
		if (m_tInfo.fX < 600.f)
		{
			if (m_dwTime + 4000 < GetTickCount())
			{
				FireToTarget();
				m_dwTime = GetTickCount();
			}
		}
		break;
	case PATTERN_END:
		break;
	default:
		break;
	}


	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CBulletMonster::Late_Update()
{
	if (-100 > m_tRect.left || WINCX + 100 < m_tRect.right ||
		-100 > m_tRect.top || WINCY + 100 < m_tRect.bottom)
		m_bDelete = true;
}

void CBulletMonster::Render(HDC hdc)
{
	Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	MoveToEx(hdc, m_tRect.left, m_tRect.top, nullptr);
	LineTo(hdc, m_tInfo.fX, m_tRect.top - m_tInfo.fCY * 0.5f);
	LineTo(hdc, m_tRect.right, m_tRect.top);
	LineTo(hdc, m_tRect.right + m_tInfo.fCX * 0.5f, m_tInfo.fY);
	LineTo(hdc, m_tRect.right, m_tRect.bottom);
	LineTo(hdc, m_tInfo.fX, m_tRect.bottom + m_tInfo.fCY * 0.5f);
	LineTo(hdc, m_tRect.left, m_tRect.bottom);
	LineTo(hdc, m_tRect.left - m_tInfo.fCX * 0.5f, m_tInfo.fY);
	LineTo(hdc, m_tRect.left, m_tRect.top);
}

void CBulletMonster::Release()
{
}

void CBulletMonster::CollisionEvent(CObj * _obj)
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


void CBulletMonster::FireToTarget()
{
	if (!CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->empty())
	{
		INFO _info = CObjMgr::Get_Instance()->Get_Player()->Get_Info();
		CObj* _bullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);//ÃÑ¾Ë »ý¼º
		static_cast<CBullet*>(_bullet)->Set_Info({ m_tInfo.fX, m_tInfo.fY, 15, 15 });
		_bullet->Set_ObjID(ENEMYBULLET);
		static_cast<CBullet*>(_bullet)->SetBulletID(m_eBulletID);//ÃÑ¾Ë Å¸ÀÔ ÁöÁ¤
		static_cast<CBullet*>(_bullet)->Set_Dir(_info.fX, _info.fY);
		m_bulletList->push_back(_bullet); //ÃÑ¾Ë Ãß°¡
	}
}