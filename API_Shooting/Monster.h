#pragma once
#include "Obj.h"
#include "Item.h"
#include "ObjMgr.h"
#include "Particle.h"

class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();
public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj* _obj) override;
	// �������������� �Ѱ���.
	list<CObj*>* Get_Monster() { return m_MonsterList; }

	void Set_Pattern(PATTERNID _pattern) { m_ePattern = _pattern; }
	void SetItemList(list<CObj*>* _itemlist) { m_pItem = _itemlist; }

	int Get_Hp() { return m_iHp; }
	int Get_MaxHp() { return m_iMaxHp; }

	void Set_Angle(float _Angle) { m_fAngle = _Angle; }

protected:
	PATTERNID      m_ePattern;
	bool         m_bDelete;
	int            m_iHp;
	int            m_iMaxHp;
	float         m_fAngle;
private:
	list<CObj*>      m_MonsterList[MONSTER_END];
	CObj*         m_pNormalMonster;
	CObj*         m_pBulletMonster;

	int m_iCurrentStage;

	// ������ ������ ����Ʈ �ּҸ� ������
	list<CObj*>*   m_pItem;

	//�߰�
public:
	int Get_CurrentStage() { return m_iCurrentStage; }

};