#pragma once
#include "Monster.h"
#include "Particle.h"
class CNormalMonster : public CMonster
{
public:
	CNormalMonster();
	virtual ~CNormalMonster();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj* _obj) override;

	void Set_Angle(float _Angle) {m_fAngle = _Angle;}

private:
	float m_fAngle;
};

