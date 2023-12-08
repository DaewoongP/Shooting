#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	:m_fSpeed(0), m_eDir(DIR_END), m_bDead(OBJ_NOEVENT),
	m_eOBJID(OBJ_END), m_dwTime(GetTickCount()), m_pTarget(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
}


CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
