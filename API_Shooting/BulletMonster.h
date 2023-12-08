#pragma once
#include "Monster.h"
#include "Bullet.h"
class CBulletMonster : public CMonster
{
public:
	CBulletMonster();
	virtual ~CBulletMonster();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj* _obj) override;
public:
	void FireToTarget();
private:
	BULLETID  m_eBulletID;
	list<CObj*>* m_bulletList;
};

