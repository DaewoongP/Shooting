#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"
#include "CollilusionMgr.h"
#include "DistanceMgr.h"
#include "ObjMgr.h"
#include "UserInterface.h"
#include "Background.h"
#include "StageMgr.h"
CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	srand(unsigned(time(NULL)));
	m_hDC = GetDC(g_hWnd);
	CBackground::Get_Instance()->Initailize();
	CStageMgr::Get_Instacne()->Initialize();
	CObjMgr::Get_Instance()->AddObject(PLAYER, CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->AddObject(PET, CAbstractFactory<CPet>::Create());
	CObjMgr::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CMonster>::Create());

	CUserInterface::Get_Instance()->Initailize();
}

void CMainGame::Update()
{
	if (!CStageMgr::Get_Instacne()->Get_isGameEnd())
	{
		CBackground::Get_Instance()->Update();
		CObjMgr::Get_Instance()->Update();
		CUserInterface::Get_Instance()->Update();
	}
	CStageMgr::Get_Instacne()->Update();
}

void CMainGame::Late_Update()
{
	if (!CStageMgr::Get_Instacne()->Get_isGameEnd())
	{
		CBackground::Get_Instance()->Late_Update();
		CObjMgr::Get_Instance()->Late_Update();
	}
	CStageMgr::Get_Instacne()->Late_Update();
}

void CMainGame::Render()
{
	if (!CStageMgr::Get_Instacne()->Get_isGameEnd())
	{
		Rectangle(m_hDC, 0, 0, WINCX, WINCY);
		CBackground::Get_Instance()->Render(m_hDC);
		CObjMgr::Get_Instance()->Render(m_hDC);
		
	}
	CUserInterface::Get_Instance()->Render(m_hDC);
	CStageMgr::Get_Instacne()->Render();

}

void CMainGame::Release()
{
	CBackground::Get_Instance()->Release();
	CBackground::Destroy_Instance();
	CObjMgr::Get_Instance()->Release();
	CObjMgr::Destroy_Instance();
	CUserInterface::Get_Instance()->Release();
	CUserInterface::Destroy_Instance();
	CStageMgr::Destroy_Instance();

	ReleaseDC(g_hWnd, m_hDC);
}

void CMainGame::Reset()
{
	Release();
	Initialize();
}
