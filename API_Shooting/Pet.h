#pragma once
#include "Obj.h"
#include "Player.h"
#include "Bullet.h"
class CPet : public CObj
{
public:
	CPet();
	virtual ~CPet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override;

	void MissileShoot();

private:
	BULLETID		 m_eBullitID;
	list<CObj*>*	 m_bulletList;

	float			m_fAngle;
};

