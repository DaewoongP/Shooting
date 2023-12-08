#pragma once
#include "NormalMonster.h"
#include "BulletMonster.h"
#include "BossMonster.h"
class CMonsterPatternMgr
{
public:
	CMonsterPatternMgr();
	~CMonsterPatternMgr();
public:
	// �Ϲݸ�
	static void NPatternA(list<CObj*>* _monsterList, CNormalMonster* _monster, DWORD& _dwTime);
	static void NPatternB(list<CObj*>* _monsterList, CNormalMonster* _monster, DWORD& _dwTime);
	// �Ѿ˸�
	static void NPatternC(list<CObj*>* _monsterList, CBulletMonster* _monster, DWORD& _dwTime);
	static void NPatternD(list<CObj*>* _monsterList, CBulletMonster* _monster, DWORD& _dwTime);
	// ������
	static void NPatternE(CBossMonster& _monster, DWORD& _dwTime);
	static void NPatternF(CBossMonster& _monster, DWORD& _dwTime);
	static void NPatternG(CBossMonster& _monster, DWORD& _dwTime);
	static void NPatternBOSS(list<CObj*>* _monsterList);
	static void NPatternRest(int time, DWORD & _dwTime);
	static void Reset_Count() { iCount = 0; }
	static int Get_Count() { return iCount; }
private:
	static int iCount;
};