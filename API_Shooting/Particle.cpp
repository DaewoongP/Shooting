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

	//��ǥ�������� �̵���
	m_tInfo.fX += cos(m_fDir)*m_fSpeed;
	m_tInfo.fY += sin(m_fDir)*m_fSpeed;

	//ũ�⸦ ���� ����
	m_tInfo.fCX -= 0.1f;
	m_tInfo.fCY -= 0.1f;

	//ũ�Ⱑ n ���ϸ� ����
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
