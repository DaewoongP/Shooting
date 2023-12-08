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
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj* _obj) override;
	// 포인터형식으로 넘겨줌.
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

	// 메인의 아이템 리스트 주소를 가져옴
	list<CObj*>*   m_pItem;

	//추가
public:
	int Get_CurrentStage() { return m_iCurrentStage; }

};