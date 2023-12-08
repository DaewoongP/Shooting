#pragma once
#include "Obj.h"
class CParticle :
	public CObj
{
public:
	CParticle();
	virtual ~CParticle();

	// Inherited via CObj
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual void CollisionEvent(CObj * _obj) override {};

public:
	void SetParticle_Option(float fCX, float fCY, float dir, float speed); //파티클의 지름x,지름y,이동방향,속도를 설정해주는 함수

private:
	float m_fDir;
};

