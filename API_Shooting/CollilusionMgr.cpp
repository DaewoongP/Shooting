#include "stdafx.h"
#include "CollilusionMgr.h"


CCollilusionMgr::CCollilusionMgr()
{
}


CCollilusionMgr::~CCollilusionMgr()
{
}

void CCollilusionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT		rc{};
	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, (&Dest->Get_Rect()), (&Src->Get_Rect())))
			{
				Dest->CollisionEvent(Src);
				Src->CollisionEvent(Dest);
			}
		}
	}
}

void CCollilusionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dest, Src))
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

bool CCollilusionMgr::Check_Sphere(CObj * pDest, CObj * pSrc)
{
	float		fWidth = pDest->Get_Info().fX - pSrc->Get_Info().fX;
	float		fHeight = pDest->Get_Info().fY - pSrc->Get_Info().fY;

	float		fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);
	float		fRadius = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;

	return fRadius >= fDistance;
}
