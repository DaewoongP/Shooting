#include "stdafx.h"
#include "Pet.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
CPet::CPet()
	:m_fAngle(0)
{
}


CPet::~CPet()
{
}

void CPet::Initialize()
{

	m_eBullitID = BULLET_NONE;

	m_fSpeed = 100.f;

	m_bulletList = CObjMgr::Get_Instance()->Get_ObjList(BULLET);
}

int CPet::Update()
{
	if (CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->empty())
		return OBJ_DEAD;

	m_fAngle += 0.05f;
	m_tInfo = { CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX + m_fSpeed*cosf(m_fAngle),
		CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY + m_fSpeed*sinf(m_fAngle),
		20.f,20.f };

	MissileShoot();

	__super::Update_Rect();
	return OBJ_NOEVENT;
}

void CPet::Late_Update()
{
}

void CPet::Render(HDC hdc)
{
	int m_iRotation = 0;
	MoveToEx(hdc, m_tInfo.fX + cosf(m_iRotation*RADIAN)*m_tInfo.fCX, m_tInfo.fY + sinf(m_iRotation*RADIAN)*m_tInfo.fCY, nullptr);
	for (int i = 1; i <= 5; i++)
	{
		LineTo(hdc, m_tInfo.fX + cosf((m_iRotation + i * 144)*RADIAN)*m_tInfo.fCX, m_tInfo.fY + sinf((m_iRotation + i * 144)*RADIAN)*m_tInfo.fCY);
	}
}

void CPet::Release()
{
}

void CPet::CollisionEvent(CObj * _obj)
{
}

void CPet::MissileShoot()
{
	if (m_dwTime + 600 < GetTickCount())
	{
		CObj* _bullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tInfo.fY);//ÃÑ¾Ë »ý¼º
		static_cast<CBullet*>(_bullet)->SetBulletID(m_eBullitID);//ÃÑ¾Ë Å¸ÀÔ ÁöÁ¤
		m_bulletList->push_back(_bullet); //ÃÑ¾Ë Ãß°¡
		m_dwTime = GetTickCount();
	}
}
