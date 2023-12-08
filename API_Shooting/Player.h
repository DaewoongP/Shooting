#pragma once
#include "Obj.h"

class CPlayer :
	public CObj
{
public:
	CPlayer();
	~CPlayer();

	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj* _obj) override;

private:
	void keyInput();
	void MissileShoot();
	void OnCollision_Item(CObj* _obj);
	void OnCollision_Enemy(CObj* _obj);

public:
	BULLETID GetBullitID() { return m_eBullitID; }
	void SetBulletList(list<CObj*>* _bulletlist) { m_bulletList = _bulletlist; }
	int GetBomb() { return m_iBomb; }
	int GetPower() { return m_iPower; }
	int GetHp() { return m_iHp; }

private:
	list<CObj*>* m_bulletList; //매니저에서 받아올 불릿 리스트

	BULLETID m_eBullitID; //보여줄 총알의 타입 사망시 초기화 해줄거
	int m_iBomb; // 보여줄 강공의 수
	int m_iPower; // 보여줄 공격력
	int m_iHp; // 보여줄 HP

	PLAYERSTATE m_ePlayerState;

	DWORD m_dwTime_bomb; //폭탄쿨
	DWORD m_dwTime_invi;//무적쿨
};