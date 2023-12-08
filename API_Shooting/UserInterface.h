#pragma once

#include"Obj.h"
#include"BulletTypeBox.h"
#include "BulletPowerBox.h"
#include "HpBox.h"
#include "BombBox.h"

class CUserInterface
{
private:


private:
	list<CObj*> m_UIList[UI_END];
	static		CUserInterface*		m_pInstance;
public:
	void AddObject(UIID eID, CObj* pObj);

	void Initailize();

	void Update();

	void Render(HDC hdc);

	void Release();
	CUserInterface();
	~CUserInterface();
public:
	list<CObj*>*	Get_ObjList(UIID eID) { return &m_UIList[eID]; }

	static CUserInterface* Get_Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CUserInterface;
		}

		return m_pInstance;
	}

	//사용이 끝났으면 해제 
	static void Destroy_Instance()
	{
		Safe_Delete(m_pInstance);
	}


#if 0 //뻘것
	//총알 타입 //플레이어에 종속
	//작은 박스에 이름
	CBulletTypeBox m_cBulletTypeBox;

	//총알 파워 //플레이어에 종속
	//작은 박스에 숫자
	CBulletPowerBox m_CBulletPowerBox;

	//체력칸 
	//플레이어의 체력만큼 간격을 땐 박스? 하트?
	CHpBox m_CHpBox;

	//폭탄칸 
	//플레이어의 특정 값만큼 간격을 땐 폭탄
	CBombBox m_CBombBox;

	//보스체력
	//보스의 체력을 가진 박스 뒤의 백그라운드(총체력) 박스 1개더
	//

	//나무 
	//그리기...


	//점수출력 폰트
	//맨위 오른쪽

	//fps
	//fps카운트 및 띄우기

	//남은 몬스터 수
	//할지 말지....
#pragma region 뻘소리...

	//해제 되는 시점은 몬스터가 파괴될때 이며 몬스터가 파괴 될때 플레이어의 타겟이 nullptr이어야 하기 때문애 

#pragma endregion

#endif // 0 //뻘것

};

