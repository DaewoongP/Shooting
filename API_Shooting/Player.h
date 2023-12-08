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
	list<CObj*>* m_bulletList; //�Ŵ������� �޾ƿ� �Ҹ� ����Ʈ

	BULLETID m_eBullitID; //������ �Ѿ��� Ÿ�� ����� �ʱ�ȭ ���ٰ�
	int m_iBomb; // ������ ������ ��
	int m_iPower; // ������ ���ݷ�
	int m_iHp; // ������ HP

	PLAYERSTATE m_ePlayerState;

	DWORD m_dwTime_bomb; //��ź��
	DWORD m_dwTime_invi;//������
};