#include "stdafx.h"
#include "Player.h"
#include "Item.h"
#include "AbstractFactory.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "Shield.h"
#include "Bomb.h"
#include "Particle.h"
#include "StageMgr.h"


CPlayer::CPlayer() :m_dwTime_bomb(GetTickCount()), m_ePlayerState(PLAYER_NONE)
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	m_ePlayerState = PLAYER_INVI;
	m_eBullitID = BULLET_CHASE;
	m_iBomb = 3; // 보여줄 강공의 수
	m_iPower = 1; // 보여줄 공격력
	m_iHp = 3; // 보여줄 HP
	m_tInfo = INFO{ 100.f,300.f,40.f,40.f };
	m_fSpeed = 10.f;
	m_dwTime = GetTickCount();
	m_dwTime_invi = GetTickCount(); //무적시간

	m_bulletList = CObjMgr::Get_Instance()->Get_ObjList(BULLET);
}

int CPlayer::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	__super::Update_Rect();
	keyInput();
	//CheckinMap();
	MissileShoot();

	if (m_dwTime_invi + 2000 < GetTickCount())
		m_ePlayerState = PLAYER_NONE;

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{

}

void CPlayer::Render(HDC hdc)
{
	if (m_ePlayerState == PLAYER_NONE)
	{
		Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		Ellipse(hdc, m_tRect.left + m_tInfo.fCX*0.5f, m_tRect.top + m_tInfo.fCY*0.5f, m_tRect.right + m_tInfo.fCX*0.25f, m_tRect.bottom + m_tInfo.fCY*0.1f);
		Ellipse(hdc, m_tRect.left - m_tInfo.fCX*0.5f, m_tRect.top - m_tInfo.fCY*0.1f, m_tRect.right - m_tInfo.fCX*0.5f, m_tRect.bottom - m_tInfo.fCY*0.5f);
		Ellipse(hdc, m_tRect.left + m_tInfo.fCX*1.1f, m_tRect.top + m_tInfo.fCY*0.5f, m_tRect.right + m_tInfo.fCX*0.2f, m_tRect.bottom - m_tInfo.fCY*0.3f);
		Ellipse(hdc, m_tRect.left + m_tInfo.fCX*0.6f, m_tRect.top + m_tInfo.fCY*0.2f, m_tRect.right - m_tInfo.fCX*0.2f, m_tRect.bottom - m_tInfo.fCY*0.5f);
		Ellipse(hdc, m_tRect.left + m_tInfo.fCX*0.7f, m_tRect.top + m_tInfo.fCY*0.3f, m_tRect.right - m_tInfo.fCX*0.25f, m_tRect.bottom - m_tInfo.fCY*0.6f);
	}
	else
	{
		if (GetTickCount() % 100<50)
		{
			Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
			Ellipse(hdc, m_tRect.left + m_tInfo.fCX*0.5f, m_tRect.top + m_tInfo.fCY*0.5f, m_tRect.right + m_tInfo.fCX*0.25f, m_tRect.bottom + m_tInfo.fCY*0.1f);
			Ellipse(hdc, m_tRect.left - m_tInfo.fCX*0.5f, m_tRect.top - m_tInfo.fCY*0.1f, m_tRect.right - m_tInfo.fCX*0.5f, m_tRect.bottom - m_tInfo.fCY*0.5f);
			Ellipse(hdc, m_tRect.left + m_tInfo.fCX*1.1f, m_tRect.top + m_tInfo.fCY*0.5f, m_tRect.right + m_tInfo.fCX*0.2f, m_tRect.bottom - m_tInfo.fCY*0.3f);
			Ellipse(hdc, m_tRect.left + m_tInfo.fCX*0.6f, m_tRect.top + m_tInfo.fCY*0.2f, m_tRect.right - m_tInfo.fCX*0.2f, m_tRect.bottom - m_tInfo.fCY*0.5f);
			Ellipse(hdc, m_tRect.left + m_tInfo.fCX*0.7f, m_tRect.top + m_tInfo.fCY*0.3f, m_tRect.right - m_tInfo.fCX*0.25f, m_tRect.bottom - m_tInfo.fCY*0.6f);
		}
	}

}

void CPlayer::Release()
{
}

void CPlayer::CollisionEvent(CObj* _obj)
{
	switch (_obj->Get_ObjID())
	{
	case ENEMYBULLET:
		OnCollision_Enemy(_obj);
		break;
	case MONSTER:
		OnCollision_Enemy(_obj);
		break;
	case ITEM:
		OnCollision_Item(_obj);
		break;
	case OBJ_END:
		break;
	}
}

