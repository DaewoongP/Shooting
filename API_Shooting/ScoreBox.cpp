#include "stdafx.h"
#include "ScoreBox.h"
#include "StageMgr.h"


CScoreBox::CScoreBox()
{
}


CScoreBox::~CScoreBox()
{
}

void CScoreBox::Initialize()
{
}

int CScoreBox::Update()
{
	return 0;
}

void CScoreBox::Late_Update()
{
}

void CScoreBox::Render(HDC hdc)
{
	TCHAR szScore[32] = L"";
	wsprintf(szScore, L"Á¡¼ö : %d", CStageMgr::Get_Instacne()->Get_Score());
	TextOut(hdc, 700, 550, szScore, lstrlen(szScore));
}

void CScoreBox::Release()
{
}

void CScoreBox::CollisionEvent(CObj * _obj)
{
}
