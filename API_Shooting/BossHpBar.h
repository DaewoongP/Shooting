#pragma once
#include "Obj.h"
class CBossHpBar :
	public CObj
{
public:
	CBossHpBar();
	virtual ~CBossHpBar();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override;

	void Update_Rect_Left_Pivot();

private:
	INFO m_tBackgroundInfo;
	RECT m_rcBackground;
	//CObj*		m_pBoss;
	int m_iMaxHp;

};

