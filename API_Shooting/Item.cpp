#include "stdafx.h"
#include "Item.h"

int CItem::m_RandCount = 0.0f;

CItem::CItem()
{
}


CItem::~CItem()
{
}

void CItem::Initialize()
{
	//��ġ �ʱ�ȭ(���� �� �޾ƿ;� ��)
	m_tInfo.fX = WINCX;
	m_tInfo.fY = WINCY;
	//������ �ʱ�ȭ(����)
	m_tInfo.fCX = 50.0f;
	m_tInfo.fCY = 50.0f;
	//���� �õ�ǥ �ʱ�ȭ
	//srand(unsigned(time(NULL)));
	//���� ���� �ʱ�ȭ
	m_fDirX = cosf((float)((rand() + m_RandCount) % 360)*RADIAN);
	m_fDirY = sinf((float)((rand() + m_RandCount) % 360)*RADIAN);
	//������ ���̵� ���� �ʱ�ȭ
	m_eItemID = (ITEMID)((rand() + m_RandCount) % ITEM_END);
	if (m_eItemID == ITEM_NONE1 || m_eItemID == ITEM_NONE2 || m_eItemID == ITEM_NONE3)
	{
		m_bDead = true;
	}
	//�Ѿ� ���̵� ���� �ʱ�ȭ
	m_eBulletID = (BULLETID)((rand() + m_RandCount) % BULLET_TARGET);

	//������ �̵� �ӵ� �ʱ�ȭ(����)
	m_fSpeed = 5.0f;
	//������ �ð� �ʱ�ȭ
	m_dwTime = GetTickCount();
	//������Ʈ ���̵� �ʱ�ȭ
	m_eOBJID = ITEM;

	//���� ���� ��
	m_RandCount += 155;

	switch (m_eItemID)
	{
	case ITEM_POWER:
		lstrcpy(szBuff, L"+");
		break;
	case ITEM_BOMB:
		lstrcpy(szBuff, L"B");
		break;
	case ITEM_HP:
		lstrcpy(szBuff, L"H");
		break;
	case ITEM_BULLET:
		switch (m_eBulletID)
		{
		case BULLET_NONE:
			break;
		case BULLET_PIERCE:
			lstrcpy(szBuff, L"PB");
			break;
		case BULLET_CHASE:
			lstrcpy(szBuff, L"CB");
			break;
		case BULLET_TARGET:
			break;
		case BULLET_END:
			break;
		default:
			break;
		}

		break;
	case ITEM_END:
		break;

	default:
		break;
	}
}

int CItem::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}


	//�̵� ������Ʈ ���� ��ǥ += ���� * �ӵ�
	m_tInfo.fX += m_fDirX*m_fSpeed;
	m_tInfo.fY += m_fDirY*m_fSpeed;

	CObj::Update_Rect();

	return OBJ_NOEVENT;
}

void CItem::Late_Update()
{
	//�ð� ���ȸ� ƨ���
	if (m_dwTime + 10000 >= GetTickCount())
	{
		//���� ���� ������ ȭ�� ���� ��� �������� ������ 
		if (m_tInfo.fCX*0.5f >= m_tInfo.fX)
		{
			m_tInfo.fX = m_tInfo.fCX*0.5f;
		}
		if (WINCX - m_tInfo.fCX*0.5f <= m_tInfo.fX)
		{
			m_tInfo.fX = WINCX - m_tInfo.fCX*0.5f;
		}
		if (m_tInfo.fCY*0.5f >= m_tInfo.fY)
		{
			m_tInfo.fY = m_tInfo.fCY*0.5f;
		}
		if (WINCY - m_tInfo.fCY*0.5f <= m_tInfo.fY)
		{
			m_tInfo.fY = WINCY - m_tInfo.fCY*0.5f;
		}


		//�¿� �浹�� ���� ��ȯ
		if (m_tInfo.fCX*0.5f >= m_tInfo.fX || WINCX - m_tInfo.fCX*0.5f <= m_tInfo.fX)
		{
			m_fDirX *= -1;
		}
		//���� �浹�� ���� ��ȯ
		if (m_tInfo.fCY*0.5f >= m_tInfo.fY || WINCY - m_tInfo.fCY*0.5f <= m_tInfo.fY)
		{
			m_fDirY *= -1;
		}
	}
	//�¿�� ������ ������ ����
	if (-m_tInfo.fCX*0.5f >= m_tInfo.fX || WINCX + m_tInfo.fCX*0.5f <= m_tInfo.fX)
	{
		Set_Dead();
	}
	//���Ϸ� ������ ������ ����
	if (-m_tInfo.fCY*0.5f >= m_tInfo.fY || WINCY + m_tInfo.fCY*0.5f <= m_tInfo.fY)
	{
		Set_Dead();
	}

}

