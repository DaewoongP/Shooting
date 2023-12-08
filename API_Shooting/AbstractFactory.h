#pragma once
#include "Obj.h"
template<typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}
public:
	static CObj*	Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}

	static CObj*	Create(float _fx, float _fy)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fx, _fy);
		return pObj;
	}

	static CObj*	Create(const T& _Copy)
	{
		CObj* pObj = new T(_Copy);
		pObj->Initialize();
		return pObj;
	}
};

