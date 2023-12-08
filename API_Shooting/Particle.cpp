#include "stdafx.h"
#include "Particle.h"
#include <time.h>


CParticle::CParticle() :m_fDir(0)
{
}


CParticle::~CParticle()
{
	Release();
}

void CParticle::Initialize()
{
	m_eOBJID = PARTICLE;
}

int CParticle::Update()
{
	if (m_bDead)
		return 1;

	//목표방향으로 이동함
	m_tInfo.fX += cos(m_fDir)*m_fSpeed;
	m_tInfo.fY += sin(m_fDir)*m_fSpeed;

	//크기를 점점 줄임
	m_tInfo.fCX -= 0.1f;
	m_tInfo.fCY -= 0.1f;

	//크기가 n 이하면 삭제
	if (m_tInfo.fCX <= 0 || m_tInfo.fCY <= 0)
		Set_Dead();

	__super::Update_Rect();
	return 0;
}

void CParticle::Late_Update()
{
}

void CParticle::Render(HDC hdc)
{
	Rectangle(hdc, m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CParticle::Release()
{
}

void CParticle::SetParticle_Option(float fCX, float fCY, float dir, float speed)
{
	m_tInfo.fCX = fCX;
	m_tInfo.fCY = fCY;
	m_fDir = dir;
	m_fSpeed = speed;
}
