#include "stdafx.h"
#include "DistanceMgr.h"


CDistanceMgr::CDistanceMgr()
{
}


CDistanceMgr::~CDistanceMgr()
{
}


//dest->setTarget(Src);
void	 CDistanceMgr::FindNear(list<CObj*>& _Dest, list<CObj*>& _Src)
{

	float distance = -1;
	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			float		fWidth = Dest->Get_Info().fX - Src->Get_Info().fX;
			float		fHeight = Dest->Get_Info().fY - Src->Get_Info().fY;

			float		fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);
			//���ο� ģ���� �Ÿ��� ���� ���� ũ��
			if (distance < fDistance&&!Dest->Get_Target())
			{
				distance = fDistance;
				Dest->Set_Target(Src);
			}
		}
	}
}