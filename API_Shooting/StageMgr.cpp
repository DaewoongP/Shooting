#include "stdafx.h"
#include "StageMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "AbstractFactory.h"
#include "UserInterface.h"
#include "Background.h"

#include "Monster.h"

CStageMgr* CStageMgr::m_pInstance = nullptr;

CStageMgr::CStageMgr():m_bIsGameEnd(false), m_iScore(0), m_bEndTrigger(false)
{
}


CStageMgr::~CStageMgr()
{
}

void CStageMgr::Initialize()
{
	MakerPartenList();
}

void CStageMgr::Update()
{
	if (m_bEndTrigger)
	{
 		if (dwTime+3000<GetTickCount())
		{
			Set_isGameEnd(true);
		}
	}
	KeyInput();
}

void CStageMgr::Late_Update()
{
}

void CStageMgr::Render()
{

}

void CStageMgr::Release()
{
}

void CStageMgr::MakerPartenList()
{
	for (int i = 0; i < 8; i++)
	{
		m_partenList[i].push_back((PATTERNID)(rand() % 4 + 1));
		m_partenList[i].push_back((PATTERNID)(9));
		m_partenList[i].push_back((PATTERNID)(rand() % 4 + 1));
		m_partenList[i].push_back((PATTERNID)(9));
		m_partenList[i].push_back((PATTERNID)(rand() % 4 + 1));
		m_partenList[i].push_back((PATTERNID)(9));
		m_partenList[i].push_back((PATTERNID)(rand() % 4 + 1));
		m_partenList[i].push_back((PATTERNID)(9));
	}
	m_partenList[8].push_back(PATTERN_BOSS);
}

void CStageMgr::KeyInput()
{
	if (GetAsyncKeyState(VK_SPACE)&&m_bEndTrigger&&m_bIsGameEnd && !CObjMgr::Get_Instance()->Get_Monster()[MONSTER_BOSS].empty())
	{
		Set_isGameEnd(false);
		Set_EndTrigger(false);
		if (!CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->empty())
		{
			CObjMgr::Get_Instance()->Get_ObjList(PLAYER)->front()->Set_Dead();
		}
			
		CObjMgr::Get_Instance()->AddObject(PLAYER, CAbstractFactory<CPlayer>::Create());
	}
	else if (GetAsyncKeyState(VK_CONTROL) && m_bEndTrigger&&m_bIsGameEnd)
	{
		Set_isGameEnd(false);
		Set_EndTrigger(false);

		CBackground::Get_Instance()->Release();
		CBackground::Destroy_Instance();
		CObjMgr::Get_Instance()->Release();
		CObjMgr::Destroy_Instance();
		CUserInterface::Get_Instance()->Release();
		CUserInterface::Destroy_Instance();
		CStageMgr::Destroy_Instance();

		CBackground::Get_Instance()->Initailize();
		CStageMgr::Get_Instacne()->Initialize();
		CObjMgr::Get_Instance()->AddObject(PLAYER, CAbstractFactory<CPlayer>::Create());
		CObjMgr::Get_Instance()->AddObject(MONSTER, CAbstractFactory<CMonster>::Create());
		CUserInterface::Get_Instance()->Initailize();
		//메인게임에 들어가는 stagemgr,objmgr,uimgr를 삭제/재생성 시켜줘야함.
	}
}
