#pragma once
#include "Obj.h"
class CTree :
	public CObj
{
public:
	CTree();
	virtual ~CTree();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override;

	int m_iRand;
};

