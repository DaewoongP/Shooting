#include "stdafx.h"
#include "Monster.h"
#include "AbstractFactory.h"
#include "MonsterPatternMgr.h"
#include "StageMgr.h"

CMonster::CMonster() : m_pNormalMonster(nullptr), m_pBulletMonster(nullptr), m_ePattern(PATTERN_NONE), m_bDelete(false), m_iCurrentStage(0)
{
	m_eOBJID = MONSTER;
}


CMonster::~CMonster()
{
	Release();
}

void CMonster::Initialize()
{
	if (!m_pNormalMonster)
	{
		m_pNormalMonster = CAbstractFactory<CNormalMonster>::Create();
	}
	if (!m_pBulletMonster)
	{
		m_pBulletMonster = CAbstractFactory<CBulletMonster>::Create();
	}
}

int CMonster::Update()
{
	if (CMonsterPatternMgr::Get_Count() == 4)
	{
		CMonsterPatternMgr::Reset_Count();
		CStageMgr::Get_Instacne()->Get_PartenList()[m_iCurrentStage].pop_front();
	}

	if (!(CStageMgr::Get_Instacne()->Get_PartenList()[m_iCurrentStage].empty()))
	{
		switch (CStageMgr::Get_Instacne()->Get_PartenList()[m_iCurrentStage].front())
		{
		case PATTERN_A:
			CMonsterPatternMgr::NPatternA(&m_MonsterList[MONSTER_NORMAL], static_cast<CNormalMonster*>(m_pNormalMonster), m_dwTime);
			break;
		case PATTERN_B:
			CMonsterPatternMgr::NPatternB(&m_MonsterList[MONSTER_NORMAL], static_cast<CNormalMonster*>(m_pNormalMonster), m_dwTime);
			break;
		case PATTERN_C:
			CMonsterPatternMgr::NPatternC(&m_MonsterList[MONSTER_BULLET], static_cast<CBulletMonster*>(m_pBulletMonster), m_dwTime);
			break;
		case PATTERN_D:
			CMonsterPatternMgr::NPatternD(&m_MonsterList[MONSTER_BULLET], static_cast<CBulletMonster*>(m_pBulletMonster), m_dwTime);
			break;
		case PATTERN_BOSS:
			CMonsterPatternMgr::NPatternBOSS(&m_MonsterList[MONSTER_BOSS]);
		case PATTERN_REST:
			CMonsterPatternMgr::NPatternRest((rand() % 3), m_dwTime);


		default:
			break;
		}
	}
	else if (CObjMgr::Get_Instance()->Get_Monster()[MONSTER_BOSS].empty() &&
		CObjMgr::Get_Instance()->Get_Monster()[MONSTER_NORMAL].empty() &&
		CObjMgr::Get_Instance()->Get_Monster()[MONSTER_BULLET].empty())
	{
		if (m_iCurrentStage == 8&& CObjMgr::Get_Instance()->Get_Monster()[MONSTER_BOSS].empty())
		{
			if(!CStageMgr::Get_Instacne()->Get_EndTrigger())
				CStageMgr::Get_Instacne()->Set_EndTrigger(true);
		}
		else
			m_iCurrentStage++;
	}

	for (size_t i = 0; i < MONSTER_END; ++i)
	{
		for (auto& iter = m_MonsterList[i].begin();
		iter != m_MonsterList[i].end();)
		{
			int iResult = (*iter)->Update();
			if (iResult == OBJ_DEAD)
			{
				(*CObjMgr::Get_Instance()->Get_ObjList(ITEM)).push_back(CAbstractFactory<CItem>::Create());
				CObjMgr::Get_Instance()->Get_ObjList(ITEM)->back()->Set_Pos((*iter)->Get_Info().fX, (*iter)->Get_Info().fY);
				Safe_Delete<CObj*>(*iter);
				iter = m_MonsterList[i].erase(iter);
			}
			else if (iResult == OBJ_DELETE)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_MonsterList[i].erase(iter);
			}
			else
				++iter;
		}
	}
	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	for (size_t i = 0; i < MONSTER_END; ++i)
	{
		for (auto& iter = m_MonsterList[i].begin();
		iter != m_MonsterList[i].end(); ++iter)
		{
			(*iter)->Late_Update();
		}
	}

}

void CMonster::Render(HDC hdc)
{
	for (size_t i = 0; i < MONSTER_END; ++i)
	{
		for (auto& iter = m_MonsterList[i].begin();
		iter != m_MonsterList[i].end(); ++iter)
		{
			(*iter)->Render(hdc);
		}
	}
}


void CMonster::Release()
{
	for (size_t i = 0; i < MONSTER_END; ++i)
	{
		for_each(m_MonsterList[i].begin(), m_MonsterList[i].end(), Safe_Delete<CObj*>);
		m_MonsterList[i].clear();
	}

	Safe_Delete<CObj*>(m_pNormalMonster);
	Safe_Delete<CObj*>(m_pBulletMonster);
}

void CMonster::CollisionEvent(CObj * _obj)
{
	if (static_cast<CBullet*>(_obj)->GetBulletID() != BULLET_TARGET)
		Set_Dead();
}
