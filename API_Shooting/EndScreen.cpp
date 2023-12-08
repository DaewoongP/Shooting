#include "stdafx.h"
#include "EndScreen.h"
#include "StageMgr.h"


CEndScreen::CEndScreen()
{
}


CEndScreen::~CEndScreen()
{
}

void CEndScreen::Initialize()
{
	m_tInfo.fX = 400.0f;
	m_tInfo.fY = 300.0f;
	m_tInfo.fCX = 800.0f;
	m_tInfo.fCY = 600.0f;
	Update_Rect();
}

int CEndScreen::Update()
{
	return 0;
}

void CEndScreen::Late_Update()
{
}

void CEndScreen::Render(HDC hdc)
{
	if (CStageMgr::Get_Instacne()->Get_isGameEnd())
	{
		Rectangle(hdc,
			m_tRect.left,
			m_tRect.top,
			m_tRect.right,
			m_tRect.bottom);
		TCHAR szScore[32] = L"";
		wsprintf(szScore, L"GAME OVER");
		TextOut(hdc, 360, 300, szScore, lstrlen(szScore));
		wsprintf(szScore, L"Á¡¼ö: %d", CStageMgr::Get_Instacne()->Get_Score());
		TextOut(hdc, 360, 320, szScore, lstrlen(szScore));
	}
}

void CEndScreen::Release()
{
}

void CEndScreen::CollisionEvent(CObj * _obj)
{
}
