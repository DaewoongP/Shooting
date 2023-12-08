#include "stdafx.h"
#include "BossHpBar.h"
#include "ObjMgr.h"
#include "BossMonster.h"


CBossHpBar::CBossHpBar()
{
}


CBossHpBar::~CBossHpBar()
{
}

void CBossHpBar::Initialize()
{
	//위치//보스를 따라가게 할것인가?
	m_tInfo.fX = 0.0f;
	m_tInfo.fY = 20.0f;


	//크기 특정단위로 윈쪽에서부터 커지는 느낌으로 
	m_tInfo.fCX = 800.0f;
	m_tInfo.fCY = 20.0f;

	m_tBackgroundInfo.fCX = m_tInfo.fCX;
	m_tBackgroundInfo.fCY = m_tInfo.fCY + 10;

}

int CBossHpBar::Update()
{
	if (!(CObjMgr::Get_Instance()->Get_Monster() + MONSTER_BOSS)->empty())
	{
		//m_tInfo.fX = m_tBackgroundInfo.fX = static_cast<CBossMonster*>((CObjMgr::Get_Instance()->Get_Monster() + MONSTER_BOSS)->front())->Get_Info().fX - 200;
		//m_tInfo.fY = m_tBackgroundInfo.fY = static_cast<CBossMonster*>((CObjMgr::Get_Instance()->Get_Monster() + MONSTER_BOSS)->front())->Get_Info().fY - 100;

		//백그라운드 박스는 보스를 따라다니고


		//보스의 피통은 백그라운드 박스를 따라 다니며, 피통에 따라 갱신 된다.

		//반대로 할까나....

		m_iMaxHp = static_cast<CBossMonster*>((CObjMgr::Get_Instance()->Get_Monster() + MONSTER_BOSS)->front())->Get_MaxHp();

		//게이지의 최대크기 / 최대 체력 * 현제 체력
		m_tInfo.fCX = m_tBackgroundInfo.fCX / m_iMaxHp*static_cast<CBossMonster*>((CObjMgr::Get_Instance()->Get_Monster() + MONSTER_BOSS)->front())->Get_Hp();

		Update_Rect_Left_Pivot();
	}


	return 0;
}

void CBossHpBar::Late_Update()
{
}

void CBossHpBar::Render(HDC hdc)
{
	if (!(CObjMgr::Get_Instance()->Get_Monster() + MONSTER_BOSS)->empty())
	{
		Rectangle(hdc,
			m_rcBackground.left,
			m_rcBackground.top,
			m_rcBackground.right,
			m_rcBackground.bottom);
		Rectangle(hdc,
			m_tRect.left,
			m_tRect.top,
			m_tRect.right,
			m_tRect.bottom);
	}
}

void CBossHpBar::Release()
{
}

void CBossHpBar::CollisionEvent(CObj * _obj)
{
}

void CBossHpBar::Update_Rect_Left_Pivot()
{

	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.0f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 1.0f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	m_rcBackground.left = long(m_tBackgroundInfo.fX - (m_tBackgroundInfo.fCX * 0.0f));
	m_rcBackground.top = long(m_tBackgroundInfo.fY - (m_tBackgroundInfo.fCY * 0.5f));
	m_rcBackground.right = long(m_tBackgroundInfo.fX + (m_tBackgroundInfo.fCX * 1.0f));
	m_rcBackground.bottom = long(m_tBackgroundInfo.fY + (m_tBackgroundInfo.fCY * 0.5f));
}
