#include "stdafx.h"
#include "MonsterPatternMgr.h"
#include "AbstractFactory.h"

int CMonsterPatternMgr::iCount = 0;

CMonsterPatternMgr::CMonsterPatternMgr()
{
}


CMonsterPatternMgr::~CMonsterPatternMgr()
{
}

void CMonsterPatternMgr::NPatternA(list<CObj*>* _monsterList, CNormalMonster* _monster, DWORD& _dwTime)
{
	if (_dwTime + 300 < GetTickCount() && iCount < 4)
	{
		_monster->Set_Pattern(PATTERN_A);
		_monster->Set_Info({ 850.f ,-50.f,  30.f , 30.f });
		_monster->Set_Speed(3.f);
		_monsterList->push_back(CAbstractFactory<CNormalMonster>::Create(*_monster));
		_monster->Set_Info({ 850.f ,650.f,  30.f , 30.f });
		_monster->Set_Speed(-3.f);
		_monsterList->push_back(CAbstractFactory<CNormalMonster>::Create(*_monster));
		_dwTime = GetTickCount();
		++iCount;
	}

}

void CMonsterPatternMgr::NPatternB(list<CObj*>* _monsterList, CNormalMonster * _monster, DWORD & _dwTime)
{
	if (_dwTime + 300 < GetTickCount() && iCount < 4)
	{
		_monster->Set_Pattern(PATTERN_B);
		_monster->Set_Speed(1.f);
		_monster->Set_Angle(1.f);
		_monster->Set_Info({ 450.f ,-50.f,  30.f , 30.f });
		_monsterList->push_back(CAbstractFactory<CNormalMonster>::Create(*_monster));
		_monster->Set_Speed(2.f);
		_monster->Set_Info({ 450.f ,650.f,  30.f , 30.f });
		_monsterList->push_back(CAbstractFactory<CNormalMonster>::Create(*_monster));
		_dwTime = GetTickCount();
		++iCount;
	}

}

void CMonsterPatternMgr::NPatternC(list<CObj*>* _monsterList, CBulletMonster * _monster, DWORD & _dwTime)
{
	_monster->Set_Pattern(PATTERN_C);
	if(iCount < 4)
	{
		_monster->Set_Info({ 850.f ,450.f - (iCount * 100.f),  30.f , 30.f });
		_monster->Set_Speed(2.f);
		_monsterList->push_back(CAbstractFactory<CBulletMonster>::Create(*_monster));
		++iCount;
	}
}

void CMonsterPatternMgr::NPatternD(list<CObj*>* _monsterList, CBulletMonster * _monster, DWORD & _dwTime)
{
	if (_dwTime + 300 < GetTickCount() && iCount < 4)
	{
		_monster->Set_Pattern(PATTERN_D);
		_monster->Set_Speed(3.f);
		_monster->Set_Info({ 850.f ,100.f,  30.f , 30.f });
		_monsterList->push_back(CAbstractFactory<CBulletMonster>::Create(*_monster));
		_monster->Set_Info({ 850.f ,500.f,  30.f , 30.f });
		_monsterList->push_back(CAbstractFactory<CBulletMonster>::Create(*_monster));
		_dwTime = GetTickCount();
		++iCount;
	}
}
// °¡À§ ÃÑ
void CMonsterPatternMgr::NPatternE(CBossMonster& _monster, DWORD & _dwTime)
{
	_monster.Set_Pattern(PATTERN_E);
	_monster.Set_AktInfo({ _monster.Get_Info().fX - _monster.Get_Info().fCX * 0.75f, _monster.Get_Info().fY - _monster.Get_Info().fCY * 0.375f, 0, 0 });
	_monster.Set_BulletList(CObjMgr::Get_Instance()->Get_ObjList(ENEMYBULLET));
}
// ÁÖ¸Ôµ¹Áø
void CMonsterPatternMgr::NPatternF(CBossMonster& _monster, DWORD & _dwTime)
{
	_monster.Set_Pattern(PATTERN_F);
	
	if (0 <= _monster.Get_Speed())
	{
		if (_monster.Get_Info().fX <= 200)
		{
			_monster.Set_Speed(-5.f);
		}
		else
			_monster.Set_Speed(20.f);
	}
	else
	{
		if (_monster.Get_Info().fX >= 600.f)
		{
			_monster.Set_Pattern(PATTERN_NONE);
			_monster.Set_Speed(0.f);
			_monster.Set_Info({ 600.f, _monster.Get_Info().fY, _monster.Get_Info().fCX, _monster.Get_Info().fCY});

			if (_dwTime + 500 < GetTickCount())
			{
				_monster.Set_BossParten(rand() % 3);
				_dwTime = GetTickCount();
			}
		}
	}
	_monster.Set_Angle(-90.f);
}
// º¸ Èð»Ñ¸®±â
void CMonsterPatternMgr::NPatternG(CBossMonster& _monster, DWORD & _dwTime)
{
	_monster.Set_Pattern(PATTERN_G);
	_monster.Set_BulletList(CObjMgr::Get_Instance()->Get_ObjList(ENEMYBULLET));
	_monster.Set_AktInfo({ (float)_monster.Get_Info().fX, _monster.Get_Info().fY, 0, 0 });
	_monster.Set_Speed(3.f);
}

void CMonsterPatternMgr::NPatternBOSS(list<CObj*>* _monsterList)
{
	if (iCount < 4)
	{
		_monsterList[MONSTER_BOSS].push_back(CAbstractFactory<CBossMonster>::Create());
		iCount = 4;
	}

}

void CMonsterPatternMgr::NPatternRest(int time, DWORD & _dwTime)
{
	if (_dwTime + time * 1000 < GetTickCount())
	{
		iCount = 4;
	}
}