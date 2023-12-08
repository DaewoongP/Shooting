#pragma once
#include "Obj.h"
class CBulletPowerBox :
	public CObj
{
public:
	CBulletPowerBox();
	virtual ~CBulletPowerBox();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override;

private:
	TCHAR szBuff[32]{};

	int m_iPower{};
};

