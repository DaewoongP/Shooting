#include "stdafx.h"
#include "Background.h"
#include "AbstractFactory.h"
#include "FallingStar.h"
#include "Tree.h"
#include "Building.h"

CBackground* CBackground::m_pInstance = nullptr;

CBackground::CBackground()
{
}


CBackground::~CBackground()
{
}

void CBackground::Initailize()
{

	AddObject(BG_STAR, CAbstractFactory<CFallingStar>::Create());

	//건물 초기 위치
	for (size_t i = 0; i < 10; i++)
	{
		AddObject(BG_BUILDING, CAbstractFactory<CBuilding>::Create());
		m_BGList[BG_BUILDING].back()->Set_Pos(i*120.0f, m_BGList[BG_BUILDING].back()->Get_Info().fY);
	}
	//나무 초기위치
	for (size_t i = 0; i < 10; i++)
	{
		AddObject(BG_TREE, CAbstractFactory<CTree>::Create());
		m_BGList[BG_TREE].back()->Set_Pos(i*120.0f, m_BGList[BG_TREE].back()->Get_Info().fY);
	}


}

void CBackground::Update()
{
	if (dwTime + 3000 < GetTickCount())
	{
		AddObject(BG_STAR, CAbstractFactory<CFallingStar>::Create());
		dwTime = GetTickCount();
	}


	for (int i = 0; i < BG_END; i++)
	{
		for (auto iter : m_BGList[i])
		{
			iter->Update();
		}
	}
}

void CBackground::Late_Update()
{
	for (int i = 0; i < BG_END; i++)
	{
		for (auto iter : m_BGList[i])
		{
			iter->Late_Update();
		}
	}
}

void CBackground::Render(HDC hdc)
{
	for (int i = 0; i < BG_END; i++)
	{
		for (auto iter : m_BGList[i])
		{
			iter->Render(hdc);
		}
	}
}

void CBackground::Release()
{
	for (size_t i = 0; i < BG_END; i++)
	{
		for_each(m_BGList[i].begin(), m_BGList[i].end(), Safe_Delete<CObj*>);
		m_BGList[i].clear();
	}
}
