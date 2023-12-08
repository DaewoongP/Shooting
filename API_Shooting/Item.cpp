#include "stdafx.h"
#include "Item.h"

int CItem::m_RandCount = 0.0f;

CItem::CItem()
{
}


CItem::~CItem()
{
}

void CItem::Initialize()
{
	//위치 초기화(몬스터 꺼 받아와야 함)
	m_tInfo.fX = WINCX;
	m_tInfo.fY = WINCY;
	//사이즈 초기화(상의)
	m_tInfo.fCX = 50.0f;
	m_tInfo.fCY = 50.0f;
	//랜덤 시드표 초기화
	//srand(unsigned(time(NULL)));
	//방향 랜덤 초기화
	m_fDirX = cosf((float)((rand() + m_RandCount) % 360)*RADIAN);
	m_fDirY = sinf((float)((rand() + m_RandCount) % 360)*RADIAN);
	//아이템 아이디 랜덤 초기화
	m_eItemID = (ITEMID)((rand() + m_RandCount) % ITEM_END);
	if (m_eItemID == ITEM_NONE1 || m_eItemID == ITEM_NONE2 || m_eItemID == ITEM_NONE3)
	{
		m_bDead = true;
	}
	//총알 아이디 랜덤 초기화
	m_eBulletID = (BULLETID)((rand() + m_RandCount) % BULLET_TARGET);

	//아이템 이동 속도 초기화(상의)
	m_fSpeed = 5.0f;
	//생성시 시간 초기화
	m_dwTime = GetTickCount();
	//오브젝트 아이디 초기화
	m_eOBJID = ITEM;

	//각도 변경 용
	m_RandCount += 155;

	switch (m_eItemID)
	{
	case ITEM_POWER:
		lstrcpy(szBuff, L"+");
		break;
	case ITEM_BOMB:
		lstrcpy(szBuff, L"B");
		break;
	case ITEM_HP:
		lstrcpy(szBuff, L"H");
		break;
	case ITEM_BULLET:
		switch (m_eBulletID)
		{
		case BULLET_NONE:
			break;
		case BULLET_PIERCE:
			lstrcpy(szBuff, L"PB");
			break;
		case BULLET_CHASE:
			lstrcpy(szBuff, L"CB");
			break;
		case BULLET_TARGET:
			break;
		case BULLET_END:
			break;
		default:
			break;
		}

		break;
	case ITEM_END:
		break;

	default:
		break;
	}
}

int CItem::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}


	//이동 업데이트 현제 좌표 += 방향 * 속도
	m_tInfo.fX += m_fDirX*m_fSpeed;
	m_tInfo.fY += m_fDirY*m_fSpeed;

	CObj::Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::Late_Update()
{
	//시간 동안만 튕기고
	if (m_dwTime + 10000 >= GetTickCount())
	{
		//만약 생성 시점에 화면 밖일 경우 껴버리기 때문에 
		if (m_tInfo.fCX*0.5f >= m_tInfo.fX)
		{
			m_tInfo.fX = m_tInfo.fCX*0.5f;
		}
		if (WINCX - m_tInfo.fCX*0.5f <= m_tInfo.fX)
		{
			m_tInfo.fX = WINCX - m_tInfo.fCX*0.5f;
		}
		if (m_tInfo.fCY*0.5f >= m_tInfo.fY)
		{
			m_tInfo.fY = m_tInfo.fCY*0.5f;
		}
		if (WINCY - m_tInfo.fCY*0.5f <= m_tInfo.fY)
		{
			m_tInfo.fY = WINCY - m_tInfo.fCY*0.5f;
		}


		//좌우 충돌시 방향 전환
		if (m_tInfo.fCX*0.5f >= m_tInfo.fX || WINCX - m_tInfo.fCX*0.5f <= m_tInfo.fX)
		{
			m_fDirX *= -1;
		}
		//상하 충돌시 방향 전환
		if (m_tInfo.fCY*0.5f >= m_tInfo.fY || WINCY - m_tInfo.fCY*0.5f <= m_tInfo.fY)
		{
			m_fDirY *= -1;
		}
	}
	//좌우로 완전히 나갈시 해제
	if (-m_tInfo.fCX*0.5f >= m_tInfo.fX || WINCX + m_tInfo.fCX*0.5f <= m_tInfo.fX)
	{
		Set_Dead();
	}
	//상하로 완전히 나갈시 해제
	if (-m_tInfo.fCY*0.5f >= m_tInfo.fY || WINCY + m_tInfo.fCY*0.5f <= m_tInfo.fY)
	{
		Set_Dead();
	}

}

void CItem::Render(HDC hdc)
{
	switch (m_eItemID)
	{
	case ITEM_POWER:
		Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		DrawText(hdc,
			szBuff,
			lstrlen(szBuff),
			&m_tRect,
			DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		break;
	case ITEM_HP:
	{
		//좌측 반월
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
		//우측 반월
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
		//밑 반월
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
		DrawText(hdc,
			szBuff,
			lstrlen(szBuff),
			&m_tRect,
			DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	}
	break;
	case ITEM_BOMB:
		Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		Ellipse(hdc, m_tRect.left + 5., m_tRect.top + 5, m_tRect.right - 5, m_tRect.bottom - 5);
		DrawText(hdc,
			szBuff,
			lstrlen(szBuff),
			&m_tRect,
			DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		break;
	case ITEM_BULLET:
		switch (m_eBulletID)
		{
		case BULLET_NONE:
			break;
		case BULLET_PIERCE:
			Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
			DrawText(hdc,
				szBuff,
				lstrlen(szBuff),
				&m_tRect,
				DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			break;
		case BULLET_CHASE:
			Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
			DrawText(hdc,
				szBuff,
				lstrlen(szBuff),
				&m_tRect,
				DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			break;
		case BULLET_TARGET:

			break;
		case BULLET_END:
			break;
		default:
			break;
		}

		break;
	case ITEM_END:
		break;
	default:
		break;
	}

}

void CItem::Release()
{
}

void CItem::CollisionEvent(CObj*_Obj)
{
	Set_Dead();
}