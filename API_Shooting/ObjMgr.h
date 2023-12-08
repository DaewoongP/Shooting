#pragma once
#include "Obj.h"

class CObjMgr
{
public:
	CObjMgr();
	~CObjMgr();
public:
	CObj*			Get_Player() { return m_ObjList[PLAYER].front(); }
	list<CObj*>*	Get_Monster();
	list<CObj*>*	Get_ObjList(OBJID eID) { return &m_ObjList[eID]; }
	CObj*			Get_Target(OBJID eID, CObj* pObj);


public:
	void	AddObject(OBJID eID, CObj* pObj);
	int		Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);

private:
	list<CObj*>		m_ObjList[OBJ_END];
	static		CObjMgr*		m_pInstance;

public:
	static CObjMgr*		Get_Instance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new CObjMgr;
		}

		return m_pInstance;
	}

	static void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
};

