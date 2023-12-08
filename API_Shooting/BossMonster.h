#pragma once
#include "Monster.h"

class CBullet;

class CBossMonster : public CMonster
{
public:
	CBossMonster();
	virtual ~CBossMonster();
public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj* _obj) override;

	void Set_Damage(int _Damage) { m_iHp -= _Damage; }
	void Set_AktInfo(INFO _info) { m_AtkInfo = _info; }
	void Set_BulletList(list<CObj*>* _list) { m_bulletList = _list; }
	void Set_BulletAngle(float _Angle) { m_BulletAngle = _Angle; }

public:
	void FireToTarget_Fast();
	void FireToTarget();
	void Set_BossParten(int _Num) { parten_num = _Num; }

private:
	void BossParten();

private:
	int parten_num;
	float parten_E_time;
	float parten_F_time;
	float parten_G_time;
	DWORD parten_time;

	float      m_BulletAngle;

	BULLETID  m_eBulletID;
	list<CObj*>* m_bulletList;

	INFO      m_AtkInfo;
};