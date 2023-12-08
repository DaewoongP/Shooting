#pragma once
#include "Define.h"
#include "Player.h"
#include "Monster.h"
#include "Pet.h"
#include "Item.h"
#include "UserInterface.h"
class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();
	void Reset();

private:
	HWND			m_hWnd;
	HDC				m_hDC;

	list<CObj*>		m_ObjList[OBJ_END];
};

