#include "stdafx.h"
#include "BossMonster.h"
#include "Weapon.h"
#include "AbstractFactory.h"
#include "MonsterPatternMgr.h"
#include "Bullet.h"
#include "StageMgr.h"

CBossMonster::CBossMonster()
	:m_eBulletID(BULLET_BOSS), m_BulletAngle(0), parten_time(GetTickCount()), parten_E_time(3), parten_F_time(3),parten_G_time(3)
{
}


CBossMonster::~CBossMonster()
{
	Release();
}

void CBossMonster::Initialize()
{
	m_iMaxHp = 1000;
	m_iHp = m_iMaxHp;
	m_tInfo = { 700.f, 300.f, 200.f, 200.f };
	m_fSpeed = 10.f;
}

int CBossMonster::Update()
{
	if (0 >= m_iHp)
	{
		CStageMgr::Get_Instacne()->Set_Score(m_iMaxHp);
		return OBJ_DEAD;
	}

	// 보스 등장
	if (m_tInfo.fX > 800.f)
	{
		m_tInfo.fX -= m_fSpeed;
	}

	BossParten();

	switch (m_ePattern)
	{
	case PATTERN_E:
		if (m_dwTime + 300 < GetTickCount())
		{
			FireToTarget_Fast();
			m_dwTime = GetTickCount();
		}
		break;
	case PATTERN_F:
		m_tInfo.fX -= m_fSpeed;
		break;
	case PATTERN_G:
		FireToTarget();
		if (m_dwTime + 8000 < GetTickCount())
		{
			m_dwTime = GetTickCount();
			m_ePattern = PATTERN_NONE;
		}
		break;
	default:
		break;
	}

	__super::Update_Rect();
	return OBJ_NOEVENT;
}



void CBossMonster::Late_Update()
{

}

void CBossMonster::Render(HDC hdc)
{
	switch (m_ePattern)
	{
		// 가위
	case PATTERN_E:
		//엄지
		MoveToEx(hdc, m_tInfo.fX + m_tInfo.fCX * 0.5f, m_tInfo.fY + m_tInfo.fCY * 0.5f, nullptr);//.
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX * 0.5f, m_tInfo.fY - m_tInfo.fCY * 0.75f);//|
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX * 0.25f, m_tInfo.fY - m_tInfo.fCY * 0.75f);
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX * 0.25f, m_tInfo.fY - m_tInfo.fCY * 0.5f);//|
		//검지
		//MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY - m_tInfo.fCY * 0.5f, nullptr);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.75f, m_tInfo.fY - m_tInfo.fCY * 0.5f);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.75f, m_tInfo.fY - m_tInfo.fCY * 0.25f);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY - m_tInfo.fCY * 0.25f);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY + m_tInfo.fCY * 0.5f);
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX * 0.5f, m_tInfo.fY + m_tInfo.fCY * 0.5f);
		//중지
		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY - m_tInfo.fCY * 0.25f, nullptr);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.25f, m_tInfo.fY - m_tInfo.fCY * 0.25f);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.25f, m_tInfo.fY);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.25f, m_tInfo.fY + m_tInfo.fCY*0.5f);

		//LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY);
		//약지
		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY, nullptr);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.25f, m_tInfo.fY);
		//소지
		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY + m_tInfo.fCY*0.25f, nullptr);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.25f, m_tInfo.fY + m_tInfo.fCY * 0.25f);
		break;
		// 바위
	case PATTERN_F:
		Rectangle(hdc,
			m_tRect.left,
			m_tRect.top,
			m_tRect.right,
			m_tRect.bottom);
		//주먹 엄지
		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.125f, m_tInfo.fY - m_tInfo.fCY * 0.5f, nullptr);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.125f, m_tInfo.fY);
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX * 0.125f, m_tInfo.fY);
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX * 0.125f, m_tInfo.fY - m_tInfo.fCY*0.25f);
		//첫번째 윗손가락
		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY - m_tInfo.fCY * 0.25f, nullptr);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.125f, m_tInfo.fY - m_tInfo.fCY * 0.25f);
		//두번째 윗손가락
		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY, nullptr);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.125f, m_tInfo.fY);
		//세번째 아랫손가락
		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY + m_tInfo.fCY * 0.25f, nullptr);
		LineTo(hdc, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * 0.25f);
		LineTo(hdc, m_tInfo.fX, m_tInfo.fY);
		//네번째 아랫손가락
		LineTo(hdc, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * 0.5f);
		break;
		// 보
	case PATTERN_G:
		MoveToEx(hdc, m_tInfo.fX + m_tInfo.fCX * 0.5f, m_tInfo.fY + m_tInfo.fCY * 0.5f, nullptr);//.
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX * 0.5f, m_tInfo.fY - m_tInfo.fCY * 0.75f);//|
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX * 0.25f, m_tInfo.fY - m_tInfo.fCY * 0.75f);
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX * 0.25f, m_tInfo.fY - m_tInfo.fCY * 0.5f);//|

		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.75f, m_tInfo.fY - m_tInfo.fCY * 0.5f);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.75f, m_tInfo.fY - m_tInfo.fCY * 0.25f);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.75f, m_tInfo.fY + m_tInfo.fCY * 0.5f);
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX * 0.5f, m_tInfo.fY + m_tInfo.fCY * 0.5f);

		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.75f, m_tInfo.fY - m_tInfo.fCY * 0.25f, nullptr);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.25f, m_tInfo.fY - m_tInfo.fCY * 0.25f);
		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.75f, m_tInfo.fY - m_tInfo.fCY * 0.0f, nullptr);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.25f, m_tInfo.fY - m_tInfo.fCY * 0.0f);
		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.75f, m_tInfo.fY + m_tInfo.fCY * 0.25f, nullptr);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.25f, m_tInfo.fY + m_tInfo.fCY * 0.25f);
		break;
	default:
		Rectangle(hdc,
			m_tRect.left,
			m_tRect.top,
			m_tRect.right,
			m_tRect.bottom);
		//주먹 엄지
		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.125f, m_tInfo.fY - m_tInfo.fCY * 0.5f, nullptr);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.125f, m_tInfo.fY);
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX * 0.125f, m_tInfo.fY);
		LineTo(hdc, m_tInfo.fX + m_tInfo.fCX * 0.125f, m_tInfo.fY - m_tInfo.fCY*0.25f);
		//첫번째 윗손가락
		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY - m_tInfo.fCY * 0.25f, nullptr);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.125f, m_tInfo.fY - m_tInfo.fCY * 0.25f);
		//두번째 윗손가락
		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY, nullptr);
		LineTo(hdc, m_tInfo.fX - m_tInfo.fCX * 0.125f, m_tInfo.fY);
		//세번째 아랫손가락
		MoveToEx(hdc, m_tInfo.fX - m_tInfo.fCX * 0.5f, m_tInfo.fY + m_tInfo.fCY * 0.25f, nullptr);
		LineTo(hdc, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * 0.25f);
		LineTo(hdc, m_tInfo.fX, m_tInfo.fY);
		//네번째 아랫손가락
		LineTo(hdc, m_tInfo.fX, m_tInfo.fY + m_tInfo.fCY * 0.5f);
		break;
	}
}

