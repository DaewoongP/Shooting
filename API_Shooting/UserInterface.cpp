#include "stdafx.h"
#include "UserInterface.h"
#include "BombBox.h"
#include "HpBox.h"
#include "AbstractFactory.h"
#include "BossHpBar.h"
#include "BulletPowerBox.h"
#include "BulletTypeBox.h"
#include "Tree.h"
#include "ScoreBox.h"
#include "EndScreen.h"

CUserInterface* CUserInterface::m_pInstance = nullptr;

CUserInterface::CUserInterface()
{
}


CUserInterface::~CUserInterface()
{
}

void CUserInterface::Initailize()
{
	for (size_t i = 0; i < 3; i++)
	{
		AddObject(UI_BOMBBOX, CAbstractFactory<CBombBox>::Create());
		AddObject(UI_HPBOX, CAbstractFactory<CHpBox>::Create());
	}
	AddObject(UI_ENDSCREEN, CAbstractFactory<CEndScreen>::Create());

	AddObject(UI_BOSSHPBAR, CAbstractFactory<CBossHpBar>::Create());

	AddObject(UI_BULLETPOWERBOX, CAbstractFactory<CBulletPowerBox>::Create());
	AddObject(UI_BULLETTYPEBOX, CAbstractFactory<CBulletTypeBox>::Create());

	//갯수 생각해보고 넣어보기

	AddObject(UI_SCOREBOX, CAbstractFactory<CScoreBox>::Create());




#pragma region 회복, 폭탄
	int iCount = 1;

	//회복, 폭탄 거리 두기 위한 카운트 값
	for (auto & iter : m_UIList[UI_BOMBBOX])
	{
		static_cast<CBombBox*>(iter)->Set_Count(iCount);
		static_cast<CBombBox*>(iter)->Initialize();
		iCount++;
	}

	iCount = 1;

	for (auto & iter : m_UIList[UI_HPBOX])
	{
		static_cast<CHpBox*>(iter)->Set_Count(iCount);
		static_cast<CHpBox*>(iter)->Initialize();
		iCount++;
	}
#pragma endregion

}

void CUserInterface::AddObject(UIID eID, CObj * pObj)
{
	if (UI_END <= eID || nullptr == pObj)
		return;

	m_UIList[eID].push_back(pObj);
}

void CUserInterface::Update()
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for (auto& iter = m_UIList[i].begin();
		iter != m_UIList[i].end();)
		{
			int iResult = (*iter)->Update();

			if (iResult == OBJ_DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_UIList[i].erase(iter);
			}
			else
				++iter;
		}
	}
}

void CUserInterface::Render(HDC hdc)
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for (auto& iter = m_UIList[i].begin();
		iter != m_UIList[i].end(); ++iter)
		{
			(*iter)->Render(hdc);
		}
	}
}

void CUserInterface::Release()
{
	for (size_t i = 0; i < UI_END; i++)
	{
		for_each(m_UIList[i].begin(), m_UIList[i].end(), Safe_Delete<CObj*>);
		m_UIList[i].clear();
	}
}
