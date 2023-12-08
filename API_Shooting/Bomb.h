#pragma once
#include "Weapon.h"

enum BombState
{
	Back, Front, Splash, End
};

class CBomb :
	public CWeapon
{
public:
	CBomb();
	virtual ~CBomb();

	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override;

private:
	float m_fBackMove_timer;
	float m_fFrontMove_timer;
	float m_fSplash_timer;

	BombState m_eState;
};

