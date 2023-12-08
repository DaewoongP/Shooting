#pragma once
#include "Obj.h"
class CFallingStar :
	public CObj
{
private:
	float m_fDirX{ cosf(150 * RADIAN) };
	float m_fDirY{ sinf(150 * RADIAN) };
	int	  m_iRotation{ 0 };
public:
	CFallingStar();
	virtual ~CFallingStar();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override;

};

