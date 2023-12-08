#pragma once
#include "Define.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();
public:
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hdc) PURE;
	virtual void Release() PURE;
	virtual void CollisionEvent(CObj* _obj) PURE;

	INFO Get_Info(void) { return m_tInfo; }
	RECT Get_Rect(void) { return m_tRect; }
	OBJID Get_ObjID(void) { return m_eOBJID; }
	void Set_ObjID(OBJID _objid) { m_eOBJID = _objid; }
	bool Get_Dead() { return m_bDead; }
	void Update_Rect();
	void Set_Dead() { m_bDead = true; }
	void Set_Pos(float _fX, float _fY)
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	CObj* Get_Target() { return m_pTarget; }
	void Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	void Set_Info(INFO _info) { m_tInfo = _info; }
	void Set_Speed(float _speed) { m_fSpeed = _speed; }
	float Get_Speed(void) { return m_fSpeed; }
protected:
	OBJID   m_eOBJID;
	INFO	m_tInfo;
	RECT	m_tRect;
	float	m_fSpeed;
	DIRECTION m_eDir;
	bool m_bDead;
	DWORD m_dwTime;

	CObj*		m_pTarget;
};

