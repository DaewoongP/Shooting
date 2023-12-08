#pragma once
#include "Obj.h"
class CCollilusionMgr
{
public:
	CCollilusionMgr();
	~CCollilusionMgr();
public:
	static void Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src);
	static void Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src);
	static bool Check_Sphere(CObj* pDest, CObj* pSrc);

};