void CItem::Render(HDC hdc)
{
	switch (m_eItemID)
	{
	case ITEM_POWER:
		Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		DrawText(hdc,
			szBuff,
			lstrlen(szBuff),
			&m_tRect,
			DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		break;
	case ITEM_HP:
	{
		//���� �ݿ�
		MoveToEx(hdc, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
		LineTo(hdc,
			(int)(m_tInfo.fX - m_tInfo.fCX*0.25f + cosf(-45 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(-45 * RADIAN)*m_tInfo.fCY*0.25f));
		LineTo(hdc,
			(int)(m_tInfo.fX - m_tInfo.fCX*0.25f + cosf(-90 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(-90 * RADIAN)*m_tInfo.fCY*0.25f));
		LineTo(hdc,
			(int)(m_tInfo.fX - m_tInfo.fCX*0.25f + cosf(-135 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(-135 * RADIAN)*m_tInfo.fCY*0.25f));
		LineTo(hdc,
			(int)(m_tInfo.fX - m_tInfo.fCX*0.25f + cosf(180 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(180 * RADIAN)*m_tInfo.fCY*0.25f));
		//���� �ݿ�
		MoveToEx(hdc, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
		LineTo(hdc,
			(int)(m_tInfo.fX + m_tInfo.fCX*0.25f + cosf(-135 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(-135 * RADIAN)*m_tInfo.fCY*0.25f));
		LineTo(hdc,
			(int)(m_tInfo.fX + m_tInfo.fCX*0.25f + cosf(-90 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(-90 * RADIAN)*m_tInfo.fCY*0.25f));
		LineTo(hdc,
			(int)(m_tInfo.fX + m_tInfo.fCX*0.25f + cosf(-45 * RADIAN)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(-45 * RADIAN)*m_tInfo.fCY*0.25f));
		LineTo(hdc,
			(int)(m_tInfo.fX + m_tInfo.fCX*0.25f + cosf(0)*m_tInfo.fCX*0.25f),
			(int)(m_tInfo.fY + sinf(0)*m_tInfo.fCY*0.25f));
		//�� �ݿ�
		LineTo(hdc,
			(int)(m_tInfo.fX + cosf(45 * RADIAN)*m_tInfo.fCX*0.5f),
			(int)(m_tInfo.fY + sinf(45 * RADIAN)*m_tInfo.fCY*0.5f));
		LineTo(hdc,
			(int)(m_tInfo.fX + cosf(90 * RADIAN)*m_tInfo.fCX*0.5f),
			(int)(m_tInfo.fY + sinf(90 * RADIAN)*m_tInfo.fCY*0.5f));
		LineTo(hdc,
			(int)(m_tInfo.fX + cosf(135 * RADIAN)*m_tInfo.fCX*0.5f),
			(int)(m_tInfo.fY + sinf(135 * RADIAN)*m_tInfo.fCY*0.5f));
		LineTo(hdc,
			(int)(m_tInfo.fX + cosf(180 * RADIAN)*m_tInfo.fCX*0.5f),
			(int)(m_tInfo.fY + sinf(180 * RADIAN)*m_tInfo.fCY*0.5f));
		DrawText(hdc,
			szBuff,
			lstrlen(szBuff),
			&m_tRect,
			DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	}
	break;
	case ITEM_BOMB:
		Ellipse(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		Ellipse(hdc, m_tRect.left + 5., m_tRect.top + 5, m_tRect.right - 5, m_tRect.bottom - 5);
		DrawText(hdc,
			szBuff,
			lstrlen(szBuff),
			&m_tRect,
			DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		break;
	case ITEM_BULLET:
		switch (m_eBulletID)
		{
		case BULLET_NONE:
			break;
		case BULLET_PIERCE:
			Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
			DrawText(hdc,
				szBuff,
				lstrlen(szBuff),
				&m_tRect,
				DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			break;
		case BULLET_CHASE:
			Rectangle(hdc, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
			DrawText(hdc,
				szBuff,
				lstrlen(szBuff),
				&m_tRect,
				DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			break;
		case BULLET_TARGET:

			break;
		case BULLET_END:
			break;
		default:
			break;
		}

		break;
	case ITEM_END:
		break;
	default:
		break;
	}

}

void CItem::Release()
{
}

void CItem::CollisionEvent(CObj*_Obj)
{
	Set_Dead();
}