#include "stdafx.h"
#include"Define.h"
#include "HpBox.h"
#include "ObjMgr.h"
#include "Player.h"


CHpBox::CHpBox()
{
}


CHpBox::~CHpBox()
{
}

void CHpBox::Initialize()
{
	//��ǥ
	m_tInfo.fX = m_iCount * 60.0f;
	m_tInfo.fY = 50.0f;
	//ũ��
	m_tInfo.fCX = 50.0f;
	m_tInfo.fCY = 50.0f;
	CObj::Update_Rect();
}

int CHpBox::Update()
{
	//�÷��̾��� ü�°��� ���Ѵٸ�
	//m_tInfo.fX = m_iCount * 60.0f;


	return 0;
}

void CHpBox::Late_Update()
{
}

void CHpBox::Render(HDC hdc)
{

	if (!CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->empty() && m_iCount <= static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->GetHp())
	{
		//���� �ݿ�
		MoveToEx(hdc, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
		LineTo(hdc,
			(int)(m_tInfo.fX - m_tInfo.fCX*0.25f + cosf(-45 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(-45 * RADIAN)*m_tInfo.fCY*0.25f));
		LineTo(hdc,
			(int)(m_tInfo.fX - m_tInfo.fCX*0.25f + cosf(-90 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(-90 * RADIAN)*m_tInfo.fCY*0.25f));
		LineTo(hdc,
			(int)(m_tInfo.fX - m_tInfo.fCX*0.25f + cosf(-135 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(-135 * RADIAN)*m_tInfo.fCY*0.25f));
		LineTo(hdc,
			(int)(m_tInfo.fX - m_tInfo.fCX*0.25f + cosf(180 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(180 * RADIAN)*m_tInfo.fCY*0.25f));
		//���� �ݿ�
		MoveToEx(hdc, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
		LineTo(hdc,
			(int)(m_tInfo.fX + m_tInfo.fCX*0.25f + cosf(-135 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(-135 * RADIAN)*m_tInfo.fCY*0.25f));
		LineTo(hdc,
			(int)(m_tInfo.fX + m_tInfo.fCX*0.25f + cosf(-90 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(-90 * RADIAN)*m_tInfo.fCY*0.25f));
		LineTo(hdc,
			(int)(m_tInfo.fX + m_tInfo.fCX*0.25f + cosf(-45 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(-45 * RADIAN)*m_tInfo.fCY*0.25f));
		LineTo(hdc,
			(int)(m_tInfo.fX + m_tInfo.fCX*0.25f + cosf(0)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(0)*m_tInfo.fCY*0.25f));
		//�� �ݿ�
		LineTo(hdc,
			(int)(m_tInfo.fX + cosf(45 * RADIAN)*m_tInfo.fCX*0.5f),
			(int)(m_tInfo.fY + sinf(45 * RADIAN)*m_tInfo.fCY*0.5f));
		LineTo(hdc,
			(int)(m_tInfo.fX + cosf(90 * RADIAN)*m_tInfo.fCX*0.5f),
			(int)(m_tInfo.fY + sinf(90 * RADIAN)*m_tInfo.fCY*0.5f));
		LineTo(hdc,
			(int)(m_tInfo.fX + cosf(135 * RADIAN)*m_tInfo.fCX*0.5f),
			(int)(m_tInfo.fY + sinf(135 * RADIAN)*m_tInfo.fCY*0.5f));
		LineTo(hdc,
			(int)(m_tInfo.fX + cosf(180 * RADIAN)*m_tInfo.fCX*0.5f),
			(int)(m_tInfo.fY + sinf(180 * RADIAN)*m_tInfo.fCY*0.5f));
	}
}

void CHpBox::Release()
{
}

void CHpBox::CollisionEvent(CObj * _obj)
{
}
