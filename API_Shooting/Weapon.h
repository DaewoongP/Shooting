#pragma once
#include "Obj.h"
class CWeapon :
	public CObj
{
public:
	CWeapon();
	virtual~CWeapon();

	// Inherited via CObj
	virtual void Initialize() PURE;
	virtual int Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hdc) PURE;
	virtual void Release() PURE;
	virtual void CollisionEvent(CObj * _obj) PURE;

public:
	int Get_Dmg() { return m_iDmg; }

public:
	int m_iDmg;
};

