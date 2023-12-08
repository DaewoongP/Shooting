#pragma once
#include "Define.h"
class CStageMgr
{
private:
	CStageMgr();
	~CStageMgr();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();

public:
	void	MakerPartenList();
	list<PATTERNID>*	Get_PartenList() { return m_partenList; }
	bool Get_isGameEnd() { return m_bIsGameEnd; }
	void Set_isGameEnd(bool isEnd) { m_bIsGameEnd = isEnd; }
	bool Get_EndTrigger() { return m_bEndTrigger; }
	void Set_EndTrigger(bool isEnd) { m_bEndTrigger = isEnd; dwTime = GetTickCount(); }
	void Set_Score(int score) { m_iScore += score; }
	int Get_Score() { return m_iScore; }
	
	void KeyInput();

public:
	static CStageMgr* Get_Instacne()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new CStageMgr;
		}
		return m_pInstance;
	}
	static void	Destroy_Instance(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	DWORD  dwTime;
	static CStageMgr* m_pInstance;
	list<PATTERNID> m_partenList[9];
	bool m_bIsGameEnd;
	bool m_bEndTrigger;
	int m_iScore;

};

