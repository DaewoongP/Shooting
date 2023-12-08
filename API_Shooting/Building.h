#pragma once
#include "Obj.h"
class CBuilding :
	public CObj
{
public:
	CBuilding();
	virtual ~CBuilding();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override;

	void Update_Rect_Bottom_Pivot();
};

