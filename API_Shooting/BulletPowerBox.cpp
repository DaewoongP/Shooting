#include "stdafx.h"
#include "BulletPowerBox.h"
#include "ObjMgr.h"
#include "Player.h"


CBulletPowerBox::CBulletPowerBox()
{
}


CBulletPowerBox::~CBulletPowerBox()
{
}

void CBulletPowerBox::Initialize()
{
	lstrcpy(szBuff, L"1");
	m_iPower = static_cast<CPlayer*>((CObjMgr::Get_Instance()->Get_Player()))->GetPower();
	//��ǥ
	m_tInfo.fX = 110.0f;
	m_tInfo.fY = 550.0f;
	//ũ��
	m_tInfo.fCX = 50.0f;
	m_tInfo.fCY = 50.0f;
	CObj::Update_Rect();
}

int CBulletPowerBox::Update()
{
	if (!CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->empty())
	{
		m_iPower = static_cast<CPlayer*>((CObjMgr::Get_Instance()->Get_Player()))->GetPower();
	}
	//���� �÷��̾��� ���� �ٸ��ٸ�
	switch (m_iPower)
	{
	case 1:
		lstrcpy(szBuff, L"1");
		break;
	case 2:
		lstrcpy(szBuff, L"2");
		break;
	case 3:
		lstrcpy(szBuff, L"3");
		break;

	default:
		break;
	}
	return 0;
}

void CBulletPowerBox::Late_Update()
{
}

void CBulletPowerBox::Render(HDC hdc)
{
	Rectangle(hdc,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
	DrawText(hdc,
		szBuff,
		lstrlen(szBuff),
		&m_tRect,
		DT_VCENTER | DT_SINGLELINE | DT_CENTER);
}

void CBulletPowerBox::Release()
{
}

void CBulletPowerBox::CollisionEvent(CObj * _obj)
{
}