void CBossMonster::Release()
{
}

void CBossMonster::CollisionEvent(CObj* _obj)
{
	if (_obj->Get_ObjID() == BULLET || _obj->Get_ObjID() == SHIELD)
		m_iHp -= static_cast<CWeapon*>(_obj)->Get_Dmg();

	if (_obj->Get_ObjID() == BOMB)
	{
		if (m_dwTime + 1000 < GetTickCount())
		{
			m_iHp -= static_cast<CWeapon*>(_obj)->Get_Dmg();
			m_dwTime = GetTickCount();
		}
	}
}

void CBossMonster::FireToTarget_Fast()
{
	if (!CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->empty())
	{
		INFO _info = CObjMgr::Get_Instance()->Get_Player()->Get_Info();
		CObj* _bullet = CAbstractFactory<CBullet>::Create(m_AtkInfo.fX, m_AtkInfo.fY);//총알 생성
		static_cast<CBullet*>(_bullet)->Set_Info({ m_AtkInfo.fX, m_AtkInfo.fY, 20, 20 });
		_bullet->Set_ObjID(ENEMYBULLET);
		static_cast<CBullet*>(_bullet)->SetBulletID(BULLET_TARGET);//총알 타입 지정
		static_cast<CBullet*>(_bullet)->Set_Dir(_info.fX, _info.fY);
		_bullet->Set_Speed(20.f);
		m_bulletList->push_back(_bullet); //총알 추가
	}
}

void CBossMonster::FireToTarget()
{
	if (!CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->empty())
	{
		++m_BulletAngle;
		CObj* _bullet = CAbstractFactory<CBullet>::Create(m_AtkInfo.fX, m_AtkInfo.fY);
		static_cast<CBullet*>(_bullet)->Set_Info({ m_AtkInfo.fX, m_AtkInfo.fY, 15, 15 });
		_bullet->Set_ObjID(ENEMYBULLET);
		static_cast<CBullet*>(_bullet)->SetBulletID(m_eBulletID);
		static_cast<CBullet*>(_bullet)->Set_Angle(m_BulletAngle);
		m_bulletList->push_back(_bullet);

	}
}

void CBossMonster::BossParten()
{
	switch (parten_num)
	{
	case 0:
		CMonsterPatternMgr::NPatternE(*this, parten_time);
		if (parten_time + parten_E_time * 1000 < GetTickCount())
		{
			parten_num = (rand() % 3);
			parten_time = GetTickCount();
		}
		break;
	case 1:
		CMonsterPatternMgr::NPatternF(*this, parten_time);
		break;
	case 2:
		CMonsterPatternMgr::NPatternG(*this, parten_time);
		if (parten_time + parten_G_time * 1000 < GetTickCount())
		{
			parten_num = (rand() % 3);
			parten_time = GetTickCount();
		}
		break;
	default:
		parten_num = (rand() % 3);
		break;
	}
}
