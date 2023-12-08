#include "stdafx.h"
#include "BulletTypeBox.h"
#include "ObjMgr.h"
#include "Player.h"


CBulletTypeBox::CBulletTypeBox()
{
}


CBulletTypeBox::~CBulletTypeBox()
{
}

void CBulletTypeBox::Initialize()
{
	lstrcpy(szBuff, L"빈칸");
	m_eBulletID = BULLET_NONE;
	//좌표
	m_tInfo.fX = 50.0f;
	m_tInfo.fY = 550.0f;
	//크기
	m_tInfo.fCX = 50.0f;
	m_tInfo.fCY = 50.0f;
	CObj::Update_Rect();

}

int CBulletTypeBox::Update()
{
	if (!CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->empty())
	{
		m_eBulletID = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->GetBullitID();
	}
	//만약 플레이어의 ID와 다르다면 대입후
	switch (m_eBulletID)
	{
	case BULLET_NONE:
		lstrcpy(szBuff, L"빈칸");
		break;
	case BULLET_PIERCE:
		lstrcpy(szBuff, L"관통");
		break;
	case BULLET_CHASE:
		lstrcpy(szBuff, L"유도");
		break;
	case BULLET_END:
		break;
	default:
		break;
	}
	return 0;
}

void CBulletTypeBox::Late_Update()
{
}

void CBulletTypeBox::Render(HDC hdc)
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

void CBulletTypeBox::Release()
{
}

void CBulletTypeBox::CollisionEvent(CObj * _obj)
{
}
