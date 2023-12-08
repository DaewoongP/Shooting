#pragma once
#include "Obj.h"
class CBulletTypeBox :
	public CObj
{
public:
	CBulletTypeBox();
	virtual ~CBulletTypeBox();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override;

private:
	TCHAR szBuff[32]{};

	BULLETID m_eBulletID{};
};

