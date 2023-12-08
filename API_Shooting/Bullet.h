#pragma once
#include "Obj.h"
#include "Weapon.h"
class CBullet :
	public CWeapon
{
public:
	CBullet();
	~CBullet();

	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override;

public:
	void SetBulletID(BULLETID _bulletID) { m_eBulletID = _bulletID; }
	BULLETID GetBulletID() { return m_eBulletID; }

	void Set_Dir(float _x, float _y) { m_fPX = _x; m_fPY = _y; }
	void Set_Angle(float _Angle) { m_fAngle = _Angle; }

	void MBullet();
	void BBullet();
private:
	float m_fDir;
	float m_fRotSpeed;
	BULLETID   m_eBulletID;

	float m_fPX;
	float m_fPY;


	float m_fAngle;
};
