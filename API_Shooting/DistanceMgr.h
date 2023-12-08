#pragma once
#include "Obj.h"
class CDistanceMgr
{
public:
	CDistanceMgr();
	~CDistanceMgr();

	static void	FindNear(list<CObj*>& _Dest, list<CObj*>& _Src);
};

