#pragma once
#include "Weapon.h"
class CShield :
	public CWeapon
{
public:
	CShield();
	virtual ~CShield();

private:
	int m_iGardCount;
	float m_fAngle;
	float m_fDistance;
	POINT m_ePos;

	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override;
};

