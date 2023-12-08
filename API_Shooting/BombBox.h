#pragma once
#include "Obj.h"
class CBombBox :
	public CObj
{
public:
	CBombBox();
	CBombBox(int _playerBomb);
	virtual ~CBombBox();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override;

	void Set_Count(int _Count) { m_iCount = _Count; }
	int Get_Count() { return m_iCount; }

private:
	int m_iCount;
};

