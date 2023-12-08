#include "stdafx.h"
#include "BombBox.h"
#include "ObjMgr.h"
#include "Player.h"
CBombBox::CBombBox()
{
}

CBombBox::CBombBox(int _playerBomb)
	: m_iCount(_playerBomb)
{
}


CBombBox::~CBombBox()
{
}

void CBombBox::Initialize()
{

	//좌표
	m_tInfo.fX = m_iCount * 60.0f;
	m_tInfo.fY = 110.0f;
	//크기
	m_tInfo.fCX = 50.0f;
	m_tInfo.fCY = 50.0f;
	CObj::Update_Rect();
}

int CBombBox::Update()
{



	//플레이어의 특수공격값이 변한다면
	//m_tInfo.fX = m_iCount * 60.0f;
	//CObj::Update_Rect();

	return 0;
}

void CBombBox::Late_Update()
{
}

void CBombBox::Render(HDC hdc)
{
	if (!CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->empty())
	{
		//작거나 같다면 출력
		if (m_iCount <= static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->GetBomb())
		{
			Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
			Ellipse(hdc, m_tRect.left + 5., m_tRect.top + 5, m_tRect.right - 5, m_tRect.bottom - 5);
		}
	}

}

void CBombBox::Release()
{
}

void CBombBox::CollisionEvent(CObj * _obj)
{
}
