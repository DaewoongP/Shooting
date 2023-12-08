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

	//����� �������� ���� 
	static void Destroy_Instance()
	{
		Safe_Delete(m_pInstance);
	}


#if 0 //����
	//�Ѿ� Ÿ�� //�÷��̾ ����
	//���� �ڽ��� �̸�
	CBulletTypeBox m_cBulletTypeBox;

	//�Ѿ� �Ŀ� //�÷��̾ ����
	//���� �ڽ��� ����
	CBulletPowerBox m_CBulletPowerBox;

	//ü��ĭ 
	//�÷��̾��� ü�¸�ŭ ������ �� �ڽ�? ��Ʈ?
	CHpBox m_CHpBox;

	//��źĭ 
	//�÷��̾��� Ư�� ����ŭ ������ �� ��ź
	CBombBox m_CBombBox;

	//����ü��
	//������ ü���� ���� �ڽ� ���� ��׶���(��ü��) �ڽ� 1����
	//

	//���� 
	//�׸���...


	//������� ��Ʈ
	//���� ������

	//fps
	//fpsī��Ʈ �� ����

	//���� ���� ��
	//���� ����....
#pragma region ���Ҹ�...

	//���� �Ǵ� ������ ���Ͱ� �ı��ɶ� �̸� ���Ͱ� �ı� �ɶ� �÷��̾��� Ÿ���� nullptr�̾�� �ϱ� ������ 

#pragma endregion

#endif // 0 //����

};