void CPlayer::keyInput()
{

	if (GetAsyncKeyState(VK_LEFT) && (m_tRect.left >= ScreenSize_minX))
	{
		if (GetAsyncKeyState(VK_UP) && m_tRect.top >= ScreenSize_minY)
		{
			m_tInfo.fX -= (m_fSpeed) / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN) && m_tRect.bottom <= ScreenSize_maxY)
		{
			m_tInfo.fX -= (m_fSpeed) / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
		{
			m_tInfo.fX -= m_fSpeed;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT) && m_tRect.right <= ScreenSize_maxX)
	{
		if (GetAsyncKeyState(VK_UP) && m_tRect.top >= ScreenSize_minY)
		{
			m_tInfo.fX += (m_fSpeed) / sqrtf(2.f);
			m_tInfo.fY -= m_fSpeed / sqrtf(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN) && m_tRect.bottom <= ScreenSize_maxY)
		{
			m_tInfo.fX += (m_fSpeed) / sqrtf(2.f);
			m_tInfo.fY += m_fSpeed / sqrtf(2.f);
		}
		else
		{
			m_tInfo.fX += m_fSpeed;
		}
	}
	else if (GetAsyncKeyState(VK_UP) && m_tRect.top >= ScreenSize_minY)
	{
		m_tInfo.fY -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_DOWN) && m_tRect.bottom <= ScreenSize_maxY)
	{
		m_tInfo.fY += m_fSpeed;
	}

	if (GetAsyncKeyState('A'))
	{
		if (CObjMgr::Get_Instance()->Get_ObjList(SHIELD)->size()<35)
			CObjMgr::Get_Instance()->Get_ObjList(SHIELD)->push_back(CAbstractFactory<CShield>::Create());
	}

	if (GetAsyncKeyState('S'))
	{
		for (auto& iter : *(CObjMgr::Get_Instance()->Get_ObjList(SHIELD)))
		{
			iter->Set_Target(nullptr);
		}
	}

	if (GetAsyncKeyState('D'))
	{
		if (m_dwTime_bomb + 1000 < GetTickCount() && m_iBomb>0)
		{
			CObjMgr::Get_Instance()->Get_ObjList(BOMB)->push_back(CAbstractFactory<CBomb>::Create(m_tInfo.fX, m_tInfo.fY));
			m_dwTime_bomb = GetTickCount();
			m_iBomb--;
		}
	}
}

void CPlayer::MissileShoot()
{
	if (m_dwTime + 300< GetTickCount())
	{
		//파워에 따라 총알의 갈래를 결정
		for (int i = 0; i < m_iPower; i++)
		{                                                                  //꼭대기 + 지름/세기*(총알 인덱스)
			CObj* _bullet = CAbstractFactory<CBullet>::Create(m_tInfo.fX, m_tRect.top + (float)(m_tInfo.fCY / (m_iPower + 1)*(i + 1)));//총알 생성
			static_cast<CBullet*>(_bullet)->SetBulletID(m_eBullitID);//총알 타입 지정
			m_bulletList->push_back(_bullet); //총알 추가
			m_dwTime = GetTickCount();
		}
	}
}

void CPlayer::OnCollision_Item(CObj* _obj)
{
	switch (static_cast<CItem*>(_obj)->Get_ITEMID())
	{
	case ITEM_POWER:
		++m_iPower;
		if (m_iPower > 3)
			m_iPower = 3;
		break;
	case ITEM_HP:
		++m_iHp;
		if (m_iHp > 3)
			m_iHp = 3;
		break;
	case ITEM_BOMB:
		++m_iBomb;
		if (m_iBomb > 3)
			m_iBomb = 3;
		break;
	case ITEM_BULLET:
	{
		switch (static_cast<CItem*>(_obj)->Get_BULLETID())
		{
		case BULLET_NONE:
			m_eBullitID = BULLET_NONE;
			break;
		case BULLET_PIERCE:
			m_eBullitID = BULLET_PIERCE;
			break;
		case BULLET_CHASE:
			m_eBullitID = BULLET_CHASE;
			break;
		}
		break;
	}
	}
}

void CPlayer::OnCollision_Enemy(CObj* _obj)
{
	if (m_ePlayerState != PLAYER_INVI)
	{
		if (m_iHp <= 1)
		{
			CStageMgr::Get_Instacne()->Set_EndTrigger(true);
			Set_Dead();
		}
		else
		{
			m_iHp--;
			m_ePlayerState = PLAYER_INVI;
			m_dwTime_invi = GetTickCount();
			m_eBullitID = BULLET_NONE;
			m_iPower = 1;
		}
		for (int i = 0; i < 4; i++)
		{
			CObjMgr::Get_Instance()->Get_ObjList(PARTICLE)->push_back(CAbstractFactory<CParticle>::Create(m_tInfo.fX, m_tInfo.fY));
			float radius = (rand() + 1) % 30;
			static_cast<CParticle*>(CObjMgr::Get_Instance()->Get_ObjList(PARTICLE)->back())->SetParticle_Option(
				radius, radius, (rand() + 1) % 360, (rand() + 1) % 3
				);
		}
	}
}