#include "stdafx.h"
#include "ObjMgr.h"
#include"DistanceMgr.h"
#include "Monster.h"
#include "CollilusionMgr.h"
#include "Monster.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
{
}


CObjMgr::~CObjMgr()
{
}

list<CObj*>* CObjMgr::Get_Monster()
{
	return static_cast<CMonster*>(m_ObjList[MONSTER].front())->Get_Monster();
}


CObj * CObjMgr::Get_Target(OBJID eID, CObj * pObj)
{
	return nullptr;
}

void CObjMgr::AddObject(OBJID eID, CObj * pObj)
{
	if (OBJ_END <= eID || nullptr == pObj)
		return;

	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
		iter != m_ObjList[i].end();)
		{
			int iResult = (*iter)->Update();

			if (iResult == OBJ_DEAD)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	for (size_t i = 0; i < MONSTER_END; ++i)
	{
		CDistanceMgr::FindNear(m_ObjList[BULLET], Get_Monster()[i]);
	}
	return 0;
}

void CObjMgr::Late_Update(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
		iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->Late_Update();
		}
	}

	CCollilusionMgr::Collision_Rect(m_ObjList[ITEM], m_ObjList[PLAYER]);
	CCollilusionMgr::Collision_Rect(m_ObjList[ENEMYBULLET], m_ObjList[PLAYER]);
	CCollilusionMgr::Collision_Rect(m_ObjList[SHIELD], m_ObjList[ENEMYBULLET]);
	CCollilusionMgr::Collision_Rect(m_ObjList[BOMB], m_ObjList[ENEMYBULLET]);

	// 몬스터 리스트 순회하면서 충돌처리
	for (size_t i = 0; i < MONSTER_END; ++i)
	{
		CCollilusionMgr::Collision_Rect(m_ObjList[BOMB], Get_Monster()[i]);
		CCollilusionMgr::Collision_Rect(m_ObjList[SHIELD], Get_Monster()[i]);
		CCollilusionMgr::Collision_Rect(m_ObjList[PLAYER], Get_Monster()[i]);
		CCollilusionMgr::Collision_Rect(m_ObjList[BULLET], Get_Monster()[i]);
	}

}

void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_ObjList[i].begin();
		iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->Render(hDC);
		}
	}
}

void CObjMgr::Release(void)
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), Safe_Delete<CObj*>);
		m_ObjList[i].clear();
	}
}
