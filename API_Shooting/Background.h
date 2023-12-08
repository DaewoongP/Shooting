#pragma once
#include "Obj.h"
#include "Define.h"
class CBackground
{
public:
	CBackground();
	~CBackground();
private:
	list<CObj*> m_BGList[BG_END]{};
	static CBackground* m_pInstance;
	DWORD dwTime{GetTickCount()};
public:
	static CBackground* Get_Instance()
	{
		if (m_pInstance==nullptr)
		{
			m_pInstance = new CBackground;
		}
		return m_pInstance;
	}

	static void Destroy_Instance()
	{
		Safe_Delete(m_pInstance);
	}

	void AddObject(BGID eID, CObj* pObj)
	{
		if (eID >= BG_END || pObj == nullptr)
		{
			return;
		}
		m_BGList[eID].push_back(pObj);
	}

	void Initailize();
	void Update();
	void Late_Update();
	void Render(HDC hdc);
	void Release();
};

