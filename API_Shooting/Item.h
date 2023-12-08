#pragma once
#include "Obj.h"

class CItem :
	public CObj
{
public:
	CItem();
	virtual ~CItem();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	ITEMID Get_ITEMID() { return m_eItemID; }
	BULLETID Get_BULLETID() { return m_eBulletID; }


protected:
	float m_fDirX;
	float m_fDirY;

	ITEMID m_eItemID;
	BULLETID m_eBulletID;


	// CObj��(��) ���� ��ӵ�
	virtual void CollisionEvent(CObj* _Obj) override;


	//�߰�
	static int m_RandCount;
	TCHAR szBuff[32]{};
};

