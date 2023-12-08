#pragma once
#include "Obj.h"
class CScoreBox :
	public CObj
{
public:
	CScoreBox();
	virtual ~CScoreBox();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override;
};

