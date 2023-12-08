#pragma once
#include "Obj.h"
class CEndScreen :
	public CObj
{
public:
	CEndScreen();
	virtual ~CEndScreen();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override;
};

